#include "../m6808.hxx"

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
