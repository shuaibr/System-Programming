
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval start, end;

void startTimer() {
    gettimeofday(&start, NULL);
}

void stopTimer(char *str) {
    gettimeofday(&end, NULL);
    printf("%s's elapsed time\t = %ld\n", str, (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
}

void printUsageAndExit(char *filename) {
    printf("usage: %s filename bytes typeofcallsused\n", filename);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 4) 
        printUsageAndExit(argv[0]);

    char *filename;
    filename = argv[1];

    if (access(filename, F_OK) == -1)
        printUsageAndExit(argv[0]);

    int bytes = atoi(argv[2]);
    if ((bytes == 0 && argv[2][0] != '0') || bytes < 0) 
        printUsageAndExit(argv[0]);

    int typeofcalls = atoi(argv[3]);
    if ((typeofcalls == 0 && argv[3][0] != '0') || (typeofcalls != 0 && typeofcalls != 1))
        printUsageAndExit(argv[0]);


    if (typeofcalls == 1) {
        printf("Using Unix I/O systems calls to read a file by %d bytes per read\n", bytes);
        char buf[bytes];
        int file = open(filename, O_RDONLY);

        startTimer();
        while (read(file, buf, bytes) > 0);
        stopTimer("Unix read");
		
		
    } else if (typeofcalls == 0) {
        printf("Using C functions to read a file by %d bytes 0per fread\n", bytes);
        char buf[bytes];
        FILE *file = fopen(filename, "r");

        startTimer();
        if (bytes == 1) {
            while (!feof(file)) fgetc(file);
        } else {
            while (!feof(file)) fread(buf, bytes, 1, file);
        }

        stopTimer("C fread");
    }

    return EXIT_SUCCESS;
}