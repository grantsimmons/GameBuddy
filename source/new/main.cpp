/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  GameBaby Open Source GameBoy Emulator
 *
 *        Version:  0.0
 *        Created:  7/17/2022 19:37:37
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

    sys top();

    top.init();

    top.start();
    
    return 0;
}

