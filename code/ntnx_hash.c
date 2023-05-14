#define NTNX_HASH_GET_API_VERSION 0
#define NTNX_HASH_DEVICE "/dev/ntnx_hash"
#define NTNX_HASH_COMPUTE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "ntnx_hash.h"

struct ntnx_hash_compute {
 void *buf; // pointer to the area for hashing
 size_t len; // length of area for checksumming
 void *hash; // pointer to the area for the computed hash
};


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
    
    // Check if IOCTL API version is compatible
    unsigned int api_version;
    if (ioctl(ctx->fd, NTNX_HASH_GET_API_VERSION, &api_version)<0) {
        errno = ENOMEM;
        return NULL;
    }
    
    return ctx;
}


char *ntnx_hash_compute(ntnx_hash_t *ctx, void *buf, size_t len) {
    if (!ctx) {
        errno = EINVAL;
        return NULL;
    }

    // Allocate memory for hash value string
    char *hash = malloc(33* sizeof(char));
    
    if (!hash) 
        { //printf("ERROR");
        errno = ENOMEM;
        return NULL;
    }

    
    // Set up compute_args struct
    struct ntnx_hash_compute compute_args = {buf, len, hash};

    // Call IOCTL to compute hash value
    if (ioctl(ctx->fd, NTNX_HASH_COMPUTE, &compute_args) == -1) {
        // IOCTL call failed
        errno = ENOMEM;
        return NULL;
    }
    
    return hash;
}


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

