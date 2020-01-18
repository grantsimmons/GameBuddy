#TODO: Fix LDH commands
import re

define = re.compile('^\#')
newline = re.compile('^\s*\/*\n')
LDBasic = re.compile('void\sZ80::LD([ABCDEFHL])([ABCDEFHL])\(')
LDdectom = re.compile('void\sZ80::LDD(mHLA|AmHL)')
LDinctom = re.compile('void\sZ80::LDI(mHLA|AmHL)')
LDtom = re.compile('void\sZ80::LDm([ABCDEFHL]|nn)([ABCDEFHL])?([ABCDEFHLn]|SP)') #Catch DEC case
LDfromm = re.compile('void\sZ80::LD([ABCDEFHL])m([ABDEFHL]|C(?!A))([ABCDEFHL])') #FIXME: Make only valid couples
LDn = re.compile('void\sZ80::LD([ABCDEFHL])n')
LDnn = re.compile('void\sZ80::LD(?=[^m])([ABCDEFHL]|SP)([ABCDEFHL])?nn')
LDH = re.compile('void\sZ80::LDH(mnA|mCA|Amn)')
INC8 = re.compile('void\sZ80::INC([ABCDEFHL])\(')
DEC8 = re.compile('void\sZ80::DEC([ABCDEFHL])\(')
INC16 = re.compile('void\sZ80::INC(([ABCDEFHL])([ABCDEFHL])|(SP))')
DEC16 = re.compile('void\sZ80::DEC(([ABCDEFHL])([ABCDEFHL])|(SP))')
INCmem = re.compile('void\sZ80::INCmHL')
DECmem = re.compile('void\sZ80::DECmHL')
RLCA = re.compile('void\sZ80::RLCA')
RLA = re.compile('void\sZ80::RLA')
ADDA = re.compile('void\sZ80::ADDA([ABCDEFHLn]|mHL)')
ADD16 = re.compile('void\sZ80::ADD(HL|SP)(B|D|d)(C|E)*\(')
SUBA = re.compile('void\sZ80::SUBA([ABCDEFHLn]|mHL)')
ADC = re.compile('void\sZ80::ADCA([ABCDEHLn]|mHL)')
AND = re.compile('void\sZ80::AND([ABCDEFHLn]|mHL)')
OR = re.compile('void\sZ80::OR([ABCDEFHLn]|mHL)')
XOR = re.compile('void\sZ80::XOR([ABCDEFHLn]|mHL)')
PUSH = re.compile('void\sZ80::PUSH([ABDH])([FCEL])')
POP = re.compile('void\sZ80::POP([ABDH])([FCEL])')
JP = re.compile('void\sZ80::JP(N)?(Cnn|Znn|mHL|nn)')
JR = re.compile('void\sZ80::JR(N)?(Cn|Zn|n)')
EXT = re.compile('void\sZ80::Extops')
EXT_RLC = re.compile('void\sZ80::ERLC([ABCDEHL]|mHL)') #Rotate Left w/ carry
EXT_RRC = re.compile('void\sZ80::ERRC([ABCDEHL]|mHL)') #Rotate right w/ carry
EXT_RL = re.compile('void\sZ80::ERL([ABCDEHL]|mHL)') #Rotate left, no carry #FIXME: Conflicts with ERLC*
EXT_RR = re.compile('void\sZ80::ERR([ABCDEHL]|mHL)') #Rotate Right, no carry
EXT_SLA = re.compile('void\sZ80::ESLA([ABCDEHL]|mHL)') #Shift left preserving sign
EXT_SRA = re.compile('void\sZ80::ESRA([ABCDEHL]|mHL)') #Shift right preserving sign
EXT_SRL = re.compile('void\sZ80::ESRL([ABCDEHL]|mHL)') #Shift right no preserve
EXT_SWAP = re.compile('void\sZ80::ESWAP([ABCDEHL]|mHL)') #Swap nibbles in register
EXT_BIT = re.compile('void\sZ80::EBIT([0-7])([ABCDEHL]|mHL)') #Test bit
EXT_RES = re.compile('void\sZ80::ERES([0-7])([ABCDEHL]|mHL)') #Reset bit
EXT_SET = re.compile('void\sZ80::ESET([0-7])([ABCDEHL]|mHL)') #Set bit
CALL = re.compile('void\sZ80::CALL(N)?(C|Z)?nn') #Function Call
RET = re.compile('void\sZ80::RET(N)?(I|C|Z)?')
CP = re.compile('void\sZ80::CP([ABCDEHLn]|mHL)')



