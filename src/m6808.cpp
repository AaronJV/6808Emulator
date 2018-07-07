#include "./m6808.hxx"
#include <string.h>

const uint8_t M6808::cycles[] = {
         /*0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F*/
    /*0*/  5, 4, 3, 4, 1, 1, 4, 3, 7, 3, 2, 3, 4, 4, 3, 2,
    /*1*/  5, 4, 3, 5, 4, 4, 5, 4, 4, 3, 2, 3, 4, 4, 3, 2,
    /*2*/  5, 4, 3, _, 5, 7, 3, 2, _, 3, 2, 3, 4, 4, 3, 2,
    /*3*/  5, 4, 3, 4, 1, 1, 4, 3, 9, 3, 2, 3, 4, 4, 3, 2,
    /*4*/  5, 4, 3, 4, 1, 1, 4, 3, 2, 2, 2, 3, 4, 4, 4, 2, 
    /*5*/  5, 4, 3, 4, 3, 4, 3, 4, 1, 2, 2, 3, 4, 4, 3, 2,
    /*6*/  5, 4, 3, 4, 1, 1, 4, 3, 2, _, 2, 3, 4, 4, 3, 2,
    /*7*/  5, 4, 3, 4, 1, 1, 4, 3, 2, 1, 2, 3, 4, 4, 3, 2,
    /*8*/  5, 4, 3, 4, 1, 1, 4, 3, 2, 1, 2, 3, 4, 4, 3, 2,
    /*9*/  5, 4, 3, 4, 1, 1, 4, 3, 2, 1, 2, 3, 4, 4, 3, 2,
    /*A*/  5, 4, 3, 4, 1, 1, 4, 3, 2, 2, 2, 3, 4, 4, 3, 2,
    /*B*/  5, 4, 3, 5, 3, 3, 5, 4, 2, 2, 2, 3, 4, 4, 3, 2,
    /*C*/  5, 4, 3, 4, 1, 1, 4, 3, 1, 1, _, 2, 3, 4, 3, 2,
    /*D*/  5, 4, 3, 3, 1, 1, 3, 2, _, 1, 4, 4, 5, 6, 5, 4,
    /*E*/  5, 4, 3, _, 5, 4, 4, 4, 1, _, 2, 3, 4, 4, 3, 2,
    /*F*/  5, 4, 3, 3, 1, 1, 3, 2, 1, 1, 2, 3, 4, 4, 3, 2
};


const uint8_t M6808::sp_cycles[] = {
         /*6  D  E*/
    /*0*/  5, 5, 4,
    /*1*/  6, 5, 4,
    /*2*/  _, 5, 4,
    /*3*/  5, 5, 4,
    /*4*/  5, 5, 4,
    /*5*/  _, 5, 4,
    /*6*/  5, 5, 4,
    /*7*/  5, 5, 4,
    /*8*/  5, 5, 4,
    /*9*/  5, 5, 4,
    /*A*/  5, 5, 4,
    /*B*/  6, 5, 4,
    /*C*/  5, _, _,
    /*D*/  4, _, _,
    /*E*/  _, 5, 4,
    /*F*/  4, 5, 4
};

// const M6808::opHandler M6808::opTable[] = {};

