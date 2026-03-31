#include "packet.h"
#include <stdint.h>
#include <string.h>

int main()
{
    
    packet* packet = packet_init();

    struct in_addr address; 
    uint32_t ip = 3232235876;
    address.s_addr = ip;

    packet_append(packet, &address);
    packet_print_all_ips(packet, stdout);
    
    
    packet_destroy(packet);
    return 0;
}
