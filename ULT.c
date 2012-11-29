#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
/* We want the extra information from these definitions */
#ifndef __USE_GNU
#define __USE_GNU
#endif /* __USE_GNU */
#include <ucontext.h>
#include "ULT.h"



//struct node* ready_list = NULL; //pointer to first element of ready list
//struct node* zombie_list = NULL;

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
        while(cur != NULL ){
		if(cur->idata->tid != wantTid) { //loop through until wantTid is found
                cur = cur->pnext;
        	}
		else{return cur->idata;}
	}
        return 0; //breaks if it doesn't find wantTid
}










Tid
ULT_CreateThread(void (*fn)(void *), void *parg)
{
  assert(0); /* TBD */
  return ULT_FAILED;
}



Tid ULT_Yield(Tid wantTid)
{
  volatile Tid returnThis;
  if(wantTid < -2 || wantTid >= ULT_MAX_THREADS) {
    return ULT_INVALID;
  }
  // store current thread
  ThrdCtlBlk * current_thread = (ThrdCtlBlk*)malloc(sizeof(ThrdCtlBlk));
  current_thread->rfgc = false;
  current_thread->tid  = current_tid;
  getcontext(&(current_thread->context));
  if(!current_thread->rfgc) {
    current_thread->rfgc = true;
    push_back(&ready_list, current_thread);
    // pick the next tcb to run
    ThrdCtlBlk * tcb_to_run;
    if(wantTid == ULT_ANY) {
      return ULT_NONE;
      
      //tcb_to_run = front(&ready_list);
      //pop_front(&ready_list);
    }
    else if(wantTid == ULT_SELF) {
      tcb_to_run = back(&ready_list);
      pop_back(&ready_list);
    }
    else {
      tcb_to_run = findTcb(&ready_list, wantTid);
      if(!tcb_to_run) {

	return ULT_INVALID;
        pop_back(&ready_list);
        return ULT_INVALID;
      }
    }
    current_tid = tcb_to_run->tid;
    returnThis = current_tid;
    setcontext(&(tcb_to_run->context));
  }

  if(is_empty(&ready_list)) {
    if(wantTid == ULT_ANY) {
      returnThis = ULT_NONE;
    }
  }
  free(current_thread);
  return returnThis;
 // assert(0); /* TBD */
 // return ULT_FAILED;

}


Tid ULT_DestroyThread(Tid tid)
{
  assert(0); /* TBD */
  return ULT_FAILED;
}


//int main() {
//	return 0;
//}

