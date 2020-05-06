/* rinsert.c - rinsert,lowestprv,highestprv  */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  rinsert  -  rinsert a process into a queue in ascending key order (key here is cpu usage)
 *------------------------------------------------------------------------
 */
status	rinsert(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Key for the inserted process	*/
	)
{
	qid16	curr;			/* Runs through items in a queue*/
	qid16	prev;			/* Holds previous node index	*/

	/* If badpid or badqid */
	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	/*If null process is already in readylist, abort, liu1589, lab3.5*/
	if (pid == 0 && queuetab[queuehead(q)].qnext != queuetail(q)){
		return OK;
	}
	
	/*If normal process is to be inserted and readylist has null process (non-empty)
	 If process has higher prvgrosscpu than null, update null to be prvgrosscpu+quantum
	 liu1589, lab3.5 
	*/
	if (pid != 0 && queuetab[queuehead(q)].qnext != queuetail(q)){
		if (key >= queuetab[queuetab[queuetail(q)].qprev].qkey){
			queuetab[queuetab[queuetail(q)].qprev].qkey = key + QUANTUM;
		}
	}
		
	/*Travese to find right spot*/
	curr = firstid(q);
	while (queuetab[curr].qkey <= key) {
		curr = queuetab[curr].qnext;
	}
	
	/* Insert process between curr node and previous node */
	prev = queuetab[curr].qprev;	/* Get index of previous node	*/
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	
	if (XINUDEBUG == 1){
		printReadyList(pid);
	}
	return OK;
}

/*------------------------------------------------------------------------
 *  lowestprv  -  Return the lowest prv in ready list
 *------------------------------------------------------------------------
 */
int32 lowestprv(){
	/*if the lowestprv prv guy isn't null, liu1589, lab3 part5*/
	if (firstid(readylist) != queuetail(readylist)){
		return queuetab[firstid(readylist)].qkey;
	}else{	/*If readylist has nothing but null, wakeup process has prv as 0*/
		return 0;
	}
	
} 

/*------------------------------------------------------------------------
 *  highestprv  -  Return the highest prv in ready list
 *------------------------------------------------------------------------
 */
int32 highestprv(){
	/*if the highest prv guy isn't head, liu1589, lab3 part5*/
	if (queuetab[lastid(readylist)].qprev != queuehead(readylist)){
		return queuetab[queuetab[lastid(readylist)].qprev].qkey;
	}else{	/*If readylist has nothing but null, new creately process has prv as 0*/
		return 0;
	}
} 
/*------------------------------------------------------------------------
 * printReadyList -  print the readylist
 *------------------------------------------------------------------------
 */
void printReadyList(pid32 pid){
	qid16	curr;			/* Runs through items in a queue*/
	curr = firstid(readylist);
	kprintf("After insert pid: %d, readylist: head", pid);
	while (curr != queuetail(readylist)) {
		kprintf("-->pid:%d,qkey:%d",curr,queuetab[curr].qkey);
		curr = queuetab[curr].qnext;
	}
	kprintf("-->tail\n");
}


