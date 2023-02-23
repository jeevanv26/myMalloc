#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"


static char memory[4096];

struct header{
  size_t data;
  bool free;
  struct header * next;
};

// for my use only
void printHeapRange(){
  printf("%p\n", (void*)memory);
  printf("%p\n", (void*)(memory+4096));
}


void *mymalloc(size_t size, char *file, int line){

// checks if someone tries to malloc 0 bytes
  if(size == 0)
    return NULL;
  struct header *p = (struct header*)memory;

  //initializes heap memory
  if(p -> data == 0){
    p-> data = 4096 - sizeof(struct header);
    p-> free = true;
    p-> next = NULL;
  }

  // while look to search for free space
  while(p!= NULL){

     if(p -> free == true &&  size <= p -> data){ // if statement to check if space is free and has enough space for requested number of bytes

      // unfrees requested byte size for use and leaves the rest of the chunk of memory free
      p->free = false;
      struct header *temp = p -> next;
      p-> next = (struct header*)((char*)p + sizeof(struct header) + size);
      if( p-> data > size){
        (p -> next) -> data = p -> data - size - sizeof(struct header);
      (p->next) -> free = true;
      ( p->next)-> next = temp;
      }
      p -> data = size;
      return (void*)((char*)p + sizeof(struct header));
    }
    else{
      p = p -> next; // goes to the next chunk of memory
    }
  }
  // case where there is no space for malloc
  printf("Error: From file %s, line %d, you are calling malloc when there is no heap space left\n",file,line);
  return NULL;
}
void myfree(void *ptr, char *file, int line){

  struct header * pointer = (struct header*)memory;

  // error case where address is within heap array
  if(ptr == NULL)
    printf("Error: From file %s, line %d, you are calling free on an address not obtained from malloc\n",file,line);
  else{
    while(pointer != NULL){
      // checks if address matches the start of a chunk of data
      if((void*)((char*)pointer + sizeof(struct header)) == ptr){
        //checks if that pointer has already been freed
        if(pointer -> free == false){
          //frees chunk of memory and handles coalescing of adjacent block
          if(pointer->next != NULL && (pointer -> next )-> free == true){
            char* temp = (char*) (pointer -> next);
            pointer -> data = pointer -> data + sizeof(struct header) + (pointer-> next)-> data;
            pointer -> next = (pointer -> next) -> next;
            for(int x=0; x < sizeof(struct header); x++){
              *temp = 0;
              temp = temp + 1;
            }
          }
          pointer-> free = true;
        }
        else
        // error case where pointer is already freed
          printf("Error: From file %s, line %d, you are calling free on an already free chunk\n",file,line);
        break;
      }
      //error case where address called  is not at the start of the chunk of data
      if( (void*)((char*)pointer + sizeof(struct header)) != ptr && ptr >= (void*)pointer && ptr < (void*)(pointer->next) ){
        printf("Error: From file %s, line %d, you are calling free at an address not at the start of the chunk\n",file,line);
        break;
      }
      //goes to next chunk of memory
      pointer = pointer->next;
    }
  }
}
