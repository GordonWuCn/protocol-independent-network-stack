#include <stdio.h>
#include "loopback_t.h"
#include "loopback_ip_t.h"
#include "loopback_ip_udp_t.h"
#include "loopback_ip_udp_quic_header_t.h"
#include "loopback_ip_udp_quic_header_quic_frame_t.h"
#include "rubik_temp_data_defination.h"
#include "usage.h"
#include "pcap.h"

void solid_pcap_handler (u_char * par, struct pcap_pkthdr *hdr, u_char * data)
{
	loopback_parse (data, hdr->len, &hdr->ts);
}

int main (int argc, char const *argv[])
{
	loopback_init ();
	loopback_ip_init ();
	loopback_ip_udp_init ();
	loopback_ip_udp_quic_header_init ();
	loopback_ip_udp_quic_header_quic_frame_init ();
	temp_data_init ();

	if (argc < 2)
	{
		fprintf (stderr, "Please specify pcap data file.");
		return 1;
	}
	const char *pcap_file = argv[1];

	char errbuf[100];
	pcap_t *desc = pcap_open_offline (pcap_file, errbuf);

	struct timeval tpstart;
	GetStartTime (&tpstart);

	pcap_loop (desc, -1, (pcap_handler) solid_pcap_handler, 0);

	double used_time = GetEndTime (tpstart);

	PrintThroughput (pcap_file, used_time);
	return 0;
}
