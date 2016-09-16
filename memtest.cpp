#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "my_allocator.h"

int main(int argc, char ** argv) {

	int c;
	int b = 128;	 // block size = 2^9
	int M = b * 12;  // mem size = 512kB = 2^10 * 2^7 // so we have space for 12 items
	
	
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
  // input parameters (basic block size, memory length)

  // init_allocator(basic block size, memory length)

  //ackerman_main();

  // release_allocator()
}
