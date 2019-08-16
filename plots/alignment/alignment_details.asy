import root;
import pad_layout;
include "../run_info.asy";

string topDir = "../../";

//string dataset = "DS-run-10322";
string dataset = "DS-run-10323";
//string dataset = "DS-run-10327";
//string dataset = "DS-run-10332";

string units[] = { "L_1_F", "L_1_N", "R_1_N", "R_1_F" };
string unit_labels[] = { "left, 210, far", "left, 210, near", "right, 210, near", "right, 210, far" };

/*
string units[] = { "L_1_F", "L_1_N", "R_1_F" };
string unit_labels[] = { "left, 210, far", "left, 210, near", "right, 210, far" };
*/

xSizeDef = 10cm;
drawGridDef = true;

TGraph_errorBar = None;

string period = "period 0";

//----------------------------------------------------------------------------------------------------
NewRow();

for (int ui : units.keys)
{
	NewPad("$y\ung{mm}$", "$\hbox{mean } x\ung{mm}$");

	draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/horizontal/horizontal profile/p"), "d0,eb", blue);

	RootObject fit = RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/horizontal/horizontal profile/p|ff", error=false);
	if (fit.valid)
		draw(fit, "l", red+1pt);
	
	//limits((-7, 2), (+7, 4), Crop);
	limits((-6, 1), (+6, 3), Crop);
	AttachLegend(unit_labels[ui], NE, NE);
}

//----------------------------------------------------------------------------------------------------
/*
NewRow();

for (int ui : units.keys)
{
	NewPad("$y\ung{mm}$", "");
	scale(Linear, Log);

	draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/vertical/y_hist|y_hist"), "d0,vl", blue);
	draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/vertical/y_hist|y_hist_range"), "d0,vl", red);

	limits((-7, 1), (+7, 2e2), Crop);
	AttachLegend(unit_labels[ui], NE, NE);
}


//----------------------------------------------------------------------------------------------------
NewRow();

for (int ui : units.keys)
{
	NewPad("$\de y\ung{mm}$", "");

	if (units[ui] == "R_1_N")
		continue;

	draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/vertical/g_max_diff"), "l,p", heavygreen, mCi+1pt+heavygreen);

	limits((-2.5, 0), (+2.5, 1), Crop);
	AttachLegend(unit_labels[ui], NE, NE);
}
*/
