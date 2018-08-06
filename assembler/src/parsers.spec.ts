import { assert, expect } from 'chai';
import 'mocha';

import CommandParseError from './errors/commandParseError';
import LineParseError from './errors/lineParseError';
import { parseCommand, parseLines } from './parsers';

describe('parseLines', () => {
    it('should parse the lines', () => {
        const source = `Label: ADD ,X ;this is a comment
        PSHX`;

        const parsedLines = parseLines(source);

        expect(parsedLines.length).to.equal(2);
        expect(parsedLines[0].lineNumber).to.equal(0);
        expect(parsedLines[0].label).to.equal('Label');
        expect(parsedLines[0].command).to.equal('ADD ,X');
        expect(parsedLines[0].comment).to.equal('this is a comment');
    });

    it('should filter empty lines', () => {
        const source = `Label: ADD , X ;this is a comment

        PSHX`;

        const matches = parseLines(source);

        expect(matches.length).to.equal(2);
    });


    it('should filter comment only lines', () => {
        const source = `Label: ADD #5
        ;this is a comment
        PSHX`;

        const matches = parseLines(source);

        expect(matches.length).to.equal(2);
    });


    it('should throw an error for invalid lines', () => {
        const source = `Label: ASRX
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


describe('parseCommands', () => {
    it('should throw an error for invalid operations', () => {
        const command = `AAAAAAA`;

        try {
            parseCommand(command, 0);
            assert.fail();
        } catch (error) {
            expect(error).to.be.a('CommandParseError');
            expect((error as CommandParseError).getLineNumber()).to.equal(0);
        }
    });

    it('should parse bit commands', () => {
        let parsed = parseCommand('BSET 2, $FF', 0);

        expect(parsed.opCode).to.equal(0x14);
        expect(parsed.operands).to.have.length(1);
        expect(parsed.operands[0]).to.equal(0xFF);

        parsed = parseCommand('BRSET 7, LABEL1, LABEL2', 0);

        expect(parsed.opCode).to.equal(0x0E);
        expect(parsed.operands).to.have.length(2);
        expect(parsed.operands).to.eql(['LABEL1', 'LABEL2']);
    });
});
