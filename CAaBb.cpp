// vim:ts=4 sts=0 sw=4

#include "CAaBb.h"

int main()
{
	CAa *a = new CAa();
	CBb *b = new CBb();


	a->Connect("SigA1(const char*,int)",b,"SlotB1()");
	b->Connect("SigA1(const char*,int)",a,"SigA1(const char*,int)");

	a->DisconnectAll();
	delete a;
	b->DisconnectAll();
	delete b;

	return 0;
}


#if 0
int main()
{
	CAa a; //a.name="CAa";
	CBb b; //b.name="CBb";
	a.Connect("SigA1(const char*,int)",&a,"SlotA2(const char*)");
	a.Test("Testing A1 to A2");
	a.Connect("SigA1(const char*,int)",&b,"SlotB1()");
	a.Test("Testing A1 to B1");
	a.Connect("SigA1(const char*,int)",&b,"SlotB2(const char*)");
	a.Test("Testing A1 to B2");

//	b.DisconnectSlots();
//	a.Disconnect(0,0,0);
//	a.Disconnect("SigA1(const char*,int)",&b,"SlotB2(const char*)");
	b.DisconnectSlot("SlotB1()",&a,"SigA1(const char*,int)");

	b.ConnectSlot("SlotB1()",&a,"SigA1(const char*,int)",0);
//	a.Connect("SigA1(const char*,int)",&b,"SlotB1()",0);

	printf("----------\n");
	b.Connect("SigA1(const char*,int)",&a,"SigA1(const char*,int)");

	a.Connect("SigA1(const char*,int)",&b,"SigB1(const char*)");
	a.Test("Testing A1 to SigB2");

	printf("----------\n");
	b.Connect("SigB1(const char*)",&b,"SlotA2(const char*)");
	a.Test("Testing B1 to A2");
	printf("----------\n");
	b.Connect("SigB1(const char*)",&b,"SlotB1()");
	a.Test("Testing B1 to B1");
	printf("----------\n");
	b.Connect("SigB1(const char*)",&b,"SlotB2(const char*)");
	a.Test("Testing B1 to B2");



	printf("----------\n");
	a.DisconnectAll();
	printf("----------\n");
	b.DisconnectAll();
/*	printf("----------\n");
	a.DisconnectSlot(0,0,0);
	printf("----------\n");
	b.DisconnectSlot(0,0,0);
	printf("----------\n");
	a.DisconnectSlots();
	b.DisconnectSlots();//*/
	printf("----------\n");
	a.Disconnect(0,0,0);
	printf("----------\n");
	b.Disconnect(0,0,0);//*/
	printf("----------\n");

	a.SigA1("Test A1",8);
	b.SigB1("Test B1");

/*	b.Connect("SigB1(const char *)",&a,"SigA1(const char *)");
	a.Test("Testing LOOOOOOOP");
	printf("----------\n");*/
	return 0;
}
#endif



/*
void ListDir(const char *n, int in, int max)
{
	int i;
	RDir r;
	for(const char *cc = r.GetFirst(&i,n); cc; cc = r.GetNext(&i)) {
		char buf[256];
		strncpy(buf,n,255);
		strcat(buf,cc);
		strcat(buf,"/");
//		printf("-%i-%i->%s\n",in,i,cc);
		if(i == RD_DIR) {
			printf("-%i-%i->%s\n",in,i,buf);
		}
		if(in < max && i == RD_DIR) {
			ListDir(buf, in+1, max);
		}
	}
	printf("-----\n");
}

int main()
{
#ifdef WIN32
	ListDir("C:\\",0,1);
#else
	ListDir("/",0,2);
#endif
	return 0;
}
*/


