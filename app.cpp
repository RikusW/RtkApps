// vim:ts=4 sts=0 sw=4

#include "app.h"

RConfig rcf;
RConfigNode *colors;

//-----------------------------------------------
// RSpp_text -- testing code

CLASS_RSPP(text)	
	bool Match(const char *sig, const char *sisl)
	{
		return RSpp::SppMatch(sig,(char*)"(int)","(char*)",sisl);
	};

	void Call(void *ths, void **ppv)
	{
		const char *t;
		switch((uptr)ppv[0] & 0x1F) {
		case 1: t = "MBut1"; break;
		case 2: t = "MBut2"; break;
		case 3: t = "MBut3"; break;
		default: t = "NoBut"; break;
		}
		void *pv = (void*)t;
		NextCall(ths,&pv);
	}
};
// RSpp_text -- testing code
//-----------------------------------------------

void SetupColors(RConfigNode *n);

void RProgApp::ColorsChanged(int i, void *vp)
{
	RConfigNode *n,*m;
	
	if(colors && colors->child) {
		n = (RConfigNode*)colors->child;

		m = n->GetNode(i);

		if(!m || !m->line) {
			puts("color setting failed\n");
			return;
		}
		SetupColors(m);
		printf("colors set to %i -- %s\n",i,m->line);

		wnd->Draw(true); //redraw everything
		return;
	}
	puts("color setting failed, missing file\n");
}

//-----------------------------------------------


