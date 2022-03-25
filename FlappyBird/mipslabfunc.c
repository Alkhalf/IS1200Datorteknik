/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

/* Declare a helper function which is local to this file */
static void num32asc(char *s, int);

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc)
{
  int i;
  for (i = cyc; i > 0; i--)
    ;
}

/* tick:
   Add 1 to time in memory, at location pointed to by parameter.
   Time is stored as 4 pairs of 2 NBCD-digits.
   1st pair (most significant byte) counts days.
   2nd pair counts hours.
   3rd pair counts minutes.
   4th pair (least significant byte) counts seconds.
   In most labs, only the 3rd and 4th pairs are used. */
void tick(unsigned int *timep)
{
  /* Get current value, store locally */
  register unsigned int t = *timep;
  t += 1; /* Increment local copy */

  /* If result was not a valid BCD-coded time, adjust now */

  if ((t & 0x0000000f) >= 0x0000000a)
    t += 0x00000006;
  if ((t & 0x000000f0) >= 0x00000060)
    t += 0x000000a0;
  /* Seconds are now OK */

  if ((t & 0x00000f00) >= 0x00000a00)
    t += 0x00000600;
  if ((t & 0x0000f000) >= 0x00006000)
    t += 0x0000a000;
  /* Minutes are now OK */

  if ((t & 0x000f0000) >= 0x000a0000)
    t += 0x00060000;
  if ((t & 0x00ff0000) >= 0x00240000)
    t += 0x00dc0000;
  /* Hours are now OK */

  if ((t & 0x0f000000) >= 0x0a000000)
    t += 0x06000000;
  if ((t & 0xf0000000) >= 0xa0000000)
    t = 0;
  /* Days are now OK */

  *timep = t; /* Store new value */
}

void display_debug(volatile int *const addr)
{
  display_string(1, "Addr");
  display_string(2, "Data");
  num32asc(&textbuffer[1][6], (int)addr);
  num32asc(&textbuffer[2][6], *addr);
  display_update();
}

uint8_t spi_send_recv(uint8_t data)
{
  while (!(SPI2STAT & 0x08))
    ;
  SPI2BUF = data;
  while (!(SPI2STAT & 1))
    ;
  return SPI2BUF;
}

void display_init(void)
{
  DISPLAY_CHANGE_TO_COMMAND_MODE;
  quicksleep(10);
  DISPLAY_ACTIVATE_VDD;
  quicksleep(1000000);

  spi_send_recv(0xAE);
  DISPLAY_ACTIVATE_RESET;
  quicksleep(10);
  DISPLAY_DO_NOT_RESET;
  quicksleep(10);

  spi_send_recv(0x8D);
  spi_send_recv(0x14);

  spi_send_recv(0xD9);
  spi_send_recv(0xF1);

  DISPLAY_ACTIVATE_VBAT;
  quicksleep(10000000);

  spi_send_recv(0xA1);
  spi_send_recv(0xC8);

  spi_send_recv(0xDA);
  spi_send_recv(0x20);

  spi_send_recv(0xAF);
}


//Hasan
int getIndex(int x, int y)
{
  int tillbaka;
  int part = y / 8;
  switch (part)
  {
  case 0:
    tillbaka = x;
    break;

  case 1:
    tillbaka = x + 128;
    break;

  case 2:
    tillbaka = x + (2 * 128);
    break;

  default:
    tillbaka = x + (3 * 128);
  }
  return tillbaka;
}


//Hasan
void draw(int state, int x, int y)
{

  int index = getIndex(x, y);
  int  bitPos= y % 8;
  uint8_t array[8] = {254, 253, 251, 247, 239, 223, 191, 127};

  if (state == 0)
  {
    icon[index] = icon[index] & array[bitPos];
  }
 else
  {
    icon[index] = icon[index] | ~array[bitPos];
  }
}


//Ahmed
void wall(void)
{

  int i;
  for (i = 0; i < 128; i++)
  {
    draw(0, i, 0);
    draw(0, i, 31);
  }
}


