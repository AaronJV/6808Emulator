#include "../m6808.hxx"


uint8_t isBetween(uint8_t number, uint8_t lower, uint8_t upper) {
	return lower <= number && number <= upper;
}

/**
 * @brief Arithmetic Shift Right
 * 
 * Shifts all bits of A, X, or M one place to the right.
 * Bit 7 is held constant. Bit 0 is loaded into the C bit of the CCR
 * 
 * CCR:
 *  V: R7 XOR b0
 *  N: R7
 *  Z: R == 0
 *  C: b0
 */
void M6808::ASR() {
    uint8_t* operand = GetReadModifyWriteOperand();

	uint8_t msb = (*operand) & 0xF0;
	registers.CCR.C = (*operand) & 0x01;
	registers.CCR.N = msb > 0;
	*operand = ((*operand) >> 1 | msb);
	registers.CCR.V = (registers.CCR.C != registers.CCR.N);
	registers.CCR.Z = *operand == 0;
};



/**
 * @brief Clear
 * 
 * The contents of memory (M), A, X, or H are replaced with zeros
 * 
 * CCR:
 *  V: 0
 *  N: 0
 *  Z: 1
 */
void M6808::CLR() {
    uint8_t* operand = GetReadModifyWriteOperand();
	*operand = 0;
	registers.CCR.V = 0;
	registers.CCR.N = 0;
	registers.CCR.Z = 1;
};



/**
 * @brief Compliment (One's Compliment)
 * 
 * Replaces the contents of A, X, or M with the one’s complement
 * 
 * CCR:
 *  V: 0
 *  N: R7
 *  Z: R == 0
 *  C: 1
 */
void M6808::COM() {
    uint8_t* operand = GetReadModifyWriteOperand();
	*operand = 0xFF - *operand;
	registers.CCR.V = 0;
	registers.CCR.N = ((int8_t)*operand) < 0;
	registers.CCR.Z = *operand == 0;
	registers.CCR.C = 1;
};



/**
 * @brief Compare Index Register with Memory
 * 
 * CPHX compares index register (H:X) with the 16-bit value in memory
 * and sets the condition codes, which may then be used for arithmetic
 * (signed or unsigned) and logical conditional branching
 * 
 * CCR:
 *  V: H7&~M15&~R15 | ~H7&M15&R15
 *  N: R15
 *  Z: R == 0
 *  C: ~H7&M15 | M15&R15 | R15&~H7
 */
void M6808::CPHX() {
	uint8_t opCode = memory[registers.PC++];
	uint16_t index = registers.H << 8 | registers.X;
	uint16_t other = 0;

	if (opCode == 0x65) {
		// immediate
		other = memory[registers.PC++] << 8 | memory[registers.PC++];
	} else if (opCode == 0x75) {
		// direct
		uint16_t addr = memory[registers.PC++];
		other = memory[addr] << 8 | memory[addr + 1];
	} else {
    	FAIL();
		return;
	}

	int16_t result = index - other;

	int8_t twosCheckOne = ((int8_t)registers.H) < 0 && ((int16_t)other) > 0  && ((int16_t)result) > 0;
	int8_t twosCheckTwo = ((int8_t)registers.H) > 0 && ((int16_t)other) < 0  && ((int16_t)result) < 0;

	int8_t carry1 = ((int8_t)registers.H) > 0 && ((int16_t)other) < 0;
	int8_t carry2 = ((int16_t)other) > 0 && ((int16_t)result) > 0;
	int8_t carry3 = ((int16_t)result) < 0 && ((int8_t)registers.H) > 0;

	registers.CCR.V = twosCheckOne || twosCheckTwo;
	registers.CCR.N = result < 0;
	registers.CCR.Z = result == 0;
	registers.CCR.C = carry1 || carry2 || carry3;
};



/**
 * @brief Decimal Adjust Accumulator
 * 
 * Adjusts the contents of the accumulator and the state of the CCR carry
 * bit after an ADD or ADC operation involving binary-coded decimal (BCD)
 * values, so that there is a correct BCD sum and an accurate carry indication
 */
