
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <iostream>
#include "my_allocator.h"
#include <math.h>
#include <typeinfo>

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
	M = _length;		// total memory
	C = _basic_block_size;				// the smallest (it will be used Addr my malloc)
	//cout << "in init" << endl;
	numHeaders = (log((double)M)/log((double)2)-log((double)C)/log((double)2))+1; //5
	//cout << "numHeaders" << numHeaders << endl;
	linked_list = (char*)malloc(M);
	//cout << "linkedlist" << endl;
	free_list = (char*)malloc(numHeaders*20);
	//cout << "freelist" << endl;
	head = (node*)linked_list;
	//cout << "linkedhead" << endl;
	free_head = (free_node*)(free_list+(numHeaders-1)*20);
	//cout << "freehead" << endl;
	free_node* p = free_head;
	//free_node* free_tail = free_head;
	p->size = C;
	//cout << "m = " << M << endl;

	//cout << "numHeaders = " << numHeaders << endl;
	for (int i =0; i < numHeaders-1; ++i) {	//Free list
		//cout << "infreelistloop, i = " << i << endl;
		p = (free_head-1);	//Might be wrong
		//cout << "moved head back" << endl;
		p->next = free_head;
		//cout << "assigned node" << endl;
		p->size = p->next->size*2;
		//cout << "assigned size" << endl;
		free_head = p;
		//cout << "moved head to front" << endl;
		/* I think we need to insert two nodes here undert p, 
		if we do not insert two nodes, then p->down node is always null*/
	}
	//cout << "made freelist" << endl;
	free_head->down = head;
	head->size = M;
	head->free = true;
	cout << "succesfully initialized" << endl;
}	

