import re

emptyOpcodes = [0xd3, 0xe3, 0xe4, 0xf4, 0xdb, 0xeb, 0xec, 0xfc, 0xdd, 0xed, 0xfd]

def readLines(fileC):
  info = []
  opcode = 0
  with open(fileC , 'r') as f:
    while True:
      lines = []
      for i in range(3):
        try:
          lines.append(f.next())
        except StopIteration:
          return info
      
      for i in range(3):
        lines[i] = lines[i].replace("\n","")

      mnemonic = lines[0]

      lenght = re.findall("\d+", lines[1])[0]
      cycles = re.findall("\d+", lines[1])[1]

      lines[2] = lines[2].replace(" ", "")
      Z = lines[2][0]
      N = lines[2][1]
      H = lines[2][2]
      C = lines[2][3]

      info.append({"opcode" : opcode, "mnemonic" : mnemonic, "lenght" : lenght, "cycles" : cycles, "flags" : lines[2]})

      opcode = opcode + 1
      while opcode in emptyOpcodes:
        opcode = opcode + 1

  return info

  #Z N H C


info = readLines("mnemonics.txt")

for mnemonic in info:
  line = ("%s, \"%s\", %s, %s, \"%s\"," % (hex(int(mnemonic["opcode"])), mnemonic["mnemonic"], mnemonic["lenght"], mnemonic["cycles"], mnemonic["flags"]))
  print line
