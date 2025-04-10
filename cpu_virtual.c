#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MEM_SIZE 256

// Memoria y registros
uint8_t memory[MEM_SIZE];
uint8_t registers[4];
uint8_t pc = 0;
bool running = true;
uint8_t flag_zero = 0;

// Opcodes
#define MOV   1
#define ADD   2
#define PRN   3
#define HLT   255
#define SUB   4
#define CMP   5
#define JEQ   6
#define JMP   7
#define STORE 8
#define LOAD  9

void debug_state(uint8_t instr) {
    printf("\n=== Estado CPU ===\n");
    printf("PC: %d\n", pc);
    printf("Instrucción: %d\n", instr);
    printf("Registros: ");
    for (int i = 0; i < 4; i++) {
        printf("R%d=%d ", i, registers[i]);
    }
    printf("\nFlag Zero: %d\n", flag_zero);
    printf("Memoria (0-15): ");
    for (int i = 0; i < 16; i++) {
        printf("%02d ", memory[i]);
    }
    printf("\n==================\n");
}

void run_cpu() {
    while (running) {
        uint8_t instr = memory[pc];
        debug_state(instr);
        switch (instr) {
            case MOV: {
                uint8_t r = memory[pc + 1];
                uint8_t val = memory[pc + 2];
                registers[r] = val;
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
            case SUB: {
                uint8_t r1 = memory[pc + 1];
                uint8_t r2 = memory[pc + 2];
                registers[r1] -= registers[r2];
                pc += 3;
                break;
            }
            case CMP: {
                uint8_t r1 = memory[pc + 1];
                uint8_t r2 = memory[pc + 2];
                flag_zero = (registers[r1] == registers[r2]) ? 1 : 0;
                pc += 3;
                break;
            }
            case JEQ: {
                uint8_t addr = memory[pc + 1];
                if (flag_zero == 1)
                    pc = addr;
                else
                    pc += 2;
                break;
            }
            case JMP: {
                uint8_t addr = memory[pc + 1];
                pc = addr;
                break;
            }
            case STORE: {
                uint8_t reg = memory[pc + 1];
                uint8_t addr = memory[pc + 2];
                memory[addr] = registers[reg];
                pc += 3;
                break;
            }
            case LOAD: {
                uint8_t reg = memory[pc + 1];
                uint8_t addr = memory[pc + 2];
                registers[reg] = memory[addr];
                pc += 3;
                break;
            }
            case PRN: {
                uint8_t r = memory[pc + 1];
                printf("Salida R%d: %d\n", r, registers[r]);
                pc += 2;
                break;
            }
            case HLT: {
                running = false;
                pc += 1;
                break;
            }
            default:
                printf("Instrucción desconocida: %d\n", instr);
                running = false;
        }
    }
}
