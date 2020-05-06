/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	umsg32	msg;			/* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {	
		if (XINUDEBUG == 1){
			kprintf("recv: prhasmsg is false, PR_RECV&resched\n");
		}
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	msg = prptr->prmsg;		/* Retrieve message		*/

	/*  before the message is returned
		check if there are any blocker sender processes
		liu1589, 3/23, lab4.3
	*/
	if (prptr->prsenderflag == TRUE){
		
		pid32 sndProc = dequeue(prptr->prblockedsenders);	//extract the sender process from queue
		if (XINUDEBUG == 1){
			kprintf("recv: prsenderflag is true, dequeue prblockedsenders\n");
			printQueue(sndProc, prptr->prblockedsenders, FALSE);
		}
		ready(sndProc);	//make it ready
		struct	procent *sndPrEntry = &proctab[sndProc];
		prptr->prmsg = sndPrEntry->prsndmsg;	//copy sender's msg to receiver
		prptr->prhasmsg = TRUE;	//The receiver's prhasmsg flag remains 1
		if (isempty(prptr->prblockedsenders)){	//if queue is empty, mark prsenderflag false
			prptr->prsenderflag = FALSE;
		}
	}else{	//if there is no process waiting in queue
		if (XINUDEBUG == 1){
			kprintf("recv: prsenderflag is false, prhasmsg=false\n");
		}
		prptr->prhasmsg = FALSE;	/* Reset message flag		*/
	}	
	if (XINUDEBUG == 1){
		kprintf("recv: Received message: %c\n",msg);
	}
	restore(mask);
	return msg;
}
