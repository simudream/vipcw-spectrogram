#include <sys/select.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFLEN 1

int main(){
	setbuf(stdin, NULL);
	char buf[BUFLEN];
	char buf2[BUFLEN];
	int repeat = 1;

	// try with the select..

	// int flags = fcntl(stdin, F_GETFL);  /* get current file status flags */
 //    flags |= O_NONBLOCK;                /* turn off blocking flag */
 //    fcntl(stdin, F_SETFL, flags);       /* set up non-blocking read */

	while(1){
		while(repeat != 0){
			int n = read(fileno(stdin), buf, BUFLEN);
			printf("    Read %d bytes\n", n);
			if(n == 1){
				bcopy(buf, buf2, BUFLEN);
			} else {
				repeat = 0;
			}
		}
		printf(">>%c\n", buf2[0]);
		repeat = 1;
		// sleep(5);
	}
}