#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

char* getUser() { return getenv("USER"); }
int compare(const void * a, const void * b) { return ( *(int*)a - *(int*)b ); }

int main(int argc, char *argv[], char *envp[]) {
    int numIntegers = 100;  //min = 0 | no max
    int minInt = 1; //cannot be lower than 1
    int maxInt = 255; //max = 1,000,000 & can't be less than minInt
    FILE* input = stdin;
    FILE* output = stdout;
    FILE* countOutput = stdout;

    /* Parse Input */
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-u") == 0) {
            fprintf(stderr, "%s", "prog1sorter [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]\n");
            exit(EXIT_FAILURE);
        }
    }

    int sw;
    while((sw = getopt(argc, argv, "n:m:M:i:o:c:")) != -1) {
        switch(sw) {
            case 'n':
                numIntegers = atoi(optarg);

                if(numIntegers < 0) {
                    fprintf(stderr, "%s\n", "Invalid number of integers. -n must be greater than or equal to 0.");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'm':
                minInt = atoi(optarg);

                if(minInt < 1) {
                    fprintf(stderr, "%s\n", "Invalid minimum integer. -m must be greater than or equal to 1.");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'M':
                maxInt = atoi(optarg);

                if(maxInt > 1000000) {
                    fprintf(stderr, "%s\n", "Invalid maximum integer. -M must be less than or equal to 1000000.");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'i':
                input = fopen(optarg, "r");
                break;
            case 'o':
                output = fopen(optarg, "w");
                break;
            case 'c':
                countOutput = fopen(optarg, "w");
                break;
            case '?':
                fprintf(stderr, "%s\n", "prog1sorter [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]");
                exit(EXIT_FAILURE);
        }
    }

    if(minInt > maxInt) {
        fprintf(stderr, "%s\n", "max-int cannot be less than min-int");
        exit(EXIT_FAILURE);
    }

    //begin timer
    struct timeval start;
    gettimeofday(&start, NULL);

    int n = -1;
    if(fscanf(input, "%d", &n) != EOF) {
    } else {
        fprintf(stderr, "%s", "Input file is empty.");
        //exit(EXIT_FAILURE);
    }

    if(numIntegers != n) {
        fprintf(stderr, "%s\n", "# of integers in input -i is not equal to the size of the file");
        //exit(EXIT_FAILURE);
    }

    int *array = (int *) malloc (n * sizeof(int));

    if(array) {
        for(int i = 0; i < n; i++) {
            int temp = -1;
            
            fscanf(input, "%d", &temp);
            if(temp >= minInt && temp <= maxInt) array[i] = temp;
            else {
                fprintf(stderr, "%s\n", "Input value out of bounds.");
                exit(EXIT_FAILURE);
            }
        }

        qsort(array, n, sizeof(int), compare);

        for(int i = 0; i < n; i++) fprintf(output, "%d\n", array[i]);
    }
    else fprintf(stderr, "%s", "Memory allocation failure.\n");

    char* user = getUser();
    int *asciiVals = (int*) malloc ((int)strlen(user) * sizeof(int));

    for(int i = 0; i < (int)strlen(user); i++) {
        asciiVals[i] = 0;
    }

    if(asciiVals) {
        for(int i = 0; i < (int)strlen(user); i++) {
            for(int j = 0; j < n; j++) {
                if(array[j] == user[i]) {
                    asciiVals[i]++;
                }
            }
        }
        
        for(int i = 0; user[i] != '\0'; i++) {
            fprintf(countOutput, "%c\t%d\t%d\n", user[i], user[i], asciiVals[i]);
        }
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    int micro = (end.tv_sec - start.tv_sec) * 1000000 + ((int)end.tv_usec - (int)start.tv_usec);
    fprintf(stderr, "Elapsed Runtime: %d.%.6d\n", (micro/1000000), (micro % 1000000));
    
    return 0;
}


