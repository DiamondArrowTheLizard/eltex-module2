#include "packet.h"
#include <arpa/inet.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct statistics
{
    int ip_all;
    int ip_in;
    int ip_foreign;

} stats;

void stats_print(stats st)
{
    double ip_in_percent = ( (double)st.ip_in * 100 ) / (double)st.ip_all;
    double ip_foreign_percent = ( (double)st.ip_foreign * 100 ) / (double)st.ip_all;

    printf("    IPs within network: %d (%lf%c)\n", st.ip_in, ip_in_percent, '%');
    printf("    IPs outside of network: %d (%lf%c)\n", st.ip_foreign, ip_foreign_percent, '%');
}

stats stats_get(packet* packet, in_addr_t ip_network, in_addr_t mask)
{
    stats st;
    st.ip_all = packet->count;
    st.ip_in = 0;
    st.ip_foreign = 0;

    for(size_t i = 0; i < packet->count; i++)
    {
        if(packet_check_ip_in_network(packet->addresses[i].s_addr, ip_network, mask) == PACKET_IP_IN_NETWORK)
            ++st.ip_in;
        else ++st.ip_foreign;
    }

    return st;
}

unsigned int new_ip()
{
    int fd = open("/dev/urandom", O_RDONLY);
    unsigned int ip;

    read(fd, &ip, sizeof(ip));
    ip = ip % (4294967295 - 4294967295/2 + 1) + 4294967295/2;

    close(fd);
    return ip;
}

int main(int argc, char** argv)
{
    if(argc < 3)    
    {
        fprintf(stderr, "Error: not enough arguments (3 required).\n");
        return -1;

    } 
    
    in_addr_t ip_network = inet_addr(argv[1]);
    in_addr_t mask = inet_addr(argv[2]);

    packet* packet = packet_init();

    for(size_t i = 0; i < (size_t)atoi(argv[3]); i++)
    {
        struct in_addr* addr = (struct in_addr*)malloc(sizeof(*addr));
        addr->s_addr = new_ip();

        packet_append(packet, addr);

        free(addr);
        addr = NULL;
    }
    
    packet_print_all_ips(packet, stdout);
    
    stats st = stats_get(packet, ip_network, mask);
    stats_print(st);

    packet_destroy(packet);


    return 0;
}
