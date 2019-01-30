#include <stdio.h>
#include "eth_t.h"
#include "eth_ip_t.h"
#include "eth_ip_udp_t.h"
#include "eth_ip_udp_gtp_t.h"
#include "eth_ip_udp_gtp_ip_t.h"
#include "eth_ip_udp_gtp_ip_udp_t.h"
#include "eth_ip_udp_gtp_ip_tcp_t.h"
#include "rubik_temp_data_defination.h"
#include "usage.h"
#include "pcap.h"

void init ()
{
	eth_init ();
	eth_ip_init ();
	eth_ip_udp_init ();
	eth_ip_udp_gtp_init ();
	eth_ip_udp_gtp_ip_init ();
	eth_ip_udp_gtp_ip_udp_init ();
	eth_ip_udp_gtp_ip_tcp_init ();
	temp_data_init ();
}

void parse (u_char * data, int length)
{
	static struct timeval now;
	static struct timeval ts;
	static long long int data_len = 0;
	static char first = 1;

	data_len += length;
	gettimeofday (&now, NULL);

	if (first)
	{
		ts = now;
		first = 0;
	}
	else
	{
		if (now.tv_sec - ts.tv_sec >= 1)
		{
			double timeuse =
				((double) (1000000 * (now.tv_sec - ts.tv_sec) + now.tv_usec -
					ts.tv_usec)) / 1000000.0;
			printf ("time: %fs\n", timeuse);
			printf ("volume: %lfGb\n", data_len * 8 / 1000000000.0);
			data_len = 0;
			ts = now;
		}
	}
	eth_parse (data, length, &now);
}
