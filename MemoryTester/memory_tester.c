#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    long long int bytes_count;
    uint64_t i;
    uint8_t *test_buffer;

    if (argc != 2) {
        printf("Invalid arguments\n");
        return 0;
    }
    
    bytes_count = atoll(argv[1]);

    test_buffer = (uint8_t *)malloc((size_t)bytes_count);

    if (test_buffer == NULL) {
        printf("Error while allocating memory\n");
    }
    for (i = 0; i < bytes_count; i++) {
        test_buffer[i] = (uint8_t)(i + 1);
    }

    for (i = 0; i < bytes_count; i++) {
        if (test_buffer[i] != (uint8_t)(i + 1)) {
            printf("FAILED\n");
            return 0;
        }
    }

    printf("PASS\n");
    return 0;
}