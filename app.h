
#include "Rtk-gui/RtkAll.h"


class RProgApp : public RApp
{
public:
	RProgApp() {};
	~RProgApp() { DINIT(); };
	SISL(2);

	void Setup();
	SLOT(ColorsChanged)(int,void*);

};