M6808::opHandler M6808::opTable[] = {
         /*           0             1             2             3             4             5             6             7             8             9             A            B            C            D            E             F*/
    /*0*/ &M6808::BRSET, &M6808::BSET,  &M6808::BRA,  &M6808::NEG,  &M6808::NEG,  &M6808::NEG,  &M6808::NEG,  &M6808::NEG,  &M6808::RTI,  &M6808::BGE,  &M6808::SUB, &M6808::SUB, &M6808::SUB, &M6808::SUB, &M6808::SUB,  &M6808::SUB,
    /*1*/ &M6808::BRCLR, &M6808::BCLR,  &M6808::BRN, &M6808::CBEQ, &M6808::CBEQ, &M6808::CBEQ, &M6808::CBEQ, &M6808::CBEQ,  &M6808::RTS,  &M6808::BLT,  &M6808::CMP, &M6808::CMP, &M6808::CMP, &M6808::CMP, &M6808::CMP,  &M6808::CMP,
    /*2*/ &M6808::BRSET, &M6808::BSET,  &M6808::BHI, &M6808::FAIL,  &M6808::MUL,  &M6808::DIV,  &M6808::NSA,  &M6808::DAA, &M6808::FAIL,  &M6808::BGT,  &M6808::SBC, &M6808::SBC, &M6808::SBC, &M6808::SBC, &M6808::SBC,  &M6808::SBC,
    /*3*/ &M6808::BRCLR, &M6808::BCLR,  &M6808::BLS,  &M6808::COM,  &M6808::COM,  &M6808::COM,  &M6808::COM,  &M6808::COM,  &M6808::SWI,  &M6808::BLE,  &M6808::CPX, &M6808::CPX, &M6808::CPX, &M6808::CPX, &M6808::CPX,  &M6808::CPX,
    /*4*/ &M6808::BRSET, &M6808::BSET,  &M6808::BCC,  &M6808::LSR,  &M6808::LSR,  &M6808::LSR,  &M6808::LSR,  &M6808::LSR,  &M6808::TAP,  &M6808::TXS,  &M6808::AND, &M6808::AND, &M6808::AND, &M6808::AND, &M6808::AND,  &M6808::AND,
    /*5*/ &M6808::BRCLR, &M6808::BCLR,  &M6808::BCS, &M6808::STHX, &M6808::LDHX, &M6808::LDHX, &M6808::CPHX, &M6808::CPHX,  &M6808::TPA,  &M6808::TSX,  &M6808::BIT, &M6808::BIT, &M6808::BIT, &M6808::BIT, &M6808::BIT,  &M6808::BIT,
    /*6*/ &M6808::BRSET, &M6808::BSET,  &M6808::BNE,  &M6808::ROR,  &M6808::ROR,  &M6808::ROR,  &M6808::ROR,  &M6808::ROR,  &M6808::PUL, &M6808::FAIL,  &M6808::LDA, &M6808::LDA, &M6808::LDA, &M6808::LDA, &M6808::LDA,  &M6808::LDA,
    /*7*/ &M6808::BRCLR, &M6808::BCLR,  &M6808::BEQ,  &M6808::ASR,  &M6808::ASR,  &M6808::ASR,  &M6808::ASR,  &M6808::ASR,  &M6808::PSH,  &M6808::TAX,  &M6808::AIS, &M6808::STA, &M6808::STA, &M6808::STA, &M6808::STA,  &M6808::STA,
    /*8*/ &M6808::BRSET, &M6808::BSET, &M6808::BHCC,  &M6808::LSL,  &M6808::LSL,  &M6808::LSL,  &M6808::LSL,  &M6808::LSL,  &M6808::PUL,  &M6808::CLC,  &M6808::EOR, &M6808::EOR, &M6808::EOR, &M6808::EOR, &M6808::EOR,  &M6808::EOR,
    /*9*/ &M6808::BRCLR, &M6808::BCLR, &M6808::BHCS,  &M6808::ROL,  &M6808::ROL,  &M6808::ROL,  &M6808::ROL,  &M6808::ROL,  &M6808::PSH,  &M6808::SEC,  &M6808::ADC, &M6808::ADC, &M6808::ADC, &M6808::ADC, &M6808::ADC,  &M6808::ADC,
    /*A*/ &M6808::BRSET, &M6808::BSET,  &M6808::BPL,  &M6808::DEC,  &M6808::DEC,  &M6808::DEC,  &M6808::DEC,  &M6808::DEC,  &M6808::PUL,  &M6808::CLI,  &M6808::ORA, &M6808::ORA, &M6808::ORA, &M6808::ORA, &M6808::ORA,  &M6808::ORA,
    /*B*/ &M6808::BRCLR, &M6808::BCLR,  &M6808::BMI, &M6808::DBNZ, &M6808::DBNZ, &M6808::DBNZ, &M6808::DBNZ, &M6808::DBNZ,  &M6808::PSH,  &M6808::SEI,  &M6808::ADD, &M6808::ADD, &M6808::ADD, &M6808::ADD, &M6808::ADD,  &M6808::ADD,
    /*C*/ &M6808::BRSET, &M6808::BSET,  &M6808::BMC,  &M6808::INC,  &M6808::INC,  &M6808::INC,  &M6808::INC,  &M6808::INC,  &M6808::CLR,  &M6808::RSP, &M6808::FAIL, &M6808::JMP, &M6808::JMP, &M6808::JMP, &M6808::JMP, &M6808::FAIL,
    /*D*/ &M6808::BRCLR, &M6808::BCLR,  &M6808::BMS,  &M6808::TST,  &M6808::TST,  &M6808::TST,  &M6808::TST,  &M6808::TST, &M6808::FAIL,  &M6808::NOP,  &M6808::BSR, &M6808::JSR, &M6808::JSR, &M6808::JSR, &M6808::JSR, &M6808::FAIL,
    /*E*/ &M6808::BRSET, &M6808::BSET,  &M6808::BIL, &M6808::FAIL,  &M6808::MOV,  &M6808::MOV,  &M6808::MOV,  &M6808::MOV, &M6808::STOP, &M6808::FAIL,  &M6808::LDX, &M6808::LDX, &M6808::LDX, &M6808::LDX, &M6808::LDX,  &M6808::LDX,
    /*F*/ &M6808::BRCLR, &M6808::BCLR,  &M6808::BIH,  &M6808::CLR,  &M6808::CLR,  &M6808::CLR,  &M6808::CLR,  &M6808::CLR, &M6808::WAIT,  &M6808::TXA,  &M6808::AIX, &M6808::STX, &M6808::STX, &M6808::STX, &M6808::STX,  &M6808::STX
};

