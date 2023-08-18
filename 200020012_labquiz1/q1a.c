#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> 

int main(){
	int pid1,pid2;
	int fd_one, fd_two;

	fd_one = open("secret1.txt", O_RDONLY);
	fd_two = open("secret2.txt", O_RDONLY);
	pid1 = fork();
	if(pid1 == 0){
		char buf[6];
		read(fd_one,buf,5);
		buf[5] = 0;
		printf("%d: Secret code for Alice is %s\n",getpid(),buf);
		return 0;
	}
	else if(pid1 > 0){
		wait(NULL);
		pid2 = fork();
		if(pid2 == 0){
			char buf2[6];
			read(fd_two,buf2,5);
			buf2[5] = 0;
			printf("%d: Secret code for Bob is %s\n",getpid(), buf2);
		}
		else if(pid2 > 0){
			wait(NULL);
			return 0;
		}
	
	}
	
	close(fd_one);
	close(fd_two);
	return 0;

}
