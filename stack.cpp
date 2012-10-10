#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <cstdlib>
//using namespace std;

struct node {
    int idata;
    struct node* pnext;

};

char *fetchline(char *s)
{
    /* get one line from standard input */
	register int c;
	int n = 80;
	register char *pcs;
	pcs = s;
	while (--n > 0 && (c = getchar()) != EOF)
		if ((*pcs++ = c) == '\n')
			break;
	*pcs = '\0';
	return (c == EOF && pcs == s) ? NULL : s;

}

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

void clear(struct node ** ppnodeHead)
{
    /* delete everything from the stack */
    
    struct node *temp;
    if(*ppnodeHead != NULL) { //if there are elements on the stack
        temp = *ppnodeHead;
        while(temp->pnext != NULL) { //iterate through and delete each one
            *ppnodeHead = temp->pnext;
            delete(temp);
            temp = *ppnodeHead;
        }
        *ppnodeHead = temp->pnext; //end with pnodeHead pointing to NULL
        delete(temp);
    }
}

void peek(struct node * pnodeHead)
{
    /* prints the top value of the stack. */
    
    if(pnodeHead != NULL) { //if there are elements on the stack
        struct node *cur = pnodeHead;
        while(cur->pnext != NULL) { //run to the end (top)
            cur = cur->pnext;
        }
        printf("%d\n", cur->idata); //print the top value
    } else {
        printf("NULL\n"); //if there are no elements, print NULL.
    }
}

void printstack(struct node * pnodeHead)
{
    /* prints the entire stack top down. */
    
    if(pnodeHead != NULL) { //if there are elements in the stack...
        struct node *cur = pnodeHead;
        while(cur->pnext != NULL) { //find the end of the list (top element)
            cur = cur->pnext;
        }
        struct node *end = cur; //record position of the last element.

        cur = pnodeHead;
        struct node *temp;
        while(cur != end) { //then loop through repeatedly...
            temp = cur;
            cur = cur->pnext;

            if(cur == end) { //and every time you reach the end,
                printf("%d\n", cur->idata); //print the value,
                end = temp; //and move the end up one element.
                cur = pnodeHead;
            }
        }
        printf("%d\n", cur->idata); //print the bottom element of the stack
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

void add(struct node ** ppnodeHead)
{
    /* pops 2 values off stack; adds them; and then pushes result
    back on stack. It prints nothing */
    
    int value1;
    int value2;
    int result1 = ipop(ppnodeHead, &value1); //pop first and second element off the stack
    int result2 = ipop(ppnodeHead, &value2);
    if((result1 == 0) && (result2 == 0)) { //if two such elements exist,
        int total = value1 + value2; //add them and push the result
        push(ppnodeHead, total);
    } //otherwise, just pop one (or zero) and fail silently.
}

void subtract(struct node ** ppnodeHead)
{
    /* pops 2 values off stack; Subtracts the first number popped from
       the second and then pushes result back on stack. It prints nothing */
    
    int value1;
    int value2;
    int result1 = ipop(ppnodeHead, &value1); //pop first and second element off stack
    int result2 = ipop(ppnodeHead, &value2);
    if((result1 == 0) && (result2 == 0)) { //if two elements are popped,
        int total = value2 - value1; //total = second element minus first (top) element
        push(ppnodeHead, total); //push total back on the stack
    } //if there weren't two elements to pop, just fail silently.
}



int main(int argc, char *argv[])
{
    struct node *pnodeHead = NULL;
    
    
    char cline[81];
    char pcOp[20];
    int iarg;
    while(fetchline(cline))
    {
       if (sscanf(cline, "%s", pcOp))
       {
           if (strcmp(pcOp, "PUSH") == 0)
           {
           		if (sscanf(cline, "%s %d", pcOp, &iarg))
				{
           			push(&pnodeHead, iarg);
           		}
           		
           }
           else if (strcmp(pcOp, "POP") == 0)
		   {
		   	   	pop(&pnodeHead);
		   }
		   else if (strcmp(pcOp, "ADD") == 0)
		   {
		   		add(&pnodeHead);
		   }
		   
		   else if (strcmp(pcOp, "SUBTRACT") == 0)
		   {		
		   	    subtract(&pnodeHead);
		   }
		   else if (strcmp(pcOp, "PEEK") == 0)
		   {		
		   	    peek(pnodeHead);
		   }
		   else if (strcmp(pcOp, "PRINTSTACK") == 0)
		   {
		   		printstack(pnodeHead);
		   }
		   else if (strcmp(pcOp, "CLEAR") == 0)
		   {
		   		clear(&pnodeHead);
		   }
		}
    }
    return 0;
}


