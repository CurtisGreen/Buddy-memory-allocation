
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
struct free_node* free_head;
char* linked_list;
char* free_list;
int totalSize = 0;
int curSize = 0;
int blockSize = 0;
int M,C;
int numHeaders;

unsigned int init_allocator(unsigned int _basic_block_size, unsigned int _length){
	M = _basic_block_size;		// total memory, TODO: might need to change this to M = (M/C)
	C = _length;				// the smallest (it will be used Addr my malloc)
	numHeaders = (log((double)M)/log((double)2)-log((double)C)/log((double)2))+1; //5
	linked_list = (char*)malloc(M);
	free_list = (char*)malloc(numHeaders*20);
	head = (node*)linked_list;
	free_head = (free_node*)(free_list+(numHeaders-1)*20);
	free_node* p = free_head;
	//free_node* free_tail = free_head;
	p->size = C;
	for (int i =0; i < numHeaders-1; ++i) {	//Free list
		p = free_head-1;	//Might be wrong
		p->next = free_head;
		p->size = p->next->size*2;
		free_head = p;
	}
	free_head->down = head;	
}	

char* split(free_node* p){
	int original = p->size;
	int temp_size = p->size;
	free_node* search = free_head;
	while (temp_size < M){	//might need to be <=
		while (search->next->size != temp_size){	//Might need to be search->size
			search = search->next;
		}
		if (p->down != NULL){	//Free node exists
			while (p->size != original){	//Run until reach original block
				node* buddy1 = p->down;
				buddy1->size = p->size;
				node* buddy2 = (node*)((char*)p->down+p->size/2);
				buddy1->free = true;
				buddy2->free = true;
				p->down = buddy1;
				p = p->next;
				p->down = buddy2;
			}
			node* ret_node = p->down;
			p->down = p->down->next;    //Set to next down node
			ret_node->free = false;
			return (char*)ret_node + 16;
		}
		else{
			temp_size = temp_size*2;
		}
	}
	return (char*)(-1);
}

//my_malloc(129);
extern Addr my_malloc(unsigned int _length) {
	if (_length+16 <= M){	//Verify that the block can fit
	    //search free list
	    free_node* p = free_head;
	    if (_length <= 16+C){	//Use smallest block
	    	while (p){
				p = p->next;
			}
			if (p->down != NULL){	//Free node exists
				node* ret_node = p->down;
	    	    p->down = p->down->next;    //Set to next down node
				ret_node->free = false;
	    	    return (char*)ret_node + 16;
			}
			else{
				return split(p);
			}
	    }
	    else if (_length >= (M/2)+16){    //Use biggest block 
	    	if (p->down != NULL){	//Free node exists
				node* ret_node = p->down;
	    	    p->down = p->down->next;    //Set to next down node
	    	    ret_node->free = false;
				return (char*)ret_node + 16;
	    	}
	    	else{    //No free space
	    	    printf("Not enough space in memory");
				return (char*)-1;
	    	}
	    }
	    else{    //Use middle blocks
			while (_length+16 < p->size && _length+16 <= p->next->size){    // 64< x <512
				p = p->next;
			}
			if (p->down != NULL){	//Check if there is a node here
				node* ret_node = p->down;
				p->down = p->down->next;    //Set to next down node
				ret_node->free = false;
				return (char*)ret_node + 16;
			}
			else{
				return split(p);	//No node of this size
			}
	    }
	}
	else{
	    printf("The length provided is too large to store data in");
	}
}




// back to orginal memory + merge -_-
int release_allocator(){
    //TODO: call free and make sure no more operations are allowed to be done
	return 0;
}

extern int my_free(Addr _a) {
  //assign pointer to given address
  //check if its buddy is free, find the buddy address using xor (and possibly bit shift>>) on the given address
  //If it's free, combine it and call my_free() using this new block (this recursively combines blocks)
  //If it's not free, just make the header point to it (make sure that if the header is already pointing to an object, use that object's next pointer)
  //Assign that block as free
  return 0;
}

