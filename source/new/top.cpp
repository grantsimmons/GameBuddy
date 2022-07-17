
typedef op uint8_t;

class sys {

    sys() {
        this->cpu = new CPU();
        this->gpu = new GPU();
        this->mmu = new MMU();
    }

    ~sys() {

    }

    int init() {
        //Initialize the complete system
        init_status = 0;

        cpu->init();
        gpu->init();
        mmu->init();
    }

    int start() {
        //Fetch instruction from MMU
        op fetch_op = mmu.read();

        //Execute instruction
        cpu->execute(fetch_op);

        //Update timings
    }

};
