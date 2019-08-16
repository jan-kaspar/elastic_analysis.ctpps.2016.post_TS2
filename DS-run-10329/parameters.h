#include "parameters_global.h"

void Init_base()
{
	// load global settings
	Init_global();

	// list of (sub-)directories with distilled ntuples
	distilledNtuples.push_back("block0");

	// alignment periods
	anal.alignment_t0 = 93962;		// beginning of the first time-slice
	anal.alignment_ts = 94336 - 93962 + 30;		// time-slice in s
}

//----------------------------------------------------------------------------------------------------

void Init_45b_56t()
{
	Init_global_45b_56t();
}

//----------------------------------------------------------------------------------------------------

void Init_45t_56b()
{
	Init_global_45t_56b();
}
