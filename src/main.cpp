#include <stdio.h>
#include "./m6808.hxx"

int main() {
    M6808 processor;

    processor = M6808();

    uint8_t program[] = {
		// MOV #10, 0xF0
		0x6E, 10, 0xF0,

		// LDA #3
		0xA6, 3,

		// STA 0xF1,X
		0xE7, 0xF1,

		// LDA #0
		0xA6, 0,

        // ADC #127
        0xA9, 127,

        // ADC 0xF0
        0xB9, 0xF0,

        // NOP
        0x9D,

        // INCA
        0x4C,

        // SUB #5
        0xA0, 5,

        // SUB 0xF1
        0xB0, 0xF1,

        // SEC
        0x99,

        // CEC
        0x98,

        // NEG 0xF0
        0x30, 0xF0,

		// LDX 0xF0
		0xAE, 0xF0,

        // ADD ,X
        0xFB
    };
    
    processor.WriteData(0, (int)program, sizeof(program) / sizeof(uint8_t));

    processor.Execute();

    Registers regs = processor.GetRegisters();

    printf("A:  %d\n", regs.A);
    printf("H:  %d\n", regs.H);
    printf("X:  %d\n", regs.X);
	printf("HX: 0x%02x%02x\n", regs.H, regs.X);
    printf("PC: %x\n", regs.PC);
    printf("SP: %x\n", regs.SP);

	getchar();
}