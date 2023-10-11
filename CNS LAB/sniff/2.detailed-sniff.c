
#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<linux/if_packet.h>
#include<arpa/inet.h>
#include<netinet/ip_icmp.h>      //Provides declarations for icmp header
#include<netinet/udp.h>       	 //Provides declarations for udp header
#include<netinet/tcp.h>		//Provides declarations for tcp header
#include<netinet/ip.h>		//Provides declarations for ip header
#include <linux/if_ether.h>  	//For ether_header

void ProcessPacket(unsigned char* packet, int size)
{
	struct ethhdr *eth = (struct ethhdr *)packet;

	if(ntohs(eth->h_proto) == 0x0800){
		printf("IP PAcket : \t"); 

		struct iphdr *ip = (struct iphdr*)(packet + sizeof(struct ethhdr));

		switch(ip->protocol) {
			case 1 : //ICMP packet
				printf("ICMP \n"); break;
			case 2 : printf("IGMP \n"); break;
			case 6 : printf("TCP \n"); break;
			case 17 : printf("UDP \n"); break;
			default : printf("others\n"); break;
			} 
	}
	else if(ntohs(eth->h_proto) == 0x0806)
			printf("ARP Packet \n ");
	else 
		printf("other packet \n");
		
}


int main()
{
	int PACKET_LEN = 512;
	char buffer[PACKET_LEN];
	struct sockaddr saddr;
	struct packet_mreq mr;
	
	//create a raw socket
	int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	
	//Turn on Promiscuous mode
	mr.mr_type = PACKET_MR_PROMISC;
	setsockopt(sock, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof(mr));
	
	//Getting captured packets
	while(1)
	{
		int data_size = recvfrom(sock, buffer, PACKET_LEN,
					0, &saddr, (socklen_t*) sizeof(saddr));
		
		if(data_size)
			ProcessPacket(buffer , data_size);
	}
	close(sock);
	return 0;
}




