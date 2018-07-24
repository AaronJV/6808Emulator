const regex =  /^\s*(?:([A-Z]\w+):\s+)?(?:([A-Z]{3,5}(?:\s+\w+,\s*\w*)?)?(?:\s*;(.*))?(?:))?$/i;

interface IParsedLine {
    lineNumber: number;
    label: string;
    command: string;
    comment: string;
};

function assemble(source: string) {
    const matches = regex.exec(source);

    return matches;
}


export function parseLines(source: string): IParsedLine[] {
    const lines = source.split('\n');

    return lines.map((line, index) => {
        const match = regex.exec(line.trim());

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

export default assemble;