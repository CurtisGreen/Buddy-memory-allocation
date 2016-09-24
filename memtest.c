#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <getopt.h>
#include <iostream>
#include <cstring> //memset
#include<assert.h> //assert

#include "my_allocator.h"


using namespace std;
unsigned long int num_allocations;



void print_time_diff(struct timeval * tp1, struct timeval * tp2) {
  /* Prints to stdout the difference, in seconds and museconds, between two
     timevals. */

  long sec = tp2->tv_sec - tp1->tv_sec;
  long musec = tp2->tv_usec - tp1->tv_usec;
  if (musec < 0) {
    musec += 1000000;
    sec--;
  }
  printf(" [sec = %ld, musec = %ld] ", sec, musec);

}




int ackerman(int a, int b) {
 /*
 This is the implementation of the Ackerman function. The function itself is very
   function is very simple (just two recursive calls). We use it to exercise the
   memory allocator (see "my_alloc" and "my_free"). 
   For this, there are additional calls to "gettimeofday" to measure the elapsed
   time.
 */
 cout << "1 ?_? " << endl;
  void * mem;
  //The size "to_alloc" of the region to allocate is computed randomly: 
  int to_alloc =  ((2 << (rand() % 19)) * (rand() % 100)) / 100;
  if  (to_alloc < 4) to_alloc = 4;
  int result = 0, i;
 cout << "2 ?_? " << endl;
  char c;
  mem = my_malloc(to_alloc * sizeof(char));
  num_allocations++;
  if (mem != NULL) {
 cout << "3 ?_? " << endl;
    // generate a random byte to fulfill the allocated block of memory
    c = rand() % 128;
    memset(mem, c, to_alloc * sizeof(char));
    if (a == 0)
      result = b + 1;
    else if (b == 0)
      result = ackerman(a - 1, 1);
    else
      result = ackerman(a - 1, ackerman(a, b - 1) );
    // check memory value before deleting
    for (i = 0; i < to_alloc; i++) {
        if (((char*)mem)[i] != c) {
            printf("Memory checking error!\n");
            break;
        }
    }
 //cout << " ?_? " << endl;
    //my_free(mem);
  }
  return result;
}


extern void ackerman_main() {
  /* This is function repeatedly asks the user for the two parameters
     "n" and "m" to pass to the ackerman function, and invokes the function.
     Before and after the invocation of the ackerman function, the 
     value of the wallclock is taken, and the elapsed time for the computation
     of the ackerman function is output.
  */

  int n, m; /* Parameter for the invocation of the Ackerman function. */ 

  struct timeval tp_start; /* Used to compute elapsed time. */
  struct timeval tp_end;

  for (;;) {

    num_allocations = 0;

    printf("\n");
    printf("Please enter parameters n and m to ackerman function.\n");
    printf("Note that this function takes a long time to compute,\n");
    printf("even for small values. Keep n at or below 3, and mat or\n");
    printf("below 8. Otherwise, the function takes seemingly forever.\n");
    printf("Enter 0 for either n or m in order to exit.\n\n");

    printf("  n = "); scanf("%d", &n);
    if (!n) break;
     printf("  m = "); scanf("%d", &m);
    if (!m) break;

    printf("      n = %d, m = %d\n", n, m);

    assert(gettimeofday(&tp_start, 0) == 0);
    /* Assert aborts if there is a problem with gettimeofday.
       We rather die of a horrible death rather than returning
       invalid timing information! 
    */

    int result = ackerman(n, m);

    assert(gettimeofday(&tp_end, 0) == 0);
    /* (see above) */

    printf("Result of ackerman(%d, %d): %d\n", n, m, result); 

    printf("Time taken for computation : "); 
    print_time_diff(&tp_start, &tp_end);
    printf("\n");

    printf("Number of allocate/free cycles: %lu\n\n\n", num_allocations); 
  }
  
  printf("Reached end of Ackerman program. Thank you for using it.\n");

}


int main(int argc, char ** argv) {

	int c;
	int a;
	int b = 128;	 // block size = 2^9
	int M = b * 12;  // mem size = 512kB = 2^10 * 2^7 // so we have space for 12 items
	void * A;
	void * B;
	void * C;
	void * D;
	
	cout << "---- test case----" << endl;
	cout << "bbs=128, m = 128MB" << endl;
	cout << "(3,6)(3,8)(1,x)(2,x)(3,x)(3,7)(3,8)" << endl; 

	
	
	// their getopt() code, keep intact
	while ((c = getopt(argc, argv, "bs:")) != -1){
		switch (c){
			case 'b':
				b = atoi(optarg);
				break;
			case 's':
				M = atoi(optarg);
				break;
		}
	}

	init_allocator(1024,64);

	ackerman_main();
  	release_allocator();
  	cout << "bye" << endl;
	/*
	cout <<"initialize"<<endl;
	init_allocator(1024,64);
	printlist();
	cout <<"allocate 20"<<endl;
	A = my_malloc(20);

	//cout << "A buddy: " << ((node*)((void*)(((unsigned long)(A))^(((node*)(A-16))->size))-16))->free << " A size: " << ((node*)(A-16))->size << endl;


	cout <<"allocate 20"<<endl;
	B = my_malloc(20);
	C = my_malloc(20);
	cout << "real A   : " << A << endl; 
	cout << "A address: " << (A-16) << endl;
	cout << "B address: " << (B-16) << endl;
	

	//Test function
	printlist();

	cout << "A buddy = " << ((void*)(((unsigned long)(A))^(((node*)(A-16))->size))-16)<<endl;
	cout << "B buddy = " << ((void*)(((unsigned long)(B))^(((node*)(B-16))->size))-16)<<endl;

	my_free(A); 
	//cout << "A    :" << A << endl;
	//cout << "A-16 :" << A-16 << endl;
	my_free(B);


	//cout << "B buddy free = " << ((node*)(B-16))->free << endl;

  // input parameters (basic block size, memory length)

  // init_allocator(basic block size, memory length)

  
*/
  
}
