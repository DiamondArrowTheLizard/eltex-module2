#ifndef PACKET_H
#define PACKET_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

#define PACKET_MIN_CAPACITY 10

#define PACKET_OK 0
#define PACKET_BAD -1

#define PACKET_IP_LEN 20

#define PACKET_IP_IN_NETWORK 0
#define PACKET_IP_FOREIGN_NETWORK -1

typedef struct packet_ip
{
    struct in_addr* addresses;
    size_t count;
    size_t capacity;

} packet;

packet* packet_init();
void packet_destroy(packet* packet);

int packet_append(packet* packet, struct in_addr* address);

void packet_print_ip_at(packet* packet, size_t index, FILE* stream);
void packet_print_all_ips(packet* packet, FILE* stream);

int packet_check_ip_in_network(in_addr_t ip, in_addr_t ip_network, in_addr_t mask);


#endif // !PACKET_H
