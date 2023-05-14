#ifndef NTNX_HASH_H
#define NTNX_HASH_H

#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct {
    int fd;  // file descriptor for device file
} ntnx_hash_t;


ntnx_hash_t *ntnx_hash_setup(void);
char *ntnx_hash_compute(ntnx_hash_t *ctx, void *buf, size_t len);
int ntnx_hash_destroy(ntnx_hash_t *ctx);

#endif
