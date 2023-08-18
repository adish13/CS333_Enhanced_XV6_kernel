#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
	int child_pid1, child_pid2;
	int fd_one, fd_two;
	int fd1[2];
	int fd2[2];
	pipe(fd1);
	pipe(fd2);

	child_pid1 = fork();
	if (child_pid1 == 0) { // alice
		fd_one = open("secret1.txt", O_RDONLY);
		char msg1[6];
		read(fd_one,msg1,5);
		msg1[5] = 0;
		printf("%d: Secret code for Alice is %s\n", getpid(), msg1);
		write(fd1[1], msg1, 5);
		close(fd_one);
		return 0;

	}
	waitpid(child_pid1, NULL, 0);

	child_pid2 = fork();
	if (child_pid2 == 0) { // bob
		fd_two = open("secret2.txt", O_RDONLY);
		char msg2[6];
		read(fd_two,msg2,5);
		msg2[5] = 0;
		printf("%d: Secret code for Bob is %s\n", getpid(), msg2);
		write(fd2[1], msg2, 5);
		close(fd_two);
		return 0;
	}

	waitpid(child_pid2, NULL, 0);

	char combined_msg[11];
	read(fd1[0], combined_msg, 5);
	read(fd2[0], combined_msg + 5, 5);
	combined_msg[10] = 0;
	printf("%d: Passcode is %s\n", getpid(), combined_msg);
	
	return 0;
}
