/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
	if (XINUDEBUG == 1){
		 kprintf("main: NQENT is: %d\n",NQENT);
		 kprintf("readylist is: %d\n",readylist);
		 kprintf("sleepq is: %d\n",sleepq);
	}	
   
   /*Testing liu1589, 3/23, lab4 Part3.3*/
	/*Test 1
	pid32 receiver = create(doNothing, 512, 10, "receive", 0, NULL);
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(receiver);
	*/
	
	/*Test 2
	pid32 receiver = create(infiniteRecv, 512, 10, "receive", 0, NULL);
	resume(receiver);
	*/
	
	/*Test 3		
	pid32 receiver = create(receiveXtimes, 512, 10, "receive", 1, 5);
	resume(receiver);
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'X'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'I'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'N'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'U'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, '-'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'E'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'B'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'U'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'G'));
*/
	
	/*Test 4
	pid32 receiver = create(receiveXtimes, 512, 10, "receive", 1, 5);
	resume(receiver);
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'X'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'I'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'N'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'U'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, '-'));
	*/
	
	/*Test 5	
	pid32 receiver = create(infiniteRecv, 512, 10, "receive", 0, NULL);
	resume(receiver);
	resume(create(infiniteSend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(infiniteSend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(infiniteSend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(infiniteSend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(infiniteSend, 512, 10, "send E", 2, receiver, 'E'));
	*/
	
	/*Test 6	
	pid32 receiver = create(receiveXtimes, 512, 10, "receive", 1, 95);
	resume(receiver);
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
		resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
		resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
		resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
		resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
		resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
		resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	resume(create(bsend, 512, 10, "send A", 2, receiver, 'A'));
	resume(create(bsend, 512, 10, "send B", 2, receiver, 'B'));
    resume(create(bsend, 512, 10, "send C", 2, receiver, 'C'));
	resume(create(bsend, 512, 10, "send D", 2, receiver, 'D'));
	resume(create(bsend, 512, 10, "send E", 2, receiver, 'E'));
	*/
		
	/*Testing liu1589, 3/27, lab4 Part4.2-4.3*/
	/*Test attackerA	*/
	resume(create(victimA, 4096, 20, "victimA 1", 0, NULL));
	resume(create(victimA, 4096, 20, "victimA 2", 0, NULL));	
	resume(create(victimA, 4096, 20, "victimA 3", 0, NULL));
	resume(create(attackerA, 4096, 20, "attackerA", 1, 3));		

	
	/*Test attackerB	*/
	resume(create(victimA, 4096, 20, "victimA 1", 0, NULL));
	resume(create(victimA, 4096, 20, "victimA 2", 0, NULL));	
	resume(create(victimA, 4096, 20, "victimA 3", 0, NULL));
	resume(create(attackerB, 4096, 20, "attackerB", 1, 3));		

	
	return OK;
}

void doNothing(){
	while(1){
		;
	}
}

void printLetter(char c){
	kprintf("%c\n",c);
}

void receiveXtimes(int xTimes){
	int i = 0;
	for (i = 0; i < xTimes; i++){
		umsg32 msg = receive();
		kprintf("%c",msg);
		sleepms(100);
	}
}

void infiniteSend( pid32 pid,umsg32	msg){
	while (1){
		bsend(pid, msg);
	}
}

void infiniteRecv(){
	while (1){
		umsg32 msg = receive();
		kprintf("%c",msg);
	}
}

/*------------------------------------------------------------------------
 * printReadyList -  print the readylist
 *------------------------------------------------------------------------
 */
void printQueue(pid32 pid, qid16 receiverQueue, bool8 enqueue){
	qid16	curr;			/* Runs through items in a queue*/
	curr = firstid(receiverQueue);
	if (enqueue){
		kprintf("After enqueue %d, Queue %d: head",pid,receiverQueue);
	}else{
		kprintf("After dequeue %d, Queue %d: head",pid,receiverQueue);
	}
	while (curr != queuetail(receiverQueue)) {
		kprintf("-->pid:%d",curr);
		curr = queuetab[curr].qnext;
	}
	kprintf("-->tail\n");
}


