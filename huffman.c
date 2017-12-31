#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"
#include "huffman.h"
//Define functions to find the parent, left child and right child in the array
#define p(x) ((x-1)/2)
#define l(x) ((x)*2+1)
#define r(x) ((x)*2+2)

int count = 0;
struct tree *heap[256+1], *nodes[256+1];

int main (int argc, char *argv[])
{
  //Handle incorrect command line arguments 
  if(argc == 1)
  {
    printf("Input and output File is missing"); 
  }
  else if(argc == 2)
  {
    printf("Output file is missing");
  }
  else
  {
    int counts[257];
    FILE *inp;                         
    char c;

    //Open a file I/O stream for reading
    if((inp = fopen(argv[1],"r")) == NULL)
    {  
      printf("Couldn't open file");     
      exit(EXIT_FAILURE);
    }

    for(int i = 0; i < 257; i++)
    {       
      //Initialize arrays
      counts[i] = 0;
      nodes[i] = NULL;
    }

    while ((c = getc(inp))!=EOF)
    {       
      //Get the frequency of the characters in the array and store it in counts
      counts[(int)c]++;
    }

    for(int i = 0; i<257; i++)
    {       
      //Create nodes in nodes array based on the frequency stored in counts
      if(counts[i]>0)
      {
        nodes[i] = createTree(counts[i], NULL,NULL);
        //Insert the nodes into the heap
        insert(nodes[i]);                          
      }
    }
    
    insert(nodes[256] = createTree(0,NULL,NULL));

    while(count > 1)
    {                                      
      //Delete the first two nodes from the heap, combine them and put the new tree at the end of the heap
      struct tree *l = delete();
      struct tree *r = delete();
      insert(createTree(getData(l)+getData(r),l,r));
    }

    for(int i=0; i<=256; i++)
    {                                 
      //Print out the valid characters and their respective binary encoding recursively
      if(nodes[i]!=NULL)
      {
        printf(isprint(i) ? "%c = ": "%3o",i);
				printf("%d", counts[i]);
        printcode(nodes[i]);
        printf("\n");
      }
    }
    //Call pack function
    pack(argv[1],argv[2],nodes);                            
  }

  return 0;
}

static void printcode(struct tree*np)
{
  if(getParent(np)!= NULL)
  {      
    //recursively calls the function until it gets to the root, then checks if the current node is the left or right child of its parent
    printcode(getParent(np));
    printf("%d", np==getLeft(getParent(np)));
  }
}


static void insert (struct tree *np)
{
  int idx;
  idx = count++;
  while(idx > 0 && getData(np) < getData(heap[p(idx)]))
  {    
    //if the value of the parent is bigger than the node to be entered the function moves the parents value to the place that np is suppoed to be entered. It does this until the value is bigger and then inserts np into that index
    heap[idx] = heap[p(idx)];
    idx = p(idx);
  }
  heap[idx] = np;
}

static struct tree *delete(void)
{
  int idx, child;
  struct tree *min, *np;

  //min is value to be deleted
  min = heap[0];
  //np is value of the last node in the array                 
  np = heap[--count];
  //start at the index of the root            
  idx = 0;

  //Deletes the root node and replaces it with the last value in the array. 
  //Then switches that value with the left or right node if it is bigger until a min heap is obtained
  while(l(idx) < count)
  {        
    child = l(idx);
    if(r(idx) < count && getData(heap[l(idx)]) > getData(heap[r(idx)]))
      child = r(idx);

      if(getData(np) > getData(heap[child]))
      {
        heap[idx] = heap[child];
        idx = child;
      }
      else
        break;
      }
  
  //idx equals to child so it puts np into its correct place
  heap[idx] = np;   
  return min;
}



