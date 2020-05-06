/* procgrosscpu.c - procgrosscpu */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  procgrosscpu  -  Return the grosscpu of a process liu1589,2/23,lab3.3
 *------------------------------------------------------------------------
 */
uint32 procgrosscpu(
	  pid32		pid		/* Process ID			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	uint32	grosscpu;			/* grosscpu to return		*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	grosscpu = proctab[pid].prgrosscpu;
	restore(mask);
	return grosscpu;
}
