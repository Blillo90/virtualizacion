import yaml

# Mapeo de nombres a registros
reg_map = {
    "a": 0,
    "b": 1,
    "c": 2,
    "d": 3
}

def traducir_linea(linea):
    partes = linea.strip().split()
    if not partes or partes[0].startswith("#"):
        return None

    comando = partes[0]

    if comando == "set":
        return {"instr": "MOV", "reg": reg_map[partes[1]], "val": int(partes[2])}
    elif comando == "sum":
        return {"instr": "ADD", "r1": reg_map[partes[1]], "r2": reg_map[partes[2]]}
    elif comando == "sub":
        return {"instr": "SUB", "r1": reg_map[partes[1]], "r2": reg_map[partes[2]]}
    elif comando == "print":
        return {"instr": "PRN", "reg": reg_map[partes[1]]}
    elif comando == "store":
        return {"instr": "STORE", "reg": reg_map[partes[1]], "addr": int(partes[2])}
    elif comando == "load":
        return {"instr": "LOAD", "reg": reg_map[partes[1]], "addr": int(partes[2])}
    elif comando == "halt":
        return {"instr": "HLT"}
    else:
        raise Exception(f"Instrucción desconocida: {linea}")

def main():
    instrucciones = []

    with open("programa.txt", "r") as f:
        for linea in f:
            instruccion = traducir_linea(linea)
            if instruccion:
                instrucciones.append(instruccion)

    with open("programa.yaml", "w") as out:
        yaml.dump(instrucciones, out)

    print("✔️ Traducción completa. Archivo generado: programa.yaml")

if __name__ == "__main__":
    main()
