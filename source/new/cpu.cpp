typedef union {
    uint16_t registers[6];
    struct {
        uint16_t af,
                 bc,
                 de,
                 hl,
                 sp,
                 pc;
    };
    struct {
        uint8_t f,
                a,
                c,
                b,
                l,
                h;
    };
} GB_registers_t;

class CPU {

    GB_registers_t registers;

    cpu() {
        registers = new GB_registers_t();
    }

    ~cpu() {
        delete [] registers;
    }

    int init() {
       return status;
    }

    uint8_t* get_register_8(uint8_t addr) {
        switch(addr) {
            case 0: return &registers.b;
            case 1: return &registers.c;
            case 2: return &registers.d;
            case 3: return &registers.e;
            case 4: return &registers.h;
            case 5: return &registers.l;
            case 6: return nullptr;
            case 7: return &registers.a;
            default: return nullptr;
        }
    }

    uint16_t* get_register_16(uint8_t addr) {
        switch(addr) {
            default: return nullptr;
        }
    }

    void op_mov(uint8_t dest, uint8_t src) { //Filter for memory access outside of function

        uint8_t* src_reg = get_register_8(src);
        uint8_t* dest_reg = get_register_8(dest);

        *dest_reg = *src_reg;
    }

    void set_flag_value(uint8_t flag, bool val) {
        f_val = registers.f;
        
        f_val = f_val & ~(1 << flag); //Clear the flag
        f_val |= val ? (1 << flag) : 0;

        registers.f = f_val;
    }

    void execute(uint8_t opcode) {
        

    }


};
