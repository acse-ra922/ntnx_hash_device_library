#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../code/ntnx_hash.h"

int main(int argc, char **argv) {
    // Setup ntnx_hash context
    ntnx_hash_t *ctx = ntnx_hash_setup();
    assert(ctx != NULL);

    // Test ntnx_hash_compute() with an empty buffer
    char *hash = ntnx_hash_compute(ctx, "", 0);
    assert(hash != NULL);
    assert(strcmp(hash, "d41d8cd98f00b204e9800998ecf8427e") == 0);
    free(hash);

    // Test ntnx_hash_compute() with a non-empty buffer
    char *data = "The quick brown fox jumps over the lazy dog";
    hash = ntnx_hash_compute(ctx, data, strlen(data));
    assert(hash != NULL);
    assert(strcmp(hash, "9e107d9d372bb6826bd81d3542a419d6") == 0);
    free(hash);

    // Destroy ntnx_hash context
    assert(ntnx_hash_destroy(ctx) == 0);

    printf("All tests passed successfully!\n");
    return 0;
}
