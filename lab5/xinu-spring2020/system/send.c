/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	send(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* Contents of message		*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->prhasmsg || (prptr->prstate == PR_FREE) ) {
		restore(mask);
		return SYSERR;
	}
	
	/*If no callback function was registered for receiver*/
	if (!prptr->prcbvalid){
		restore(mask);
		return SYSERR;	
	}
	
	/*If callback function has already been registered*/
	if (prptr->prtmpvalid){	/*If receiver has a prior message already*/
		/*Discard the message*/
		kprintf("send %d failed: receiver has a prior message already\n",msg);
		restore(mask);
		return SYSERR;
	}else{					/*If no message is stored yet*/
		prptr->prtmpvalid = TRUE;	//set tmpmsgbuf to non-empty
		prptr->prtmpbuf = msg;	//write msg to tmpmsgbuf
		restore(mask);
		return OK;
	}
	
	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
	restore(mask);		/* Restore interrupts */
	return OK;
}
