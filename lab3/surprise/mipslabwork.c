/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int timecounter =0;
int prime = 1234567;
int mytime = 0x5957;
//TRISE address
volatile int* TE =(volatile int*) 0xbf886100;
//PORTE address
volatile int* PE =(volatile int*) 0xbf886110;




char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void ) {
    if (IFS(0)&0x80){
      IFSCLR(0) = 0x80;
      *PE = *PE + 1;
    }


    if(IFS(0) & 0x100){
      timecounter++; 
      IFSCLR(0) = 0x100; 
      }
    if (timecounter==10){
 time2string( textstring, mytime );
 display_string( 3, textstring );
 display_update();
 tick( &mytime );
 timecounter=0;
    }
}



/* Lab-specific initialization goes here */
void labinit( void )
{ 
  T2CONSET = 0x70;
  
  PR2 = (80000000 / 256) / 10;  

  TMR2 = 0;                     
  T2CONSET = 0x8000;
  *TE=0xFF00;
  *PE= 0x00;
  TRISDSET = (0xFF << 5);

   //enable intrrup on timer2
  IEC(0)= IEC(0) | 0x100;

  IEC(0)= IEC(0) | 0x80;

  IPC(2)= IPC(2) | 0x11;
  IPC(1)= IPC(1) | 0x10;

  

  enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
 prime = nextprime( prime );
 display_string( 0, itoaconv( prime ) );
 display_update();
}
