#include "./m6808.hxx"


ConditionCodes addConditionCodes(ConditionCodes initialCC, uint8_t acc, uint8_t data, uint8_t result) {
    uint8_t a7 = (1 << 7) & acc;
    uint8_t a3 = (1 << 3) & acc;
    uint8_t m7 = (1 << 7) & data;
    uint8_t m3 = (1 << 3) & data;
    uint8_t r7 = (1 << 7) & result;
    uint8_t r3 = (1 << 3) & result;

    ConditionCodes ccr;

    ccr.V = (a7 && m7 && !r7) || (!a7 && !m7 && r7);
    ccr.H = (a3 && m3) || (m3 && r3) || (r3 && a3);
    ccr.I = initialCC.I;
    ccr.N = r7 != 0;
    ccr.Z = result == 0;
    ccr.C = (a7 && m7) || (m7 && !r7) || (!r7 && a7);

    return ccr;
}


ConditionCodes subtractConditionCodes(ConditionCodes initialCC, uint8_t acc, uint8_t data, uint8_t result) {
    uint8_t a7 = (1 << 7) & acc;
    uint8_t m7 = (1 << 7) & data;
    uint8_t r7 = (1 << 7) & result;

    ConditionCodes ccr;

    ccr.V = (a7 && !m7 && !r7) || (!a7 && m7 && !r7);
    ccr.H = initialCC.H;
    ccr.I = initialCC.I;
    ccr.N = r7 != 0;
    ccr.Z = result == 0;
    ccr.C = (!a7 && m7) || (m7 && r7) || (r7 && !a7);

    return ccr;
}

void M6808::BCLR() {
    FAIL();
};

void M6808::BRCLR() {
    FAIL();
};

void M6808::BRSET() {
    FAIL();
};

void M6808::BSET() {
    FAIL();
};


// Branching
void M6808::BCC() {
    FAIL();
};

void M6808::BCS() {
    FAIL();
};

void M6808::BEQ() {
    FAIL();
};

void M6808::BHCC() {
    FAIL();
};

void M6808::BHCS() {
    FAIL();
};

void M6808::BHI() {
    FAIL();
};

void M6808::BIH() {
    FAIL();
};

void M6808::BIL() {
    FAIL();
};

void M6808::BLS() {
    FAIL();
};

void M6808::BMC() {
    FAIL();
};

void M6808::BMI() {
    FAIL();
};

void M6808::BMS() {
    FAIL();
};

void M6808::BNE() {
    FAIL();
};

void M6808::BPL() {
    FAIL();
};

void M6808::BRA() {
    FAIL();
};

void M6808::BRN() {
    FAIL();
};


// Read/Modify/Write
void M6808::ASR() {
    FAIL();
};

void M6808::CBEQ() {
    FAIL();
};

void M6808::CLR() {
    FAIL();
};

void M6808::COM() {
    FAIL();
};

void M6808::CPHX() {
    FAIL();
};

void M6808::DAA() {
    FAIL();
};

void M6808::DBNZ() {
    FAIL();
};

void M6808::DEC() {
    uint8_t* pNumber = GetReadModifyWriteOperand();
    registers.CCR.V = *pNumber == 0x80;
    (*pNumber)--;
    registers.CCR.Z = *pNumber == 0;
    registers.CCR.N = ((int8_t)*pNumber) < 0;
};

void M6808::DIV() {
	uint16_t numerator = registers.H << 8 | registers.A;

	if (registers.X == 0) {
		registers.CCR.C = 1;
	} else {
		uint16_t quotient = numerator / registers.X;
		registers.A = quotient;
		registers.H = numerator % registers.X;
		registers.CCR.C = quotient > 0xFF;
		registers.CCR.Z = registers.A == 0;
	}
	registers.PC++;
};

void M6808::INC() {
    uint8_t* pNumber = GetReadModifyWriteOperand();
    registers.CCR.V = *pNumber == 0x7F;
    (*pNumber)++;
    registers.CCR.Z = *pNumber == 0;
    registers.CCR.N = ((int8_t)*pNumber) < 0;
};

void M6808::LDHX() {
    FAIL();
};

void M6808::LSL() {
    FAIL();
};

void M6808::LSR() {
    FAIL();
};

