#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <getopt.h>
#include <iostream>
#include <cstring> //memset
#include "my_allocator.h"
#include "ackerman.h"

using namespace std;


int main(int argc, char ** argv) {

	int c;
	int b = 128;	 // block size = 2^9
	int M = 134217728;  // mem size = 512kB = 2^10 * 2^7 // so we have space for 12 items
	void * A;
	void * B;
	void * C;
	void * D;
	
	// their getopt() code, keep intact
	while ((c = getopt(argc, argv, "b:s:")) != -1){
		switch (c){
			case 'b':
				b = atoi(optarg);
				break;
			case 's':
				M = atoi(optarg);
				break;
		}
	}


	cout <<"initialize"<<endl;
	init_allocator(b, M);
	printlist();
  
  
  	//These tests can be used in place of the ackerman function
  
	/*
	cout <<"allocate 20"<<endl;
	A = my_malloc(20);



	cout <<"allocate 20"<<endl;
	B = my_malloc(20);
	//C = my_malloc(20);
	//cout << "A address: " << (A-16) << endl;
	//cout << "B address: " << (B-16) << endl;
	

	//Test function
	//printlist();

	//cout << "A buddy = " << ((void*)(((unsigned long)(A))^(((node*)(A-16))->size))-16)<<endl;
	//cout << "B buddy = " << ((void*)(((unsigned long)(B))^(((node*)(B-16))->size))-16)<<endl;


	my_free(A);
	//printlist();
	my_free(B);
	//printlist();

	//cout << "B buddy free = " << ((node*)(B-16))->free << endl;
	*/

  // input parameters (basic block size, memory length)

  // init_allocator(basic block size, memory length)

  ackerman_main();

  release_allocator();
}
