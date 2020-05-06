/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;
uint32 currentgrosscpu;	/*gross cpu time of current process liu1589,2/23,lab3.3*/
uint64 ret;	/*Return value of rdtsc, liu1589,2/24,lab3.5*/
uint64 currentgrosscputick;	/*gross cpu ticks liu1589,2/24,lab3.5*/
/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/
	pid32 pidold;	/*store the old pid, liu1589, 2/29 lab3 part5*/
	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	pidold = currpid;
	ptold = &proctab[currpid];

	/*update the current process's prgrosscpu&prvgrosscpu, liu1589,2/23,lab3.3&3.5*/
	if (clktimemilli == currentgrosscpu){
		ptold->prgrosscpu += 1;
		ptold->prvgrosscpu += 1;
	}else{
		ptold->prgrosscpu += (clktimemilli - currentgrosscpu);
		ptold->prvgrosscpu += (clktimemilli - currentgrosscpu);
	}
	
	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prvgrosscpu <= firstkey(readylist)) {
			return;
		}
		
		/* Old process will no longer remain current, moved from if loop to here 
		   because we need the new prvgrosscpu, liu1589, 2/29, lab3.5
		*/
		ptold->prstate = PR_READY;
		if (XINUDEBUG == 1){
			kprintf("CTXSW: insert oldproc: %d(prvgrosscpu: %d) in readylist\n", pidold, ptold->prvgrosscpu);
		}
		rinsert(pidold, readylist, (int32)ptold->prvgrosscpu);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
		
	/*Update CPU tick counter liu1589,2/24,lab3.5*/
	asm volatile ( "rdtsc" : "=A"(ret) );
	ptold->prgrosscputick += (ret - currentgrosscputick);
	
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);
	
	/*start a CPU tick counter, liu1589,2/24,lab3.5*/
	asm volatile ( "rdtsc" : "=A"(ret) );
	currentgrosscputick = ret;
	
	/*start a millisecond counter, liu1589,2/23,lab3.3*/
	currentgrosscpu = clktimemilli;
	
	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
