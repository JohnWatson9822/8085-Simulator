#include <iostream>
#include <vector>
#include <iomanip>

// Define Registers
uint8_t A = 0;  // Accumulator
uint8_t B = 0, C = 0;  // BC register pair
uint8_t D = 0, E = 0;  // DE register pair
uint8_t H = 0, L = 0;  // HL register pair
uint16_t SP = 0xFFFF;  // Stack Pointer
uint16_t PC = 0;  // Program Counter

// Memory
std::vector<uint8_t> memory(0x10000, 0);  // 64 KB memory

// Print Registers
void printRegisters() {
    std::cout << "Registers: A=" << std::hex << (int)A << " "
        << "B=" << (int)B << " C=" << (int)C << " "
        << "D=" << (int)D << " E=" << (int)E << " "
        << "H=" << (int)H << " L=" << (int)L << " "
        << "Flags=" << "00000000 " // Assume no flags for simplicity
        << "PC=" << std::hex << PC << std::dec << std::endl;
}

// Update Flags (for simplicity, we will not handle flags in this example)
void updateFlags(uint8_t result) {
    // Update flags based on the result (e.g., Zero, Carry, Sign, Parity, etc.)
    // For simplicity, this is left as a placeholder
}

// Decode and Execute Instructions
void decodeAndExecute(uint8_t opcode) {
    uint8_t low = 0, high = 0;
    uint16_t address = 0;

    std::cout << "Executing Opcode: " << std::hex << (int)opcode << std::dec << std::endl;

    switch (opcode) {
        // Data Transfer Instructions
    case 0x78:  // MOV A, B
        std::cout << "MOV A, B" << std::endl;
        A = B;
        break;
    case 0x79:  // MOV A, C
        std::cout << "MOV A, C" << std::endl;
        A = C;
        break;
    case 0x7A:  // MOV A, D
        std::cout << "MOV A, D" << std::endl;
        A = D;
        break;
    case 0x7B:  // MOV A, E
        std::cout << "MOV A, E" << std::endl;
        A = E;
        break;
    case 0x7C:  // MOV A, H
        std::cout << "MOV A, H" << std::endl;
        A = H;
        break;
    case 0x7D:  // MOV A, L
        std::cout << "MOV A, L" << std::endl;
        A = L;
        break;
    case 0x47:  // MOV B, A
        std::cout << "MOV B, A" << std::endl;
        B = A;
        break;
    case 0x4F:  // MOV C, A
        std::cout << "MOV C, A" << std::endl;
        C = A;
        break;
    case 0x57:  // MOV D, A
        std::cout << "MOV D, A" << std::endl;
        D = A;
        break;
    case 0x5F:  // MOV E, A
        std::cout << "MOV E, A" << std::endl;
        E = A;
        break;
    case 0x67:  // MOV H, A
        std::cout << "MOV H, A" << std::endl;
        H = A;
        break;
    case 0x6F:  // MOV L, A
        std::cout << "MOV L, A" << std::endl;
        L = A;
        break;
    case 0x7E:  // MOV A, M (from memory at HL)
        std::cout << "MOV A, M" << std::endl;
        A = memory[(H << 8) | L];
        break;
    case 0x77:  // MOV M, A (to memory at HL)
        std::cout << "MOV M, A" << std::endl;
        memory[(H << 8) | L] = A;
        break;

        // Arithmetic Instructions
    case 0x80:  // ADD B
        std::cout << "ADD B" << std::endl;
        A += B;
        updateFlags(A);
        break;
    case 0x81:  // ADD C
        std::cout << "ADD C" << std::endl;
        A += C;
        updateFlags(A);
        break;
    case 0x82:  // ADD D
        std::cout << "ADD D" << std::endl;
        A += D;
        updateFlags(A);
        break;
    case 0x83:  // ADD E
        std::cout << "ADD E" << std::endl;
        A += E;
        updateFlags(A);
        break;
    case 0x84:  // ADD H
        std::cout << "ADD H" << std::endl;
        A += H;
        updateFlags(A);
        break;
    case 0x85:  // ADD L
        std::cout << "ADD L" << std::endl;
        A += L;
        updateFlags(A);
        break;
    case 0x87:  // ADD A
        std::cout << "ADD A" << std::endl;
        A += A;
        updateFlags(A);
        break;

    case 0x90:  // SUB B
        std::cout << "SUB B" << std::endl;
        A -= B;
        updateFlags(A);
        break;
    case 0x91:  // SUB C
        std::cout << "SUB C" << std::endl;
        A -= C;
        updateFlags(A);
        break;
    case 0x92:  // SUB D
        std::cout << "SUB D" << std::endl;
        A -= D;
        updateFlags(A);
        break;
    case 0x93:  // SUB E
        std::cout << "SUB E" << std::endl;
        A -= E;
        updateFlags(A);
        break;
    case 0x94:  // SUB H
        std::cout << "SUB H" << std::endl;
        A -= H;
        updateFlags(A);
        break;
    case 0x95:  // SUB L
        std::cout << "SUB L" << std::endl;
        A -= L;
        updateFlags(A);
        break;
    case 0x97:  // SUB A
        std::cout << "SUB A" << std::endl;
        A -= A;
        updateFlags(A);
        break;

        // Jump Instructions
    case 0xC3:  // JMP address
        low = memory[PC++];
        high = memory[PC++];
        address = (high << 8) | low;
        std::cout << "JMP to address: " << std::hex << address << std::dec << std::endl;
        PC = address;  // Jump to the address
        break;

        // Stack Instructions
    case 0xC5:  // PUSH B
        std::cout << "PUSH B" << std::endl;
        memory[--SP] = B;
        memory[--SP] = C;
        break;
    case 0xD5:  // PUSH D
        std::cout << "PUSH D" << std::endl;
        memory[--SP] = D;
        memory[--SP] = E;
        break;

    case 0xC1:  // POP B
        std::cout << "POP B" << std::endl;
        C = memory[SP++];
        B = memory[SP++];
        break;
    case 0xD1:  // POP D
        std::cout << "POP D" << std::endl;
        E = memory[SP++];
        D = memory[SP++];
        break;

    case 0xC9:  // RET
        std::cout << "RET" << std::endl;
        low = memory[SP++];
        high = memory[SP++];
        PC = (high << 8) | low;
        break;

        // Halt instruction
    case 0x76:  // HLT
        std::cout << "HLT" << std::endl;
        std::exit(0);  // Halt the program

    default:
        std::cout << "Unknown opcode: " << std::hex << (int)opcode << std::dec << std::endl;
        break;
    }

    // Increment Program Counter to the next opcode
    PC++;
}

int main() {
    // Initialize memory with some example instructions
    memory[0] = 0x06;  // MVI B, 0x05
    memory[1] = 0x05;  // Data byte for MVI B
    memory[2] = 0x80;  // ADD B
    memory[3] = 0xC3;  // JMP to 0x0000
    memory[4] = 0x00;  // Low byte for address
    memory[5] = 0x00;  // High byte for address
    memory[6] = 0x76;  // HLT

    // Execute instructions starting at address 0x00
    while (PC < 6) {  // End the program after executing the instructions
        uint8_t opcode = memory[PC];
        decodeAndExecute(opcode);
        printRegisters();  // Print register status after every instruction
    }

    return 0;
}
