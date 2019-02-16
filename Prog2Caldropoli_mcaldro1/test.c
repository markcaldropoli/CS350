#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    fprintf(stdout, "%s\n", "this is a message");
    //sleep(20);
    pause();
    fprintf(stdout, "%s\n", "this is another message");
    return 0;
}
