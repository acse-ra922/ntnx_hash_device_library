#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "ntnx_hash.h"

#define NTNX_HASH_DEVICE "/dev/ntnx_hash"
#define NTNX_HASH_API_VERSION 1
#define NTNX_HASH_COMPUTE 1

struct ntnx_hash_s {
    int fd;
};

struct ntnx_hash_compute {
 void *buf; // pointer to the area for hashing
 size_t len; // length of area for checksumming
 void *hash; // pointer to the area for the computed hash
};


/**
 * @brief Set up a new ntnx_hash_t context
 *
 * @return Pointer to ntnx_hash_t on success, or NULL on failure
 * @note The caller is responsible for calling ntnx_hash_destroy() on the returned
 *       pointer when the context is no longer needed.
 *
 */
ntnx_hash_t *ntnx_hash_setup(void) {
    // Allocate memory for ntnx_hash_t context
    ntnx_hash_t *ctx = malloc(sizeof(ntnx_hash_t));
    if (!ctx) {
        errno = ENOMEM;
        return NULL;
    }

    // Open device file
    ctx->fd = open(NTNX_HASH_DEVICE, O_RDWR);
    if (ctx->fd == -1) {
        free(ctx);
        return NULL;
    }

    // Set IOCTL API version
    int api_version = NTNX_HASH_API_VERSION;
    if (ioctl(ctx->fd, _IOR('h', 1, int), &api_version) == -1) {
        close(ctx->fd);
        free(ctx);
        return NULL;
    }

    return ctx;
}

/**
 * @brief Compute the hash value of a given buffer
 *
 * @param ctx Pointer to the ntnx_hash_t context
 * @param buf Pointer to the buffer to compute the hash value for
 * @param len Length of the buffer in bytes
 *
 * @return Pointer to the hash value string on success, or NULL on failure
 * @note The caller is responsible for freeing the returned pointer with free()
 *       when it is no longer needed.
 */
char *ntnx_hash_compute(ntnx_hash_t *ctx, void *buf, size_t len) {
    if (!ctx) {
        errno = EINVAL;
        return NULL;
    }

    // Allocate memory for hash value string
    char *hash = malloc(33);
    if (!hash) {
        errno = ENOMEM;
        return NULL;
    }

    // Set up compute_args struct
    struct ntnx_hash_compute compute_args = {buf, len, hash};

    // Call IOCTL to compute hash value
    if (ioctl(ctx->fd, NTNX_HASH_COMPUTE, &compute_args) == -1) {
        // IOCTL call failed
        free(hash);
        return NULL;
    }

    return hash;
}

/**
 * @brief Destroy an ntnx_hash_t context
 *
 * @param ctx Pointer to the ntnx_hash_t context to destroy
 *
 * @return 0 on success, or -1 on failure
 */
int ntnx_hash_destroy(ntnx_hash_t *ctx) {
    if (!ctx) {
        errno = EINVAL;
        return -1;
    }

    // Close device file and free context memory
    int ret = close(ctx->fd);
    free(ctx);
    return ret;
}

