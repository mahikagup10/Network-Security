#include<stdio.h>
#include<stdlib.h>
#include<pcap.h>

void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet){
	printf("Got Packet\n");
}

int main() {
	pcap_t *handle;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct bpf_program fp;
	char filter_exp[]= "icmp";
	bpf_u_int32 net;
	
	//Step I : Open live pcap session on NIC
	handle = pcap_open_live("enp0s3", BUFSIZ, 1, 1000, errbuf);
	
	//Step 2 : Compiler Filter Expression into BPF pesudocode
	pcap_compile(handle, &fp, filter_exp, 0, net);
	
	//Step 3 : Set the filter on the pcap handler
	pcap_setfilter(handle, &fp);

	//Step 4 : Capture the packets
	pcap_loop(handle, -1, got_packet, NULL);

	//Close the handle
	pcap_close(handle);
	
	return 0;
}