with open("../scripts/uncovered.cpp", 'w') as uncovered:
    with open("../source/ops_impl.cpp", 'w') as out_file:
        with open("../scripts/functions.cpp", 'r') as in_file:
            counter = 0
            counter2 = 0
            match = False
            verbose = True
            for line in in_file:
                if define.search(line) or newline.search(line): #Skip define statements and newlines
                    out_file.write(line)
                    continue

                print(counter)
                out_file.write(line[0:-2] + "{\n")
                if verbose:
                    out_file.write("    std::cout << \"{}\" <<std::endl;\n".format(line[10:-4]))
                
                basic = LDBasic.search(line)
                if basic:
                    match = True
                    print("Basic")
                    out_file.write('    this->_r.{} = this->_r.{};\n'.format(basic.group(1).lower(), basic.group(2).lower()))
                    counter += 1

                tom = LDtom.search(line)
                if tom:
                    match = True
                    print("To Mem")
                    if tom.group(1) == 'nn':
                        if tom.group(3) == 'SP':
                            out_file.write('    this->mmu.ww(this->mmu.rb(this->_r.pc) | (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.sp);\n')
                            out_file.write('    this->_r.pc += 2;\n')
                        elif tom.group(3) == 'A':
                            out_file.write('    this->mmu.wb(this->mmu.rb(this->_r.pc) | (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.a);\n')
                            out_file.write('    this->_r.pc += 2;\n')
                    elif tom.group(3) == 'n':
                        out_file.write('    this->mmu.wb(this->_r.{} << 8 | this->_r.{}, this->mmu.rb(this->_r.pc));\n'.format(tom.group(1).lower(), tom.group(2).lower()))
                        out_file.write('    this->_r.pc += 1;\n')
                    else:
                        out_file.write('    this->mmu.wb(this->_r.{} << 8 | this->_r.{}, this->_r.{});\n'.format(tom.group(1).lower(), tom.group(2).lower(), tom.group(3).lower()))
                    counter += 1

                dec = LDdectom.search(line)
                inc = LDinctom.search(line)
                fromm = LDfromm.search(line)
                if dec:
                    match = True
                    print("Dec Mem")
                    if dec.group(1) == 'mHLA':
                        #out_file.write('    printf(\"Writing to address %04x\n\", this->_r.h << 8 | this->_r.l);\n')
                        out_file.write('    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.a);\n')
                        out_file.write('    this->DECHL();\n')
                    if dec.group(1) == 'AmHL':
                        out_file.write('    this->_r.a = this->mmu.rb(this->_r.h << 8 | this->_r.l);\n')
                        out_file.write('    this->DECHL();\n')
                    counter += 1
                    
                elif inc:
                    match = True
                    print("Inc Mem")
                    if inc.group(1) == 'mHLA':
                        out_file.write('    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.a);\n')
                        out_file.write('    this->INCHL();\n')
                    if inc.group(1) == 'AmHL':
                        out_file.write('    this->_r.a = this->mmu.rb(this->_r.h << 8 | this->_r.l);\n')
                        out_file.write('    this->INCHL();\n')
                    counter += 1
                    
                elif fromm:
                    match = True
                    print("From Mem")
                    out_file.write('    this->_r.{} = this->mmu.rb(this->_r.{} << 8 | this->_r.{});\n'.format(fromm.group(1).lower(), fromm.group(2).lower(), fromm.group(3).lower()))
                    counter += 1
                
                inc8 = INC8.search(line)
                if inc8: #Flags
                    match = True
                    print("Inc 8 bit")
                    out_file.write('    this->_r.{} += 1;\n'.format(inc8.group(1).lower()))
                    out_file.write('    this->_r.f = (this->_r.f | (this->_r.{} == 0 ? ZERO : 0) | (this->_r.{} & 0x1F == 0x10 ? HALF_CARRY : 0)) & ~(ADD_SUB);\n'.format(inc8.group(1).lower(), inc8.group(1).lower()))
                    counter += 1

                dec8 = DEC8.search(line)
                if dec8: #Flags
                    match = True
                    print("Dec 8 bit")
                    out_file.write('    this->_r.{} -= 1;\n'.format(dec8.group(1).lower()))
                    out_file.write('    this->_r.f = this->_r.{} == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);\n'.format(dec8.group(1).lower()))
                    out_file.write('    this->_r.f = this->_r.{} & 0x1F == 0x0F ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));\n'.format(dec8.group(1).lower()))
                    out_file.write('    this->_r.f |= ADD_SUB;\n')
                    counter += 1

                inc16 = INC16.search(line)
                if inc16:
                    match = True
                    print("Inc 16 bit")
                    print(inc16.group(1))
                    if inc16.group(1) == 'SP':
                        out_file.write('    this->_r.sp += 1;\n')
                    else:
                        out_file.write('    this->_r.{} += 1;\n'.format(inc16.group(3).lower()))
                        out_file.write('    this->_r.{} = this->_r.{} == 0x00 ? this->_r.{} + 1 : this->_r.{};\n'.format(inc16.group(2).lower(), inc16.group(3).lower(), inc16.group(2).lower(), inc16.group(2).lower()))
                    out_file.write('    //Set OF, Z, etc.\n')
                    counter += 1

                dec16 = DEC16.search(line)
                if dec16:
                    match = True
                    print("Dec 16 bit")
                    if dec16.group(1) == 'SP':
                        out_file.write('    this->_r.sp -= 1;\n')
                    else:
                        out_file.write('    this->_r.{} -= 1;\n'.format(dec16.group(3).lower()))
                        out_file.write('    this->_r.{} = this->_r.{} == 0xFF ? this->_r.{} - 1 : this->_r.{};\n'.format(dec16.group(2).lower(), dec16.group(3).lower(), dec16.group(2).lower(), dec16.group(2).lower()))
                        out_file.write('    this->_r.f = (this->_r.h == 0x0 && this->_r.l == 0x0) ? this->_r.f | ZERO : this->_r.f;\n')
                    out_file.write('    //Set UF, Z, etc.\n')
                    counter += 1

                incmem = INCmem.search(line)
                if incmem:
                    match = True
                    print("Inc mem location")
                    out_file.write('    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->mmu.rb(this->_r.h << 8 | this->_r.l) + 1);\n')
                    out_file.write('    //Set OF, Z, etc. if needed?\n')
                    counter += 1

                decmem = DECmem.search(line)
                if decmem:
                    match = True
                    print("Dec mem location")
                    out_file.write('    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->mmu.rb(this->_r.h << 8 | this->_r.l) - 1);\n')
                    out_file.write('    //Set UF, Z, etc. if needed?\n')
                    counter += 1

                rlca = RLCA.search(line)
                if rlca:
                    match = True
                    print("Rotate A left w/ carry")
                    out_file.write('    this->_r.f |= (this->_r.a & 0x80) ? CARRY : 0;\n')
                    out_file.write('    this->_r.a = this->_r.a << 1 | (this->_r.f & CARRY) ? 1 : 0;\n')
                    counter += 1

                rla = RLA.search(line)
                if rla:
                    match = True
                    print("Rotate A left")
                    out_file.write('    bool orig_carry = this->_r.f & CARRY ? 1 : 0;\n')
                    out_file.write('    this->_r.f &= (this->_r.a & 0x80) ? 0xFF : ~CARRY; //Clear Carry\n')
                    out_file.write('    this->_r.f |= (this->_r.a & 0x80) ? CARRY : 0x00;\n')
                    out_file.write('    this->_r.a = ((this->_r.a << 1) | (int) orig_carry) & 0xFF;\n')

                ldn = LDn.search(line)
                if ldn:
                    match = True
                    print("Load 8-bit immediate")
                    out_file.write('    this->_r.{} = this->mmu.rb(this->_r.pc);\n'.format(ldn.group(1).lower()))
                    out_file.write('    this->_r.pc += 1;\n')
                    counter += 1

                ldnn = LDnn.search(line)
                if ldnn:
                    match = True
                    print("Load 16-bit immediate")
                    if ldnn.group(1) == 'SP':
                        out_file.write('    this->_r.sp = this->mmu.rw(this->_r.pc);\n');
                    else:
                        out_file.write('    this->_r.{} = this->mmu.rb(this->_r.pc);\n'.format(ldnn.group(2).lower()))
                        out_file.write('    this->_r.{} = this->mmu.rb(this->_r.pc + 1);\n'.format(ldnn.group(1).lower()))
                    out_file.write('    this->_r.pc += 2;\n')
                    counter += 1

                ldh = LDH.search(line)
                if ldh:
                    match = True
                    print("Load to FF00 w/ Offset")
                    if ldh.group(1) == 'mnA':
                        out_file.write('    this->mmu.wb(0xFF00 | this->mmu.rb(this->_r.pc), this->_r.a);\n')
                        out_file.write('    this->_r.pc += 1;\n')
                    elif ldh.group(1) == 'mCA':
                        out_file.write('    this->mmu.wb(0xFF00 | this->_r.c, this->_r.a);\n')
                    elif ldh.group(1) == 'Amn':
                        out_file.write('    this->_r.a = this->mmu.rb(0xFF00 | this->mmu.rb(this->_r.pc));\n')
                        out_file.write('    this->_r.pc += 1;\n')
                    counter += 1

                cp = CP.search(line)
                if cp: #Flags
                    match = True
                    print("Compare")
                    if cp.group(1) == 'n':
                        reg = 'this->mmu.rb(this->_r.pc)'
                    elif cp.group(1) == 'mHL':
                        reg = 'this->mmu.rb(this->_r.h << 8 | this->_r.l)'
                    else:
                        reg = 'this->_r.{}'.format(cp.group(1).lower())
                    out_file.write('    uint8_t val = this->_r.a - {};\n'.format(reg))
                    out_file.write('    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - ({} & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);\n'.format(reg))
                    if cp.group(1) == 'n':
                        out_file.write('    this->_r.pc += 1;\n')
                    #TODO: Check half-carry
                    counter += 1

                adda = ADDA.search(line)
                if adda: #Flags
                    match = True
                    print("Accumulator add")
                    if adda.group(1) != 'mHL' and adda.group(1) != 'n':
                        val = '_r.{}'.format(adda.group(1).lower())
                    elif adda.group(1) == 'mHL':
                        val = 'mmu.rb(this->_r.h << 8 | this->_r.l)'
                    elif adda.group(1) == 'n':
                        val = 'mmu.rb(this->_r.pc)'
                    out_file.write('    this->_r.f = this->_r.a + this->{} > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY)); //Carry flag\n'.format(val))
                    out_file.write('    this->_r.f = ((this->_r.a & 0xF) + (this->{} & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag\n'.format(val))
                    out_file.write('    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;\n')
                    out_file.write('    this->_r.a += this->{};\n'.format(val))
                    out_file.write('    this->_r.a &= 0xFF;\n')
                    out_file.write('    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));\n')
                    if adda.group(1) == 'n':
                        out_file.write('    this->_r.pc += 1;\n')
                    counter += 1

                add16 = ADD16.search(line)
                if add16:
                    match = True
                    print("16-bit add")
                    if add16.group(1) == 'SP':
                        out_file.write('    this->_r.sp += this->mmu.rb(this->_r.pc) > 0x7F ? ((int8_t)~this->mmu.rb(this->_r.pc) + 1) & 0xFF : this->mmu.rb(this->_r.pc);\n')
                        out_file.write('    this->_r.pc += 1;\n')
                    #else:
                    counter += 1
                
                adc = ADC.search(line)
                if adc: #Flags
                    match = True
                    print("Add with carry")
                    if adc.group(1) != 'mHL' and adc.group(1) != 'n':
                        val = '_r.{}'.format(adc.group(1).lower())
                    elif adc.group(1) == 'mHL':
                        val = 'mmu.rb(this->_r.h << 8 | this->_r.l)'
                    elif adc.group(1) == 'n':
                        val = 'mmu.rb(this->_r.pc)'
                    out_file.write('    this->_r.f = this->_r.a + this->{} + (this->_r.f & CARRY ? 1 : 0) > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY)); //Carry flag\n'.format(val))
                    out_file.write('    this->_r.f = ((this->_r.a & 0xF) + (this->{} & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag\n'.format(val))
                    out_file.write('    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;\n')
                    out_file.write('    this->_r.a += this->{} + (this->_r.f & CARRY ? 1 : 0);\n'.format(val))
                    out_file.write('    this->_r.a &= 0xFF;\n')
                    out_file.write('    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));\n')
                    if adc.group(1) == 'n':
                        out_file.write('    this->_r.pc += 1;\n')
                    counter += 1

                suba = SUBA.search(line)
                if suba:
                    match = True
                    print("Accumulator Subtract")
                    if suba.group(1) != 'mHL' and suba.group(1) != 'n':
                        val = '_r.{}'.format(suba.group(1).lower())
                    elif suba.group(1) == 'mHL':
                        val = 'mmu.rb(this->_r.h << 8 | this->_r.l)'
                    elif suba.group(1) == 'n':
                        val = 'mmu.rb(this->_r.pc)'
                    out_file.write('    this->_r.f |= ADD_SUB; //Set Add_Sub flag;\n')
                    out_file.write('    this->_r.f = ((this->_r.a & 0x0F) < (this->{} & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));\n'.format(val))
                    out_file.write('    this->_r.f = (this->_r.a < this->{}) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));\n'.format(val))
                    out_file.write('    this->_r.a -= this->{};\n'.format(val))
                    out_file.write('    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));\n')
                    if suba.group(1) == 'n':
                        out_file.write('    this->_r.pc += 1;\n')
                    counter += 1


                anda = AND.search(line)
                if anda: #Flags
                    match = True
                    print("Accumulator and")
                    if anda.group(1) != 'mHL' and anda.group(1) != 'n':
                        val = '_r.{}'.format(anda.group(1).lower())
                    elif anda.group(1) == 'mHL':
                        val = 'mmu.rb(this->_r.h << 8 | this->_r.l)'
                    elif anda.group(1) == 'n':
                        val = 'mmu.rb(this->_r.pc)'
                    out_file.write('    this->_r.a &= this->{};\n'.format(val))
                    out_file.write('    this->_r.f = HALF_CARRY | this->_r.a == 0 ? ZERO : 0;\n')
                    if anda.group(1) == 'n':
                        out_file.write('    this->_r.pc += 1;\n')
                    counter += 1

                xora = XOR.search(line)
                if xora: #Flags
                    match = True
                    print("Accumulator xor")
                    if xora.group(1) != 'mHL' and xora.group(1) != 'n':
                        val = '_r.{}'.format(xora.group(1).lower())
                    elif xora.group(1) == 'mHL':
                        val = 'mmu.rb(this->_r.h << 8 | this->_r.l)'
                    elif xora.group(1) == 'n':
                        val = 'mmu.rb(this->_r.pc)'
                    out_file.write('    this->_r.a ^= this->{};\n'.format(val))
                    out_file.write('    this->_r.f = this->_r.a == 0 ? ZERO : 0;\n')
                    if xora.group(1) == 'n':
                        out_file.write('    this->_r.pc += 1;\n')
                    counter += 1

                ora = OR.search(line)
                if ora: #Flags
                    match = True
                    print("Accumulator xor")
                    if ora.group(1) != 'mHL' and ora.group(1) != 'n':
                        val = '_r.{}'.format(ora.group(1).lower())
                    elif ora.group(1) == 'mHL':
                        val = 'mmu.rb(this->_r.h << 8 | this->_r.l)'
                    elif ora.group(1) == 'n':
                        val = 'mmu.rb(this->_r.pc)'
                    out_file.write('    this->_r.a |= this->{};\n'.format(val))
                    out_file.write('    this->_r.f = this->_r.a == 0 ? ZERO : 0;\n')
                    if ora.group(1) == 'n':
                        out_file.write('    this->_r.pc += 1;\n')
                    counter += 1

                push = PUSH.search(line)
                if push:
                    match = True
                    print("Push to stack")
                    out_file.write('    this->mmu.wb(this->_r.sp - 1, this->_r.{});\n'.format(push.group(1).lower()))
                    out_file.write('    this->mmu.wb(this->_r.sp - 2, this->_r.{});\n'.format(push.group(2).lower()))
                    out_file.write('    this->_r.sp -= 2;\n')
                    counter += 1

                pop = POP.search(line)
                if pop:
                    match = True
                    print("Pop from stack")
                    out_file.write('    this->_r.{} = this->mmu.rb(this->_r.sp);\n'.format(pop.group(2).lower()))
                    out_file.write('    this->_r.{} = this->mmu.rb(this->_r.sp + 1);\n'.format(pop.group(1).lower()))
                    out_file.write('    this->_r.sp += 2;\n')
                    counter += 1

                jp = JP.search(line)
                if jp:
                    match = True
                    print("Absolute Jump")
                    if jp.group(2) == 'Cnn':
                        out_file.write('    this->_r.pc = (this->_r.f & CARRY) ? {} : {};\n'.format('this->_r.pc' if jp.group(1) == 'N' else 'this->mmu.rw(this->_r.pc)', 'this->mmu.rw(this->_r.pc)' if jp.group(1) == 'N' else 'this->_r.pc'))
                        out_file.write('    this->_r.pc += (this->_r.f & CARRY) ? {} : {};\n'.format(0 if jp.group(1) == 'N' else 2, 2 if jp.group(1) == 'N' else 0))
                    elif jp.group(2) == 'Znn':
                        out_file.write('    this->_r.pc = (this->_r.f & ZERO) ? {} : {};\n'.format('this->_r.pc' if jp.group(1) == 'N' else 'this->mmu.rw(this->_r.pc)', 'this->mmu.rw(this->_r.pc)' if jp.group(1) == 'N' else 'this->_r.pc'))
                        out_file.write('    this->_r.pc += (this->_r.f & ZERO) ? {} : {};\n'.format(0 if jp.group(1) == 'N' else 2, 2 if jp.group(1) == 'N' else 0))
                    elif jp.group(2) == 'mHL':
                        out_file.write('    this->_r.pc = this->mmu.rw(this->_r.h << 8 | this->_r.l);\n')
                        out_file.write('    this->_r.pc += 2;\n')
                    counter += 1

                jr = JR.search(line)
                if jr:
                    match = True
                    print("Relative Jump")
                    if jr.group(2) == 'Cn':
                        out_file.write('    this->_r.pc += this->_r.f & CARRY ? {} : {};\n'.format('0' if jr.group(1) == 'N' else '(int8_t) this->mmu.rb(this->_r.pc)', '(int8_t) this->mmu.rb(this->_r.pc)' if jr.group(1) == 'N' else '0'))
                    elif jr.group(2) == 'Zn':
                        out_file.write('    this->_r.pc += this->_r.f & ZERO ? {} : {};\n'.format('0' if jr.group(1) == 'N' else '(int8_t) this->mmu.rb(this->_r.pc)', '(int8_t) this->mmu.rb(this->_r.pc)' if jr.group(1) == 'N' else '0'))
                    elif jr.group(2) == 'n':
                        out_file.write('    this->_r.pc += (int8_t) this->mmu.rb(this->_r.pc);\n')
                    out_file.write('    this->_r.pc += 1;\n')
                    counter += 1

                call = CALL.search(line)
                if call:
                    match = True
                    print("Function Call")
                    if call.group(2) is not None:
                        out_file.write('    if(this->_r.f & {} == {})'.format('CARRY' if call.group(2) == 'C' else 'ZERO', 0 if call.group(1) == 'N' else 1))
                        out_file.write('{\n')
                    out_file.write('        this->mmu.wb(this->_r.sp - 1, (this->_r.pc + 2) & 0xFF00);\n') #Push pc MSB to stack
                    out_file.write('        this->mmu.wb(this->_r.sp - 2, (this->_r.pc + 2) & 0x00FF);\n') #Push pc LSB to stack
                    out_file.write('        this->_r.sp -= 2;\n')
                    out_file.write('        this->_r.pc = this->mmu.rw(this->_r.pc);\n')
                    if call.group(2) is not None:
                        out_file.write('    }\n')
                    counter += 1

                ret = RET.search(line)
                if ret:
                    match = True
                    print("Function Return")
                    if ret.group(2) != 'I': #TODO: Enable interrupt coverage
                        if ret.group(2) is not None: 
                            out_file.write('    if(this->_r.f & {} == {})'.format('CARRY' if ret.group(2) == 'C' else 'ZERO', 0 if ret.group(1) == 'N' else 1))
                            out_file.write('{\n')
                        out_file.write('        this->_r.pc = this->mmu.rb(this->_r.sp) | this->mmu.rb(this->_r.sp + 1);\n')
                        out_file.write('        this->_r.sp += 2;\n')
                        if ret.group(2) is not None:
                            out_file.write('    }\n')
                        counter += 1





