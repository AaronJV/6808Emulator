#ifndef _M6808_HELPERS_
#define _M6808_HELPERS_
#include "./m6808.hxx"
/**
 * @brief Read next operand to get pointer to memory/register
 * 
 * Reads the next operand (incrementing the PC) and returns a
 * pointer to the specified memory address of register
 * 
 * @return uint8_t* a pointer to memory/register that can be modified
 */
uint8_t* M6808::GetReadModifyWriteOperand() {
	uint8_t opCode = memory[registers.PC++];
	bool useStackpointer = false;

	if (opCode == 0x9E) {
		opCode = memory[registers.PC++];
		useStackpointer = true;
	}

	return GetReadModifyWriteOperand(opCode, useStackpointer);
}

/**
 * @brief Gets the a pointer to memory for an operand
 * 
 * Uses an opcode and a bool of wether the operation is a SP address mode
 * to retrieve a memory address
 * 
 * @param opCode The opcode to read the memory for 
 * @param useStackpointer indicates whether or not to use SP addressing mode
 * 
 * @return uint8_t* a pointer to memory/register that can be modified
 */
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

/**
 * @brief Gets memory address for the next operand
 * 
 * Fetches the next operand (incrementing PC) and using that operand
 * to get a memory address for that operation
 * 
 * @return uint8_t The memory address for the operand read
 */
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

/**
 * @brief Read memory location for operand
 * 
 * 
 * @return uint8_t the number read from the address specified
 */
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
#endif