#include "Shop.h"
#include "View.h"
#include "Controller.h"

//////////////////////////////
/////		MAIN
//////////////////////////////

int main()
{
	Shop sh;
	View v(sh);
	Controller c(sh, v);
	//run_main_win(400, 300, "Robbie Robot Shop", c);
	c.run();
	return 0;
}
