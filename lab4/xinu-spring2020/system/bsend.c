/* bsend.c - bsend */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  bsend  -  liu1589, LAB4, part3
 *	same as send but block waiting until the receiver's buffer frees up 
 *------------------------------------------------------------------------
 */
syscall	bsend(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* Contents of message		*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	struct	procent *currpidptr;		/* Ptr to process's table entry	*/
	
	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	currpidptr = &proctab[currpid];
	//if message buffer is not empty
	if (prptr->prhasmsg) {	
		currpidptr->prstate = PR_SND; //change state to PR_SND
		currpidptr->prsndmsg = msg; //record the message into sender process' prsndmsg
		prptr->prsenderflag = 1; //set flag to 1
		enqueue(currpid, prptr->prblockedsenders); //insert sender process into receiver process' prblockedsenders queue
		if (XINUDEBUG == 1){
			kprintf("bsend: prhasmsg is true, enqueue %c\n",msg);
			printQueue(currpid, prptr->prblockedsenders, TRUE);
		}
		resched();		/* Block until message arrives	*/
	}
	
	if (XINUDEBUG == 1){
			kprintf("bsend: prhasmsg is false, write msgbuffer directly %c\n",msg);
	}
	//if message buffer is empty, behave like normal send
	prptr->prmsg = msg;		/* Deliver message		*/
	prptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/

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
