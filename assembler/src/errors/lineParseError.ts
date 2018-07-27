import AssemblerError from "./assemblerError";

export default class LineParseError extends AssemblerError {
    [Symbol.toStringTag] = 'LineParseError';

    public constructor(message: string, lineNumber: number) {
        super(message, lineNumber);
    }
}