M6808::opHandler M6808::sp_opTable[] = {
         /*          6             D            E*/
    /*0*/  &M6808::NEG,  &M6808::SUB, &M6808::SUB,
    /*1*/ &M6808::CBEQ,  &M6808::CMP, &M6808::CMP,
    /*2*/ &M6808::FAIL,  &M6808::SBC, &M6808::SBC,
    /*3*/  &M6808::COM,  &M6808::CPX, &M6808::CPX,
    /*4*/  &M6808::LSR,  &M6808::AND, &M6808::AND,
    /*5*/ &M6808::FAIL,  &M6808::BIT, &M6808::BIT,
    /*6*/  &M6808::ROR,  &M6808::LDA, &M6808::LDA,
    /*7*/  &M6808::ASR,  &M6808::STA, &M6808::STA,
    /*8*/  &M6808::LSL,  &M6808::EOR, &M6808::EOR,
    /*9*/  &M6808::ROL,  &M6808::ADC, &M6808::ADC,
    /*A*/  &M6808::DEC,  &M6808::ORA, &M6808::ORA,
    /*B*/ &M6808::DBNZ,  &M6808::ADD, &M6808::ADD,
    /*C*/  &M6808::INC, &M6808::FAIL, &M6808::JMP,
    /*D*/  &M6808::TST, &M6808::FAIL, &M6808::JSR,
    /*E*/ &M6808::FAIL,  &M6808::LDX, &M6808::LDX,
    /*F*/  &M6808::CLR,  &M6808::STX, &M6808::STX
};



/**
 * executes the program stored in the ROM,
 **/
void M6808::Execute() {
    while (running) {
        // load opCode
        uint8_t opCode = memory[registers.PC];
        bool spMode = opCode == 0x9E;

        if (spMode) {
            opCode = memory[registers.PC + 1];
        }

        if (!spMode) {
            opCode = ((opCode & 0x0F) << 4) | ((opCode & 0xF0) >> 4);
            (this->*opTable[opCode])();

            if (running) {
                cycleCount += cycles[opCode];
            }
        } else {
            uint8_t row = (opCode & 0xF0) >> 4;
            uint8_t col = (opCode & 0x0F) << 4;

            if (col == 6) {
                col = 0;
            } else if (col == 0xD) {
                col = 1;
            } else if (col == 0xE) {
                col = 2;
            } else {
                FAIL();
            }

            uint8_t pos = col + 3 * row;

            if (running) {
                (this->*sp_opTable[pos])();
            }

            if (running) {
                cycleCount += sp_cycles[pos];
            }
        }
    }
};


void M6808::Step() {
    if (running) {
        // load opCode
        uint8_t opCode = memory[registers.PC];
        bool spMode = opCode == 0x9E;

        if (spMode) {
            opCode = memory[registers.PC + 1];
        }

        if (!spMode) {
            opCode = ((opCode & 0x0F) << 4) | ((opCode & 0xF0) >> 4);
            (this->*opTable[opCode])();

            if (running) {
                cycleCount += cycles[opCode];
            }
        } else {
            uint8_t row = (opCode & 0xF0) >> 4;
            uint8_t col = (opCode & 0x0F) << 4;

            if (col == 6) {
                col = 0;
            } else if (col == 0xD) {
                col = 1;
            } else if (col == 0xE) {
                col = 2;
            } else {
                FAIL();
            }

            uint8_t pos = col + 3 * row;

            if (running) {
                (this->*sp_opTable[pos])();
            }

            if (running) {
                cycleCount += sp_cycles[pos];
            }
        }
    }
}



void M6808::WriteData(uint16_t location, uint8_t* data, uint16_t length) {
    uint16_t len = length;

    if (len + location > MEM_SIZE) {
        len = MEM_SIZE - location;
    }

    memcpy(memory + location, data, len);
}


void M6808::WriteByte(uint16_t location, uint8_t value) {
    memory[location] = value;
}



void M6808::FAIL() {
    running = false;
}


Registers M6808::GetRegisters() {
    return registers;
}

int M6808::GetCycleCount() {
    return cycleCount;
}


M6808::M6808() {
    running = true;
	registers.A = 0;
	registers.H = 0;
	registers.X = 0;
	registers.SP = 0;
	registers.PC = 0;
	registers.CCR.V = 0;
	registers.CCR.H = 0;
	registers.CCR.I = 0;
	registers.CCR.N = 0;
	registers.CCR.Z = 0;
	registers.CCR.C = 0;
}

bool M6808::GetStatus() {
    return running;
}