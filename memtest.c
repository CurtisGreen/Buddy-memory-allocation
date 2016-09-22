#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <getopt.h>
#include <iostream>

#include "my_allocator.h"

using namespace std;

int main(int argc, char ** argv) {

	int c;
	int b = 128;	 // block size = 2^9
	int M = b * 12;  // mem size = 512kB = 2^10 * 2^7 // so we have space for 12 items
	void * A;
	void * B;
	void * C;
	void * D;
	
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
	cout <<"initialize"<<endl;
	init_allocator(1024,64);
	cout <<"allocate 20"<<endl;
	A = my_malloc(20);
	cout <<"allocate 20"<<endl;
	B = my_malloc(20);
	cout << "A address: " << A << endl;
	cout << "B address: " << B << endl;
	
	
	
	int i = 16;
	std::ostringstream os;
	os << std::hex <<  i;
	string k = os.str();
	//cout << k << os.str();
	i = atoi((k).c_str());
	cout << i << endl;

	int m = 0;
	m = i ^ (int)C;
	cout << "xor: " << m;
  // input parameters (basic block size, memory length)

  // init_allocator(basic block size, memory length)

  //ackerman_main();

  // release_allocator()
}
