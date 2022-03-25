/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */


//All code had written by both Ahmed and Hasan
int birdX = 10;
int birdY = 5;

int obstX = 60;
int obstX1 = 90;
int obstX2 = 120;
int score1 =0;


char starttext[] = "* FLAPPY BIRD *";
char starttext1[] = " BTN4 TO START ";
char starttext2[] = " BTN2 TO JUMP  ";

char gameover[] = " **GAME OVER** ";
char gameover1[] = "SCORE IS ON LED";
char gameover3[] = "BTN4 TO RESTART ";

int start = 1;
int counter12 = 1;

volatile int* PE =(volatile int*) 0xbf886110;
volatile int* TE =(volatile int*) 0xbf886100;



int start1 = 1;

int prime = 1234567;
int mytime = 0x5957;
int timecount = 0;


/* Interrupt Service Routine */
void user_isr( void ) {

      IFSCLR(0) = 0x100; 
	  interupt = 1;

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
  
  IPC(2)= IPC(2) | 0x10;

  enable_interrupt();
  return;
}


/* This function is called repetitively from the main program */
void labwork(void)
{
	while (1)
	{

		while ((getbtns() >> 2) != 1 && counter12 == 1)
		{
			display_string(0, starttext);
			display_string(1, starttext1);
			display_string(2, starttext2);
			display_update();
		}
		counter12 = 0;
		start1 = 1;
		int vari = 1;
		while (vari)
		{
			display_string(0, gameover);
			display_string(1, gameover1);
			display_string(2, gameover3);
			display_update();

			if ((getbtns() >> 2) == 1)
			{
				vari = 0;
				birdX = 10;
				birdY = 5;
				obstX = 60;
				obstX1 = 90;
				obstX2 = 120;
				*PE= 0x00;

			}
		}
		while (start1 == 1)
		{
			display_string(0, "");
			display_string(1, "");
			display_string(2, "");

			wall();
		if (getbtns()!= 1){
			drawBird1(birdX, birdY++);

		}
		if (getbtns()== 1){
			drawBird2(birdX, birdY++);
		}

			if (checkWall(birdY) == 0)
			{
				start1 = 0;
			}
			downObs(obstX--, 4, 6);
			if (obstX == 0)
				obstX = 127;
			downObs(obstX1--, 7, 4);
			if (obstX1 == 0)
				obstX1 = 127;
			downObs(obstX2--, 6, 6);
			if (obstX2 == 0)
				obstX2 = 127;
			display_image(0, icon);
			resetDisplay();
			delay(50);
			display_update();
			if (getbtns() == 1)
			{
				birdY = birdY - 2;

			}

	   	int ch=		checkObsclash(obstX, 4, 6, birdX, birdY );
		int ch1=	checkObsclash(obstX1, 7, 4, birdX, birdY );
		int ch2=	checkObsclash(obstX2, 6, 6, birdX, birdY );

		if (ch ==0 || ch1==0 || ch2==0)
			start1 = 0;
		int sc = score (obstX, birdX);
		int sc1 = score (obstX1, birdX);
		int sc2 = score (obstX2, birdX);
		if (sc ==1 ||sc1 ==1 || sc2 ==1  )
		*PE = *PE +1;
		

		}


	}
}