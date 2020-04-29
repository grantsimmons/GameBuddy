/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  GameBaby Open Source GameBoy Emulator
 *
 *        Version:  1.0
 *        Created:  10/28/2019 1:58:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Grant Simmons (gs), gsimmons@stevens.edu
 *   Organization:  Stevens Institute of Technology
 *
 * =====================================================================================
 */

#include "Z80.h"
#include <iostream>

int main(int argc, char* args[]){

    Z80 z80(0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    z80.status(0);
    z80.exec();
    return 1;
}

