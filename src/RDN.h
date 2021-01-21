#pragma once
#include <time.h>
#include <Windows.h>
class RDN
{
public:
	RDN();
	~RDN();

	int random_lane(int c); //0-c
	int random_ptp(int a, int b); //a-b
};

