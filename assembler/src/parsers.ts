import CommandParseError from "./errors/commandParseError";
import LineParseError from "./errors/lineParseError";
import opcodes, { AddressingModes } from "./opcodes";

// Matches: [(Label):][ (Mnemonic [Operand1[, Operand2]])][ ;(Comment)]
const matchLine =  /^\s*(?:([A-Z]\w+):\s+)?(?:([A-Z]{3,5}(?:\s+#?\$?\w*(?:,\s*#?\$?\w*){0,2})?)?(?:\s*;(.*))?(?:))?$/i;

interface IParsedLine {
    lineNumber: number;
    label: string;
    command: string;
    comment: string;
}

interface IParsedCommand {
    mnemonic: string;
    opCode: number;
    operands: Array<string|number>;
    usesLabel: boolean;
}

export function parseLines(source: string): IParsedLine[] {
    const lines = source.split('\n');

    return lines.map((line, index) => {
        if (!line.trim()) {
            return null;
        }

        const match = matchLine.exec(line.trim());

        if (!match) {
            // line doesn't match pattern
            throw new LineParseError(`'${line}' is invalid`, index);
        }

        const label = match[1] ? match[1].trim() : null;
        const command = match[2] ? match[2].trim() : null;
        const comment = match[3] ? match[3].trim() : null;

        if (label || command) {
            return {
                command,
                comment,
                label,
                lineNumber: index
            };
        }

        return null;
    }).filter((line) => line !== null);
}


function parseImmediateVal(operand: string): number {
    let value: number = null;

    if (operand.charAt(0) === '$') {
        // hex
        if (operand.length !== 3 && operand.length !== 5) {
            throw new Error('Wrong number of digits for hex number');
        }
        value = parseInt(operand.slice(1), 16);
    } else if (operand.charAt(0) === '%') {
        const trimmed = operand.replace(/\s/, '');
        // binary
        if (trimmed.length !== 9 && trimmed.length !== 17) {
            throw new Error('Wrong number of digits for binary number');
        }
        value = parseInt(trimmed.slice(0), 2);
    } else {
        // decimal
        value = parseInt(operand, 10);
    }


    return value;
}


function parseBitVal(operand: string, lineNumber: number) {
    let bitNumber: number = null;

    bitNumber = parseInt(operand, 10);

    if (bitNumber.toString() !== operand) {
        throw new CommandParseError(`Expected a bit number, found '${bitNumber}' instead`, lineNumber);
    } else if (bitNumber < 0 || bitNumber > 7) {
        throw new CommandParseError(`Bit number must be in the range 0-7, ${bitNumber} was provided`, lineNumber);
    }

    return bitNumber;
}


function parseRelativeVal(rel: string, lineNumber: number) {
    interface IparsedRel {
        offset: string|number;
        usesLabel: boolean;
    }

    const parsed: IparsedRel = {
        offset: rel,
        usesLabel: true
    };

    if (rel.startsWith("#")) {
        // immediate value
        parsed.offset = parseImmediateVal(rel.slice(1));
        parsed.usesLabel = false;

        if (parsed.offset < -127 || parsed.offset > 255) {
            throw new CommandParseError("Offset is too big", lineNumber);
        }
    }

    return parsed;
}

export function parseCommand(command: string, lineNumber: number): IParsedCommand {
    let mnemonic = command.toUpperCase();
    let addressingMode: AddressingModes;
    let operands: string[] = [];
    let relativeOffset: number|string;
    let indexed = false;
    let stackPointer = false;
    let bitNumber: number = null;


    if (command.indexOf(' ') > 0) {
        const index = command.indexOf(' ');
        mnemonic = command.slice(0, index).toUpperCase();
        operands = command.slice(index)
            .split(',')
            .map((operand) => operand ? operand.trim().toUpperCase() : '')
            .filter((operand) => operand.length > 0);
    }

    const operation = opcodes[mnemonic];

    if (!operation) {
        throw new CommandParseError(`Invalid mnemonic: '${mnemonic}'`, lineNumber);
    }


    if (!operation.opCodes) {
        throw new CommandParseError(`Unsupported mnemonic: '${mnemonic}'`, lineNumber);
    }

    const parsedCommand: IParsedCommand = {
        mnemonic,
        opCode: null,
        operands: [],
        usesLabel: false
    };

    if (operation.rel) {
        // relative operands are always the last operand
        const rel = parseRelativeVal(operands.pop(), lineNumber);
        relativeOffset = rel.offset;
        parsedCommand.usesLabel = rel.usesLabel;
    }

    if (operation.bit) {
        bitNumber = parseBitVal(operands[0], lineNumber);
        operands.splice(0, 0);
    }



    if (operands.length >= 2) {
        if (operands[1] === 'X') {
            indexed = true;
            operands.splice(1, 1);
        } else if (operands[1] === 'SP') {
            stackPointer = true;
            operands.splice(1, 1);
        }
    } else if (operands.length === 1) {
        if (operands[0].startsWith('#')) {
            // immediate
            const value = parseImmediateVal(operands[0].slice(1));

            if (value < -127 || value > 255) {
                throw new Error();
            }

            addressingMode = AddressingModes.Immediate;
            parsedCommand.operands.push(value);
        } else if (!operands[0] && indexed) {
            addressingMode = AddressingModes.Indexed;
        }
    } else {
        addressingMode = AddressingModes.Inherent;
    }

    if (operation.opCodes[addressingMode] === undefined) {
        const msg = `Operation '${mnemonic}' does not support addressing mode of '${addressingMode}'`;
        throw new CommandParseError(msg, lineNumber);
    }

    parsedCommand.opCode = operation.opCodes[addressingMode];

    return parsedCommand;
}
