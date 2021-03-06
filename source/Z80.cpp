#include "Z80.h"
#include <fstream>
#include <bitset>
#include <String>
#include <stdio.h>

#ifndef VERIF
Z80::Z80(uint8_t a = 0x00, uint8_t b = 0x00, uint8_t c = 0x00, uint8_t d = 0x00,
         uint8_t e = 0x00, uint8_t h = 0x00, uint8_t l = 0x00, uint8_t f = 0x00,
         uint8_t m = 0x00, uint16_t t = 0x00, uint16_t pc = 0x0000,
         uint16_t sp = 0xfffe, uint64_t cm = 0x00, uint64_t ct = 0x00):
        _r{a,b,c,d,e,h,l,f,m,t,pc,sp}, _clock{cm,ct}, gpu(0,0,0,0,0,0,0,0),
        mmu(gpu, 1), running(true){

    mmu.loadBios();
    //mmu.loadRom("Tetris.bin");
    //mmu.loadRom("..\\..\\gb-test-roms\\cpu_instrs\\cpu_instrs.gb");
    mmu.loadRom("..\\..\\gb-test-roms\\cpu_instrs\\individual\\06-ld\ r,r.gb");
    //mmu.loadRom("..\\..\\gb-test-roms\\cpu_instrs\\individual\\10-bit\ ops.gb");
}

#else
Z80::Z80(uint8_t a = 0x00, uint8_t b = 0x00, uint8_t c = 0x00, uint8_t d = 0x00,
         uint8_t e = 0x00, uint8_t h = 0x00, uint8_t l = 0x00, uint8_t f = 0x00,
         uint8_t m = 0x00, uint16_t t = 0x00, uint16_t pc = 0x0100,
         uint16_t sp = 0xfffe, uint64_t cm = 0x00, uint64_t ct = 0x00):
        _r{a,b,c,d,e,h,l,f,m,t,pc,sp}, _clock{cm,ct}, gpu(0,0,0,0,0,0,0,0),
        mmu(gpu, 0), running(true), verif_write(true){

    mmu.loadBios();
    mmu.loadRom("D:\\Git\\GameBuddy-Verilog\\sim\\stim\\rand_stim_1600016999_v0.3_s2000\\stim.bin");
}
#endif

void Z80::exec(){
    static bool cont = false;
    bool debug = false;
    int verbose = 1;
    int counter = 0;
    uint16_t pc_target = 0;

#ifdef VERIF
    std::ofstream outfile;
    outfile.open("D:\\Git\\GameBuddy\\source\\stim.tv", std::ios_base::out);
#endif

    //while(this->_r.pc < 0xd801){
    //while(this->_r.pc < 0x100){
    //while(this->_clock.t < 0x172e598){
    while(running){
        if(verbose > 0)
            std::cout << "Executing function " << std::hex << this->_r.pc << ": " << std::hex << (int) this->mmu.rb(this->_r.pc) << '\n' << this->ops[mmu.rb(this->_r.pc)].op << '\n';
        updateTiming(false); //Increment timing registers for next instruction

#ifdef VERIF
        if(this->mmu.rb(this->_r.pc) == 0x10){ //Don't include STOP command in test vector generation
            //verif_write = false;
            running = false;
        }
        if(verif_write){
            std::string s = std::bitset<8>(this->mmu.rb(this->_r.pc)).to_string();
            outfile << s;
            outfile << "_";
        }
#endif

        (this->*ops[mmu.rb(this->_r.pc++)].op_function)(); //Execute op at pc
        gpu.step(this->_r.t); //Increment GPU timing registers

#ifdef VERIF
        if(verif_write){
            outfile << std::bitset<8>(this->_r.a).to_string() << "_"
                    << std::bitset<8>(this->_r.b).to_string() << "_"
                    << std::bitset<8>(this->_r.c).to_string() << "_"
                    << std::bitset<8>(this->_r.d).to_string() << "_"
                    << std::bitset<8>(this->_r.e).to_string() << "_"
                    << std::bitset<8>(this->_r.h).to_string() << "_"
                    << std::bitset<8>(this->_r.l).to_string() << "_"
                    << std::bitset<8>(this->_r.f).to_string() << "\n";
        }
#endif

        if(verbose > 1)
            this->status(verbose);
        if(debug){
            if(pc_target < this->_r.pc){
                if(!cont){
                    if (counter > 0){
                        counter--;
                        continue;
                    }
                    this->status(2);
                    std::cout << "p = print mem, x = continue, # = # of steps to continue, n = next instruction, r = reset, s = CPU status\n";
                    uint8_t choice;
                    std::cin >> choice;
                    switch(choice){
                        case 'p':
                            this->mmu.dump_mem();
                            std::cin >> choice;
                        case 'c':
                            std::cin >> std::hex >> pc_target;
                            break;
                        case 'n':
                            break;
                        case 'x':
                            cont = true;
                            break;
                        case 'r':
                            std::cout << "Resetting..." << std::endl;
                            this->reset();
                            break;
                        case 's':
                            this->status(2);
                            break;
                        //default:
                            //counter = (int)choice;
                    }
                }
            }
        }
    }
    gpu.printFB();
    mmu.dump_mem();
#ifdef VERIF
    outfile.close();
#endif
    //gpu.printFB();
    //mmu.dump_mem();
    //status();
    //this->debug();
}

