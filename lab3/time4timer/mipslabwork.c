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

int mytime = 0x5957;
int timecounter =0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )

{
  return;
}
//TRISE address
volatile int* TE =(volatile int*) 0xbf886100;
//PORTE address
volatile int* PE =(volatile int*) 0xbf886110;


/* Lab-specific initialization goes here */
void labinit( void )
{ 
  T2CONSET = 0x70; //presecla 256
  
  PR2 = (80000000 / 256) / 10;  //Period reg

  TMR2 = 0;     //current time                
  T2CONSET = 0x8000; //bit 15 
  *TE=0xFF00;
  *PE= 0x00;
  TRISD = TRISD | (0x0FE0);
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  int btn = getbtns();
  int btn4 = btn >> 2;
  int btn3 = btn & 2;
  int btn2 = btn & 1;

  if (btn4 == 1)
      mytime = (mytime &0x0FFF) | (getsw() << 12);
  if (btn3 == 2)
      mytime = (mytime &0xF0FF) | (getsw() << 8);
  if (btn2 == 1)
      mytime = (mytime &0xFF0F) | (getsw() << 4);
 
    // check for timeout event
    if(IFS(0) & 0x100){
      timecounter++;
      //Reset the  event flag
      IFSCLR(0) = 0x100; 
    }
  if(timecounter == 10){
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  timecounter=0;
  *PE = *PE +1;
  }

  


  display_image(96, icon);
  
}
