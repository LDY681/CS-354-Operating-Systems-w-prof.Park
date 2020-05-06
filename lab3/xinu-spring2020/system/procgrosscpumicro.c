/* procgrosscpumicro.c - procgrosscpumicro */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  procgrosscpumicro  -  cpu time in unit of microsecond (calculated from prgrosscputick)
 *  liu1589,2/24,lab3.5
 *------------------------------------------------------------------------
 */

uint32 procgrosscpumicro(
	  pid32		pid		/* Process ID			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	uint32	cpumicro;			/* cpumicro to return		*/
	uint64 grosscputick;	/*grosscputick from process table*/
	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	grosscputick = proctab[pid].prgrosscputick;
	cpumicro = (uint32)((grosscputick * 2.5)/1000);
	restore(mask);
	return cpumicro;
}
