#include "../m6808.hxx"

/**
 * @brief Set Addition Operations CCR
 * 
 * @param initialCC The current state of the CCR
 * @param acc       The value of the accumulator before the operation
 * @param data      the value of the memory used
 * @param result    the resulting value
 * 
 * @return ConditionCodes The CCR from the addition
 */
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



/**
 * @brief Set Subtraction Operations CCR
 * 
 * @param initialCC The current state of the CCR
 * @param acc       The value of the accumulator before the operation
 * @param data      the value of the memory used
 * @param result    the resulting value
 * 
 * @return ConditionCodes The CCR from the subtraction
 */
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



/**
 * @brief Add with Carry
 * 
 * Adds the contents of the C bit to the sum of the contents of A and M and places the result in A. 
 * 
 * CCR:
 *  V: A7&M7&~R7 | ~A7&~M7&R7
 *  H: A3&M3 | M3&~R3 | ~R3&A3
 *  N: R7
 *  Z: R == 0
 *  C: A7&M7 | M7&~R7 | ~R7&A7
 * 
 */
void M6808::ADC() {
    uint8_t number = GetRegisterMemoryOperand();
    uint8_t acc = registers.A;

    registers.A += number + registers.CCR.C;
    registers.CCR = addConditionCodes(registers.CCR, acc, number, registers.A);
};



/**
 * @brief Add without Carry
 * 
 * Adds the contents of M to the contents of A and places the result in A
 * 
 * CCR:
 *  V: A7&M7&~R7 | ~A7&~M7&R7
 *  H: A3&M3 | M3&~R3 | ~R3&A3
 *  N: R7
 *  Z: R == 0
 *  C: A7&M7 | M7&~R7 | ~R7&A7
 */
void M6808::ADD() {
    uint8_t number = GetRegisterMemoryOperand();
    uint8_t acc = registers.A;

	registers.A += number;
    registers.CCR = addConditionCodes(registers.CCR, acc, number, registers.A);
};



/**
 * @brief Subtract
 * 
 * Subtracts the contents of M from A and places the result in A
 * 
 * CCR:
 *  V: A7&~M7&~R7 | ~A7&M7&R7
 *  N: R7
 *  Z: R == 0
 *  C: ~A7&M7 | M7&R7 | R7&~A7
 * 
 */
void M6808::SUB() {
    uint8_t number = GetRegisterMemoryOperand();
    uint8_t acc = registers.A;

    registers.A -= number;
    registers.CCR = subtractConditionCodes(registers.CCR, acc, number, registers.A);
};



/**
 * @brief Subtract with Carry
 * 
 * Subtracts the contents of M and the contents of the C bit of the
 * CCR from the contents of A and places the result in A
 * 
 * CCR:
 *  V: A7&~M7&~R7 | ~A7&M7&R7
 *  N: R7
 *  Z: R == 0
 *  C: ~A7&M7 | M7&R7 | R7&~A7
 * 
 */
void M6808::SBC() {
    uint8_t number = GetRegisterMemoryOperand();
    uint8_t acc = registers.A;

    registers.A -= number + registers.CCR.C;
    registers.CCR = subtractConditionCodes(registers.CCR, acc, number, registers.A);
};



/**
 * @brief Logical AND
 * 
 * Performs the logical AND between the contents of A and the
 * contents of M and places the result in A
 * 
 * CCR:
 *  V: 0
 *  N: R7
 *  Z: R == 0
 */
void M6808::AND() {
    uint8_t number = GetRegisterMemoryOperand();

    registers.A &= number;

    registers.CCR.V = 0;
    registers.CCR.N = ((int8_t)registers.A) < 0;
    registers.CCR.Z = registers.A == 0;
};



/**
 * @brief Bit Test
 * 
 * Performs the logical AND comparison of the contents of A and
 * the contents of M and modifies the condition codes accordingly.
 * Neither the contents of A nor M are altered.
 * 
 * CCR:
 *  V: 0
 *  N: R7
 *  Z: R == 0
 */
void M6808::BIT() {
    uint8_t number = GetRegisterMemoryOperand();
    uint8_t result = registers.A & number;

    registers.CCR.V = 0;
    registers.CCR.N = ((int8_t)result) < 0;
    registers.CCR.Z = result == 0;
};



/**
 * @brief Inclusive-OR Accumulator and Memory
 * 
 * Performs the logical inclusive-OR between the contents of A
 * and the contents of M and places the result in A
 * 
 * CCR:
 *  V: 0
 *  N: R7
 *  Z: R == 0
 */
