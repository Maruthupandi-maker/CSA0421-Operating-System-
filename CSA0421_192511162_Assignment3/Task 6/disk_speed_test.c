#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#define CHUNK 1048576 // 1 MB
#define TOTAL_MB 256

int main(void) {
    char *buf = malloc(CHUNK);
    int fd = open("speed_test.tmp", O_CREAT | O_WRONLY | O_SYNC, 0644);
    if (fd < 0) { perror("open"); return 1; }

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    for (int i = 0; i < TOTAL_MB; i++) {
        write(fd, buf, CHUNK);
    }
    gettimeofday(&t2, NULL);
    close(fd);

    double sec = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1000000.0;
    printf("Write Throughput (Direct I/O): %6.2f MB/s\n", TOTAL_MB / sec);

    unlink("speed_test.tmp");
    free(buf);
    return 0;
}
