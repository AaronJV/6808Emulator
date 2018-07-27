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
            [AddressingModes.Immediate]:                0xA5,
            [AddressingModes.Direct]:                   0xB5,
            [AddressingModes.Extended]:                 0xC5,
            [AddressingModes.Indexed16BitOffset]:       0xD5,
            [AddressingModes.Indexed8BitOffset]:        0xE5,
            [AddressingModes.Indexed]:                  0xF5,
            [AddressingModes.StackPointer16BitOffset]:  0x9eD5,
            [AddressingModes.StackPointer8BitOffset]:   0x9eE5
        }
    },
    BLE: {
        rel: true,
        opCodes: {
            [AddressingModes.Relative]:                0x25
        }
    },
    BLO: {},
    BLS: {},
    BLT: {},
    BMC: {},
    BMI: {},
    BMS: {},
    BNE: {},
    BPL: {},
    BRA: {},
    BRCLR: {},
    BRN: {},
    BRSET: {},
    BSET: {},
    BSR: {},
    CBEQ: {},
    CLC: {},
    CLI: {},
    CLR: {},
    CMP: {},
    COM: {},
    CPHX: {},
    CPX: {},
    DAA: {},
    DBNZ: {},
    DEC: {},
    DIV: {},
    EOR: {},
    INC: {},
    JMP: {},
    JSR: {},
    LDA: {},
    LDHX: {},
    LDX: {},
    LSL: {},
    LSR: {},
    MOV: {},
    MUL: {},
    NEG: {},
    NOP: {},
    NSA: {},
    ORA: {},
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
    ROL: {},
    ROR: {},
    RSP: {},
    RTI: {},
    RTS: {},
    SBC: {},
    SEC: {},
    SEI: {},
    STA: {},
    STHX: {},
    STOP: {},
    STX: {},
    SUB: {},
    SWI: {},
    TAP: {},
    TAX: {},
    TPA: {},
    TST: {},
    TSX: {},
    TXA: {},
    TXS: {},
    WAIT: {}
}

export default opcodes;
