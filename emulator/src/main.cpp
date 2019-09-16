#include <stdio.h>
#include "./m6808.hxx"

int main() {
    M6808 processor;

    processor = M6808();

    uint8_t program[] = {
        // MOV #10, 0xF0 (10=1010)
        0x6E, 10, 0xF0,
		// BCLR 3, 0xFo
        0x17, 0xF0,
        // BCLR 1, 0xF0
        0x13, 0xF0,
        // BSET 3, 0xFo
        0x16, 0xF0,
        // BSET 1, 0xF0
        0x12, 0xF0, 
        //WAIT
        0x8F
    };
    
    processor.WriteData(0, program, sizeof(program) / sizeof(uint8_t));

    processor.Execute();

    Registers regs = processor.GetRegisters();

    printf("Program finished after running for %d cycles.\n\n", processor.GetCycleCount());
    printf("Registers:\n-------------\n");
    printf("A:  %d (%x)\n", regs.A, regs.A);
    printf("H:  %d\n", regs.H);
    printf("X:  %d\n", regs.X);
	printf("HX: 0x%02x%02x\n", regs.H, regs.X);
    printf("PC: %x\n", regs.PC);
    printf("SP: %x\n", regs.SP);
}