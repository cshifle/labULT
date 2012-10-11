#ifndef _ULT_H_
#define _ULT_H_
#include <ucontext.h>
//#include "deque"
//#include "map"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> //may not be necessary

//using namespace std;
typedef int Tid;
#define ULT_MAX_THREADS 1024
#define ULT_MIN_STACK 32768



typedef struct ThrdCtlBlk{
  Tid tid;
  bool rfgc;
  ucontext_t context;

} ThrdCtlBlk;

typedef struct node {
    ThrdCtlBlk* idata;
    struct node* pnext;
} node;

struct node* ready_list = NULL; //pointer to first element of ready list
struct node* zombie_list = NULL; //pointer to first element of zombie list
int iarg;


void pop_front(struct node ** ppnodeHead) //pop the front element of the given list
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

void pop_back(struct node ** ppnodeHead) //pop the back element of the given list
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

void push_front(struct node ** ppnodeHead, ThrdCtlBlk* iarg) //push a new element to the front of the given list
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

void push_back(struct node ** ppnodeHead, ThrdCtlBlk* iarg) //push a new element to the back of the given list
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

int is_empty(struct node ** ppnodeHead) {
	if(*ppnodeHead == NULL) {
		return 1;
	}
	return 0;
}

ThrdCtlBlk* front(struct node** ppnodeHead) {
	struct node *first = *ppnodeHead;
	return first->idata; //breaks if list is empty
}

ThrdCtlBlk* back(struct node** ppnodeHead) {
	struct node *last = *ppnodeHead;
	while(last->pnext != NULL) { //loop through to the end
		last = last->pnext;
	}
	return last->idata; //breaks if list is empty
}

ThrdCtlBlk* findTcb(struct node** ppnodeHead, Tid wantTid) {
	struct node *cur = *ppnodeHead;
	while(cur->idata->tid != wantTid) { //loop through until wantTid is found
		cur = cur->pnext;
	}
	return cur->idata; //breaks if it doesn't find wantTid
}


//static deque<ThrdCtlBlk*> ready_list;
//static deque<ThrdCtlBlk*> zombie_list;
//static map<Tid, void*> tcb_stacks;
// 1 = taken
// 0 = available
static bool __attribute__ ((unused)) taken_tids[ULT_MAX_THREADS] = {1};


static int __attribute__ ((unused)) current_tid = 0;



/*
 * Tids between 0 and ULT_MAX_THREADS-1 may
 * refer to specific threads and negative Tids
 * are used for error codes or control codes.
 * The first thread to run (before ULT_CreateThread
 * is called for the first time) must be Tid 0.
 */
static const Tid ULT_ANY = -1;
static const Tid ULT_SELF = -2;
static const Tid ULT_INVALID = -3;
static const Tid ULT_NONE = -4;
static const Tid ULT_NOMORE = -5;
static const Tid ULT_NOMEMORY = -6;
static const Tid ULT_FAILED = -7;

static inline int ULT_isOKRet(Tid ret){
  return (ret >= 0 ? 1 : 0);
}

Tid ULT_CreateThread(void (*fn)(void *), void *parg);
Tid ULT_Yield(Tid tid);
Tid ULT_DestroyThread(Tid tid);


Tid nextAvailableTid(void);
void init(void);



 




#endif



