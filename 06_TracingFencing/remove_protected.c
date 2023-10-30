#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>

typedef int (*remove_type)(const char *);

int remove(const char *__filename)
{
    if (strstr(__filename, "PROTECT"))
    {
        errno = EPERM;
        return -1;
    }
    return ((remove_type)(dlsym(RTLD_NEXT, "remove")))(__filename);
}
