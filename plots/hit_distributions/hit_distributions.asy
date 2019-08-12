import root;
import pad_layout;

string topDir = "../../";

TH2_palette = Gradient(blue, heavygreen, yellow, red);

string datasets[] = {
	"DS-run-10322",
	"DS-run-10323",
	"DS-run-10324",
	"DS-run-10325",
	"DS-run-10326",
	"DS-run-10327",
	"DS-run-10328",
	"DS-run-10329",
	"DS-run-10331",
	"DS-run-10332",
};

string units[] = { "L_1_F", "L_1_N", "R_1_N", "R_1_F" };
string unit_labels[] = { "45-210-fr", "45-210-nr", "56-210-nr", "56-210-fr" };

//real sh_top[] = { 6.6, 6.0, 5.7,     7.2, 7.5, 8.2 };
//real sh_bot[] = { -6.8, -6.4, -6.2, -6.3, -6.4, -7.1 };

drawGridDef = true;

TH2_x_min = -5;
TH2_x_max = +5;
TH2_y_min = -7;
TH2_y_max = +7;

string s_dirs[], s_suffixes[];
//s_dirs.push("hit distributions/vertical, aligned, before selection"); s_suffixes.push("_al_nosel");
s_dirs.push("hit distributions/vertical, aligned, after selection"); s_suffixes.push("_al_sel");

bool rebin = true;

//----------------------------------------------------------------------------------------------------

real edge = 3.6101;
real cutEdge = 2.22721 / sqrt(2);
int strips = 11;
real margin_v_e = 0.2;
real margin_v_b = 0.4;
real margin_u = 0.1;

path det_shape = (cutEdge, 0)--(edge, 0)--(edge, edge)--(0, edge)--(0, cutEdge)--cycle;
det_shape = scale(10) * rotate(45) * shift(-cutEdge/2, -cutEdge/2) * det_shape;

path hor_det_shape = shift(0, -cutEdge/sqrt(2)*10) * det_shape;

//----------------------------------------------------------------------------------------------------

for (int seli : s_dirs.keys)
{
	for (int dsi : datasets.keys)
	{
		NewRow();

		NewPad(false);
		label("{\SetFontSizesXX " + datasets[dsi] + "}");

		string file_45b = topDir + datasets[dsi] + "/distributions_45b_56t.root";
		string file_45t = topDir + datasets[dsi] + "/distributions_45t_56b.root";

		for (int ui : units.keys)
		{
			real w = 6cm, h = w * (TH2_y_max - TH2_y_min) / (TH2_x_max - TH2_x_min);
			NewPad("$x\ung{mm}$", "$y\ung{mm}$", w, h);
			scale(Linear, Linear, Log);

			//TH2_z_max = 1e3;

			RootObject obj = RootGetObject(file_45b, s_dirs[seli] + "/h_y_"+units[ui]+"_vs_x_"+units[ui] + s_suffixes[seli]);
			if (rebin)
				obj.vExec("Rebin2D", 2, 2);
			draw(robj, "p,bar");

			RootObject obj = RootGetObject(file_45t, s_dirs[seli] + "/h_y_"+units[ui]+"_vs_x_"+units[ui] + s_suffixes[seli]);
			if (rebin)
				obj.vExec("Rebin2D", 2, 2);
			draw(robj, "p");

			/*
			draw(shift(0, sh_top[ui])*det_shape);
			draw(shift(0, sh_bot[ui])*scale(1, -1)*det_shape);
			*/

			//draw(shift(6.2, 0)*rotate(-90)*det_shape);

			real x_min = 0., x_max = +4.5;
			real y_min = -5.5, y_max = +5.5;

			draw((x_min, y_min)--(x_max, y_min)--(x_max, y_max)--(x_min, y_max)--cycle, black+2pt);

			limits((TH2_x_min, TH2_y_min), (TH2_x_max, TH2_y_max), Crop);
			//limits((-15, -30), (+15, +30), Crop);

			AttachLegend(replace(unit_labels[ui], "_", "\_"));
		}
	}

	GShipout("hit_distributions" + s_suffixes[seli], hSkip=1mm, vSkip=1mm);
}
