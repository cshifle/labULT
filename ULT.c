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
    ready_list.push_back(current_thread);

    // pick the next tcb to run
    ThrdCtlBlk * tcb_to_run;
    if(wantTid == ULT_ANY) {
      tcb_to_run = ready_list.front();
      ready_list.pop_front();
    }
    else if(wantTid == ULT_SELF) {
      tcb_to_run = ready_list.back();
      ready_list.pop_back();
    }
    else {
      tcb_to_run = findTcb(wantTid);
      if(!tcb_to_run) {
        ready_list.pop_back();
        return ULT_INVALID;
      }
    }
    current_tid = tcb_to_run->tid;
    returnThis = current_tid;
    setcontext(&(tcb_to_run->context));
  }

  if(ready_list.empty()) {
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




