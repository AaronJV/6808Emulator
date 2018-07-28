import AssemblerError from './errors/assemblerError';
import { parseCommand, parseLines } from './parsers';

const matchLabelOrDirect = /^(?:#(?:(\d+)|\$([A-F0-9]+))|([A-Z]\w+))$/i;

interface ILabel {
    [label: string]: number;
}

function assemble(source: string) {
    const labels: ILabel = {};
    const commands = [];
    const program = [];

    parseLines(source).forEach((cmd) => {
        if (cmd.command) {
            commands.push(parseCommand(cmd.command, cmd.lineNumber));
        }
        if (cmd.label) {
            if (labels[cmd.label] !== undefined) {
                labels[cmd.label] = cmd.lineNumber;
            } else {
                throw new AssemblerError(`Label '${cmd.label}' is already defined`, cmd.lineNumber);
            }
        }
    });

    return new Uint8Array(program);
}

export default assemble;