void drawBird1(int x, int y)
{
  //Hasan 
  uint8_t firstPicture1[17] = {
      1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
  uint8_t firstPicture2[17] = {
      1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1};
  uint8_t firstPicture3[17] = {
      1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
  uint8_t firstPicture4[17] = {
      1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1};
  uint8_t firstPicture5[17] = {
      0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1};
  uint8_t firstPicture6[17] = {
      0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1};
  uint8_t firstPicture7[17] = {
      0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1};
  uint8_t firstPicture8[17] = {
      1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0};
  uint8_t firstPicture9[17] = {
      1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1};
  uint8_t firstPicture10[17] = {
      1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1};
  uint8_t firstPicture11[17] = {
      1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1};
  uint8_t firstPicture12[17] = {
      1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1};



  // draw the first image
  //Ahmed 
  int i = 0;
  int j = 0;
  int tempX = x;
  int tempY = y;

  for (i = 0; i < 17; i++)
  {

    if (firstPicture1[i] == 0)
    {
      draw(0, tempX, tempY);
    }

    if (firstPicture2[i] == 0)
    {
      draw(0, tempX, tempY + 1);
    }
    if (firstPicture3[i] == 0)
    {
      draw(0, tempX, tempY + 2);
    }
    if (firstPicture4[i] == 0)
    {
      draw(0, tempX, tempY + 3);
    }
    if (firstPicture5[i] == 0)
    {
      draw(0, tempX, tempY + 4);
    }
    if (firstPicture6[i] == 0)
    {
      draw(0, tempX, tempY + 5);
    }
    if (firstPicture7[i] == 0)
    {
      draw(0, tempX, tempY + 6);
    }
    if (firstPicture8[i] == 0)
    {
      draw(0, tempX, tempY + 7);
    }
    if (firstPicture9[i] == 0)
    {
      draw(0, tempX, tempY + 8);
    }
    if (firstPicture10[i] == 0)
    {
      draw(0, tempX, tempY + 9);
    }
    if (firstPicture11[i] == 0)
    {
      draw(0, tempX, tempY + 10);
    }
    if (firstPicture12[i] == 0)
    {
      draw(0, tempX, tempY + 11);
    }

    tempX++;
  }
}
//Hasan och Ahmed
void drawBird2(int x, int y)
{
  int tempX, tempY;
  int i;
  uint8_t secondPicture1[17] = {
      1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
  uint8_t secondPicture2[17] = {
      1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1};
  uint8_t secondPicture3[17] = {
      1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
  uint8_t secondPicture4[17] = {
      1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1};

  uint8_t secondPicture5[17] = {
      1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1};

  uint8_t secondPicture6[17] = {
      1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1};

  uint8_t secondPicture7[17] = {
      0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1};

  uint8_t secondPicture8[17] = {
      0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0};

  uint8_t secondPicture9[17] = {
      1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1};
  uint8_t secondPicture10[17] = {
      1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1};
  uint8_t secondPicture11[17] = {
      1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1};
  uint8_t secondPicture12[17] = {
      1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1};

  tempX = x;
  tempY = y;
  for (i = 0; i < 17; i++)
  {
    draw(1, tempX + i, tempY);
    draw(1, tempX + i, tempY + 1);
    draw(1, tempX + i, tempY + 2);
    draw(1, tempX + i, tempY + 3);
    draw(1, tempX + i, tempY + 4);
    draw(1, tempX + i, tempY + 5);
    draw(1, tempX + i, tempY + 6);
    draw(1, tempX + i, tempY + 7);
    draw(1, tempX + i, tempY + 8);
    draw(1, tempX + i, tempY + 9);
    draw(1, tempX + i, tempY + 10);
    draw(1, tempX + i, tempY + 11);
  }

  tempX = x;
  tempY = y;

  for (i = 0; i < 17; i++)
  {

    if (secondPicture1[i] == 0)
    {
      draw(0, tempX, tempY);
    }

    if (secondPicture2[i] == 0)
    {
      draw(0, tempX, tempY + 1);
    }
    if (secondPicture3[i] == 0)
    {
      draw(0, tempX, tempY + 2);
    }
    if (secondPicture4[i] == 0)
    {
      draw(0, tempX, tempY + 3);
    }
    if (secondPicture5[i] == 0)
    {
      draw(0, tempX, tempY + 4);
    }
    if (secondPicture6[i] == 0)
    {
      draw(0, tempX, tempY + 5);
    }
    if (secondPicture7[i] == 0)
    {
      draw(0, tempX, tempY + 6);
    }
    if (secondPicture8[i] == 0)
    {
      draw(0, tempX, tempY + 7);
    }
    if (secondPicture9[i] == 0)
    {
      draw(0, tempX, tempY + 8);
    }
    if (secondPicture10[i] == 0)
    {
      draw(0, tempX, tempY + 9);
    }
    if (secondPicture11[i] == 0)
    {
      draw(0, tempX, tempY + 10);
    }
    if (secondPicture12[i] == 0)
    {
      draw(0, tempX, tempY + 11);
    }

    tempX++;
  }
}

//Ahmed
void upObs(int x, int upLength)
{
  int i;
  for (i = 0; i <= upLength; i++)
  {
    draw(0, x, i);
    draw(0, x + 1, i);
  }
}

//Ahmed
void downObs(int x, int downLength, int upLength)
{
  int downBorder = 32 - downLength;

  int i;
  for (i = 31; i >= downBorder; i--)
  {
    draw(0, x, i);
    draw(0, (x + 1), i);
  }

  upObs(x, upLength);
}

//Hasan och Ahmed
int checkWall(int birdY)
{
  int obsBor = birdY + 11;
  if (obsBor >= 31 || birdY == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

//Hasan och Ahmed
int checkObsclash(int obsX, int downLength, int upLength, int birdX, int birdY)
{
  int downBorder = 30 - downLength;
  int i = 0;
  int retur = 1;
  for (i = 0; i < 6; i++)
  {
    if ((birdX + 6 + i) == obsX && birdY == upLength)
    {
      retur = 0;
      break;
    }
  }

  if ((birdX + 12) == obsX && birdY + 1 == upLength)
  {
    retur = 0;
  }

  if ((birdX + 13) == obsX && birdY + 2 == upLength)
  {
    retur = 0;
  }
  for (i = 0; i < 3; i++)

    if ((birdX + 14) == obsX && birdY + 3 + i == upLength)
    {
      retur = 0;
      break;
    }
  if ((birdX + 15) == obsX && birdY + 6 == downBorder)
    retur = 0;
  if ((birdX + 16) == obsX && birdY + 7 == downBorder)
    retur = 0;
  for (i = 0; i < 2; i++)
    if ((birdX + 15) == obsX && (birdY + 7 + i) == downBorder)
      retur = 0;
  for (i = 0; i < 5; i++)
    if ((birdX + 14 - i) == obsX && (birdY + 10) == downBorder)
      retur = 0;
  for (i = 0; i < 5; i++)
    if ((birdX + 9 - i) == obsX && (birdY + 11) == downBorder)
      retur = 0;

  return retur;
}
//Hasan och Ahmed
int score(int obsX, int birdX)
{
  int score1 = 0;
  if (obsX == birdX)
    score1 = 1;
  return score1;
}

//Hasan och Ahmed
void resetDisplay(void)
{
  int i;
  for (i = 0; i < 512; i++)
  {

    icon[i] = 255;
  }
}


void display_string(int line, char *s)
{
  int i;
  if (line < 0 || line >= 4)
    return;
  if (!s)
    return;

  for (i = 0; i < 16; i++)
    if (*s)
    {
      textbuffer[line][i] = *s;
      s++;
    }
    else
      textbuffer[line][i] = ' ';
}

void display_image(int x, const uint8_t *data)
{
  int i, j;

  for (i = 0; i < 4; i++)
  {
    DISPLAY_CHANGE_TO_COMMAND_MODE;

    spi_send_recv(0x22);
    spi_send_recv(i);

    spi_send_recv(x & 0xF);
    spi_send_recv(0x10 | ((x >> 4) & 0xF));

    DISPLAY_CHANGE_TO_DATA_MODE;

    for (j = 0; j < 32 * 4; j++)
      spi_send_recv(~data[i * 32 * 4 + j]);
  }
}

void display_update(void)
{
  int i, j, k;
  int c;
  for (i = 0; i < 4; i++)
  {
    DISPLAY_CHANGE_TO_COMMAND_MODE;
    spi_send_recv(0x22);
    spi_send_recv(i);

    spi_send_recv(0x0);
    spi_send_recv(0x10);

    DISPLAY_CHANGE_TO_DATA_MODE;

    for (j = 0; j < 16; j++)
    {
      c = textbuffer[i][j];
      if (c & 0x80)
        continue;

      for (k = 0; k < 8; k++)
        spi_send_recv(font[c * 8 + k]);
    }
  }
}
int i = 0;

/* Helper function, local to this file.
   Converts a number to hexadecimal ASCII digits. */
static void num32asc(char *s, int n)
{
  int i;
  for (i = 28; i >= 0; i -= 4)
    *s++ = "0123456789ABCDEF"[(n >> i) & 15];
}

/*
 * nextprime
 *
 * Return the first prime number larger than the integer
 * given as a parameter. The integer must be positive.
 */
#define PRIME_FALSE 0 /* Constant to help readability. */
#define PRIME_TRUE 1  /* Constant to help readability. */
int nextprime(int inval)
{
  register int perhapsprime = 0; /* Holds a tentative prime while we check it. */
  register int testfactor;       /* Holds various factors for which we test perhapsprime. */
  register int found;            /* Flag, false until we find a prime. */

  if (inval < 3) /* Initial sanity check of parameter. */
  {
    if (inval <= 0)
      return (1); /* Return 1 for zero or negative input. */
    if (inval == 1)
      return (2); /* Easy special case. */
    if (inval == 2)
      return (3); /* Easy special case. */
  }
  else
  {
    /* Testing an even number for primeness is pointless, since
     * all even numbers are divisible by 2. Therefore, we make sure
     * that perhapsprime is larger than the parameter, and odd. */
    perhapsprime = (inval + 1) | 1;
  }
  /* While prime not found, loop. */
  for (found = PRIME_FALSE; found != PRIME_TRUE; perhapsprime += 2)
  {
    /* Check factors from 3 up to perhapsprime/2. */
    for (testfactor = 3; testfactor <= (perhapsprime >> 1) + 1; testfactor += 1)
    {
      found = PRIME_TRUE;                   /* Assume we will find a prime. */
      if ((perhapsprime % testfactor) == 0) /* If testfactor divides perhapsprime... */
      {
        found = PRIME_FALSE;   /* ...then, perhapsprime was non-prime. */
        goto check_next_prime; /* Break the inner loop, go test a new perhapsprime. */
      }
    }
  check_next_prime:;         /* This label is used to break the inner loop. */
    if (found == PRIME_TRUE) /* If the loop ended normally, we found a prime. */
    {
      return (perhapsprime); /* Return the prime we found. */
    }
  }
  return (perhapsprime); /* When the loop ends, perhapsprime is a real prime. */
}

/*
 * itoa
 *
 * Simple conversion routine
 * Converts binary to decimal numbers
 * Returns pointer to (static) char array
 *
 * The integer argument is converted to a string
 * of digits representing the integer in decimal format.
 * The integer is considered signed, and a minus-sign
 * precedes the string of digits if the number is
 * negative.
 *
 * This routine will return a varying number of digits, from
 * one digit (for integers in the range 0 through 9) and up to
 * 10 digits and a leading minus-sign (for the largest negative
 * 32-bit integers).
 *
 * If the integer has the special value
 * 100000...0 (that's 31 zeros), the number cannot be
 * negated. We check for this, and treat this as a special case.
 * If the integer has any other value, the sign is saved separately.
 *
 * If the integer is negative, it is then converted to
 * its positive counterpart. We then use the positive
 * absolute value for conversion.
 *
 * Conversion produces the least-significant digits first,
 * which is the reverse of the order in which we wish to
 * print the digits. We therefore store all digits in a buffer,
 * in ASCII form.
 *
 * To avoid a separate step for reversing the contents of the buffer,
 * the buffer is initialized with an end-of-string marker at the
 * very end of the buffer. The digits produced by conversion are then
 * stored right-to-left in the buffer: starting with the position
 * immediately before the end-of-string marker and proceeding towards
 * the beginning of the buffer.
 *
 * For this to work, the buffer size must of course be big enough
 * to hold the decimal representation of the largest possible integer,
 * and the minus sign, and the trailing end-of-string marker.
 * The value 24 for ITOA_BUFSIZ was selected to allow conversion of
 * 64-bit quantities; however, the size of an int on your current compiler
 * may not allow this straight away.
 */
#define ITOA_BUFSIZ (24)
char *itoaconv(int num)
{
  register int i, sign;
  static char itoa_buffer[ITOA_BUFSIZ];
  static const char maxneg[] = "-2147483648";

  itoa_buffer[ITOA_BUFSIZ - 1] = 0; /* Insert the end-of-string marker. */
  sign = num;                       /* Save sign. */
  if (num < 0 && num - 1 > 0)       /* Check for most negative integer */
  {
    for (i = 0; i < sizeof(maxneg); i += 1)
      itoa_buffer[i + 1] = maxneg[i];
    i = 0;
  }
  else
  {
    if (num < 0)
      num = -num;        /* Make number positive. */
    i = ITOA_BUFSIZ - 2; /* Location for first ASCII digit. */
    do
    {
      itoa_buffer[i] = num % 10 + '0'; /* Insert next digit. */
      num = num / 10;                  /* Remove digit from number. */
      i -= 1;                          /* Move index to next empty position. */
    } while (num > 0);
    if (sign < 0)
    {
      itoa_buffer[i] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return (&itoa_buffer[i + 1]);
}
