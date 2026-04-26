#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 512

void main() {
	int fd, pd[2], pid, n;
	char str1[SIZE], str2[SIZE];
	fd = open("sample.txt", O_RDONLY | O_CREAT, 0764);
	n = read(fd, str1, SIZE);
	pipe(pd);
	pid = fork();
	if (pid > 0) {
		close(pd[0]);
		write(pd[1], str1, n);
		printf("Pipe writes: %s\n", str1);
		close(pd[1]);
	}
	else if (pid == 0) {
		close(pd[1]);
		n = read(pd[0], str2, SIZE);
		str2[n] = '\0';
		printf("Pipe reads: %s\n", str2);
		close(pd[0]);
	}
	else printf("Error in fork\n");
	close(fd);
}
