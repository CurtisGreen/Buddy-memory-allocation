
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <iostream>
#include "my_allocator.h"
#include <math.h>

// M b 
// M/C

using namespace std;
struct node* head;
struct free_node* free;
char* linked_list;
char* free_list;
int totalSize = 0;
int curSize = 0;
int blockSize = 0;
int M,C;

unsigned int init_allocator(unsigned int _basic_block_size, unsigned int _length){
	M = _basic_block_size;		// total memory
	C = _length;				// the smallest (it will be used Addr my malloc)
	int numHeaders = (log((double)M)/log((double)2)-log((double)C)/log((double)2))+1; //5
	linked_list = (char*)malloc(M);
	free_list = (char*)malloc(numHeaders*20);
	head = (node*)linked_list;
	free = (free_node*)(free_list+(numHeader-1)*20);
	free_node* p = free;
	for (int i =0; i < numHeaders-1; ++i) {	//Free list
		free_node* p = free-1;
		p->next = free;
		free = p;
	}
	free->down = head;


		
	
}	

//my_malloc(129);
extern Addr my_malloc(unsigned int _length) {
	
	
	
  return malloc((size_t)_length); // returning char pointer
}

// back to orginal memory + merge -_-
int release_allocator(){
	
}

extern int my_free(Addr _a) {
  /* Same here! */
  free(_a);
  return 0;
}

