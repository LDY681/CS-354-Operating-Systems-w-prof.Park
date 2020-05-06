/*  main.c  - main */

#include <xinu.h>

void testio();
void testcpu();
process	main(void)
{	

/*mytest, test if scheduling is fair, liu1589, 2/24, lab3 3.5 */
		resume(create(myTest,1024,19,"myTest",1,'a'));
		resume(create(myTest,1024,19,"myTest",1,'b'));
		resume(create(myTest,1024,19,"myTest",1,'c'));
		
	if (XINUDEBUG == 1){
		kprintf("main running, pid: %d\n", currpid);
		/*compare the values of procgrosscpumicro and procgrosscpu liu1589,2/24,lab3 3.5
		resume(create(testBirthNLifeTime,1024,19,"test birthtime and lifetime",0,NULL));
		resume(create(testBirthNLifeTime,1024,19,"test birthtime and lifetime",0,NULL));
		resume(create(testBirthNLifeTime,1024,19,"test birthtime and lifetime",0,NULL));
		*/
		
		
		
	}
	
	if (XINUTEST == 1){
		/*Test each case individually, 
		  remove the comment only on the one you want to test, liu1589, 3/2
		*/
		
		/*compare testio&testcpu, liu1589, 2/24, lab3 part 5.1
		resume(create(testio,1024,19,"testio",0,NULL));
		resume(create(testcpu,1024,19,"testcpu",0,NULL));		
		 */
		/*4 cpu bounds back to back, liu1589, 2/24, lab3 part 5.2 
		resume(create(testcpu,1024,19,"testcpu",0,NULL));	
		resume(create(testcpu,1024,19,"testcpu",0,NULL));	
		resume(create(testcpu,1024,19,"testcpu",0,NULL));	
		resume(create(testcpu,1024,19,"testcpu",0,NULL));	
		*/
		
		/*4 io bounds back to back, liu1589, 2/24, lab3 part 5.3 	*/
		resume(create(testio,1024,19,"testio",0,NULL));	
		resume(create(testio,1024,19,"testio",0,NULL));	
		resume(create(testio,1024,19,"testio",0,NULL));	
		resume(create(testio,1024,19,"testio",0,NULL));	
		
		
		/*4 io and cpu bounds back to back, liu1589, 2/24, lab3 part 5.4 
		resume(create(testcpu,1024,19,"testcpu",0,NULL));	
		resume(create(testcpu,1024,19,"testcpu",0,NULL));	
		resume(create(testcpu,1024,19,"testcpu",0,NULL));	
		resume(create(testcpu,1024,19,"testcpu",0,NULL));	
		resume(create(testio,1024,19,"testio",0,NULL));	
		resume(create(testio,1024,19,"testio",0,NULL));	
		resume(create(testio,1024,19,"testio",0,NULL));	
		resume(create(testio,1024,19,"testio",0,NULL));	
		*/
		
		/*4 io cpu bounds with 500 ms delays each, liu1589, 2/24, lab3 part 5.5	
		resume(create(testcpu,1024,19,"testcpu",0,NULL));
		sleepms(500);
		resume(create(testcpu,1024,19,"testcpu",0,NULL));	
		sleepms(500);
		resume(create(testcpu,1024,19,"testcpu",0,NULL));
		sleepms(500);	
		resume(create(testcpu,1024,19,"testcpu",0,NULL));	
		*/		
	}
	
	/*Original main code from previous lab, liu1589, 3/2 */
	/* Run the Xinu shell 	
		recvclr();
		resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	*/
	
	/* Wait for shell to exit and recreate it 		
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	*/	

	return OK;
}

/*Test birth and lifetime, liu1589, lab3*/
void testBirthNLifeTime(){
	int i;
	for (i = 0; i <20; i++){
		pid32 currpid = getpid();
		uint32 grosscpu = procgrosscpu(currpid);
		uint32 grosscpumicro = procgrosscpumicro(currpid);
		kprintf("Process: %d; procgrosscpu: %d; grosscpumicro; %d\n\n",currpid,grosscpu,grosscpumicro);
	}
}

/*mytest, test if scheduling is fair, liu1589, lab3*/
void myTest(char a){
	while(1){
		;
	}
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

