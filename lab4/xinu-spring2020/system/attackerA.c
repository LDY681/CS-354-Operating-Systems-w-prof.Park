/*  attackerA.c  - attackerA */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  attackerA  -  calls hellomalware, prints message and terminate
 *  liu1589, lab4 part4, 3/27
 *------------------------------------------------------------------------
 */
void attackerA(int y) {	//victim Pid is getpid() - y

	int victimProc = getpid() - y;
	if (XINUDEBUG == 1){
		kprintf("attackerA: Who am I hijacking? pid: %d\n", victimProc);
	}
	
	struct procent *victimEntry = &proctab[victimProc];		//get victim proc's process entry
	uint32 *prstkptr = (uint32 *)victimEntry->prstkptr;	//get it's run-time stack
	
	prstkptr += 10;	//Go 10 up (8 for general purpose register,  1 for flag, 1 for register ebp for process exit)
	*prstkptr = &hellomalware;	//assign hellomalware as function address
	
	return;
}