#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    int numIntegers = 100; //min = 0 | no max
    int minInt = 1; //cannot be lower than 1
    int maxInt = 255; //max = 1,000,000 & can't be les than minInt
    int seed = time(0);
    FILE* output = stdout;
    
    /* Parse Input */
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-u") == 0) {
            fprintf(stderr, "%s\n", "prog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]");
            exit(EXIT_FAILURE);
        }
    }

    int sw;
    while((sw = getopt(argc, argv, "n:m:M:s:o:")) != -1) {
        switch(sw) {
            case 'n':
                numIntegers = atoi(optarg);

                if(numIntegers < 0) {
                    fprintf(stderr, "%s", "Invalid number of integers. -n must be greater than or equal to 0.");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'm':
                minInt = atoi(optarg);

                if(minInt < 1) {
                    fprintf(stderr, "%s", "Invalid minimum integer. -m must be greater than or equal to 1.");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'M':
                maxInt = atoi(optarg);

                if(maxInt > 1000000) {
                    fprintf(stderr, "%s", "Invalid maximum integer. -M must be less than or equal to 1000000.");
                    exit(EXIT_FAILURE);
                }
                break;
            case 's':
                seed = atoi(optarg);
                break;
            case 'o':
                output = fopen(optarg, "w");
                break;
            case '?':
                fprintf(stderr, "%s\n", "prog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]");
                exit(EXIT_FAILURE);
        }
    }

    if(minInt > maxInt) {
        fprintf(stderr, "%s", "max-int cannot be less than min-int");
        exit(EXIT_FAILURE);
    }

    //begin timer
    struct timeval start;
    gettimeofday(&start, NULL);

    fprintf(output, "%d\n", numIntegers);

    srand(seed);

    for(int i = 0; i < numIntegers; i++) {
        int r = rand() % (maxInt + 1 - minInt) + minInt;
        fprintf(output, "%d\n", r);
    }

    struct timeval end;
    gettimeofday(&end, NULL);
    int micro = (end.tv_sec - start.tv_sec) * 1000000 + ((int)end.tv_usec - (int)start.tv_usec);
    fprintf(stderr, "Elapsed Runtime: %d.%.6d\n", (micro/1000000), (micro % 1000000));

    return 0;
}
