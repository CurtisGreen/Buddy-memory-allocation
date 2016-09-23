#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <getopt.h>
#include <iostream>
#include <cstring> //memset
#include "my_allocator.h"
#include "ackerman.h"

using namespace std;
/*
unsigned long int num_allocations;
int ackerman(int a, int b) {
 This is the implementation of the Ackerman function. The function itself is very
   function is very simple (just two recursive calls). We use it to exercise the
   memory allocator (see "my_alloc" and "my_free"). 
   For this, there are additional calls to "gettimeofday" to measure the elapsed
   time.
 
 //cout << " ?_? " << endl;
  void * mem;

  //The size "to_alloc" of the region to allocate is computed randomly: 
  int to_alloc =  ((2 << (rand() % 19)) * (rand() % 100)) / 100;
  if  (to_alloc < 4) to_alloc = 4;

  int result = 0, i;
 //cout << " ?_? " << endl;
  char c;

  mem = my_malloc(to_alloc * sizeof(char));

  num_allocations++;

  if (mem != NULL) {
 //cout << " ?_? " << endl;
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
    my_free(mem);
  }

  return result;
}*/


int main(int argc, char ** argv) {

	int c;
	int b = 128;	 // block size = 2^9
	int M = b * 12;  // mem size = 512kB = 2^10 * 2^7 // so we have space for 12 items
	void * A;
	void * B;
	void * C;
	void * D;
	/* by ackerman, we have segmentation fault 
	   i copied it from ackerman.cpp (given source code)
	cout << "M value: ";
	cin >> M;
	cout << "b value: ";
	cin >> b;
	ackerman(M, b);
	*/
	
	while ((c = getopt(argc, argv, "bs:")) != -1){
		switch (c){
			case 'b':
				b = atoi(optarg);
				break;
			case 's':
				M = atoi(optarg);
				break;
		}
		//ackerman()
	}
	cout <<"initialize"<<endl;
	init_allocator(1024,64);
	/*printlist();
	cout <<"allocate 20"<<endl;
	A = my_malloc(20);

	//cout << "A buddy: " << ((node*)((void*)(((unsigned long)(A))^(((node*)(A-16))->size))-16))->free << " A size: " << ((node*)(A-16))->size << endl;


	cout <<"allocate 20"<<endl;
	B = my_malloc(20);
	C = my_malloc(20);
	//cout << "A address: " << (A-16) << endl;
	//cout << "B address: " << (B-16) << endl;
	

	//Test function
	printlist();

	//cout << "A buddy = " << ((void*)(((unsigned long)(A))^(((node*)(A-16))->size))-16)<<endl;
	//cout << "B buddy = " << ((void*)(((unsigned long)(B))^(((node*)(B-16))->size))-16)<<endl;


	my_free(A);
	printlist();
	my_free(B);
	printlist();*/

	//cout << "B buddy free = " << ((node*)(B-16))->free << endl;


  // input parameters (basic block size, memory length)

  // init_allocator(basic block size, memory length)

  ackerman_main();

  release_allocator();
}
