#ifndef __COMMON_JUN_H__
#define __COMMON_JUN_H__

#include <stdio.h>
#include <iostream>

#ifdef __DEBUG__
	#define DEBUG(format, ...) do { fprintf(stderr, format, ##__VA_ARGS__); }while(0)
#else
	#define DEBUG(format, ...) do { }while(0)
#endif





#endif