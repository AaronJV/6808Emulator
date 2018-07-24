export default class LineParseError extends Error {
    private _lineNumber: number;
    [Symbol.toStringTag] = 'LineParseError';

    public constructor(lineNumber: number, message: string) {
        super(message);

        this._lineNumber = lineNumber;
    }

    getLineNumber() {
        return this._lineNumber;
    }
}