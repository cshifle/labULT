#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int idata;
    struct node* pnext;

};

int ipop(struct node ** ppnodeHead, int *piPopped)
{
    /* pops the first value off the stack */
    
    if(*ppnodeHead != NULL) { //if there are elements on the stack...
        struct node *temp = *ppnodeHead;
        struct node *cur;
        if(temp->pnext != NULL) { //if there is more than one element on the stack
            cur = temp->pnext; //use two pointers to find the end
            while(cur->pnext != NULL) { //step to the end
                temp = cur;
                cur = cur->pnext;
            }
            *piPopped = cur->idata; //obtain the last element's value
            delete(cur); //delete the element
            temp->pnext = NULL; //reassign preceding node link.
        } else { //if there is one element on the stack
            *piPopped = temp->idata; //obtain its value
            *ppnodeHead = NULL; //delete the element
        }
        
        return 0;
    } else {
        return 1;
    }
}

void pop(struct node ** ppnodeHead)
{
    /* pops and then prints the value on top of the stack */
	int iPopped, iResult;
	iResult = ipop(ppnodeHead, &iPopped);
	if (iResult == 1)
	{
		printf("NULL\n");
	}
	else
	{
		printf("%d\n", iPopped);
	}
}

void push(struct node ** ppnodeHead, int iarg)
{
    /* push value iarg onto stack */
    
    struct node *cur;
    if(*ppnodeHead == NULL) { //if the is completely empty,
        *ppnodeHead = (node*)malloc(sizeof(struct node)); //create a starting element
        cur = *ppnodeHead;
        cur->idata = iarg; //give the starting element a value and a null pointer.
        cur->pnext = NULL;
    } else { //if there are elements on the stack
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

