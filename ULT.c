#include <assert.h>
#include <stdlib.h>

/* We want the extra information from these definitions */
#ifndef __USE_GNU
#define __USE_GNU
#endif /* __USE_GNU */
#include <ucontext.h>

#include "ULT.h"




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
      tcb_to_run = front(&ready_list);
      pop_front(&ready_list);
    }
    else if(wantTid == ULT_SELF) {
      tcb_to_run = back(&ready_list);
      pop_back(&ready_list);
    }
    else {
      tcb_to_run = findTcb(&ready_list, wantTid);
      if(!tcb_to_run) {
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


int main() {
	return 0;
}

