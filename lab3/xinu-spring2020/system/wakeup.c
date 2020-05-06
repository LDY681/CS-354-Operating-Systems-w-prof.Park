/* wakeup.c - wakeup */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wakeup  -  Called by clock interrupt handler to awaken processes
 *------------------------------------------------------------------------
 */
void	wakeup(void)
{
	/* Awaken all processes that have no more time to sleep */

	resched_cntl(DEFER_START);
	while (nonempty(sleepq) && (firstkey(sleepq) <= 0)) {
		
		/*When a newly created process put into readylist for the first time, update prvgrosscpu to highest*/
		pid32 currpid = dequeue(sleepq);
		struct procent *prptr;
		prptr = &proctab[currpid];
		prptr->prvgrosscpu = (uint32)lowestprv();
		//kprintf("wakeup: prvgrosscpu: %d\n",prptr->prvgrosscpu);
		ready(currpid);
	}

	resched_cntl(DEFER_STOP);
	return;
}
