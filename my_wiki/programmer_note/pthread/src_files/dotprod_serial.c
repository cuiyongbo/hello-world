/******************************************************************************
* FILE: dotprod_serial.c
* DESCRIPTION:
*   This is a simple serial program which computes the dot product of two 
*   vectors.  The threaded version can is dotprod_mutex.c.
* SOURCE: Vijay Sonnad, IBM
* LAST REVISED: 01/29/09 Blaise Barney
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*   
The following structure contains the necessary information  
to allow the function "dotprod" to access its input data and 
place its output so that it can be accessed later. 
*/

typedef struct 
{
  double      *a;
  double      *b;
  double     sum; 
  int    veclen; 
} DOTDATA;

#define VECLEN 100000
DOTDATA dotstr; 

/*
We will use a function (dotprod) to perform the scalar product. 
All input to this routine is obtained through a structure of 
type DOTDATA and all output from this function is written into
this same structure.  While this is unnecessarily restrictive 
for a sequential program, it will turn out to be useful when
we modify the program to compute in parallel.
*/

void dotprod()
{
/*
Perform the dot product and assign result
to the appropriate variable in the structure. 
*/
  double mysum = 0;
  for (int i=0; i<dotstr.veclen ; i++) 
    mysum += (dotstr.a[i] * dotstr.b[i]);
   
  dotstr.sum = mysum;
}

/*
The main program initializes data and calls the dotprd() function.
Finally, it prints the result.
*/

int main (int argc, char *argv[])
{
  /* Assign storage and initialize values */
  int len = VECLEN;
  double* a = (double*) malloc (len*sizeof(double));
  double* b = (double*) malloc (len*sizeof(double));
    
  for (int i=0; i<len; i++) 
  {
    a[i]=1;
    b[i]=a[i];
  }
  
  dotstr.veclen = len; 
  dotstr.a = a; 
  dotstr.b = b; 
  dotstr.sum=0;
  
  /* Perform the  dotproduct */
  dotprod ();
  
  /* Print result and release storage */ 
  printf ("Sum =  %f \n", dotstr.sum);
  free (a);
  free (b);
}