void M6808::MOV() {
	uint8_t addrMode = memory[registers.PC++] >> 4;
	uint8_t source;
	uint8_t* pDest;
	
	switch (addrMode) {
	case 4: // DIR/DIR
		source = memory[memory[registers.PC++]];
		pDest = &memory[memory[registers.PC++]];
		break;
	case 5: // DIR/IX+
		source = memory[memory[registers.PC++]];
		pDest = &memory[registers.H << 8 | registers.X++];

		if (registers.X == 0) {
			registers.H++;
		}
		break;
	case 6: // IMM/DIR
		source = memory[registers.PC++];
		pDest = &memory[memory[registers.PC++]];

		break;
	case 7: // IX+/DIR
		source = memory[registers.H << 8 | registers.X++];
		pDest = &memory[memory[registers.PC++]];

		if (registers.X == 0) {
			registers.H++;
		}
		break;
	default:
		FAIL();
	}

	*pDest = source;
	registers.CCR.V = 0;
	registers.CCR.Z = *pDest == 0;
	registers.CCR.N = ((int8_t)*pDest) < 0;
};

void M6808::MUL() {
	uint16_t product = (uint16_t)registers.A * (uint16_t)registers.X;

	registers.A = (uint8_t)product;
	registers.X = product >> 8;
	registers.CCR.C = 0;
	registers.CCR.H = 0;
	registers.PC++;
};

void M6808::NEG() {
    uint8_t* pNumber = GetReadModifyWriteOperand();

    registers.CCR.C = *pNumber != 0;

    uint8_t m7 = *pNumber >> 7;

    *pNumber = (uint8_t)(-1 * (*pNumber));

    registers.CCR.Z = *pNumber == 0;
    registers.CCR.N = ((int8_t)*pNumber) < 0;
    registers.CCR.V = *pNumber >> 7 && m7;
};

void M6808::NSA() {
    FAIL();
};

void M6808::ROL() {
    FAIL();
};

void M6808::ROR() {
    FAIL();
};

void M6808::STHX() {
    FAIL();
};

void M6808::TST() {
    FAIL();
};


// Control
void M6808::BGE() {
    FAIL();
};

void M6808::BGT() {
    FAIL();
};

void M6808::BLE() {
    FAIL();
};

void M6808::BLT() {
    FAIL();
};

void M6808::CEC() {
    FAIL();
};

void M6808::CLC() {
    registers.CCR.C = 0;
    registers.PC++;
};

void M6808::CLI() {
    FAIL();
};

void M6808::NOP() {
    // NOP
    registers.PC++;
};

void M6808::PSH() {
    FAIL();
};

void M6808::PUL() {
    FAIL();
};

void M6808::RSP() {
    FAIL();
};

void M6808::RTI() {
    FAIL();
};

void M6808::RTS() {
    FAIL();
};

void M6808::SEC() {
    registers.CCR.C = 1;
    registers.PC++;
};

void M6808::SEI() {
    FAIL();
};

void M6808::STOP() {
    FAIL();
};

void M6808::SWI() {
    FAIL();
};

void M6808::TAP() {
    FAIL();
};

void M6808::TAX() {
    FAIL();
};

void M6808::TPA() {
    FAIL();
};

void M6808::TRS() {
    FAIL();
};

void M6808::TSX() {
    FAIL();
};

void M6808::TXA() {
    FAIL();
};

void M6808::TXS() {
    FAIL();
};

void M6808::WAIT() {
    FAIL();
};


// Register/Memory
void M6808::SUB() {
    uint8_t number = GetRegisterMemoryOperand();
    uint8_t acc = registers.A;

    registers.A -= number;
    registers.CCR = subtractConditionCodes(registers.CCR, acc, number, registers.A);
};

void M6808::CMP() {
    FAIL();
};

void M6808::SBC() {
    uint8_t number = GetRegisterMemoryOperand();
    uint8_t acc = registers.A;

    registers.A -= number + registers.CCR.C;
    registers.CCR = subtractConditionCodes(registers.CCR, acc, number, registers.A);
};

void M6808::CPX() {
    FAIL();
};

void M6808::AND() {
    FAIL();
};

void M6808::BIT() {
    FAIL();
};

void M6808::LDA() {
	uint8_t number = GetRegisterMemoryOperand();
	registers.A = number;
	registers.CCR.Z = number == 0;
	registers.CCR.N = ((int8_t)number) < 0;
	registers.CCR.V = 0;
};

void M6808::AIS() {
    FAIL();
};

void M6808::STA() {
	uint8_t addr = GetRegisterMemoryAddress();
	memory[addr] = registers.A;
	registers.CCR.Z = registers.A == 0;
	registers.CCR.N = ((int8_t)registers.A) < 0;
	registers.CCR.V = 0;
};

void M6808::EOR() {
    FAIL();
};

void M6808::ADC() {
    uint8_t number = GetRegisterMemoryOperand();
    uint8_t acc = registers.A;

    registers.A += number + registers.CCR.C;
    registers.CCR = addConditionCodes(registers.CCR, acc, number, registers.A);
};

