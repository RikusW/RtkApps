// vim:ts=4 sts=0 sw=4
//Automatically generated from: app.h
//Don't edit, all changes _will be lost_.

#include "app.h"

//---class RProgApp : RApp
/*---Signals---
//---Slots-----
ColorsChanged(int,void*)
//-----------*/
//------------------------------
//---Start of connector stubs---

void RProgApp_ColorsChanged_i_v(void *ths, void **ppv)	{ ((RProgApp*)ths)->ColorsChanged((int)(uptr)ppv[0],(void*)(uptr)ppv[1]); }

//---End of connector stubs---
//----------------------------
//---Start of SiSl Data-------

SiSlLink sil_RProgApp[2] =
{
	{ "ColorsChanged(int,void*)", RProgApp_ColorsChanged_i_v },
	{ 0,0 }
};

SiSlData sd_RProgApp = { 0, "RProgApp", 0, 0, sil_RProgApp };

SiSlData *RProgApp::SiSl_GetSD()
{
	if(!sd_RProgApp.up) {
		sd_RProgApp.up = RApp::SiSl_GetSD();
	}
	return &sd_RProgApp;
}

SiSlTN tn_RProgApp = { 0, "RProgApp", 0, 1 };
const char *RProgApp::GetTypeName(SiSlTN **tn)
{
	if(tn) {
		if(!tn_RProgApp.up) {
			RApp::GetTypeName(&tn_RProgApp.up);
		}
		*tn = &tn_RProgApp;
	}
	return tn_RProgApp.name;
}

//---End of SiSl Data-----------
//------------------------------
//----Start of signal stubs-----

//-----End of signal stubs------
//------------------------------
//done with class RProgApp : RApp

