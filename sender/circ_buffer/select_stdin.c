#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main(void) {
    FILE* infile;
    char str[100];
    fd_set readset;
    struct timeval tv;
    struct termios ttystate, ttysave;

    // open a file
    if((infile = fopen("file_test.txt", "r")) == NULL)
    {
        (void)printf("Couldn't open the file\n");
        exit(1);
    }
    // file was opened successfully

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);
    ttysave = ttystate;
    //turn off canonical mode and echo
    ttystate.c_lflag &= ~(ICANON | ECHO);
    //minimum of number input read.
    ttystate.c_cc[VMIN] = 1;

    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    setbuf(stdin, NULL);

    char c;
    // while we are not at the end of a file
    while(0 < (c = getc(infile)))
    {
        // set the time value to 1 second
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        FD_ZERO(&readset);
        FD_SET(fileno(stdin), &readset);

        select(fileno(stdin)+1, &readset, NULL, NULL, &tv);
        // the user typed a character so exit
        if(FD_ISSET(fileno(stdin), &readset))
        {
            fgetc (stdin); // discard character
            break;
        }
        // the user didn't type a character so print the next line
        else
        {
            putchar(c);
            // not needed: sleep(1);
        }
    }

    // clean up
    fclose(infile);

    ttystate.c_lflag |= ICANON | ECHO;
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    // report success
    return 0;
}