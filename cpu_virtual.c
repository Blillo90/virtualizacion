#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Memoria y registros
uint8_t memory[256];      // Memoria principal
uint8_t registers[4];     // R0, R1, R2, R3
uint8_t pc = 0;           // Contador de programa (program counter)
bool running = true;

// Definimos opcodes
#define MOV  1
#define ADD  2
#define PRN  3
#define HLT  255

// Mostrar estado actual
void debug_state(uint8_t instr) {
    printf("\n=== Estado CPU ===\n");
    printf("PC: %d\n", pc);
    printf("Instrucción: %d\n", instr);
    for (int i = 0; i < 4; i++) {
        printf("R%d: %d\t", i, registers[i]);
    }
    printf("\nMemoria (0-15): ");
    for (int i = 0; i < 16; i++) {
        printf("%02d ", memory[i]);
    }
    printf("\n==================\n");
}

void run_cpu() {
    while (running) {
        uint8_t instr = memory[pc];  // Obtener instrucción
        debug_state(instr);          // Mostrar estado antes de ejecutarla
        switch (instr) {
            case MOV: {
                uint8_t reg = memory[pc + 1];
                uint8_t val = memory[pc + 2];
                registers[reg] = val;
                pc += 3;
                break;
            }
            case ADD: {
                uint8_t r1 = memory[pc + 1];
                uint8_t r2 = memory[pc + 2];
                registers[r1] += registers[r2];
                pc += 3;
                break;
            }
            case PRN: {
                uint8_t reg = memory[pc + 1];
                printf("R%d = %d\n", reg, registers[reg]);
                pc += 2;
                break;
            }
            case HLT: {
                running = false;
                pc++;
                break;
            }
            default:
                printf("Instrucción desconocida: %d\n", instr);
                running = false;
        }
    }
}

int main() {
    // Cargar programa en memoria
    memory[0] = MOV;  memory[1] = 0; memory[2] = 5;     // R0 = 5
    memory[3] = MOV;  memory[4] = 1; memory[5] = 10;    // R1 = 10
    memory[6] = ADD;  memory[7] = 0; memory[8] = 1;     // R0 = R0 + R1
    memory[9] = PRN;  memory[10] = 0;                   // Print R0
    memory[11] = HLT;

    run_cpu();
    return 0;
}
