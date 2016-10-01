#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/uio.h>

size_t build_iovec(struct iovec *, const char *, const char *);

int main(int argc, char **argv){
    struct iovec iov[8];
    size_t iovlen = 0;

    iovlen += build_iovec(&iov[iovlen], "fstype", "tmpfs");
    iovlen += build_iovec(&iov[iovlen], "fspath", "/mnt");
    iovlen += build_iovec(&iov[iovlen], "from", "tmpfs");
    iovlen += build_iovec(&iov[iovlen], "size", "32m");
    if(nmount(iov, iovlen, 0) < 0)
    {
        perror("");
        return -1;
    }

    return 0;
}

size_t build_iovec(struct iovec *iov, const char *name, const char *val)
{
    iov[0].iov_base = (void *)name;
    iov[0].iov_len = (size_t)strlen(name) + 1;
    iov[1].iov_base = (void *)val;
    iov[1].iov_len = (size_t)strlen(val) + 1;
    return 2;
}
