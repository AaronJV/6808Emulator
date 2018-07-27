import LineParseError from "./errors/lineParseError";
import opcodes, { AddressingModes } from "./opcodes";
import CommandParseError from "./errors/commandParseError";

// Matches: [(Label):][ (Mnemonic [Operand1[, Operand2]])][ ;(Comment)]
const matchLine =  /^\s*(?:([A-Z]\w+):\s+)?(?:([A-Z]{3,5}(?:\s+#?\$?\w*(?:,\s*#?\$?\w*){0,2})?)?(?:\s*;(.*))?(?:))?$/i;

interface IParsedLine {
    lineNumber: number;
    label: string;
    command: string;
    comment: string;
};

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
                lineNumber: index,
                label,
                command,
                comment
            };
        }

        return null;
    }).filter((line) => line !== null);
}


function parseImmediateVal(operand: string): number {
    let value: number = null;

    if (operand.charAt(0) == '$') {
        // hex
        if (operand.length != 3 && operand.length != 5) {
            throw new Error('Wrong number of digits for hex number')
        }
        value = parseInt(operand.slice(1), 16);
    } else if (operand.charAt(0) == '%') {
        operand = operand.replace(/\s/, '');
        // binary
        if (operand.length != 9 && operand.length != 17) {
            throw new Error('Wrong number of digits for binary number')
        }
        value = parseInt(operand.slice(0), 2);
    } else {
        // decimal
        value = parseInt(operand);
    }


    return value;
}

export function parseCommand(command: string, lineNumber: number): IParsedCommand {
    let mnemonic = command.toUpperCase();
    let addressingMode: AddressingModes;
    let operands: string[] = [];
    let relativeOffset: number|string;


    if (command.indexOf(' ') > 0) {
        const index = command.indexOf(' ');
        mnemonic = command.slice(0, index).toUpperCase();
        operands = command.slice(index)
            .split(',')
            .map(operand => operand ? operand.trim().toUpperCase() : '')
            .filter(operand => operand.length > 0);
    }

    const operation = opcodes[mnemonic];

    if (!operation) {
        throw new CommandParseError(`Invalid mnemonic: '${mnemonic}'`, lineNumber)
    }


    if (!operation.opCodes) {
        throw new CommandParseError(`Unsupported mnemonic: '${mnemonic}'`, lineNumber)
    }

    const parsedCommand: IParsedCommand = {
        mnemonic,
        opCode: null,
        operands: [],
        usesLabel: false
    }

    if (operation.rel) {
        let rel = operands.pop();

        if (rel.startsWith("#")) {
            // immediate value
            relativeOffset = parseImmediateVal(rel.slice(1));

            if (relativeOffset < -127 || relativeOffset > 255) {
                throw new Error("Offset is too big")
            }
        } else {
            // label
            relativeOffset = rel;
            parsedCommand.usesLabel = true;
        }
    }

    if (operands.length === 3) {
        switch(mnemonic) {
            case 'BRSET':
            case 'BRCLR': 
            case 'CBEQ':
            case 'DBNZ':
            case 'MOV':
        }
    } else if (operands.length === 2) {
        if (operands[1] == 'X') {

        }
    } else if (operands.length === 1) {
        if (operands[0].startsWith('#')) {
            // immediate
            let value = parseImmediateVal(operands[0].slice(1));
            
            if (value < -127 || value > 255) {
                throw new Error();
            }

            addressingMode = AddressingModes.Immediate;
            parsedCommand.operands.push(value);
        }
    } else {
        addressingMode = AddressingModes.Inherent;
    }

    if (operation.opCodes[addressingMode] == undefined) {
        throw new CommandParseError(`Operation '${mnemonic}' does not support addressing mode of '${addressingMode}'`, lineNumber);
    }

    parsedCommand.opCode = operation.opCodes[addressingMode];

    return parsedCommand;
}
