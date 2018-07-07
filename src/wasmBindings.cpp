#ifdef __EMSCRIPTEN__ 
#include <emscripten/bind.h>
#include "m6808.hxx"


EMSCRIPTEN_BINDINGS(M6808) {
    // Define CPU Type
    emscripten::class_<M6808>("M6808")
        .constructor<>()
        .function("Execute", &M6808::Execute)
        .function("Step", &M6808::Step)
        .function("GetRegisters", &M6808::GetRegisters)
        .function("GetCycleCount", &M6808::GetCycleCount)
        .function("WriteByte", &M6808::WriteByte)
        .function("GetStatus", &M6808::GetStatus);

    // Define Registers Type
    emscripten::value_object<Registers>("Registers")
        .field("A", &Registers::A)      // Accumulator
        .field("H", &Registers::H)      // Index Register (MSB)
        .field("X", &Registers::X)      // Index Register (LSB)
        .field("SP", &Registers::SP)    // Stack Pointer
        .field("PC", &Registers::PC)    // Program Counter
        .field("CCR", &Registers::CCR); // Condition Code Register

    // // Define ConditionCodes Type
    emscripten::value_object<ConditionCodes>("ConditionCodes")
        .field("V", &ConditionCodes::V) // Two's Compliment Flag
        .field("H", &ConditionCodes::H) // Half-Carry Flag
        .field("I", &ConditionCodes::I) // Interrupt Mask
        .field("N", &ConditionCodes::N) // Negative Flag
        .field("Z", &ConditionCodes::Z) // Zero Flag
        .field("C", &ConditionCodes::C); // Carry/Borrow Flag
}

#endif // __EMSCRIPTEN__