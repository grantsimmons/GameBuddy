#TODO: Fix LDH commands
import re

define = re.compile('^\#')
newline = re.compile('^\n')
LDBasic = re.compile('void\sZ80::LD([ABCDEFHL])([ABCDEFHL])\(')
LDdectom = re.compile('void\sZ80::LDD(mHLA|AmHL)')
LDinctom = re.compile('void\sZ80::LDI(mHLA|AmHL)')
LDtom = re.compile('void\sZ80::LDm([ABCDEFHL]|nn)([ABCDEFHL])?([ABCDEFHLn]|SP)') #Catch DEC case
LDfromm = re.compile('void\sZ80::LD([ABCDEFHL])m([ABCDEFHL])([ABCDEFHL])')
LDn = re.compile('void\sZ80::LD([ABCDEFHL])n')
LDnn = re.compile('void\sZ80::LD(?=[^m])([ABCDEFHL]|SP)([ABCDEFHL])?nn')
INC8 = re.compile('void\sZ80::INC([ABCDEFHL])\(')
DEC8 = re.compile('void\sZ80::DEC([ABCDEFHL])\(')
INC16 = re.compile('void\sZ80::INC(([ABCDEFHL])([ABCDEFHL])|(SP))')
DEC16 = re.compile('void\sZ80::DEC(([ABCDEFHL])([ABCDEFHL])|(SP))')
INCmem = re.compile('void\sZ80::INCmHL')
DECmem = re.compile('void\sZ80::DECmHL')
RLCA = re.compile('void\sZ80::RLCA')
ADDA = re.compile('void\sZ80::ADDA([ABCDEFHLn]|mHL)')
ADD16 = re.compile('void\sZ80::ADD(HL|SP)(B|D|d)(C|E)*\(')
ADC = re.compile('void\sZ80::ADCA([ABCDEHLn]|mHL)')
AND = re.compile('void\sZ80::AND([ABCDEFHLn]|mHL)')
OR = re.compile('void\sZ80::OR([ABCDEFHLn]|mHL)')
XOR = re.compile('void\sZ80::XOR([ABCDEFHLn]|mHL)')
PUSH = re.compile('void\sZ80::PUSH([ABDH])([FCEL])')
POP = re.compile('void\sZ80::POP([ABDH])([FCEL])')
JP = re.compile('void\sZ80::JP(N)?(Cnn|Znn|mHL|nn)')
JR = re.compile('void\sZ80::JR(N)?(Cn|Zn|n)')
EXT = re.compile('void\sZ80::Extops')


