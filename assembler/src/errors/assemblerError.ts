export default class AssemblerError extends Error {
    [Symbol.toStringTag] = 'AssemblerError';
    protected _lineNumber: number;

    public constructor(message: string, lineNumber: number) {
        super(message);

        this._lineNumber = lineNumber;
    }

    public getLineNumber() {
        return this._lineNumber;
    }
}