export enum AddressingModes {
    Inherent = 'INH',
    Immediate = 'IMM',
    Direct = 'DIR',
    Extended = 'EXT',
    Indexed = 'IX',
    Indexed8BitOffset = 'IX1',
    Indexed16BitOffset = ', 16-bit offset',
    StackPointer8BitOffset = ' SP1',
    StackPointer16BitOffset = 'SP2',
    Relative = 'REL'
}

interface IOperation {
    opCode: number;
    operands: number;
}

interface IOpCodeMap {
    [nemonic: string]: {
        rel?: boolean;
        bit?: boolean;
        opCodes?: {
            [addressingMode: string]: number
        }
    }
}

const opcodes: IOpCodeMap = {
    ADC: {
        opCodes: {
            [AddressingModes.Immediate]:               0xA9,
            [AddressingModes.Direct]:                  0xB9,
            [AddressingModes.Extended]:                0xC9,
            [AddressingModes.Indexed16BitOffset]:      0xD9,
            [AddressingModes.Indexed8BitOffset]:       0xE9,
            [AddressingModes.Indexed]:                 0xF9,
            [AddressingModes.StackPointer16BitOffset]: 0x9ED9,
            [AddressingModes.StackPointer8BitOffset]:  0x9EE9
        }
    },
    ADD: {
        opCodes: {
            [AddressingModes.Immediate]:               0xAB,
            [AddressingModes.Direct]:                  0xBB,
            [AddressingModes.Extended]:                0xCB,
            [AddressingModes.Indexed16BitOffset]:      0xDB,
            [AddressingModes.Indexed8BitOffset]:       0xEB,
            [AddressingModes.Indexed]:                 0xFB,
            [AddressingModes.StackPointer16BitOffset]: 0x9EDB,
            [AddressingModes.StackPointer8BitOffset]:  0x9EEB
        }
    },
    AIS: {
        opCodes: {
            [AddressingModes.Immediate]:               0xA7
        }
    },
    AIX: {
        opCodes: {
            [AddressingModes.Immediate]:               0xAF
        }
    },
    AND: {
        opCodes: {
            [AddressingModes.Immediate]:               0xA4,
            [AddressingModes.Direct]:                  0xB4,
            [AddressingModes.Extended]:                0xC4,
            [AddressingModes.Indexed16BitOffset]:      0xD4,
            [AddressingModes.Indexed8BitOffset]:       0xE4,
            [AddressingModes.Indexed]:                 0xF4,
            [AddressingModes.StackPointer16BitOffset]: 0x9ED4,
            [AddressingModes.StackPointer8BitOffset]:  0x9EE4
        }
    },
    ASL: {
        opCodes: {
            [AddressingModes.Immediate]:               0x38,
            [AddressingModes.Indexed8BitOffset]:       0x68,
            [AddressingModes.Indexed]:                 0x78,
            [AddressingModes.StackPointer8BitOffset]:  0x9E68
        }
    },
    ASLA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x48
        }
    },
    ASLX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x58
        }
    },
    ASR: {
        opCodes: {
            [AddressingModes.Immediate]:               0x37,
            [AddressingModes.Indexed8BitOffset]:       0x67,
            [AddressingModes.Indexed]:                 0x77,
            [AddressingModes.StackPointer8BitOffset]:  0x9E67
        }
    },
    ASRA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x47
        }
    },
    ASRX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x57
        }
    },
    BCC: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x24
        }
    },
    BCLR: {
        bit: true,
        opCodes: {
            [AddressingModes.Direct]: 0
        }
    },
    BCS: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x25
        }
    },
    BEQ: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x27
        }
    },
    BGE: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x90
        }
    },
    BGT: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x92
        }
    },
    BHCC: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x28
        }
    },
    BHCS: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x29
        }
    },
    BHI: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x22
        }
    },
    BHS: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x24
        }
    },
    BIH: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x2F
        }
    },
    BIL: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x2E
        }
    },
    BIT: {
        opCodes: {
            [AddressingModes.Immediate]:               0xA5,
            [AddressingModes.Direct]:                  0xB5,
            [AddressingModes.Extended]:                0xC5,
            [AddressingModes.Indexed16BitOffset]:      0xD5,
            [AddressingModes.Indexed8BitOffset]:       0xE5,
            [AddressingModes.Indexed]:                 0xF5,
            [AddressingModes.StackPointer16BitOffset]: 0x9ED5,
            [AddressingModes.StackPointer8BitOffset]:  0x9EE5
        }
    },
    BLE: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x93
        }
    },
    BLO: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x25
        }
    },
    BLS: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x23
        }
    },
    BLT: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x91
        }
    },
    BMC: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x2C
        }
    },
    BMI: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x2B
        }
    },
    BMS: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x2D
        }
    },
    BNE: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x26
        }
    },
    BPL: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x2A
        }
    },
    BRA: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x20
        }
    },
    BRCLR: {
        rel: true,
        opCodes: {
            [AddressingModes.Direct]: 0
        }
    },
    BRN: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x21
        }
    },
    BRSET: {
        rel: true,
        opCodes: {
            [AddressingModes.Direct]: 0
        }
    },
    BSET: {
        rel: true,
        opCodes: {
            [AddressingModes.Direct]: 0
        }
    },
    BSR: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0xAD
        }
    },
    CBEQ: {
        rel: true,
        opCodes: {
            [AddressingModes.Direct]:                  0x31,
            [AddressingModes.Indexed8BitOffset]:       0x61,
            [AddressingModes.Indexed]:                 0x71,
            [AddressingModes.StackPointer8BitOffset]:  0x9E61
        }
    },
    CBEQA: {
        rel: true,
        opCodes: {
            [AddressingModes.Immediate]:               0x41
        }
    },
    CBEQX: {
        rel: true,
        opCodes: {
            [AddressingModes.Immediate]:               0x51
        }
    },
    CLC: {
        opCodes: {
            [AddressingModes.Inherent]:                0x98
        }
    },
    CLI: {
        opCodes: {
            [AddressingModes.Inherent]:                0x9A
        }
    },
    CLR: {
        rel: true,
        opCodes: {
            [AddressingModes.Direct]:                  0x3F,
            [AddressingModes.Indexed8BitOffset]:       0x6F,
            [AddressingModes.Indexed]:                 0x7F,
            [AddressingModes.StackPointer8BitOffset]:  0x9E6F
        }
    },
    CLRA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x4F
        }
    },
    CLRX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x5F
        }
    },
    CLRH: {
        opCodes: {
            [AddressingModes.Inherent]:                0x8C
        }
    },
    CMP: {
        opCodes: {
            [AddressingModes.Immediate]:               0xA1,
            [AddressingModes.Direct]:                  0xB1,
            [AddressingModes.Extended]:                0xC1,
            [AddressingModes.Indexed16BitOffset]:      0xD1,
            [AddressingModes.Indexed8BitOffset]:       0xE1,
            [AddressingModes.Indexed]:                 0xF1,
            [AddressingModes.StackPointer16BitOffset]: 0x9ED1,
            [AddressingModes.StackPointer8BitOffset]:  0x9EE1
        }
    },
    COM: {
        opCodes: {
            [AddressingModes.Direct]:                  0x33,
            [AddressingModes.Indexed8BitOffset]:       0x63,
            [AddressingModes.Indexed]:                 0x73,
            [AddressingModes.StackPointer8BitOffset]:  0x9E63
        }
    },
    COMA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x43
        }
    },
    COMX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x53
        }
    },
    CPHX: {
        opCodes: {
            [AddressingModes.Immediate]:               0x65,
            [AddressingModes.Direct]:                  0x75
        }
    },
    CPX: {
        opCodes: {
            [AddressingModes.Immediate]:               0xA3,
            [AddressingModes.Direct]:                  0xB3,
            [AddressingModes.Extended]:                0xC3,
            [AddressingModes.Indexed16BitOffset]:      0xD3,
            [AddressingModes.Indexed8BitOffset]:       0xE3,
            [AddressingModes.Indexed]:                 0xF3,
            [AddressingModes.StackPointer16BitOffset]: 0x9ED3,
            [AddressingModes.StackPointer8BitOffset]:  0x9EE3
        }
    },
    DAA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x72
        }
    },
    DBNZ: {
        rel: true,
        opCodes: {
            [AddressingModes.Direct]:                  0x3B,
            [AddressingModes.Indexed8BitOffset]:       0x6B,
            [AddressingModes.Indexed]:                 0x7B,
            [AddressingModes.StackPointer8BitOffset]:  0x9E6B
        }
    },
    DBNZA: {
        rel: true,
        opCodes: {
            [AddressingModes.Inherent]:                0x4B
        }
    },
    DBNZX: {
        rel: true,
        opCodes: {
            [AddressingModes.Inherent]:                0x5B
        }
    },
    DEC: {
        opCodes: {
            [AddressingModes.Direct]:                  0x3A,
            [AddressingModes.Indexed8BitOffset]:       0x6A,
            [AddressingModes.Indexed]:                 0x7A,
            [AddressingModes.StackPointer8BitOffset]:  0x9E6A
        }
    },
    DECA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x4A
        }
    },
    DECX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x5A
        }
    },
    DIV: {
        opCodes: {
            [AddressingModes.Inherent]:                0x52
        }
    },
    EOR: {
        opCodes: {
            [AddressingModes.Immediate]:               0xA8,
            [AddressingModes.Direct]:                  0xB8,
            [AddressingModes.Extended]:                0xC8,
            [AddressingModes.Indexed16BitOffset]:      0xD8,
            [AddressingModes.Indexed8BitOffset]:       0xE8,
            [AddressingModes.Indexed]:                 0xF8,
            [AddressingModes.StackPointer16BitOffset]: 0x9ED8,
            [AddressingModes.StackPointer8BitOffset]:  0x9EE8
        }
    },
    INC: {
        opCodes: {
            [AddressingModes.Direct]:                  0x3C,
            [AddressingModes.Indexed8BitOffset]:       0x6C,
            [AddressingModes.Indexed]:                 0x7C,
            [AddressingModes.StackPointer8BitOffset]:  0x9E6C
        }
    },
    INCA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x4C
        }
    },
    INCX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x5C
        }
    },
    JMP: {
        opCodes: {
            [AddressingModes.Direct]:                  0xBC,
            [AddressingModes.Extended]:                0xCC,
            [AddressingModes.Indexed16BitOffset]:      0xDC,
            [AddressingModes.Indexed8BitOffset]:       0xEC,
            [AddressingModes.Indexed]:                 0xFC
        }
    },
    JSR: {
        opCodes: {
            [AddressingModes.Direct]:                  0xBD,
            [AddressingModes.Extended]:                0xCD,
            [AddressingModes.Indexed16BitOffset]:      0xDD,
            [AddressingModes.Indexed8BitOffset]:       0xED,
            [AddressingModes.Indexed]:                 0xFD
        }
    },
    LDA: {
        opCodes: {
            [AddressingModes.Immediate]:               0xA6,
            [AddressingModes.Direct]:                  0xB6,
            [AddressingModes.Extended]:                0xC6,
            [AddressingModes.Indexed16BitOffset]:      0xD6,
            [AddressingModes.Indexed8BitOffset]:       0xE6,
            [AddressingModes.Indexed]:                 0xF6,
            [AddressingModes.StackPointer16BitOffset]: 0x9ED6,
            [AddressingModes.StackPointer8BitOffset]:  0x9EE6
        }
    },
    LDHX: {
        opCodes: {
            [AddressingModes.Immediate]:               0x45,
            [AddressingModes.Direct]:                  0xB6
        }
    },
    LDX: {
        opCodes: {
            [AddressingModes.Immediate]:               0xAE,
            [AddressingModes.Direct]:                  0xBE,
            [AddressingModes.Extended]:                0xCE,
            [AddressingModes.Indexed16BitOffset]:      0xDE,
            [AddressingModes.Indexed8BitOffset]:       0xEE,
            [AddressingModes.Indexed]:                 0xFE,
            [AddressingModes.StackPointer16BitOffset]: 0x9EDE,
            [AddressingModes.StackPointer8BitOffset]:  0x9EEE
        }
    },
    LSL: {
        opCodes: {
            [AddressingModes.Direct]:                  0x38,
            [AddressingModes.Indexed8BitOffset]:       0x68,
            [AddressingModes.Indexed]:                 0x78,
            [AddressingModes.StackPointer8BitOffset]:  0x9E68
        }
    },
    LSLA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x48
        }
    },
    LSLX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x58
        }
    },
    LSR: {
        opCodes: {
            [AddressingModes.Direct]:                  0x34,
            [AddressingModes.Indexed8BitOffset]:       0x64,
            [AddressingModes.Indexed]:                 0x74,
            [AddressingModes.StackPointer8BitOffset]:  0x9E64
        }
    },
    LSRA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x44
        }
    },
    LSRX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x54
        }
    },
    MOV: {}, // TODO figureout the double addressing mode
    MUL: {
        opCodes: {
            [AddressingModes.Inherent]:                0x54
        }
    },
    NEG: {
        opCodes: {
            [AddressingModes.Direct]:                  0x30,
            [AddressingModes.Indexed8BitOffset]:       0x60,
            [AddressingModes.Indexed]:                 0x70,
            [AddressingModes.StackPointer8BitOffset]:  0x9E60
        }
    },
    NEGA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x40
        }
    },
    NEGX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x50
        }
    },
    NOP: {
        opCodes: {
            [AddressingModes.Inherent]:                0x9D
        }
    },
    NSA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x62
        }
    },
    ORA: {
        opCodes: {
            [AddressingModes.Immediate]:               0xAA,
            [AddressingModes.Direct]:                  0xBA,
            [AddressingModes.Extended]:                0xCA,
            [AddressingModes.Indexed16BitOffset]:      0xDA,
            [AddressingModes.Indexed8BitOffset]:       0xEA,
            [AddressingModes.Indexed]:                 0xFA,
            [AddressingModes.StackPointer16BitOffset]: 0x9EDA,
            [AddressingModes.StackPointer8BitOffset]:  0x9EEA
        }
    },
    PSHA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x87
        }
    },
    PSHH: {
        opCodes: {
            [AddressingModes.Inherent]:                0x8B
        }
    },
    PSHX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x89
        }
    },
    PULA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x86
        }
    },
    PULH: {
        opCodes: {
            [AddressingModes.Inherent]:                0x8A
        }
    },
    PULX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x88
        }
    },
    ROL: {
        opCodes: {
            [AddressingModes.Direct]:                  0x39,
            [AddressingModes.Indexed8BitOffset]:       0x69,
            [AddressingModes.Indexed]:                 0x79,
            [AddressingModes.StackPointer8BitOffset]:  0x9E69
        }
    },
    ROLA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x49
        }
    },
    ROLX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x59
        }
    },
    ROR: {
        opCodes: {
            [AddressingModes.Direct]:                  0x36,
            [AddressingModes.Indexed8BitOffset]:       0x66,
            [AddressingModes.Indexed]:                 0x76,
            [AddressingModes.StackPointer8BitOffset]:  0x9E66
        }
    },
    RORA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x46
        }
    },
    RORX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x56
        }
    },
    RSP: {
        opCodes: {
            [AddressingModes.Inherent]:                0x9C
        }
    },
    RTI: {
        opCodes: {
            [AddressingModes.Inherent]:                0x80
        }
    },
    RTS: {
        opCodes: {
            [AddressingModes.Inherent]:                0x81
        }
    },
    SBC: {
        opCodes: {
            [AddressingModes.Immediate]:               0xA2,
            [AddressingModes.Direct]:                  0xB2,
            [AddressingModes.Extended]:                0xC2,
            [AddressingModes.Indexed16BitOffset]:      0xD2,
            [AddressingModes.Indexed8BitOffset]:       0xE2,
            [AddressingModes.Indexed]:                 0xF2,
            [AddressingModes.StackPointer16BitOffset]: 0x9EDA,
            [AddressingModes.StackPointer8BitOffset]:  0x9EEA
        }
    },
    SEC: {
        opCodes: {
            [AddressingModes.Inherent]:                0x99
        }
    },
    SEI: {
        opCodes: {
            [AddressingModes.Inherent]:                0x9B
        }
    },
    STA: {
        opCodes: {
            [AddressingModes.Direct]:                  0xB7,
            [AddressingModes.Extended]:                0xC7,
            [AddressingModes.Indexed16BitOffset]:      0xD7,
            [AddressingModes.Indexed8BitOffset]:       0xE7,
            [AddressingModes.Indexed]:                 0xF7,
            [AddressingModes.StackPointer16BitOffset]: 0x9ED7,
            [AddressingModes.StackPointer8BitOffset]:  0x9EE7
        }
    },
    STHX: {
        opCodes: {
            [AddressingModes.Direct]:                  0x35
        }
    },
    STOP: {
        opCodes: {
            [AddressingModes.Inherent]:                0x8E
        }
    },
    STX: {
        opCodes: {
            [AddressingModes.Direct]:                  0xBF,
            [AddressingModes.Extended]:                0xCF,
            [AddressingModes.Indexed16BitOffset]:      0xDF,
            [AddressingModes.Indexed8BitOffset]:       0xEF,
            [AddressingModes.Indexed]:                 0xFF,
            [AddressingModes.StackPointer16BitOffset]: 0x9EDF,
            [AddressingModes.StackPointer8BitOffset]:  0x9EEF
        }
    },
    SUB: {
        opCodes: {
            [AddressingModes.Immediate]:               0xA0,
            [AddressingModes.Direct]:                  0xB0,
            [AddressingModes.Extended]:                0xC0,
            [AddressingModes.Indexed16BitOffset]:      0xD0,
            [AddressingModes.Indexed8BitOffset]:       0xE0,
            [AddressingModes.Indexed]:                 0xF0,
            [AddressingModes.StackPointer16BitOffset]: 0x9ED0,
            [AddressingModes.StackPointer8BitOffset]:  0x9EE0
        }
    },
    SWI: {
        opCodes: {
            [AddressingModes.Inherent]:                0x83
        }
    },
    TAP: {
        opCodes: {
            [AddressingModes.Inherent]:                0x84
        }
    },
    TAX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x97
        }
    },
    TPA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x85
        }
    },
    TST: {
        opCodes: {
            [AddressingModes.Direct]:                  0x3D,
            [AddressingModes.Indexed8BitOffset]:       0x6D,
            [AddressingModes.Indexed]:                 0x7D,
            [AddressingModes.StackPointer8BitOffset]:  0x9E6D
        }
    },
    TSTA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x4D
        }
    },
    TSTX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x5D
        }
    },
    TSX: {
        opCodes: {
            [AddressingModes.Inherent]:                0x95
        }
    },
    TXA: {
        opCodes: {
            [AddressingModes.Inherent]:                0x9F
        }
    },
    TXS: {
        opCodes: {
            [AddressingModes.Inherent]:                0x94
        }
    },
    WAIT: {
        opCodes: {
            [AddressingModes.Inherent]:                0x8F
        }
    }
}

export default opcodes;