with open("uncovered.cpp", 'w') as uncovered:
    with open("../source/ops_impl.cpp", 'w') as out_file:
        with open("functions.cpp", 'r') as in_file:
            counter = 1
            match = False
            for line in in_file:
                if define.search(line) or newline.search(line): #Skip define statements
                    out_file.write(line)
                    continue

                print(counter)
                out_file.write(line[0:-2] + "{\n")
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
                            out_file.write('    this->mmu.ww(this->mmu.rb(this->_r.pc) + (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.sp);\n')
                            out_file.write('    this->_r.pc += 2;\n')
                        elif tom.group(3) == 'A':
                            out_file.write('    this->mmu.wb(this->mmu.rb(this->_r.pc) + (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.a);\n')
                            out_file.write('    this->_r.pc += 2;\n')
                    elif tom.group(3) == 'n':
                        out_file.write('    this->mmu.wb(this->_r.{} << 8 + this->_r.{}, this->mmu.rb(this->_r.pc));\n'.format(tom.group(1).lower(), tom.group(2).lower()))
                        out_file.write('    this->_r.pc += 1;\n')
                    else:
                        out_file.write('    this->mmu.wb(this->_r.{} << 8 + this->_r.{}, this->_r.{});\n'.format(tom.group(1).lower(), tom.group(2).lower(), tom.group(3).lower()))
                    counter += 1

                dec = LDdectom.search(line)
                inc = LDinctom.search(line)
                fromm = LDfromm.search(line)
                if dec:
                    match = True
                    print("Dec Mem")
                    if dec.group(1) == 'mHLA':
                        out_file.write('    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.a);\n')
                        out_file.write('    this->DECHL();\n')
                    if dec.group(1) == 'AmHL':
                        out_file.write('    this->_r.a = this->mmu.rb(this->_r.h << 8 + this->_r.l);\n')
                        out_file.write('    this->DECHL();\n')
                    counter += 1
                    
                elif inc:
                    match = True
                    print("Inc Mem")
                    if inc.group(1) == 'mHLA':
                        out_file.write('    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.a);\n')
                        out_file.write('    this->INCHL();\n')
                    if inc.group(1) == 'AmHL':
                        out_file.write('    this->_r.a = this->mmu.rb(this->_r.h << 8 + this->_r.l);\n')
                        out_file.write('    this->INCHL();\n')
                    counter += 1
                    
                elif fromm:
                    match = True
                    print("From Mem")
                    out_file.write('    this->_r.{} = this->mmu.rb(this->_r.{} << 8 + this->_r.{});\n'.format(fromm.group(1).lower(), fromm.group(2).lower(), fromm.group(3).lower()))
                    counter += 1
                
                inc8 = INC8.search(line)
                if inc8:
                    match = True
                    print("Inc 8 bit")
                    out_file.write('    this->_r.{} += 1;\n'.format(inc8.group(1).lower()))
                    out_file.write('    //Set OF, Z, etc.\n')
                    counter += 1

                dec8 = DEC8.search(line)
                if dec8:
                    match = True
                    print("Dec 8 bit")
                    out_file.write('    this->_r.{} -= 1;\n'.format(dec8.group(1).lower()))
                    out_file.write('    //Set UF, Z, etc.\n')
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
                    out_file.write('    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->mmu.rb(this->_r.h << 8 + this->_r.l) + 1);\n')
                    out_file.write('    //Set OF, Z, etc. if needed?\n')
                    counter += 1

                decmem = DECmem.search(line)
                if decmem:
                    match = True
                    print("Dec mem location")
                    out_file.write('    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->mmu.rb(this->_r.h << 8 + this->_r.l) - 1);\n')
                    out_file.write('    //Set UF, Z, etc. if needed?\n')
                    counter += 1

                rlca = RLCA.search(line)
                if rlca:
                    match = True
                    print("Rotate A left w/ carry")
                    out_file.write('    this->_r.f = this->_r.a & 0x80; //FIXME: Carry flag position\n')
                    out_file.write('    this->_r.a = this->_r.a << 1 + ((this->_r.a & 0x80) >> 7);\n')
                    counter += 1

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

                adda = ADDA.search(line)
                if adda:
                    match = True
                    print("Accumulator add")
                    if adda.group(1) != 'mHL' and adda.group(1) != 'n':
                        out_file.write('    this->_r.f = ((this->_r.a + this->_r.{}) >> 8) & 0x1;\n'.format(adda.group(1).lower()))
                        out_file.write('    this->_r.a += this->_r.{};\n'.format(adda.group(1).lower()))
                        out_file.write('    this->_r.a &= 0xFF;\n')
                    elif adda.group(1) == 'mHL':
                        out_file.write('    this->_r.f = ((this->_r.a + this->mmu.rb(this->_r.h << 8 + this->_r.l)) >> 8) & 0x1;\n')
                        out_file.write('    this->_r.a += this->mmu.rb(this->_r.h << 8 + this->_r.l);\n')
                        out_file.write('    this->_r.a &= 0xFF;\n')
                    elif adda.group(1) == 'n':
                        out_file.write('    this->_r.f = (this->_r.a + this->mmu.rb(this->_r.pc) >> 8) & 0x1;\n')
                        out_file.write('    this->_r.a += this->mmu.rb(this->_r.pc);\n')
                        out_file.write('    this->_r.a &= 0xFF;\n')
                        out_file.write('    this->_r.pc += 1;\n')
                    out_file.write('    //Set 0, OF (above), etc.\n')
                    counter += 1

                add16 = ADD16.search(line)
                if add16:
                    match = True
                    print("16-bit add")
                    if add16.group(1) == 'SP':
                        out_file.write('    this->_r.sp += this->mmu.rb(this->_r.pc) > 0x7F ? ((int8_t)~this->mmu.rb(this->_r.pc) + 1) & 0xFF : this->mmu.rb(this->_r.pc);\n')
                        out_file.write('    this->_r.pc += 1;\n')
                    #else:
                
                adc = ADC.search(line)
                if adc:
                    match = True
                    print("Add with carry")
                    if adc.group(1) == 'n':
                        out_file.write('    this->_r.a = this->_r.a + this->mmu.rb(this->_r.pc) + (this->_r.f & CARRY);\n')
                    elif adc.group(1) == 'mHL':
                        out_file.write('    this->_r.a = this->_r.a + this->mmu.rb(this->_r.h << 8 + this->_r.l) + (this->_r.f & CARRY);\n')
                        out_file.write('    this->_r.pc += 1;\n')
                    else:
                        out_file.write('    this->_r.a = this->_r.a + this->_r.{} + (this->_r.f & CARRY);\n'.format(adc.group(1).lower()))

                anda = AND.search(line)
                if anda:
                    match = True
                    print("Accumulator and")
                    if anda.group(1) != 'mHL' and anda.group(1) != 'n':
                        out_file.write('    this->_r.a &= this->_r.{};\n'.format(anda.group(1).lower()))
                    elif anda.group(1) == 'mHL':
                        out_file.write('    this->_r.a &= this->mmu.rb(this->_r.h << 8 + this->_r.l);\n')
                    elif anda.group(1) == 'n':
                        out_file.write('    this->_r.a &= this->mmu.rb(this->_r.pc);\n')
                        out_file.write('    this->_r.pc += 1;\n')
                    out_file.write('    //Set 0, carry, etc.\n')
                    counter += 1

                xora = XOR.search(line)
                if xora:
                    match = True
                    print("Accumulator xor")
                    if xora.group(1) != 'mHL' and xora.group(1) != 'n':
                        out_file.write('    this->_r.a ^= this->_r.{};\n'.format(xora.group(1).lower()))
                    elif xora.group(1) == 'mHL':
                        out_file.write('    this->_r.a ^= this->mmu.rb(this->_r.h << 8 + this->_r.l);\n')
                    elif xora.group(1) == 'n':
                        out_file.write('    this->_r.a ^= this->mmu.rb(this->_r.pc);\n')
                        out_file.write('    this->_r.pc += 1;\n')
                    out_file.write('    //Set 0, carry, etc.\n')
                    counter += 1

                ora = OR.search(line)
                if ora:
                    match = True
                    print("Accumulator xor")
                    if ora.group(1) != 'mHL' and ora.group(1) != 'n':
                        out_file.write('    this->_r.a |= this->_r.{};\n'.format(ora.group(1).lower()))
                    elif ora.group(1) == 'mHL':
                        out_file.write('    this->_r.a |= this->mmu.rb(this->_r.h << 8 + this->_r.l);\n')
                    elif ora.group(1) == 'n':
                        out_file.write('    this->_r.a |= this->mmu.rb(this->_r.pc);\n')
                        out_file.write('    this->_r.pc += 1;\n')
                    out_file.write('    //Set 0, carry, etc.\n')
                    counter += 1

                push = PUSH.search(line)
                if push:
                    match = True
                    print("Push to stack")
                    out_file.write('    this->mmu.wb(this->_r.sp, this->_r.{});\n'.format(push.group(1).lower()))
                    out_file.write('    this->mmu.wb(this->_r.sp - 1, this->_r.{});\n'.format(push.group(2).lower()))
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
                        out_file.write('    this->_r.pc = this->mmu.rw(this->_r.h << 8 + this->_r.l);\n')
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

                ext = EXT.search(line)
                if ext:
                    print("CB Extension")
                    out_file.write('    this->_r.pc += 1;\n')
                    #Skips next instruction

                if not match:    
                    out_file.write('    std::cout << "Uncovered Function" << std::endl;\n')
                    uncovered.write(line)
                out_file.write("}\n\n")
                match = False
                print(line[0:-2])

        print("Single-Byte Coverage: {:02d}%".format(int(100 * counter / 0x100)))
        print("Total Coverage: {:02d}%".format(int(100 * counter / 0x200)))
