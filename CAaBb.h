// vim:ts=4 sts=0 sw=4

//typedef unsigned long u32;

#include <stdio.h>
#include <string.h>
#include "Rtk-gui/sisl.h"



class CAa : public CConn
{
public:
	CAa() { Init(); };
	~CAa() {};

	SISL(1);

	SIGNAL(SigA1)(const char *,int);

	SLOT(SlotA1)() { printf("SlotA1\n"); };
	SLOT(SlotA2)(const char *c) { printf("SlotA2 = %s\n",c); };

	void Test(const char *c) { printf("Test\n"); SigA1(c,1); printf("----------\n"); };
};

class CBb : public CAa
{
public:
	CBb() { Init(); };
	~CBb() {};

	SISL(2);

	SIGNAL(SigB1)(const char *);

	SIGNAL(SigXX)(const char *,int,u32);
	SIGNAL(SigZZ)(const char *,const long ,u32 *,int*);
	
	
	SLOT(SlotB1)() { printf("SlotB1\n"); };
	SLOT(SlotB2)(const char *c) { printf("SlotB2 = %s\n",c); };
};







