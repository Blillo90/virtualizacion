import yaml

# Opcodes según tu CPU
OPCODES = {
    "MOV": 1,
    "ADD": 2,
    "PRN": 3,
    "HLT": 255,
    "SUB": 4,
    "CMP": 5,
    "JEQ": 6,
    "JMP": 7,
    "STORE": 8,
    "LOAD": 9
}

def instruccion_a_opcodes(instr):
    op = instr["instr"]
    if op == "MOV":
        return [OPCODES[op], instr["reg"], instr["val"]]
    elif op in ["ADD", "SUB", "CMP"]:
        return [OPCODES[op], instr["r1"], instr["r2"]]
    elif op in ["JEQ", "JMP"]:
        return [OPCODES[op], instr["addr"]]
    elif op in ["PRN", "LOAD", "STORE"]:
        if op == "PRN":
            return [OPCODES[op], instr["reg"]]
        else:
            return [OPCODES[op], instr["reg"], instr["addr"]]
    elif op == "HLT":
        return [OPCODES[op]]
    else:
        raise Exception(f"Instrucción desconocida: {op}")

def main():
    with open("programa.yaml", "r") as f:
        instrucciones = yaml.safe_load(f)

    bytes_programa = []

    for instr in instrucciones:
        bytes_programa.extend(instruccion_a_opcodes(instr))

    with open("programa.bin", "wb") as binario:
        binario.write(bytes(bytearray(bytes_programa)))

    print("✅ Binario generado: programa.bin")

if __name__ == "__main__":
    main()