void Z80::updateTiming(bool ext){
    this->_r.t = ext ? _timings.t_ext_cycles[mmu.rb(this->_r.pc)] : _timings.t_op_cycles[mmu.rb(this->_r.pc)];
    this->_clock.t += this->_r.t;
    this->_r.m = ext ? _timings.m_ext_cycles[mmu.rb(this->_r.pc)] : _timings.m_op_cycles[mmu.rb(this->_r.pc)];
    this->_clock.m += this->_r.m;
    return;
}

void Z80::reset(){
    this->_r.a = 0x00;
    this->_r.b = 0x00;
    this->_r.c = 0x00;
    this->_r.d = 0x00;
    this->_r.e = 0x00;
    this->_r.h = 0x00;
    this->_r.l = 0x00;
    this->_r.f = 0x00;
    this->_r.pc = 0x0000;
    this->_r.sp = 0xfffe;
    this->_r.m = 0x00;
    this->_r.t = 0x00;
    this->_clock.m = 0x00;
    this->_clock.t = 0x00;
    this->mmu._inbios = 1;
}

uint8_t* Z80::getGPUFB(){
    return gpu.getFB();
}

void Z80::status(int verbose){
    if(verbose == 2 || verbose == 4){
        printf("a = %02x\n", _r.a);
        printf("b = %02x\n", _r.b);
        printf("c = %02x\n", _r.c);
        printf("d = %02x\n", _r.d);
        printf("e = %02x\n", _r.e);
        printf("h = %02x\n", _r.h);
        printf("l = %02x\n", _r.l);
        printf("f = %02x", _r.f);
        if(_r.f & 1<<4)
            printf(" CARRY");
        if(_r.f & 1<<5)
            printf(" HALF_CARRY");
        if(_r.f & 1<<6)
            printf(" ADD_SUB");
        if(_r.f & 1<<7)
            printf(" ZERO");
        printf("\n");
        printf("m = %02x\n", _r.m);
        printf("t = %02x\n", _r.t);
        printf("pc = %04x\n", _r.pc);
        printf("sp = %04x\n", _r.sp);
        printf("cm = %08x\n", _clock.m);
        printf("ct = %08x\n", _clock.t);
    }
    if(verbose == 3 || verbose == 4){
        printf("MMU = %01x\n\nGPU STATUS:\n", mmu._inbios);
        gpu.status();
    }
}

void Z80::debug(){
    //customizable debug function
    for(uint16_t i = 0; i < 0xFF7F; i++){
        if(mmu.rb(i) != 0){
            printf("\n%04x: ", i);
            printf("0x%02x ", mmu.rb(i));
        }
    }
}
