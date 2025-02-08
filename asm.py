import struct
import sys

DEBUG = True

# 指令集映射
OPCODES = {
    'nop': 0x0,
    'add': 0x1, 'sub': 0x2, 'mul': 0x3, 'div': 0x4,
    'and': 0x5, 'or': 0x6, 'xor': 0x7, 'not': 0x8,
    'uadd': 0x9, 'usub': 0xa, 'umul': 0xb, 'udiv': 0xc,
    'mov': 0xd, 'push': 0xe, 'pop': 0xf, 'num': 0x10,
    'call': 0x11, 'ret': 0x12, 'jmp': 0x13, 'jz': 0x14,
    'jnz': 0x15, 'je': 0x16, 'jne': 0x17, 'jg': 0x18,
    'jge': 0x19, 'jl': 0x1a, 'jle': 0x1b, 'cmp': 0x1c,
    'outstr': 0x1d, 'instr': 0x1e, 'outnum': 0x1f, 'innum': 0x20,
    'mov8' :0x21
}

# 寄存器映射
REGISTERS = {
    'eax': 0, 'ebx': 1, 'ecx': 2, 'edx': 3,
    'esi': 4, 'edi': 5, 'eip': 6, 'esp': 7
}

def main(inputFile,outputFile):
    f = open(inputFile, 'r')
    lines = f.readlines()
    f.close()

    #remove all comment and prefixand suffix in file
    for i in range(len(lines)):
        if '//' in lines[i]:
            lines[i] = lines[i].split('//')[0]
            lines[i] = lines[i].strip()

    functions = []
    functionsName = []
    constants = b''
    constantsAddress = {}
    tags = {}

    #scan functions and save function name 
    for i in range(len(lines)):
        if lines[i].strip() == '':
            continue
        if lines[i][0] == '.':
            functionsName.append(lines[i].strip()[1:])
        if lines[i][0] == '@':
            aliasName = lines[i].split(" ")[0][1:]
            cstr = lines[i].split(" ",1)[1]
            # remove prefix and suffix "
            cstr = cstr.strip()[1:-1]
            # address is current length of constants plus 36(header)
            constantsAddress[aliasName] = len(constants) + 36
            # append cstr to constants
            constants += cstr.encode() + b'\x00'
    
    currentFunction = []
    currentOpcodeAddr = 0
    lineNumber = 0

    # scan opcode and save it
    for i in range(len(lines)):
        lineNumber += 1
        if lines[i].strip() == '':
            continue
        # function tag
        if lines[i].startswith('.'):
            lineNumber = 0
            if currentFunction != []:
                functions.append(currentFunction.copy())
            currentFunction = []
            tags = {}
            opaddr = 0
            for j in range(i+1, len(lines)):
                if lines[j].strip().startswith('.'):
                    break
                if lines[j].strip() == '':
                    continue
                if lines[j].strip().endswith(':'):
                    tags[lines[j].strip()[:-1]] = opaddr
                if ' ' in lines[j].strip():
                    if ',' in lines[j].strip():
                        opaddr += 3
                    else:
                        opaddr += 2
                else:
                    opaddr += 1
            continue
        # tag
        if lines[i].strip().endswith(':'):
            continue
        if lines[i].strip().startswith('@'):
            continue
        # replace \t to spaces
        lines[i] = lines[i].replace('\t',' ')
        # replace multiple spaces to one space util there is no multiple spaces
        while '  ' in lines[i]:
            lines[i] = lines[i].replace('  ',' ')
        lines[i] = lines[i].strip()
        print(lines[i])
        if ' ' in lines[i] :
            opcode = lines[i].strip().split(' ')[0]
            args = lines[i].strip().split(' ',1)[1]
            if ',' in args:
                arg1 = args.split(',')[0].strip()
                arg2 = args.split(',')[1].strip()
            else:
                arg1 = args.strip()
                arg2 = None
            # debug
            print(f'opcode:{opcode},arg1:{arg1},arg2:{arg2}')
            # if arg1 is not a number ,convert it to number by array tags,function name and registers
            if arg1 in tags:
                arg1 = tags[arg1]
            elif arg1 in functionsName:
                arg1 = functionsName.index(arg1)
            elif arg1 in REGISTERS:
                arg1 = REGISTERS[arg1]
            elif arg1 in constantsAddress:
                arg1 = constantsAddress[arg1]
            else:
                try:
                    arg1 = int(arg1)
                except:
                    print(f'Error: invalid argument {arg1} at line {lineNumber+1}')
                    if DEBUG:
                        breakpoint()
                    sys.exit(1)
            # if arg2 is not a number ,convert it to number by array tags,function name and registers
            if arg2 is None:
                pass
            elif arg2 in tags:
                arg2 = tags[arg2]
            elif arg2 in functionsName:
                arg2 = functionsName.index(arg2)
            elif arg2 in REGISTERS:
                arg2 = REGISTERS[arg2]
            elif arg2 in constantsAddress:
                arg2 = constantsAddress[arg2]
            else:
                try:
                    arg2 = int(arg2)
                except:
                    print(f'Error: invalid argument {arg2} at line {lineNumber+1}')
                    if DEBUG:
                        breakpoint()
                    sys.exit(1)
            # convent opcode to number
            opcode = OPCODES[opcode]
            # append opcode and args to currentFunction
            currentFunction.append(opcode)
            currentFunction.append(arg1)
            currentOpcodeAddr += 2
            if arg2 is not None:
                currentFunction.append(arg2)
                currentOpcodeAddr += 1
        else:
            opcode = lines[i]
            opcode = OPCODES[opcode]
            currentFunction.append(opcode)
            currentOpcodeAddr += 1
    functions.append(currentFunction.copy())
        
    # generate header
    header = bytearray(36 + len(constants))
    # 24-27 is main function id
    if functionsName.index('main') == -1:
        print('Error: main function not found')
        if DEBUG:
            breakpoint()
        sys.exit(1)
    header[24:28] = struct.pack('<I', functionsName.index('main'))
    # 28-31 is stack pointer
    header[28:32] = struct.pack('<I', 0x400)
    # 32-35 is header length
    header[32:36] = struct.pack('<I', 36 + len(constants))
    # write constants to header
    header[36:] = constants

    #generate code segment
    codeSegment = bytearray()
    for fnCode in functions:
        fnLen = len(fnCode)
        codeSegment += struct.pack('<I', fnLen)
        for inst in fnCode:
            codeSegment += struct.pack('<I', inst)
    
    # write header and code segment to rom
    romData = header + codeSegment
    with open(outputFile, 'wb') as f:
        f.write(romData)

    if DEBUG:
        breakpoint()

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print('Usage: python asmer.py <input> <output>')
        sys.exit(1)
    main(sys.argv[1], sys.argv[2])