//
//  usage.c
//  ip_test
//
//  Created by gordonwu on 2017/7/26.
//
//

#include "usage.h"
void GetStartTime (struct timeval *tpstart)
{
	gettimeofday (tpstart, NULL);
}

double GetEndTime (struct timeval tpstart)
{
	struct timeval tpnow;
	gettimeofday (&tpnow, NULL);	//record the end time
	double timeuse = 0.0;
	timeuse =
		1000000 * (tpnow.tv_sec - tpstart.tv_sec) + tpnow.tv_usec -
		tpstart.tv_usec;
	timeuse /= 1000000;
	return timeuse;
}

unsigned long GetFileSize (const char *filename)
{
	struct stat buf;
	if (stat (filename, &buf) < 0)
	{
		return 0;
	}
	return (unsigned long) buf.st_size;
}

void PrintThroughput (const char *filename, double timeuse)
{
	double throughput =
		8 * (float) GetFileSize (filename) / (timeuse * 1000 * 1000);
	printf ("Time : %lf\n", timeuse);
	printf ("Speed: %fMbps\n", throughput);
}
