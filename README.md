# ntnx_hash_device_library

### **Contents**

<!-- TOC -->
* [About](#about)
* [Documentation](#documentation)
* [Testing](#testing)
* [License](#license)
<!-- TOC -->

### **About**

The given repository contains a Linux library which will enable applications to use a fictional 
MD5 hashing device. This is managed by a kernel driver which provides a userspace interface 
via a character device. 
The API of this library consists of three functions : 


ntnx_hash_t *ntnx_hash_setup(void);

char *ntnx_hash_compute(ntnx_hash_t *ctx, void *buf, size_t len);


int ntnx_hash_destroy(ntnx_hash_t *ctx)

ntnx_hash_setup() returns a pointer to a ntnx_hash_t context.
ntnx_hash_compute() returns a pointer to a null-terminated array of 33 chars (including NUL) 
which will be allocated in the heap.
ntnx_hash_destroy() releases all resources associated with the context.

### **Documentation**

The documentation for the above code can be found in the docs folder.

### **Testing**

Testing is an essential part of any software development process, and this code is no exception. To ensure the correct functioning of the code, a test file named "test.c" has been created in the "tests" folder. The test file tests the basic functionality of the three functions mentioned in the "ntnx_hash.h" file.

It is essential to note that the test file has been executed without creating a character device. However, the path for opening the device has been defined in the problem statement. The output of the test file will not be displayed and is directly written to the "output.log" file located in the "tests" folder.

However, the current "output.log" file contains the output of running the code without opening any context and returning a pointer (and printing the memory address) to a null-terminated array of 33 chars that stores the string "hello world". Therefore, it is imperative to ensure that a context is present in the "dev/ntnx_hash" directory, which can be accessed by the functions defined in the "ntnx_hash.c" file.

To execute the "test.c" file from the terminal, the following lines of code can be used:

```bash
cd tests
gcc test.c ../code/ntnx_hash.c
./a.out
```