#=================Extensions===================================================
                ext = EXT.search(line)
                if ext:
                    match = True
                    print("CB Extension")
                    out_file.write('    updateTiming(true);\n')
                    out_file.write('    (this->*ext_ops[mmu.rb(this->_r.pc++)].op_function)();\n')
                    out_file.write('    gpu.step(this->_r.t);\n')
                    counter += 1

                erlc = EXT_RLC.search(line)
                if erlc:
                    print("Extension Rotate Left with carry")
                    match = True
                    if erlc.group(1) != 'mHL':
                        out_file.write('    this->_r.f = ((this->_r.{} & 0x80) >> 7) | (this->_r.f & 0xFE);\n'.format(erlc.group(1).lower()))
                        #FIXME: Hardcoded carry position                          ^
                        out_file.write('    this->_r.{} = (this->_r.{} << 1) | ((this->_r.{} & 0x80) >> 7);\n'.format(erlc.group(1).lower(), erlc.group(1).lower(), erlc.group(1).lower()))
                    else:
                        out_file.write('    this->_r.f = ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) >> 7) | this->_r.f & 0xFE;\n')
                        out_file.write('    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) << 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) >> 7));\n')
                        #FIXME: Make all mHL accesses | instead of +
                    counter2 += 1

                errc = EXT_RRC.search(line)
                if errc:
                    print("Extension Rotate Right with carry")
                    match = True
                    if errc.group(1) != 'mHL':
                        out_file.write('    this->_r.f = (this->_r.{} & 0x1) | (this->_r.f & 0xFE);\n'.format(errc.group(1).lower()))
                        out_file.write('    this->_r.{} = (this->_r.{} >> 1) | ((this->_r.{} & 0x1) << 7);\n'.format(errc.group(1).lower(), errc.group(1).lower(), errc.group(1).lower()))
                    else:
                        out_file.write('    this->_r.f = (this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1) | this->_r.f & 0xFE;\n')
                        out_file.write('    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) >> 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1) << 7));\n')
                    counter2 += 1

                erl = EXT_RL.search(line)
                if erl:
                    match = True
                    print("Extension Rotate Left, no carry")
                    if erl.group(1) != 'mHL':
                        out_file.write('    this->_r.{} = (this->_r.{} << 1) | ((this->_r.{} & 0x80) >> 7);\n'.format(erl.group(1).lower(), erl.group(1).lower(), erl.group(1).lower()))
                    else:
                        out_file.write('    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) << 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) >> 7));\n')
                    counter2 += 1

                err = EXT_RR.search(line)
                if err:
                    match = True
                    print("Extension Rotate Right, no carry")
                    if err.group(1) != 'mHL':
                        out_file.write('    this->_r.{} = (this->_r.{} >> 1) | ((this->_r.{} & 0x1) << 7);\n'.format(err.group(1).lower(), err.group(1).lower(), err.group(1).lower()))
                    else:
                        out_file.write('    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) >> 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1) << 7));\n')
                    counter2 += 1

                esla = EXT_SLA.search(line)
                if esla:
                    if esla.group(1) != 'mHL':
                        print("Extension Shift Left Preserving Sign")
                        match = True
                        out_file.write('    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.{} & 0x80) >> 7 ? CARRY : 0x0);\n'.format(esla.group(1).lower()))
                        out_file.write('    this->_r.{} <<= 1;\n'.format(esla.group(1).lower()))
                        counter2 += 1

                esra = EXT_SRA.search(line)
                if esra:
                    if esra.group(1) != 'mHL':
                        print("Extension Shift Right Preserving Sign")
                        match = True
                        out_file.write('    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.{} & 0x1) ? CARRY : 0);\n'.format(esra.group(1).lower()))
                        out_file.write('    this->_r.{} >>= 1;\n'.format(esra.group(1).lower()))
                        counter2 += 1

                esrl = EXT_SRL.search(line)
                if esrl:
                    if esrl.group(1) != 'mHL':
                        print("Extension Shift Right, no sign preservation")
                        match = True
                        out_file.write('    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.{} & 0x1) ? CARRY : 0);\n'.format(esrl.group(1).lower()))
                        out_file.write('    this->_r.{} = (this->_r.{} >> 1) & 0x7F;\n'.format(esrl.group(1).lower(), esrl.group(1).lower()))
                        counter2 += 1

                eswap = EXT_SWAP.search(line)
                if eswap:
                    if eswap.group(1) != 'mHL':
                        match = True
                        print("Extension Swap nibbles in byte")
                        out_file.write('    this->_r.{} = (((this->_r.{} & 0xF0) >> 4) & 0x0F) | (((this->_r.{} & 0x0F) << 4) & 0xF0);\n'.format(eswap.group(1).lower(), eswap.group(1).lower(), eswap.group(1).lower()))
                        counter2 += 1

                ebit = EXT_BIT.search(line)
                if ebit:
                    match = True
                    print("Extension Test Bit")
                    if ebit.group(2) != 'mHL':
                        out_file.write('    this->_r.f = (this->_r.{} & (1<<{})) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));\n'.format(ebit.group(2).lower(), ebit.group(1)))
                    else:
                        out_file.write('    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<{})) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));\n'.format(ebit.group(1).lower()))
                    counter2 += 1

                eres = EXT_RES.search(line)
                if eres:
                    match = True
                    print("Extension Reset Bit")
                    if eres.group(2) != 'mHL':
                        out_file.write('    this->_r.{} &= ~(1<<{});\n'.format(eres.group(2).lower(), eres.group(1).lower()))
                    else:
                        out_file.write('    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<{})));\n'.format(eres.group(1).lower()))                        
                    counter2 += 1
                

                eset = EXT_SET.search(line)
                if eset:
                    match = True
                    print("Extension Set Bit")
                    if eset.group(2) != 'mHL':
                        out_file.write('    this->_r.{} |= (1<<{});\n'.format(eset.group(2).lower(), eset.group(1).lower()))
                    else:
                        out_file.write('    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<{})));\n'.format(eset.group(1).lower()))                        
                    counter2 += 1

                if not match:    
                    out_file.write('    std::cout << "Uncovered Function" << std::endl;\n')
                    uncovered.write(line)
                out_file.write("}\n\n")
                match = False
                print(line[0:-2])

        print("Single-Byte Coverage: {:02d}%".format(int(100 * counter / 0x100)))
        print("Two-Byte Coverage: {:02d}%".format(int(100 * counter2 / 0x100)))
        print("Total Coverage: {:02d}%".format(int(100 * (counter2 + counter) / 0x200)))
