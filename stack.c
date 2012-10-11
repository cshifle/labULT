#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int idata;
    struct node* pnext;

} node;


void remove_first(struct node ** ppnodeHead)
{
    if(*ppnodeHead != NULL) { //if there are elements in the list...
	struct node *first = *ppnodeHead; //grab first element
	if(first->pnext != NULL) {
		*ppnodeHead = first->pnext; //make second element new lead
        } else {
		*ppnodeHead = NULL;
        }
	free(first); //delete first element
    }
}

void remove_last(struct node ** ppnodeHead)
{
    if(*ppnodeHead != NULL) { //if there are elements in the list...
        struct node *temp = *ppnodeHead;
        struct node *cur;
        if(temp->pnext != NULL) { //if there is more than one element in the list
            cur = temp->pnext; //use two pointers to find the end
            while(cur->pnext != NULL) { //step to the end
                temp = cur;
                cur = cur->pnext;
            }
            free(cur); //delete the element
            temp->pnext = NULL; //reassign preceding node link.
        } else { //if there is one element in the list
            *ppnodeHead = NULL; //delete the element
        }
    }
}

void add_first(struct node ** ppnodeHead, int iarg)
{
	struct node *first = (node*)malloc(sizeof(struct node)); //create a new element
	first->idata = iarg;

	struct node *cur;
	if(*ppnodeHead != NULL) { //if there are elements in the list
		first->pnext = *ppnodeHead; //insert the new element at the beginning
	} else {
		first->pnext = NULL; //or just drop it in place
	}
	*ppnodeHead = first; //then set the new element as first.
}

void add_last(struct node ** ppnodeHead, int iarg)
{
    struct node *cur;
    if(*ppnodeHead == NULL) { //if the list is completely empty,
        *ppnodeHead = (node*)malloc(sizeof(struct node)); //create a starting element
        cur = *ppnodeHead;
        cur->idata = iarg; //give the starting element a value and a null pointer.
        cur->pnext = NULL;
    } else { //if there are elements in the lsit
        cur = *ppnodeHead;
        while(cur->pnext != NULL) { //loop through to the end
            cur = cur->pnext;
        }
        cur->pnext = (node*)malloc(sizeof(struct node)); //create a new node, link it to last element
        cur = cur->pnext;
        cur->idata = iarg;
        cur->pnext = NULL; //set new last element's pointer to NULL.
    }
}



int main(int argc, char *argv[])
{
    struct node *pnodeHead = NULL;
    
    
    char cline[81];
    char pcOp[20];
    int iarg;
  

    return 0;
}