void M6808::ORA() {
    FAIL();
};

void M6808::ADD() {
    uint8_t number = GetRegisterMemoryOperand();
    uint8_t acc = registers.A;

	registers.A += number;
    registers.CCR = addConditionCodes(registers.CCR, acc, number, registers.A);
};

void M6808::JMP() {
    FAIL();
};

void M6808::BSR() {
    FAIL();
};

void M6808::JSR() {
    FAIL();
};

void M6808::LDX() {
	uint8_t number = GetRegisterMemoryOperand();
	registers.X = number;
	registers.CCR.Z = number == 0;
	registers.CCR.N = ((int8_t)number) < 0;
	registers.CCR.V = 0;
};

void M6808::AIX() {
    FAIL();
};

void M6808::STX() {
    FAIL();
};


// Helper Methods

uint8_t* M6808::GetReadModifyWriteOperand() {
	uint8_t opCode = memory[registers.PC++];
	bool useStackpointer = false;

	if (opCode == 0x9E) {
		opCode = memory[registers.PC++];
		useStackpointer = true;
	}

	return GetReadModifyWriteOperand(opCode, useStackpointer);
}

uint8_t* M6808::GetReadModifyWriteOperand(uint8_t opCode, bool useStackpointer) {
    uint8_t* pNumber = 0x0;
    uint16_t addr;

    switch (opCode >> 4) {
    case 0x3: // DIRECT
		addr = memory[registers.PC++];
        pNumber = &memory[addr];
        break;
    case 0x4: // INH (A)
        pNumber = &registers.A;
        break;
    case 0x5: // INH (X)
        pNumber = &registers.X;
        break;
    case 0x6: // INDEX/STACK POINTER  8-bit offset
        addr = memory[registers.PC++];
        if (useStackpointer) {
            addr += registers.SP;
        }
        else {
            addr += (registers.H << 8 | registers.X);
        }
        pNumber = &memory[addr];
        break;
    case 0x7: // INDEX
        pNumber = &memory[(registers.H << 8 | registers.X)];
        break;
    }

    return pNumber;
}


uint8_t M6808::GetRegisterMemoryAddress() {
	uint8_t opCode = memory[registers.PC++];
	uint16_t addr;
	bool useStackpointer = false;

	if (opCode == 0x9E) {
		opCode = memory[registers.PC++];
		useStackpointer = true;
	}

	switch (opCode >> 4) {
	case 0xB: // Direct
		addr = memory[registers.PC++];
		break;
	case 0xC: // Extended
		addr = memory[registers.PC++] << 8 | memory[registers.PC++];
		break;
	case 0xDB: // Index/Stack 16-bit Offset
		addr = memory[registers.PC++] << 8 | memory[registers.PC++];
		if (useStackpointer) {
			addr += registers.SP;
		}
		else {
			addr += (registers.H << 8 | registers.X);
		}
		break;
	case 0xE: // Index/Stack 8-bit Offset
		addr = memory[registers.PC++];
		if (useStackpointer) {
			addr += registers.SP;
		}
		else {
			addr += (registers.H << 8 | registers.X);
		}
		break;
	case 0xF: // Index No-Offset
		addr = registers.H << 8 | registers.X;
		break;
	}

	return addr;
}

uint8_t M6808::GetRegisterMemoryOperand() {
    uint8_t opCode = memory[registers.PC++];
    uint8_t number = 0;
    uint16_t addr;
    bool useStackpointer = false;

    if (opCode == 0x9E) {
        opCode = memory[registers.PC++];
        useStackpointer = true;
    }

    switch (opCode >> 4) {
    case 0xA: // Immediate
        number = memory[registers.PC++];
        break;
    case 0xB: // Direct
        addr = memory[registers.PC++];
        number = memory[addr];
        break;
    case 0xC: // Extended
        addr = memory[registers.PC++] << 8 | memory[registers.PC++];
        number = memory[addr];
        break;
    case 0xDB: // Index/Stack 16-bit Offset
        addr = memory[registers.PC++] << 8 | memory[registers.PC++];
        if (useStackpointer) {
            addr += registers.SP;
        }
        else {
            addr += (registers.H << 8 | registers.X);
        }
        number = memory[addr];
        break;
    case 0xE: // Index/Stack 8-bit Offset
        addr = memory[registers.PC++];
        if (useStackpointer) {
            addr += registers.SP;
        }
        else {
            addr += (registers.H << 8 | registers.X);
        }
        number = memory[addr];
        break;
    case 0xF: // Index No-Offset
        number = memory[(registers.H << 8 | registers.X)];
        break;
    }

    return number;
}