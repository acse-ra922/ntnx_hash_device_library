#ifndef NTNX_HASH_H
#define NTNX_HASH_H

#include <stddef.h>

typedef struct ntnx_hash_s ntnx_hash_t;

// Setup a new ntnx_hash_t context. Returns NULL on error.
ntnx_hash_t *ntnx_hash_setup(void);

// Compute the hash of a buffer using the ntnx_hash_t context. Returns a heap-allocated string of 32 hexadecimal characters,
// followed by a null byte. Returns NULL on error, in which case errno will be set appropriately.
char *ntnx_hash_compute(ntnx_hash_t *ctx, void *buf, size_t len);

// Destroy an ntnx_hash_t context. Returns 0 on success, -1 on error (in which case errno will be set appropriately).
int ntnx_hash_destroy(ntnx_hash_t *ctx);

#endif // NTNX_HASH_H
