#include "ip.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ip* ip_create(int oct1, int oct2, int oct3, int oct4)
{
    struct ip* addr = (struct ip*)malloc(sizeof(*addr));
    addr->oct1 = oct1;
    addr->oct2 = oct2;
    addr->oct3 = oct3;
    addr->oct4 = oct4;

    if(ip_validate(addr) == IP_OK)
        return addr;
    else
        return NULL;
}

void ip_destroy(struct ip* addr)
{
    free(addr);
    addr = NULL;
}

int ip_validate(struct ip* addr)
{
    if(addr->oct1 <= 255 &&
        addr->oct1 >= 0 &&

        addr->oct2<= 255 && 
        addr->oct2 >= 0 &&

        addr->oct3<= 255 && 
        addr->oct3 >= 0 &&

        addr->oct4<= 255 &&
        addr->oct4 >= 0)
    {
        return IP_OK;
    }
    else return IP_BAD;
}

char* ip_string_create(struct ip* addr)
{
    char* ip_string = (char*)malloc(IP_STRING_SIZE * sizeof(*ip_string));
    sprintf(ip_string, "%d.%d.%d.%d", addr->oct1, addr->oct2, addr->oct3, addr->oct4); return ip_string;
}

void ip_print(struct ip* addr, FILE* stream)
{
    char* ip_string = ip_string_create(addr);
    fprintf(stream, "%s\n" ,ip_string);

    free(ip_string);
    ip_string = NULL;
}

int ip_cidr(struct ip* addr)
{
    int cidr = 0;

    char* mask = (char*)malloc(50 * sizeof(*mask));
    sprintf(mask, "%b%b%b%b", addr->oct1, addr->oct2, addr->oct3, addr->oct4);

    size_t i = 0;
    while(i < strlen(mask))
    {
        if(mask[i] == '0')
        {
            break;
        }
        ++cidr;
        ++i;
    }
    free(mask);
    mask = NULL;

    return cidr;
}
