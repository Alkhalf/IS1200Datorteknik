#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
//Ahmed och Hasan (lab3)
int getsw(void){


    return ( (PORTD>>8) & 0xF);
}

int getbtns (void){

        return ( (PORTD>>5) & 0x7);

}

