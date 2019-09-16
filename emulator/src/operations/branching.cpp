#include "../m6808.hxx"

void M6808::BCC() {
    FAIL();
};

void M6808::BCS() {
    FAIL();
};

void M6808::BEQ() {
    FAIL();
};

void M6808::CBEQ() {
    FAIL();
};


void M6808::DBNZ() {
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



void M6808::JMP() {
    FAIL();
};

void M6808::BSR() {
    FAIL();
};

void M6808::JSR() {
    FAIL();
};


/**
 * @brief Branch if Bit n in Memory Clear
 * 
 * Tests bit n (n = 7, 6, 5, … 0) of location M and branches if the bit is clear
 * 
 * CCR:
 *  - C: Set if Mn = 1; cleared otherwise
 */
void M6808::BRCLR() {
    FAIL();
};

/**
 * @brief Branch if Bit n in Memory Set
 * 
 * Tests bit n (n = 7, 6, 5, … 0) of location M and branches if the bit is set
 * 
 * CCR:
 *  - C: Set if Mn = 1; cleared otherwise
 */
void M6808::BRSET() {
    FAIL();
};