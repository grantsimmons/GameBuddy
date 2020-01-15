#include "Z80.h"

Z80::Z80(uint8_t a = 0x00, uint8_t b = 0x00, uint8_t c = 0x00, uint8_t d = 0x00,
         uint8_t e = 0x00, uint8_t h = 0x00, uint8_t l = 0x00, uint8_t f = 0x00,
         uint8_t m = 0x00, uint16_t t = 0x00, uint16_t pc = 0x0000,
         uint16_t sp = 0xfffe, uint64_t cm = 0x00, uint64_t ct = 0x00):
        _r{a,b,c,d,e,h,l,f,m,t,pc,sp}, _clock{cm,ct}, mmu(1){

    mmu.loadBios();
    mmu.loadRom("Tetris.bin");
}

void Z80::exec(){
    static bool cont = false;
    int counter = 0;
    while(this->_r.pc < 0x100){
        printf("Executing function %x: %x\n", this->_r.pc, this->mmu.rb(this->_r.pc));
        printf("updating t to %04x\n", _timings.t_op_cycles[this->mmu.rb(_r.pc)]);
        this->_r.t = _timings.t_op_cycles[this->mmu.rb(_r.pc)];
        printf("current ct: %08x\n", this->_clock.t);
        this->_clock.t += this->_r.t;
        printf("updated ct: %08x\n", this->_clock.t);
        printf("updating m to %04x\n", _timings.m_op_cycles[this->mmu.rb(_r.pc)]);
        this->_r.m = _timings.m_op_cycles[this->mmu.rb(_r.pc)];
        printf("current cm: %08x\n", this->_clock.m);
        this->_clock.m += this->_r.m;
        printf("updated cm: %08x\n", this->_clock.m);
        (this->*ops[mmu.rb(this->_r.pc++)].op_function)(); //Execute op at pc
        //TODO: Update clocks here
        //gpu.step();
        //if(this->_r.pc > 0x0a || this->_r.pc <= 0x06){
        if(true){
            this->status();
            if(!cont){
                if (counter > 0){
                    counter--;
                    continue;
                }
                std::cout << "p = print mem, x = continue, # = # of steps to continue, n = next instruction\n";
                //char* choice;
                //std::cin >> *choice;
                uint8_t choice;
                std::cin >> choice;
                //if(this->_debug){ //UNIMPLEMENTED
                    switch(choice){
                        case 'p':
                            this->mmu.dump_mem();
                            std::cin >> choice;
                        case 'n':
                            break;
                        case 'x':
                            cont = true;
                            break;
                        case 'r':
                            std::cout << "Resetting..." << std::endl;
                            this->reset();
                            break;
                        default:
                            counter = choice;
                            //counter = atoi(choice);
                    }
                //}
            }
        }
    }
    mmu.dump_mem();
    //this->debug();
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

void Z80::status(){
    printf("a = %02x\n", _r.a);
    printf("b = %02x\n", _r.b);
    printf("c = %02x\n", _r.c);
    printf("d = %02x\n", _r.d);
    printf("e = %02x\n", _r.e);
    printf("h = %02x\n", _r.h);
    printf("l = %02x\n", _r.l);
    printf("f = %02x\n", _r.f);
    printf("m = %02x\n", _r.m);
    printf("t = %02x\n", _r.t);
    printf("pc = %04x\n", _r.pc);
    printf("sp = %04x\n", _r.sp);
    printf("cm = %08x\n", _clock.m);
    printf("ct = %08x\n", _clock.t);
    printf("MMU = %01x\n", mmu._inbios);
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
