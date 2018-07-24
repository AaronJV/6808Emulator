import { parseLines } from './assembler';
import { expect, assert } from 'chai';
import 'mocha';
import LineParseError from './lineParseError';

describe('parseLines', () => {
    it('should parse the lines', () => {
        const source = `Label: ADD ;this is a comment
        PSHX`;

        const parsedLines = parseLines(source);

        expect(parsedLines.length).to.equal(2);
        expect(parsedLines[0].lineNumber).to.equal(0);
        expect(parsedLines[0].label).to.equal('Label');
        expect(parsedLines[0].command).to.equal('ADD');
        expect(parsedLines[0].comment).to.equal('this is a comment');
    });

    it('should filter empty lines', () => {
        const source = `Label: ADD ;this is a comment




        PSHX`;

        const matches = parseLines(source);

        expect(matches.length).to.equal(2);
    });


    it('should filter comment only lines', () => {
        const source = `Label: ADD
        ;this is a comment
        PSHX`;

        const matches = parseLines(source);

        expect(matches.length).to.equal(2);
    });


    it('should throw an error for invalid lines', () => {
        const source = `Label: ADD
        this line is not a valid line
        PSHX`;

        try {
            parseLines(source);
            assert.fail();
        } catch (error) {
            expect(error).to.be.a('LineParseError');
            expect((error as LineParseError).getLineNumber()).to.equal(1);
        }
    });
});