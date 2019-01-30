//
//  usage.h
//  ip_test
//
//  Created by gordonwu on 2017/7/26.
//
//

#ifndef usage_h
#define usage_h

#include <stdint.h>


#include "stdio.h"
#include "string.h"

#include "time.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

void GetStartTime(struct timeval* tpstart);
double GetEndTime(struct timeval tpstart);
void PrintThroughput(const char* filename, double timeuse);
#endif /* usage_h */
