/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <math.h>


//function 
//Trial division algorithm 
//if there is a rimind btn 2 and sqrt(n) n is not prime number
int is_prime(int n)
{


if(n==0 || n==1)
    return 0;
else
   for(int i = 2; i<= sqrt(n); i++)
   if((n%i)==0)
   return 0;
     

return 1;

}

int main(void){
  printf("%d\n", is_prime(17));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
