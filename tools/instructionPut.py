with open("instructions.txt") as f:
    content = f.readlines()
    instrL = []
    for line in content:
      if ";" in line:
        instr = line.split(";")[0]
        instr = instr.replace(" ", "")
        instr = instr.replace("()", "")
        instr = instr.replace("void", "")
        nr = line.split("/")[2]
        nr = nr.rstrip("\n")
        print("opcodes[%s] = std::bind(&Cpu::%s, this);" % (nr, instr))

        instrL.append(nr)

    missingInstrL = []
    for x in range(0, len(instrL)):
      if str(x) not in instrL[x]:
        missingInstrL.append(instrL[x])
    print("missing instructions: " + str(len(missingInstrL)))
    print(missingInstrL)
