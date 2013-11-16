// vim:ts=4 sts=0 sw=4

#include <stdio.h>
#include <string.h>
#include "../Rtk/RString.h"
#include "../Rtk/RTreeView.h"

RTreeNode *textpopup;

RApp* GetTheApp()
{
	return NULL;
}


int main()
{
	int i,j;
	RString a,b,c;

	for(i=0; i<11; i++) {
		a = "123456789";
		b.LeftC(a,i);
		printf("b.LeftC(a,%i) -> %s a-> %s<\n",i,b.GetStr(),a.GetStr());
	}
	for(i=0; i<11; i++) {
		a = "123456789";
		b.LeftX(a,i);
		printf("b.LeftX(a,%i) -> %s a -> %s<\n",i,b.GetStr(),a.GetStr());
	}	
	for(i=0; i<11; i++) {
		a = "123456789";
		b.RightC(a,i);
		printf("b.RightC(a,%i) -> %s a -> %s<\n",i,b.GetStr(),a.GetStr());
	}	
	for(i=0; i<11; i++) {
		a = "123456789";
		b.RightX(a,i);
		printf("b.RightX(a,%i) -> %s a -> %s<\n",i,b.GetStr(),a.GetStr());
	}	
	for(i=0; i<11; i++)
	for(j=0; j<5; j++)
	{
		a = "123456789";
		b.Mid(a,i,j);
		printf("b.Mid(a,%i,%i) -> %s a -> %s<\n",i,j,b.GetStr(),a.GetStr());
	}	
	for(i=0; i<11; i++) {
		a = "123456789";
		b.Split(a,'0'+i);
		printf("b.Split(a,'%c') -> %s<%i a -> %s<%i\n",'0'+i,b.GetStr(),b.l,a.GetStr(),a.l);
	}
	for(i=0; i<11; i++) {
		a = "123456789";
		b.RSplit(a,'0'+i);
		printf("b.RSplit(a,'%c') -> %s<%i a -> %s<%i\n",'0'+i,b.GetStr(),b.l,a.GetStr(),a.l);
	}

	a = " 	1234 	";
	a.TrimL();
	printf("\n< 	1234 	> TrimL() -> <%s>\n",a.GetStr());

	a = " 	1234 	";
	a.TrimR();
	printf("< 	1234 	> TrimR() -> <%s>\n",a.GetStr());

	a = " 	1234 	";
	a.Trim();
	printf("< 	1234 	> Trim() -> <%s>\n\n",a.GetStr());

	char buf[40];
	strcpy(buf,"123454546784");
	a = buf;
	a.Replace('4','.');
	printf("<123454546784> Replace('4','.') -> <%s>\n",a.GetStr());

	strcpy(buf,"1-----2-34---5--6---7-8-9");
	a = buf;
	a.Merge('-');
	printf("<1-----2-34---5--6---7-8-9> a.Merge('-') -> <%s>\n\n",a.GetStr());


	a = "12345--"; b.ToDec(a);
	printf("operator u32() \"%s\" -> %i -> \"%s\"\n",a.GetStr(),(u32)a,b.GetStr());

	a = "$1aB5e6--"; b.ToHed(a);
	printf("operator u32() \"%s\" -> %x -> \"%s\"\n",a.GetStr(),(u32)a,b.GetStr());

	a = "0x1aB5e6--"; b.ToHex(a);
	printf("operator u32() \"%s\" -> %x -> \"%s\"\n",a.GetStr(),(u32)a,b.GetStr());
	
	a = "06532747--"; b.ToOct(a);
	printf("operator u32() \"%s\" -> %x -> \"%s\"\n\n",a.GetStr(),(u32)a,b.GetStr());


	a = "1234";
	b = "1234-5678";
	printf("a.Cmp(b,'-') = %s\n",a.Cmp(b,'-') ? "true":"false");


	return 0;
}


	void Replace(char s,char d);
	void Merge(char m);


