#include "RDN.h"



RDN::RDN()
{
	
}


RDN::~RDN()
{
}

int RDN::random_lane(int c)
{
	return ((rand() % 5) + 1) * 100;
}

int RDN::random_ptp(int a, int b)
{
	return rand() % (b - a + 1) + a;
}