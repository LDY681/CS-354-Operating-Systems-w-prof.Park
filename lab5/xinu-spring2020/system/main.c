/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
	if (XINUDEBUG == 1){
		kprintf("Debug Message enabled!\nTo disable, change XINUDEBUG to 0 in process.h\n\n");
	}
	/*Lab5 part 3 callback function*/
	/*Test when receiver keeps running sleep()	*/
	int testSleep = create(sleepReceiver, 2048, 20, "testsleepReceiver", NULL);
	resume(testSleep);
	int testSender1 = create(testSender, 2048, 20, "testSender1", 2, testSleep, 1);
	int testSender2 = create(testSender, 2048, 20, "testSender2", 2, testSleep, 2);
	int testSender3 = create(testSender, 2048, 20, "testSender3", 2, testSleep, 3);
	int testSender4 = create(testSender, 2048, 20, "testSender4", 2, testSleep, 4);
	resume(testSender1);
	resume(testSender2);
	resume(testSender3);
	resume(testSender4);
	
	
	/*Test when receiver keeps depleting time budget*/	
	int testclkDisp = create(clkdispReceiver, 2048, 20, "testclkdispReceiver", NULL);
	resume(testclkDisp);
	int testSender5 = create(testSender, 2048, 20, "testSender5", 2, testclkDisp, 5);
	int testSender6 = create(testSender, 2048, 20, "testSender6", 2, testclkDisp, 6);
	int testSender7 = create(testSender, 2048, 20, "testSender7", 2, testclkDisp, 7);
	int testSender8 = create(testSender, 2048, 20, "testSender8", 2, testclkDisp, 8);
	resume(testSender5);
	resume(testSender6);
	resume(testSender7);
	resume(testSender8);
	
	
	/*Lab5 part 4 memory garbage collection*/
	int testMemoryGarbage = create(testGetMemFreeMemKill, 2048, 20, "testGetMemFreeMemKill", NULL);
	resume(testMemoryGarbage);
	    
}

/*A process that keeps sleeping*/
void sleepReceiver() {
	extern umsg32 ubuffer;
	umsg32 *usermbufptr = &ubuffer; 
	if (cbregister(&usercb, usermbufptr) != OK) {
		kprintf("registration of %x failed\n", (uint32) usercb);
    	return;
	}

	while(TRUE) {
		sleepms(10);
	}

	return;
}

/*A process that keeps depleting time budget*/
void clkdispReceiver() {
	extern umsg32 ubuffer;
	umsg32 *usermbufptr = &ubuffer; 
	if (cbregister(&usercb, usermbufptr) != OK) {
		kprintf("registration of %x failed\n", (uint32) usercb);
    	return;
	}

	while(TRUE) {
		;
	}

	return;
}

void testSender(pid32 receiver, umsg32 msg) {
	send(receiver, msg);
	return;
}

void testGetMemFreeMemKill(){
	/*Test getmem() */
	kprintf("Calling getmems\n");
	char *memblk1 = getmem(512);    
	char *memblk2 = getmem(512); 
	char *memblk3 = getmem(512); 
	char *memblk4 = getmem(512); 
	char *memblk5 = getmem(512); 
	printMemblkList(TRUE);
	kprintf("\n\n");
	/*Test freemem() */
	kprintf("Calling freemems\n");
	freemem(memblk1,512);
	freemem(memblk3,512);
	freemem(memblk5,512);
	printMemblkList(FALSE);
	kprintf("\n\n");
	
	/*Test kill() */
	kprintf("Calling kill\n");
	kill(currpid);
}