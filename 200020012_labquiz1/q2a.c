#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

void sigchld_handler(int sig){
	exit(0);
}

int main(int argc, char *argv[]){
	signal(SIGCHLD,sigchld_handler);
	int child_pid;
	child_pid = fork();
	if(child_pid == 0){
		printf("pid %d: I am child\n",getpid());
		char exe[55];
		sprintf(exe, "./%s", argv[1]);
		char *args[]={exe,NULL};
		execvp(args[0],args);
		return 0;
	}
	else if(child_pid > 0){
		sleep(5);
		int wstatus;
		if(waitpid(child_pid,&wstatus,WNOHANG) == 0){
			printf("Terminating process %d\n",child_pid);
			kill(child_pid,SIGTERM);
		}
		return 0;
	}
}
