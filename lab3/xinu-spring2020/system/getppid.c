/* getppid.c - getppid */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getppid  -  Get the pid of parent process of a process
 *  liu1589, 2/14, lab2 p4
 *------------------------------------------------------------------------
 */
 pid32	getppid(
		pid32		pid		/* ID of child process */
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	mask = disable();		/*Disable Interrupt*/
	
	if (isbadpid(pid)) {	/*Sanity Check*/
		restore(mask);
		return (pid32) SYSERR;
	}
	
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	prptr = &proctab[pid];
	
	restore(mask);
	return (prptr->prparent);
}