/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
	if (XINUDEBUG == 1){
	
	}
	
	
	if (XINUTEST == 1){
	
	}

	resume(create(sndch, 4096, 20, "shell", 1, 'a'));

	/* Run the Xinu shell */
	//recvclr();
	//resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	/*while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}*/
	return OK;
    
}
void sndch(
		char ch /* The character to emit continuously */
	){
	int i = 0;
	while (i <1000){
		kprintf("%c",ch);
		i++;
	}
}
void printtmslice(){
	while (1){
		kprintf("Time slice remaining is: %d\n",gettmslice());
	}
}
