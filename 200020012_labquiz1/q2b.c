#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<signal.h>
int pid;

void sig_quit_handler(int sig){
	printf("\nshell is exiting\n");
	exit(0);
	return;
}

//void sigint_chld_handler(int sig){
//	printf("\n");
//	printf("\n");
//	exit(0);
//	return;
//}


int main(){
    char command[256];
    char newargs[1] = "";
    
    signal(SIGQUIT,sig_quit_handler);
    signal(SIGINT,SIG_IGN);
    while (1)
    {
        char prompt[] = ">>> ";
        printf("%s",prompt);
        scanf("%s",command);
        pid = fork();
        if(pid){
            wait(NULL);
        }else{
         //   setpgid(getpid(), getpgid(getpid()) + 1);
            signal(SIGINT,SIG_DFL);
            execl(command,newargs,(char*)NULL);
            return 1;
        }
    }
    
    return 0;
}
