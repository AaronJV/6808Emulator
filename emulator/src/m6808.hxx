#ifndef M6808_H
#define M6808_H
#pragma once
#include <stdint.h>

#define _ 0
#define MEM_SIZE 0xFFFF

#ifdef __EMSCRIPTEN__
typedef int memory_ptr;
#else
typedef uint8_t* memory_ptr;
#endif

typedef struct ConditionCodes {
    uint8_t V; // Two's Compliment Flag
    uint8_t H; // Half-Carry Flag
    uint8_t I; // Interrupt Mask
    uint8_t N; // Negative Flag
    uint8_t Z; // Zero Flag
    uint8_t C; // Carry/Borrow Flag
} ConditionCodes;

typedef struct Registers {
    uint8_t A;   // Accumulator
    uint8_t H;   // Index Register (MSB)
    uint8_t X;   // Index Register (LSB)
    uint16_t SP; // Stack Pointer
    uint16_t PC; // Program Counter
	ConditionCodes CCR; // Condition Code Register
} Registers;

class M6808 {
public:
    typedef void (M6808::*opHandler)();

    M6808();

    Registers GetRegisters();
    int GetCycleCount();
 
    void Step();
    void Execute();

    void WriteData(uint16_t location, memory_ptr dataLocation, uint16_t length);
    void WriteByte(uint16_t location, uint8_t value);

    bool GetStatus();

private:
    static const uint8_t cycles[256];
    static const uint8_t sp_cycles[48];
    static opHandler opTable[256];
    static opHandler sp_opTable[48];

    // *************************************** //
    //             Internal State              //
    // *************************************** //
    int cycleCount;
    Registers registers;
    uint8_t memory[MEM_SIZE];
    bool running;


    // *************************************** //
    //               Opaerations               //
    // *************************************** //

    // Branching
    void BCC();
    void BCS();
    void BEQ();
    void BHCC();
    void BHCS();
    void BHI();
    void BIH();
    void BIL();
    void BLS();
    void BMC();
    void BMI();
    void BMS();
    void BNE();
    void BPL();
    void BRA();
    void BRN();
    void BRCLR();
    void BRSET();

    // Read/Modify/Write
    void ASR();
    void CBEQ();
    void CLR();
    void COM();
    void CPHX();
    void DAA();
    void DBNZ();
    void DEC();
    void DIV();
    void INC();
    void LDHX();
    void LSL();
    void LSR();
    void MOV();
    void MUL();
    void NEG();
    void NSA();
    void ROL();
    void ROR();
    void STHX();
    void TST();
    void BCLR();
    void BSET();

    // Control
    void BGE();
    void BGT();
    void BLE();
    void BLT();
    void CLC();
    void CLI();
    void NOP();
    void PSH();
    void PUL();
    void RSP();
    void RTI();
    void RTS();
    void SEC();
    void SEI();
    void STOP();
    void SWI();
    void TAP();
    void TAX();
    void TPA();
    void TSX();
    void TXA();
    void TXS();
    void WAIT();

    // Register/Memory
    void SUB();
    void CMP();
    void SBC();
    void CPX();
    void AND();
    void BIT();
    void LDA();
    void AIS();
    void STA();
    void EOR();
    void ADC();
    void ORA();
    void ADD();
    void JMP();
    void BSR();
    void JSR();
    void LDX();
    void AIX();
    void STX();


    // invalid operation
    void FAIL();


	// helper methods
	uint8_t GetRegisterMemoryAddress();
	uint8_t GetRegisterMemoryOperand();
	uint8_t* GetReadModifyWriteOperand();
	uint8_t* GetReadModifyWriteOperand(uint8_t opCode, bool useStackPointer);
};

#endif