void M6808::DAA() {
	uint8_t msbits = registers.A & 0xF0 >> 4;
	uint8_t lsbits = registers.A & 0x0F;

	uint8_t correctionFactor = 0;
	if (registers.CCR.C) {
		if (isBetween(msbits, 0, 2) && !registers.CCR.H && isBetween(lsbits, 0, 9)) {
			correctionFactor = 0x60;
		} else if (isBetween(msbits, 0, 2) && !registers.CCR.H && isBetween(lsbits, 0xA, 0xF)) {
			correctionFactor = 0x66;
		} else if (isBetween(msbits, 0, 3) && registers.CCR.H && isBetween(lsbits, 0, 3)) {
			correctionFactor = 0x66;
		}
	} else {
		if (isBetween(msbits, 0, 9) && !registers.CCR.H && isBetween(lsbits, 0, 9)) {
			correctionFactor = 0x00;
		} else if (isBetween(msbits, 0, 8) && !registers.CCR.H && isBetween(lsbits, 0xA, 0xF)) {
			correctionFactor = 0x06;
		} else if (isBetween(msbits, 0, 9) && registers.CCR.H && isBetween(lsbits, 0, 3)) {
			correctionFactor = 0x06;
		} else if (isBetween(msbits, 0xA, 0xF) && !registers.CCR.H && isBetween(lsbits, 0, 9)) {
			correctionFactor = 0x60;
			registers.CCR.C = 1;
		} else if (isBetween(msbits, 0x9, 0xF) && !registers.CCR.H && isBetween(lsbits, 0xA, 0xF)) {
			correctionFactor = 0x66;
			registers.CCR.C = 1;
		} else if (isBetween(msbits, 0xA, 0xF) && registers.CCR.H && isBetween(lsbits, 0, 3)) {
			correctionFactor = 0x66;
			registers.CCR.C = 1;
		}
	}

	registers.A += correctionFactor;

	registers.CCR.N = ((int8_t)registers.A) < 0;
	registers.CCR.Z = registers.A == 0;
	registers.CCR.C = registers.A > 99;
};



void M6808::CPX() {
    FAIL();
};



void M6808::DBNZ() {
    FAIL();
};



void M6808::CMP() {
    FAIL();
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



/**
 * @brief Move
 * 
 * Moves a byte of data from a source address to a destination address
 * 
 * CCR:
 *  V: 0
 *  N: R7
 *  Z: R == 0
 * 
 */
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

/**
 * @brief Load Accumulator from Memory
 * 
 * Loads the contents of the specified memory location into A
 * 
 * CCR:
 *  V: 0
 *  N: R7
 *  Z: R==0
 * 
 */
void M6808::LDA() {
	uint8_t number = GetRegisterMemoryOperand();
	registers.A = number;
	registers.CCR.Z = number == 0;
	registers.CCR.N = ((int8_t)number) < 0;
	registers.CCR.V = 0;
};





/**
 * @brief Store Accumulator in Memory
 * 
 * Stores the contents of A in memory. The contents of A remain unchanged. 
 * 
 * CCR:
 *  V: 0
 *  N: A7
 *  Z: A == 0
 */
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

/**
 * @brief Load X (Index Register Low) from Memory
 * 
 * Loads the contents of the specified memory location into X
 * 
 * CCR:
 *  V: 0
 *  N: R7
 *  Z: R==0
 * 
 */
void M6808::LDX() {
	uint8_t number = GetRegisterMemoryOperand();
	registers.X = number;
	registers.CCR.Z = number == 0;
	registers.CCR.N = ((int8_t)number) < 0;
	registers.CCR.V = 0;
};


void M6808::STX() {
    FAIL();
};


/**
 * @brief Clear Bit n in Memory
 * 
 * Clear bit n (n = 7, 6, 5, … 0) in location M. All other bits in M are unaffected
 * 
 * CCR:
 *  - unaffected
 */
void M6808::BCLR() {
    FAIL();
};



void M6808::BSET() {
    FAIL();
};
