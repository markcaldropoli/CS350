#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char * usage = "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]";
    int is_p = 0; //track if p is specified
    int is_s = 0; //track if s is specified
    int num_children = 1;
    int num_levels = 1;
    int sleep_time = 1;

    /* Parse Input */
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-u") == 0) {
            fprintf(stderr, "%s\n", usage);
            exit(EXIT_FAILURE);
        }
    }

    int sw;
    while((sw = getopt(argc, argv, "N:M:ps:")) != -1) {
        switch(sw) {
            case 'N':
                num_levels = atoi(optarg);

                if(num_levels > 4) {
                    fprintf(stderr, "%s\n", "Invalid number of levels. -N cannot be greater than 4.");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'M':
                num_children = atoi(optarg);

                if(num_children > 3) {
                    fprintf(stderr, "%s\n", "Invalid number of children. -M cannot be greater than 3.");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'p':
                is_p = 1;
                break;
            case 's':
                is_s = 1;
                sleep_time = atoi(optarg);
                break;
            case '?':
                fprintf(stderr, "%s\n", usage);
                exit(EXIT_FAILURE);
        }
    }

    //check if both p and s were specified
    if(is_p == 1 && is_s == 1) {
        fprintf(stderr, "%s\n", usage);
        exit(EXIT_FAILURE);
    }

    printf("ALIVE: Level %d process with pid=%d, child of ppid=%d\n", num_levels, getpid(), getppid());

    if(num_levels == 1) {
        if(is_p == 1) pause();
        else sleep(sleep_time);
    } else {
        for(int i = 0; i < num_children; i++) {
            int cpid = fork();

            if(cpid == -1) {
                fprintf(stderr, "%s\n",  "Failed to create child process");
                exit(EXIT_FAILURE);
            } else if(cpid == 0) {
                char n_levels[64];
                char n_children[64];
                char s_time[64];

                sprintf(n_levels, "%d", num_levels - 1);
                sprintf(n_children, "%d", num_children);
                sprintf(s_time, "%d", sleep_time);

                if(is_p == 1) {
                    char * args[] = {"./prog2tree", "-N", n_levels, "-M", n_children, "-p", NULL};
                    execvp(args[0], args);
                } else {
                    char * args[] = {"./prog2tree", "-N", n_levels, "-M", n_children, "-s", s_time, NULL};
                    execvp(args[0], args);
                }
            } else wait(NULL);
        }
    }

    printf("EXITING: Level %d process with pid=%d, child of ppid=%d\n", num_levels, getpid(), getppid());

    return 0;
}