void RProgApp::Setup()
{
	wnd = new RMainWindow(60,50,600,460); //XXX
	wnd->Create();
	wnd->SetText((char*)"Main Window");
	wnd->SetAlignment(AL_V);
	wnd->x_mgn = 0;
	wnd->y_mgn = 0;
	wnd->spacing = 8;

	//-------------------------------------------
	// Menu
	RControl *t;
#if 1	
	RMenuButton *mbtn;
	RMenuBar *rm = new RMenuBar(wnd);

	{
	//RMenuBar *rr = new RMenuBar(wnd);
	RMenuBar *rr = rm;
	rr->SetText((char*)"menubar");

	RPopupMenu *w;
	RMenuButton *mb;

	w = rr->AddPopup((char*)"File");
	w->SetText((char*)"Popup File");
	w->AddItem((char*)"New");
	mbtn = w->AddItem((char*)"Open");
	w->AddItem((char*)"Save");
	w->AddItemC((char*)"Close",this,(char*)"Sl_Quit()");
	
	w = rr->AddPopup((char*)"Edit");
	w->SetText((char*)"Popup Edit");
	w->AddItem((char*)"Cut");
	mb = w->AddItem((char*)"Copy");
	{	RPopupMenu *w = new RPopupMenu(mb);
		mb = w->AddItem((char*)"11New");
		{	RPopupMenu *w = new RPopupMenu(mb);
			w->AddItem((char*)"11New");
			w->AddItem((char*)"11Open");
			w->AddItem((char*)"11Save");
			w->AddItemC((char*)"11Close",this,(char*)"Sl_Quit()");
		}
		w->AddItem((char*)"11Open");
		w->AddItem((char*)"11Save");
		w->AddItemC((char*)"11Close",this,(char*)"Sl_Quit()");
	}
	mb = w->AddItem((char*)"Paste");
	{	RPopupMenu *w = new RPopupMenu(mb);
		w->AddItem((char*)"11New");
		w->AddItem((char*)"11Open");
		w->AddItem((char*)"11Save");
		w->AddItemC((char*)"11Close",this,(char*)"Sl_Quit()");
	}
	w->AddItemC((char*)"Delete",this,(char*)"Sl_Quit()");

	w = rr->AddPopup((char*)"View");
	w->SetText((char*)"Popup View");
	w->AddItem((char*)"x1");
	w->AddItem((char*)"x2");
	w->AddItem((char*)"x3");
	w->AddItem((char*)"x4");

	w = rr->AddPopup((char*)"Options");
	w->SetText((char*)"Popup Options");
	mb = w->AddItem((char*)"a");
	{	RPopupMenu *w = new RPopupMenu(mb);
		w->AddItem((char*)"11New");
		w->AddItem((char*)"11Open");
		w->AddItem((char*)"11Save");
		w->AddItemC((char*)"11Close",this,(char*)"Sl_Quit()");
	}
	w->AddItem((char*)"b");
	w->AddItem((char*)"c");
	w->AddItem((char*)"d");

	w = rr->AddPopup((char*)"Help");
	w->SetText((char*)"Popup Help");
	w->AddItem((char*)"Help");
	w->AddItem((char*)"aaa");
	w->AddItem((char*)"bbb");
	w->AddItem((char*)"ccc");
	}//*/
#endif
	//-------------------------------------------
#if 1
	// Toolbar
	{
	RControl *b;
	RHVBox *rt = new RHVBox(wnd);
	RHVBox *rr = rt;
	rr->SetAlignment(AL_H | AL_STRETCHH | AL_FITH | AL_FITV);
	rr->x_weight = 10;
	rr->SetText((char*)"ToolBar");
	rr->frame = F_UP;

	b = new RButton(rr); b->SetText((char*)"tb1"); t = b; b->x_weight = 1;
		b->SetAlignment(AL_STRETCHH);
	b = new RButton(rr); b->SetText((char*)"tb2"); b->x_weight = 1;
		t->Connect((char*)"Si_Clicked(int)",b,(char*)"Sl_SetText(char*)", 0, new RSpp_text()); t = b;
		b->SetAlignment(AL_STRETCHH);
	b = new RButton(rr); b->SetText((char*)"tb3");  b->x_weight = 1;
		b->Connect((char*)"Si_Clicked(int)",t,(char*)"Sl_SetText(char*)", (UPTR)"--uptr--", new RSpp_Uptr("(char*)"));
		b->SetAlignment(AL_STRETCHH);
	b = new RButton(rr); b->SetText((char*)"sislcnt"); b->x_weight = 1;
		b->Connect((char*)"Si_Clicked(int)"	,this,(char*)"Sl_ShowIt()");
		b->SetAlignment(AL_STRETCHH);
	b = new RButton(rr); b->SetText((char*)"close"); b->x_weight = 1;
		b->Connect((char*)"Si_Clicked(int)"	,this,(char*)"Sl_Quit()");
		b->SetAlignment(AL_STRETCHH);
	}
#endif
	//-------------------------------------------
	//* Scroll view
	RSBox *rsb;
	
#if 1
	rsb = new RSBox(wnd);
	RContainer *sv = new RScrollView(rsb);
	rsb->Setup(10,10);
	rsb->frame = F_DOWN;
#else
	RContainer *sv = new RScrollView(wnd);
	sv->x_weight = 10;
	sv->y_weight = 10;
#endif
	sv->SetAlignment(AL_V | AL_STRETCHH | AL_STRETCHV);// | AL_FITH | AL_FITV);
	sv->SetText((char*)"ScrollView");
	sv->x_mgn = 4;
	sv->y_mgn = 4;
	//sv->frame = F_UP;

	//-------------------------------------------

	/*RProgressBar *rp = new RProgressBar(rsb);
	sb->Connect((char*)"Si_Moved(int)",rp,(char*)"Sl_Move(int)",0);
	rp->SetAlignment(AL_V | AL_STRETCHV);
	rsb->SetPos(2,0);//*/
	
//	RTabControl *tc = new RTabControl(wnd);

	RControl *rra = new RRange(wnd);
//XXX	rra->Connect((char*)"Si_Moved(int)",sv,(char*)"Sl_ScrollY(int)",0);
	rra->x_weight = 10;
	rra->SetText((char*)"Range");
//	rra->frame = F_DOWN;
	rra->SetAlignment(AL_STRETCHH);

	RProgressBar *rp = new RProgressBar(wnd);
	rra->Connect((char*)"Si_Moved(int)",rp,(char*)"Sl_Move(int)",0);
	rp->SetAlignment(AL_H | AL_STRETCHH);

	RStatusBar *rstb = new RStatusBar(wnd);
	rstb->SetAlignment(AL_H | AL_STRETCHH);

//-------------------------------------------------------------------





//-------------------------------------------------------------------
// Tab control

	RTabControl *tc = new RTabControl(sv);
//	RTabControl *tc = new RTabControl(wnd);
	tc->SetText((char*)"TabControl");
	tc->x_weight = 10;
	tc->y_weight = 10;
//	tc->SetAlignment(AL_V | AL_STRETCHH | AL_STRETCHV | AL_FITH | AL_FITV); //XXX BUGGY
	tc->SetAlignment(AL_V | AL_TOP | AL_LEFT | AL_FITH | AL_FITV);
	//((RTabControl*)tc)->rrb->SetWeight(2,1,-1,0);*/

//----------------------
#if 1
	RTBox *ww = new RTBox(tc,3,8);
//	ww->SetAlignment(AL_STRETCHH | AL_STRETCHV);
	ww->SetText((char*)"RTBox");
	ww->frame = F_DOWN;
	ww->spacing = 8;

	// add some buttons
	RControl *b1,*b2,*b3,*b4,*b5,*b6,*b7,*b8,*b9,*b10;
	b1 = new RButton(ww); ww->SetPos(0,0);// b1->tooltip = (char*)"Sets focus on Quit";
	b2 = new RButton(ww); ww->SetPos(1,0);  b2->tooltip = (char*)"Quit it"; 
	b3 = new RButton(ww); ww->SetPos(0,1); b3->tooltip = (char*)"Connected to Quit";
	b4 = new RButton(ww); ww->SetPos(1,1,1,2); b4->tooltip = (char*)"Show MsgBox";
	b4->SetAlignment(AL_STRETCHV);

	b5 = new REditBox(ww); ww->SetPos(0,2); b5->tooltip = (char*)"Editbox"; b5->SetText((char*)"--EditBox--");
	b6 = new RRange(ww); ww->SetPos(0,5,2); b6->tooltip = (char*)"Ranger";
	b6->SetAlignment(AL_STRETCHH);
	//b6->frame = F_DOWN;
	b7 = new RCheckBox(ww); ww->SetPos(0,3); b7->tooltip = (char*)"Check1";
	b8 = new RCheckBox(ww); ww->SetPos(1,3); b8->tooltip = (char*)"Check2";
	b9 = new RToggleButton(ww); ww->SetPos(0,4,2); b9->tooltip = (char*)"Toggler";
	b9->SetAlignment(AL_STRETCHH | AL_STRETCHV);
	//ww->SetWeight(1,1,4,1);
	b10 = new RLabel(ww); ww->SetPos(0,6,2);

	b1->SetText((char*)"Button 1");
	b2->SetText((char*)"Quit Button");
	b3->SetText((char*)"Button 3");
	b4->SetText((char*)"Button 4");
	//b5->SetText((char*)"------The Long EditBox------");
	b6->SetText((char*)"Range Control");
	b7->SetText((char*)"Check 1");
	b8->SetText((char*)"Check 2");// b8->ListMe();
	b9->SetText((char*)"ToggleButton");
	b10->SetText((char*)"RLabel Control");

	b1->Connect((char*)"Si_Clicked(int)",rstb,(char*)"Sl_SetText(char*)", 0, new RSpp_text());
	//b1->Connect((char*)"Si_Clicked(int)"	,b2,(char*)"Sl_Focus()");
	b2->Connect((char*)"Si_Clicked(int)"	,this,(char*)"Sl_Quit()");
	b3->Connect((char*)"Si_Clicked(int)"	,b2,(char*)"Si_Clicked(int)");


//--------------

	RComboBox *cb = new RComboBox(ww);
	ww->SetPos(2,0);
	cb->SetText((char*)"Combo test");

	cb->AddItem((char*)"CItem 0");
	cb->AddItem((char*)"CItem 1");
	cb->AddItem((char*)"CItem 2");
	cb->AddItem((char*)"CItem 3");
	cb->AddItem((char*)"CItem 4");
	cb->AddItem((char*)"CItem 5");
	cb->AddItem((char*)"CItem 6");
	cb->AddItem((char*)"CItem 7");
	cb->AddItem((char*)"CItem 8");
	cb->AddItem((char*)"CItem 9");
	cb->AddItem((char*)"CItem A");
	cb->AddItem((char*)"CItem B");
	cb->AddItem((char*)"CItem C");
	cb->AddItem((char*)"CItem D");
	cb->AddItem((char*)"CItem E");
	cb->AddItem((char*)"CItem F");

//--------------

	colors = rcf.ReadRcf("../Config/Colors.rcf");
	cb = new RComboBox(ww);
	ww->SetPos(2,1);

	if(!colors) {
		cb->AddItem((char*)"CItem x0");
		cb->AddItem((char*)"CItem x1");
		cb->AddItem((char*)"CItem x2");
	}else{
		for(RConfigNode *c = (RConfigNode*)colors->child; c; c = (RConfigNode*)c->next) {
			cb->AddItem((char*) c->line);
		}
	}
	cb->Connect("Si_IndexChanged(int,void*)",this,"ColorsChanged(int,void*)");

#endif
//----------------------
#if 1
	rsb = new RSBox(tc);
	rsb->frame = F_DOWN;
	RTextEdit *te = new RTextEdit(rsb);
	rsb->Setup(10,10);
	te->RTextEdit_P::SetText((char*)"Textedit");
	te->SetText(
"Editor Control\n\
 Testing text\n\
 line 1\n\
 line 2\n\
 line 3\n\
 line 4\n\
 line 5\n\
 line 6\n\
 line 7\n\
 line 8\n\
 line 9\n\
 line 10\n\
 line 11\n\
 line 12\n\
 line 13\n\
 line 14\n\
 line 15\n\
 line 16\n\
 line 17\n\
 line 18\n\
 line 19\n\
 line 20\n\
 last line....");
 //	te->tooltip = (char*)"TextEdit Control";

//	Call(te, "Sl_ScrollY(int)", 0, (int)5);
#endif
//----------------------
#if 1
	rsb = new RSBox(tc);
	RTreeView *tv = new RTreeView(rsb);
	rsb->frame = F_DOWN;
	rsb->Setup(10,10);
	tv->SetText((char*)"TreeView");
	//tv->frame = F_DOWN;
//	Call(rsb->GetAt(1,0), "Sl_Adjust(int,int)", 0, 20, 5);
//	Call(rsb->GetAt(0,1), "Sl_Adjust(int,int)", 0, 0, 0);
//	rsb->GetAt(1,0)->bHidden = 0;

	RTreeNode *p1;//,*p2,*p3;

#ifdef WIN32
	p1 = new RTreeNodeDir(0,(char*)"C:\\");
#else
	p1 = new RTreeNodeDir(0,(char*)"/");
#endif
	tv->SetTree(p1);
	//textpopup = 0;//p1; //XXX TEMP !!!!
	p1->GetChild();//->next->next->next->next->GetChild();
	p1->bExpand = true;

/*	new RTreeNode(p1,(char*)"Child 1.1");
	new RTreeNode(p1,(char*)"Child 1.2");
	new RTreeNode(p1,(char*)"Child 1.3");
	p2 = new RTreeNode(p1,(char*)"Child 1.4");
		p3 = new RTreeNode(p2,(char*)"Child 2.1");
			new RTreeNode(p3,(char*)"Child 3.1");
			new RTreeNode(p3,(char*)"Child 3.2");
		new RTreeNode(p2,(char*)"Child 2.2");
		new RTreeNode(p2,(char*)"Child 2.3");
		new RTreeNode(p2,(char*)"Child 2.4");
	new RTreeNode(p1,(char*)"Child 1.5");
	new RTreeNode(p1,(char*)"Child 1.6");
	p1 = new RTreeNode(p1,(char*)"Child 1.7");
	p2 = p1 = new RTreeNode(p1,(char*)"Child 2.1");
	p1 = new RTreeNode(p1,(char*)"Child 3.1");
	p1 = new RTreeNode(p1,(char*)"Child 4.1");
	p1 = new RTreeNode(p1,(char*)"Child 5.1");
	p1 = new RTreeNode(p2,(char*)"Child TEST");
// */
	//tv->tooltip = (char*)"TreeView Control";
#endif
//----------------------
#if 1
	rsb = new RSBox(tc);
	RListView *lv = new RListView(rsb);
	rsb->frame = F_DOWN;
	rsb->Setup(10,10);
	lv->SetText((char*)"ListView");

	lv->AddItem((char*)"Item 1");
	lv->AddItem((char*)"Item 2");
	lv->AddItem((char*)"Item 3");
	lv->AddItem((char*)"Item 4");
	lv->AddItem((char*)"Item 5");
	lv->AddItem((char*)"Item 6");
	lv->AddItem((char*)"Item 7");
	lv->AddItem((char*)"Item 8");
	lv->AddItem((char*)"Item 9");
	lv->AddItem((char*)"Item 10");
	lv->AddItem((char*)"Item 11");
	lv->AddItem((char*)"Item 12");
	lv->AddItem((char*)"Item 13");
	lv->AddItem((char*)"Item 14");
	lv->AddItem((char*)"Item 15");
	lv->AddItem((char*)"Item 16");
	lv->AddItem((char*)"Item 17");
	lv->AddItem((char*)"Item 18");
	lv->AddItem((char*)"Item 19");
	lv->AddItem((char*)"Item 20");
#endif
//----------------------
	RRadioButton *rb=0;
	RRadioBox *rr=0;
#if 1
	rr = new RRadioBox(tc,1,6);
	rr->SetText((char*)"RadioBox A");
//	rr->SetAlignment(AL_STRETCHH | AL_STRETCHV);
	rr->frame = F_DOWN;
	rb = new RRadioButton(rr,0 ); rb->SetText((char*)"Radio 1"); rr->SetPos(0,0); rb->tooltip = (char*)"t1";
	rb = new RRadioButton(rr,rb); rb->SetText((char*)"Radio 2"); rr->SetPos(0,1); rb->tooltip = (char*)"tt2";
	rb = new RRadioButton(rr,rb); rb->SetText((char*)"Radio 3"); rr->SetPos(0,2); rb->tooltip = (char*)"ttt3";
	mbtn->Connect((char*)"Si_Clicked(int)", rb,(char*)"Sl_Check()");

	rb = new RRadioButton(rr,rb); rb->SetText((char*)"Radio 4"); rr->SetPos(0,3); rb->tooltip = (char*)"tttt4";
	mbtn->next->Connect((char*)"Si_Clicked(int)", rb,(char*)"Sl_Check()");

	rb = new RRadioButton(rr,rb); rb->SetText((char*)"Radio 5"); rr->SetPos(0,4); rb->tooltip = (char*)"ttttt5";
	rb = new RRadioButton(rr,rb); rb->SetText((char*)"Radio 6"); rr->SetPos(0,5); rb->tooltip = (char*)"tttttt6";
#endif
//----------------------
#if 1
	rr = new RRadioBox(tc,3,2);
	rr->SetText((char*)"RadioBox B");
	rr->frame = F_DOWN;
	(rb = new RRadioButton(rr,rb))->SetText((char*)"Radio 1"); rr->SetPos(0,0);
	(rb = new RRadioButton(rr   ))->SetText((char*)"Radio 2"); rr->SetPos(1,0);
	(rb = new RRadioButton(rr   ))->SetText((char*)"Radio 3"); rr->SetPos(2,0);
	(rb = new RRadioButton(rr,0 ))->SetText((char*)"Radio 4"); rr->SetPos(0,1);
	(rb = new RRadioButton(rr   ))->SetText((char*)"Radio 5"); rr->SetPos(1,1);
	(rb = new RRadioButton(rr   ))->SetText((char*)"Radio 6"); rr->SetPos(2,1);
#endif
//----------------------

}

#ifdef XLIB
//	printf((char*)"----CConn size %i----\n",sizeof(CConn));
//	printf((char*)"----RControl size %i----\n",sizeof(RControl));
//	printf((char*)"----RWindow size %i----\n",sizeof(RWindow));
#endif
	
/*
extern int iTR;
int main()
{
	RApp *TheApp = GetTheApp();
	TheApp->Main();
	printf((char*)"sislcnt = %i\n",sislcnt);
	delete TheApp;
	printf((char*)"sislcnt = %i\n",sislcnt);
	printf((char*)"iTR = %i\n",iTR);
	return 0;
}
*/





int main()
{
	RProgApp app;
	app.Setup();
	app.Run();
	return 0;
}