char* split(free_node* p){
	int original = p->size;
	int temp_size = p->size;
	free_node* search = free_head;
	while (temp_size <= M){	//might need to be <
		search = free_head;
		while (search->next->size != temp_size){	//Might need to be search->size
			search = search->next;
		}
		//cout << search->size << endl;
		if (search->down != NULL){	//Free node exists
			//cout << "search size = " << search->size << ", target = " << original << endl;
			while (search->size != original){	//Run until reach original block
				//cout << "size = " << search->down->size << ", free = " << search->down->free << endl; 
				node* buddy1 = search->down;
				buddy1->size = search->size/2;
				node* buddy2 = (node*)((char*)search->down+search->size/2);
				buddy2->size = search->size/2;
				//cout << "Buddy 1 address = " << (buddy1) << " buddy 2 address = " << (buddy2) << endl;
				buddy1->free = true;
				buddy2->free = true;
				//cout << buddy1->free << buddy2->free << endl;
				search->down = search->down->next;

				search = search->next;
				search->down = buddy1;
				buddy1->next = buddy2;
				cout << "buddy2's next" <<  (unsigned long)((void*)buddy2->next) << endl;
				if ((unsigned long)((void*)buddy2->next) > 0x800000000000){
					//cout << "in weird " << endl;
					buddy2->next = NULL;
				}
			}
			node* ret_node = search->down;
			search->down = search->down->next;    //Set to next down node
			ret_node->free = false;
			ret_node->next = NULL;
			//cout << ret_node->free << endl;
			return (char*)ret_node + 16;
		}
		else{
			//cout << "node not found, moving upwards" << endl;
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
	    	//cout << "inside smallest bracket" << endl;
	    	while (p->next!= NULL){ 				     // if next is null, escape, it is at the end of block
				p = p->next;
			}
			//cout << "got to smallest node" << endl;
			if (p->down != NULL){	//Free node exists
				//cout << "free node exists" << endl;
				//cout << p->down->size << endl;
				node* ret_node = p->down;
	    	    p->down = p->down->next;    //Set to next down node
	    	    //cout << ret_node->free << endl;
				ret_node->free = false;
				ret_node->next = NULL;
				//cout << "bool " << ret_node->free;
	    	    return (char*)ret_node + 16;
			}
			else{
				//cout << "No free nodes" << endl;
				return split(p);
			}
	    }
	    else if (_length >= (M/2)+16){    //Use biggest block 
	    	if (p->down != NULL){	//Free node exists
				node* ret_node = p->down;
	    	    p->down = p->down->next;    //Set to next down node
	    	    ret_node->free = false;
				ret_node->next = NULL;
				//cout << "bool " << ret_node->free;
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
				//cout << "bool " << ret_node->free;
				ret_node->next = NULL;
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





int release_allocator(){
	free(linked_list);
	//cout << "freed linked_list" << endl;
	//free(((char*)free_head));
	//cout << "freed free_list =" << endl;
    //TODO: call free and make sure no more operations are allowed to be done
	return 0;
}

extern int my_free(Addr _a) {
  cout << endl << "----my_free function------" << endl;
  //printlist();
  //cout << "right before node define" << endl;
  node* it = (node*)(_a-16);
  
  //comment graveyard:
  //cout << "defined node" << endl;
  //node* buddy;
  //cout << "created node it "<< (*(int*)((char*)_a-16)) << " " << (*(bool*)((char*)_a-4)) << endl;
  //node* buddy = (node*)((void*)(((unsigned long)(_a))^(((node*)(_a-16))->size))-16); 
  //node* buddy = (node*)(((_a)-((void*)(head))^((it->size)+((void*)(head)))));
  //unsigned long test = (unsigned long)((it->size) + ((void*)head));
  
  unsigned long test2 = ((unsigned long)(_a)- (unsigned long)((void*)head));
  node* buddy = (node*)((void*)((test2^(it->size))+ (unsigned long)((void*)head))-16);

  
  cout << "its size   : " << (int)((it)->size) << endl;
  cout << "its memory : " << _a-16 << endl;
  cout << "its buddy  : " << buddy <<endl;
  cout << "buddy size?: " << ((buddy)->size) << endl;
  cout << "buddy free?: " << ((buddy)->free) << endl;
  
  if ((bool)((buddy)->free)== true && buddy->size == it->size) { // // find its double size move pointer + free=1 + combine
	//cout << "buddy is free" << endl;
	free_node* search = free_head;
	while (search->size != (it)->size){	
			search = search->next;
	}
	//cout << "found header" << endl;
	node* node_search = search->down;
	cout << node_search << " " << buddy << endl;
	if (node_search == buddy){	//buddy is at the front
		//cout << "buddy first in list" << buddy->next << endl;
		search->down = node_search->next;
	}
	else{
		cout << "buddy not first in list " << node_search << endl;
		while(node_search != NULL && node_search->next != buddy){	//disconnect from list
			cout << node_search << endl;
			node_search = node_search->next;
		}
		cout << node_search << endl;
		if (node_search!= NULL && node_search->next == buddy){
			node_search->next = node_search->next->next;
		}
	}
	
	if (it < buddy){
		it->size = it->size*2;
		//cout << "buddy is second" << endl;
	}
	else{
		buddy->size = buddy->size*2;
		it = buddy;
		//cout << "buddy first" << endl;
	}
	
	it->free = true;
	it->next = NULL;
	my_free(((char*)it+16));
	
  }
  else { 
	//cout << "node is not free" << endl;
	free_node* search = free_head;
	node* node_search;
	while (search->size != ((it)->size) ){	
		search = search->next;
	}
	//cout << "found header" << endl;
	node_search = search->down;
	//cout << search->size << endl;
	if (node_search != NULL && ((unsigned long)((char*)node_search)) < 0x800000000000){
		//cout << "in if " << node_search << endl;
		while(node_search->next != NULL){
			//cout << "in while" << endl;
			node_search = node_search->next;
		}
		//cout << " out of while " << endl;
		node_search->next = it;
		//cout << "node has been pointed to" << endl;
	}
	else{
		//cout << "in else" << endl;
		search->down = it;
	}
	//search->next->down = search->next->down->next;
	//cout << "found final node" << endl;
	it->free = true;
	it->next = NULL;
  }
  
  
  //assign pointer to given address
  //check if its buddy is free, find the buddy address using xor (and possibly bit shift>>) on the given address
  //If it's free, combine it and call my_free() using this new block (this recursively combines blocks)
  //If it's not free, just make the header point to it (make sure that if the header is already pointing to an object, use that object's next pointer)
  //Assign that block as free
  return 0;
}

void printlist(){
	cout << "\nPrinting list\n" << endl;
	free_node* free_head_temp = free_head;
	node* node_temp;
	while (free_head_temp){
		node_temp = free_head_temp->down;
		cout << "under free node: " << free_head_temp->size << endl;
		while(node_temp){
			cout << node_temp->size << " " << node_temp->free << " " << node_temp << endl;
			node_temp = node_temp->next;
		}
		free_head_temp = free_head_temp->next;
	}
}
