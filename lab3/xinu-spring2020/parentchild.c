// CPP code to create three child 
// process of a parent 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/time.h>
#include <sys/resource.h>
// Driver code 
int main() 
{ 
    int pid; 
  
    // variable pid will store the 
    // value returned from fork() system call 
    pid = fork(); 
  
    // If fork() returns zero then it 
    // means it is child process. 
    if (pid == 0) {   
        // This is first child process 
        // getpid() gives the process 
        // id and getppid() gives the 
        // parent id of that process. 
		int currpid = getpid();
		int ppid = getppid();
		int prior = getpriority(PRIO_PROCESS, currpid);
        printf("This is child, pid = %d, ppid = %d, priority = %d\n", currpid, ppid, prior); 
    } else {   // If value returned from fork() in not zero and >0 that means this is parent process. 
                // This is asked to be printed at last 
                // hence made to sleep for 3 seconds. 
				int currpid = getpid();
				int prior = getpriority(PRIO_PROCESS, currpid);
                printf("This is parent, pid = %d, priority = %d\n", currpid, prior); 
            }  
    return 0; 
} 
