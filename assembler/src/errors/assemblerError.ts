export default class AssemblerError extends Error {
    protected _lineNumber: number;
    protected [Symbol.toStringTag] = 'AssemblerError';

    public constructor(message: string, lineNumber: number) {
        super(message);

        this._lineNumber = lineNumber;
    }

    public getLineNumber() {
        return this._lineNumber;
    }
}
