#include "../m6808.hxx"
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
    running = false;
    registers.PC++;
    registers.CCR.I = 0;
}
