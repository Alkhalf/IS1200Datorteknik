/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6

int myColumns = 0;

//function 
void print_number(int n)
  
{

if( myColumns==COLUMNS)
{
  
 printf("\n");
 myColumns=0;
 print_number(n);
}
else
{


  if(n<10)
  printf("    %d",n);
  else if(n>10 && n<100)
  printf("   %d",n);
  else
  printf("  %d",n);


  myColumns= myColumns+1;
}

//end of function
}

int is_prime(int n)
{

if(n==0|| n==1)
    return 0;
else
   for(int i = 2; i<=sqrt(n); i++)
   if((n%i)==0)
   return 0;
     

return 1;

}

void print_primes(int n){
 for(int i = 0; i<=n; i++){
   if(is_prime(i))
   print_number(i); 
 }
  
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
   { 
    print_primes(atoi(argv[1]));
    printf("\n");
   }
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
