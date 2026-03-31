#include "packet.h"
#include <stdlib.h>
#include <string.h>

packet* packet_init()
{
    packet* packet = (struct packet_ip*)malloc(sizeof(*packet));
    packet->addresses = (struct in_addr*)malloc(PACKET_MIN_CAPACITY * sizeof(*packet->addresses));
    packet->count = 0;
    packet->capacity = PACKET_MIN_CAPACITY;

    return packet;
}

void packet_destroy(packet* packet)
{
    free(packet->addresses);
    packet->addresses = NULL;

    free(packet);
    packet = NULL;
}

int packet_append(packet* packet, struct in_addr* address)
{
    if(packet == NULL) return PACKET_BAD;

    if(packet->count >= packet->capacity)
    {
        if(packet->capacity == 0) packet->capacity = PACKET_MIN_CAPACITY;
        else packet->capacity *= 2;

        packet->addresses = realloc(packet->addresses, packet->capacity * sizeof(*packet->addresses));
    }

    packet->addresses[packet->count++] = *address;
    return PACKET_OK;
}

static void reverse_ip(char *ip)
{
    char ip_copy[INET_ADDRSTRLEN];
    char *octs[4];
    char *saveptr;
    int i = 0;

    strcpy(ip_copy, ip);
    char *token = strtok_r(ip_copy, ".", &saveptr);
    while (token != NULL && i < 4) {
        octs[i++] = token;
        token = strtok_r(NULL, ".", &saveptr);
    }

    if (i == 4) {
        snprintf(ip, INET_ADDRSTRLEN, "%s.%s.%s.%s",
                 octs[3], octs[2], octs[1], octs[0]);
    }
}

void packet_print_ip_at(packet* packet, size_t index, FILE* stream)
{
    if(index > packet->count)
    {
        fprintf(stderr, "Error: index out of range (%d vs. %d)\n", (int)index, (int)packet->count);
    } else {
        char ip[PACKET_IP_LEN];
        inet_ntop(AF_INET, &packet->addresses[index], ip, sizeof(ip));
        reverse_ip(ip);
        fprintf(stream, "%s\n", ip);
    }
}

void packet_print_all_ips(packet* packet, FILE* stream)
{
    for(size_t i = 0; i < packet->count; i++)
    {
        packet_print_ip_at(packet, i, stream);
    }
}

int packet_check_ip_in_network(in_addr_t ip, in_addr_t ip_gateway, in_addr_t mask)
{
    if( (ip & mask) == (ip_gateway & mask) )
    {
        return PACKET_IP_IN_NETWORK;
    }
    else return PACKET_IP_FOREIGN_NETWORK;
}
