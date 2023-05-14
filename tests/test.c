#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../code/ntnx_hash.h"

int main() {
    FILE *fp;

    fp = freopen("output.log", "w", stdout); // Redirect stdout to file
    ntnx_hash_t *ctx = ntnx_hash_setup();
    if (!ctx) {
        fprintf(stderr, "Failed to set up ntnx_hash_t context: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    // Test hash computation
    char *buf = "hello world";
    char *hash = ntnx_hash_compute(ctx, buf, strlen(buf));
    if (!hash) {
        fprintf(stderr, "Failed to compute hash: %s\n", strerror(errno));
        ntnx_hash_destroy(ctx);
        return EXIT_FAILURE;
    }
    printf("Hash for \"%s\": %p\n", buf, hash);
    free(hash);

    // Clean up ntnx_hash_t context
    if (ntnx_hash_destroy(ctx) == -1) {
        fprintf(stderr, "Failed to destroy ntnx_hash_t context: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    printf("\n All tests passed");
    fclose(fp); // Close file
    return EXIT_SUCCESS;
}


