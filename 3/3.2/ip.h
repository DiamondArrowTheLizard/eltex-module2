#ifndef IP_H
#define IP_H

#define IP_OK 0
#define IP_BAD -1

#define IP_STRING_SIZE 16
#define IP_OCT_STRING_SIZE 3

#include <stdio.h>

struct ip
{
    int oct1;
    int oct2;
    int oct3;
    int oct4;
};

struct ip* ip_create(int oct1, int oct2, int oct3, int oct4);
void ip_destroy(struct ip* addr);
int ip_validate(struct ip* addr);

char* ip_string_create(struct ip* addr);
void ip_print(struct ip* addr, FILE* stream);
int ip_cidr(struct ip* addr);

#endif // !IP_H
