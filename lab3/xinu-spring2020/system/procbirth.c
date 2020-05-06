/* procbirth.c - procbirth */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  procbirth  -  Return the birth time of a process liu1589,2/23,lab3.2
 *------------------------------------------------------------------------
 */
uint32	procbirth(
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
	return birth;
}
