/* proclifetime.c - proclifetime */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  proclifetime  -  Return the lifetime of a process liu1589,2/23,lab3.2
 *------------------------------------------------------------------------
 */
uint32	proclifetime(
	  pid32		pid		/* Process ID			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	uint32	birth;			/* birth time to return		*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	birth = proctab[pid].prbirth;
	restore(mask);
	return clktimemilli - birth;
}
