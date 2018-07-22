let m;

function load6808() {
    m = new Module.M6808();
    
    // Create example data to test float_multiply_array
    const program = new Uint8Array([
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
        // CLC
        0x98,
        // NEG 0xF0
        0x30, 0xF0,
        // LDX 0xF0
        0xAE, 0xF0,
        // ADD ,X
        0xFB
    ]);

    var dataPtr = Module._malloc(program.length);
    
    // Copy data to heap
    var dataHeap = new Uint8Array(Module.HEAPU8.buffer, dataPtr, program.length);
    dataHeap.set(new Uint8Array(program.buffer));
    
    m.WriteData(0, dataHeap.byteOffset, program.length)
    // Free memory
    Module._free(dataHeap.byteOffset);

    displayState();
}


const waitForWasm = setInterval(function() {
    if (Module.M6808 !== undefined) {
        load6808();
        document.getElementById('step').disabled = false;
        clearInterval(waitForWasm);
    }
}, 100);


function toHex(number, length) {
    const str = number.toString(16).toUpperCase();
    
    return "0x" + "0".repeat(length - str.length) + str;
}

function displayState() {
    const regs = m.GetRegisters();
    
    document.getElementById('A').innerText = regs.A;
    document.getElementById('A_hex').innerText = toHex(regs.A, 2);

    document.getElementById('H').innerText = regs.H;
    document.getElementById('H_hex').innerText = toHex(regs.H, 2);

    document.getElementById('X').innerText = regs.X;
    document.getElementById('X_hex').innerText = toHex(regs.X, 2);

    document.getElementById('HX').innerText = toHex(regs.H << 8 | regs.X, 4);

    document.getElementById('PC').innerText = toHex(regs.PC, 4);
    document.getElementById('SP').innerText = toHex(regs.SP, 4);

    document.getElementById('CCR_V').innerText = regs.CCR.V;
    document.getElementById('CCR_H').innerText = regs.CCR.H;
    document.getElementById('CCR_I').innerText = regs.CCR.I;
    document.getElementById('CCR_N').innerText = regs.CCR.N;
    document.getElementById('CCR_Z').innerText = regs.CCR.Z;
    document.getElementById('CCR_C').innerText = regs.CCR.C;
    
    document.getElementById('cycles').innerText = m.GetCycleCount();
    
    document.getElementById('running').checked = m.GetStatus();
}

function step() {
    m.Step();
    displayState();
}