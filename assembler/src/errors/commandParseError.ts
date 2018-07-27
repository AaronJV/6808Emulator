import AssemblerError from "./assemblerError";

export default class CommandParseError extends AssemblerError {
    [Symbol.toStringTag] = 'CommandParseError';

    public constructor(message: string, lineNumber: number) {
        super(message, lineNumber);
    }

    public toString() {
        return `CommandParseError: On line ${this._lineNumber} - ${this.message}`;
    }
}