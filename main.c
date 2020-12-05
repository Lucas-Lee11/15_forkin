#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    int parent, child_1, child_2;

    printf("Pre-fork message\n");

    parent = getpid();
    child_1 = fork();
    if(child_1 == 0) child_2 = fork();

    if(getpid() != parent){
        printf("Child number %d running\n", getpid());

        int fd = open("/dev/random", O_RDONLY);
        unsigned int sleep_time;
        read(fd, &sleep_time, 4);
        sleep_time = sleep_time % 9 + 2;

        //printf("%d\n", sleep_time);
        sleep(sleep_time);

        printf("Child number %d finished\n", getpid());
        return sleep_time;
    }
    else{
        int status;
        int term_child = wait(&status);

        printf("Child number %d slept for %d seconds\n", term_child, WEXITSTATUS(status));
        printf("Parent finished\n");
    }

    return 0;
}
