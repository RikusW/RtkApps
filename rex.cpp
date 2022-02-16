// vim:ts=4 sts=0 sw=4

#include "Rtk-gui/RtkAll.h"

//-----------------------------------------------

RTreeNode *textpopup; //XXX TEMP!!!! 

int RMain()
{
	RApp app;

	app.wnd = new RMainWindow(60,50,600,460); //XXX
	app.wnd->Create();
	app.wnd->SetText("Main Window");
	app.wnd->SetAlignment(AL_H);
//	app.wnd->x_mgn = app.wnd->y_mgn = 0;
//	app.wnd->spacing = 8;

//----------------------

	RSBox *rsb;
	rsb = new RSBox(app.wnd);
	RTreeView *tv = new RTreeView(rsb);
	rsb->frame = F_DOWN;
	rsb->Setup(10,10);
	tv->SetText("TreeView");

	RTreeNode *p1;
#ifdef WIN32
	p1 = new RTreeNodeDir(0,(char*)"C:\\");
#else
	p1 = new RTreeNodeDir(0,(char*)"/");
#endif
	tv->SetTree(p1);
	textpopup = 0;//p1; //XXX TEMP !!!!
	p1->GetChild();//->next->next->next->next->GetChild();
	p1->bExpand = true;

//----------------------

	rsb = new RSBox(app.wnd);
	RListView *lv = new RListViewDir(rsb);
	rsb->frame = F_DOWN;
	rsb->Setup(10,10);
	lv->SetText("ListView");

	SListNode *l = new SListNode(0,(char*)"FIRST");
	lv->SetList(l);
	l = new SListNode(l,(char*)"Click on tree");

//----------------------

	tv->Connect("Si_Selected(RTreeNode*)",lv,"Sl_Setup(char*)", 0, new RSpp_TreePath());
	lv->Connect("Si_Selected(SListNode*)",lv,"Sl_Setup(char*)", 0, new RSpp_ListPath());
	lv->Sl_Setup((char*)"/");

	app.Run();

	return 0;
}

