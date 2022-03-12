
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6

int myColumns = 0;

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


//sieve of Eratosthens algorithm
void print_sieves(int n)
 {

//skapa array som börjar från 2 upp till n
  int sup= (n)*(n);
  int array [sup-1];

  for(int i = 0; i< sup;i++ )
      array[i]=2+i;

 int index=0;
        for(int j = 2;j<=sqrt(n*n);j++)
        {
            if(array[index]==1)
            {
                index++;
                //gå till nästa itration när det är ett tal som redan markerade
                continue;
            }

                //om vi börjar från 2 firstValue is 4
                int firstValue = index + j;
                while (firstValue < sup)  //make an variable for input-1
                {
                    //markera att index som fyllas med 1 är INTE prime number
                    array[firstValue] = 1;
                    firstValue = firstValue + j;
                }
                index++;

        }
        int indexs=0;
        int value=0;
          for(int i = 0; i< sup;i++ )
          { 
            if (array[i]!=1 && indexs < n)
                {
                //print_number(array[i]);
                indexs++;
                value =i;
                }

          }

            print_number(array[value]);
            printf("\n");
          
 }




// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
   { 
    print_sieves(atoi(argv[1]));
    printf("\n");
   }
  else
    printf("Please state an interger number.\n");
  return 0;
}
