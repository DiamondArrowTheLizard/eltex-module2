#include <stdio.h>
#include "ip.h"

int main()
{
    struct ip* addr = ip_create(255, 255, 0, 0);

    int cidr = ip_cidr(addr);

    ip_print(addr, stdout);
    printf("/%d\n", cidr);

    ip_destroy(addr);
}