void M6808::ORA() {
    uint8_t number = GetRegisterMemoryOperand();

    registers.A |= number;

    registers.CCR.V = 0;
    registers.CCR.N = ((int8_t)registers.A) < 0;
    registers.CCR.Z = registers.A == 0;
};


/**
 * @brief Add Immediate Value (Signed) to Stack Pointer
 * 
 * Adds an immediate operand to the 16-bit stack pointer
 * 
 * CCR:
 *  unchanged
 * 
 */
void M6808::AIS() {
    int16_t number = (int16_t)GetRegisterMemoryOperand();
    registers.SP += number;
};


/**
 * @brief Add Immediate Value (Signed) to Index Register
 * 
 * Adds an immediate operand to the 16-bit index register,
 * formed by the concatenation of the H and X registers
 * 
 * CCR:
 *  unchanged
 * 
 */
void M6808::AIX() {
    uint16_t indexReg = registers.H << 8 | registers.X;
    int16_t number = (int16_t)GetRegisterMemoryOperand();

    indexReg += number;
    registers.H = indexReg >> 8;
    registers.X = indexReg & 0xFF;
};



/**
 * @brief Increment
 * 
 * Add 1 to the contents of A, X, or M.
 * 
 * CRR:
 *  - V: ~A7&R7 ()
 *  - N: R7
 *  - Z: R==0
 */
void M6808::INC() {
    uint8_t* pNumber = GetReadModifyWriteOperand();
    registers.CCR.V = *pNumber == 0x7F;
    (*pNumber)++;
    registers.CCR.Z = *pNumber == 0;
    registers.CCR.N = ((int8_t)*pNumber) < 0;
};



/**
 * @brief Decrement
 * 
 * Subtract 1 from the contents of A, X, or M.
 * 
 * CCR:
 *  - V: ~R7 & A7 (Set if there was a two’s complement overflow as a result of the operation)
 *  - N: R7 (Set if MSB of result is 1; cleared otherwise)
 *  - Z: ~R7&~R6&~R5&~R4&~R3&~R2&~R1&~R0 (Set if result is $00; cleared otherwise)
 */
void M6808::DEC() {
    uint8_t* pNumber = GetReadModifyWriteOperand();
    registers.CCR.V = *pNumber == 0x80;
    (*pNumber)--;
    registers.CCR.Z = *pNumber == 0;
    registers.CCR.N = ((int8_t)*pNumber) < 0;
};



/**
 * @brief Divide
 * 
 * Divides a 16-bit unsigned dividend contained in the concatenated
 * registers H and A by an 8-bit divisor contained in X
 * 
 * Note: An overflow (quotient > $FF) or divide-by-0 sets the C bit,
 * and the quotient and remainder are indeterminate.
 * 
 * CCR:
 *  - Z: Set if R (quotient) == 0, otherwise cleared
 *  - C: Set if divide by 0 was attempted
 */
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



/**
 * @brief Unsigned Multiply
 * 
 * Multiplies the 8-bit value in X (index register low) by the 8-bit value
 * in the accumulator to obtain a 16-bit unsigned result in the concatenated
 * index register and accumulator.
 * 
 * After the operation, X contains the upper eight bits of the 16-bit
 * result and A contains the lower eight bits of the result.
 * 
 * CCR:
 *  H: 0
 *  C: 0
 */
void M6808::MUL() {
	uint16_t product = (uint16_t)registers.A * (uint16_t)registers.X;

	registers.A = (uint8_t)product;
	registers.X = product >> 8;
	registers.CCR.C = 0;
	registers.CCR.H = 0;
	registers.PC++;
};



/**
 * @brief Negate (Two’s Complement)
 * 
 * Replaces the contents of A, X, or M with its two’s complement.
 * 
 * Note: the value $80 is left unchanged
 * 
 * CCR:
 *  V: M7&R7
 *  N: R7
 *  Z: R==0
 *  C: A/M/X was 0 before the operation
 */
void M6808::NEG() {
    uint8_t* pNumber = GetReadModifyWriteOperand();

    registers.CCR.C = *pNumber != 0;

    uint8_t m7 = *pNumber >> 7;

    *pNumber = (uint8_t)(-1 * (*pNumber));

    registers.CCR.Z = *pNumber == 0;
    registers.CCR.N = ((int8_t)*pNumber) < 0;
    registers.CCR.V = *pNumber >> 7 && m7;
};