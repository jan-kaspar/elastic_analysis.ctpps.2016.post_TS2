#include "input_files.h"

#include "common_definitions.h"
#include "common_algorithms.h"
#include "parameters.h"
#include "common.h"

#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TChain.h"
#include "TH1D.h"

#include "TotemAnalysis/TotemNtuplizer/interface/TriggerDataFormats.h"
#include "TotemAnalysis/TotemNtuplizer/interface/RawDataFormats.h"
#include "TotemAnalysis/TotemNtuplizer/interface/RPRootTrackInfo.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	Init(argv[1]);
	if (diagonal == dCombined)
		return rcIncompatibleDiagonal;

	InitInputFiles();
	TChain *ch = new TChain("TotemNtuple");
	for (unsigned int i = 0; i < input_files.size(); i++)
	{
		ch->Add(input_files[i].c_str());
		printf("+ %s\n", input_files[i].c_str());
	}
	printf(">> chain entries: %llu\n", ch->GetEntries());

	// select and link input branches
	ch->SetBranchStatus("*", 0);

	EventMetaData *metaData = new EventMetaData();
	ch->SetBranchStatus("event_info.*", 1);
	ch->SetBranchAddress("event_info.", &metaData);

	TriggerData *triggerData = new TriggerData();
	ch->SetBranchStatus("trigger_data.*", 1);
	ch->SetBranchAddress("trigger_data.", &triggerData);

	RPRootDumpTrackInfo *rp_L_1_N = new RPRootDumpTrackInfo();
	RPRootDumpTrackInfo *rp_L_1_F = new RPRootDumpTrackInfo();

	RPRootDumpTrackInfo *rp_R_1_N = new RPRootDumpTrackInfo();
	RPRootDumpTrackInfo *rp_R_1_F = new RPRootDumpTrackInfo();

	// verticals in 45
	if (diagonal == d45b_56t || diagonal == ad45b_56b)
	{
		ch->SetBranchStatus("track_rp_1.*", 1);
		ch->SetBranchAddress("track_rp_1.", &rp_L_1_N);

		ch->SetBranchStatus("track_rp_5.*", 1);
		ch->SetBranchAddress("track_rp_5.", &rp_L_1_F);
	}
	
	if (diagonal == d45t_56b || diagonal == ad45t_56t)
	{
		ch->SetBranchStatus("track_rp_0.*", 1);
		ch->SetBranchAddress("track_rp_0.", &rp_L_1_N);

		ch->SetBranchStatus("track_rp_4.*", 1);
		ch->SetBranchAddress("track_rp_4.", &rp_L_1_F);
	}
	
	// verticals in 56
	if (diagonal == d45t_56b || diagonal == ad45b_56b)
	{
		ch->SetBranchStatus("track_rp_101.*", 1);
		ch->SetBranchAddress("track_rp_101.", &rp_R_1_N);

		ch->SetBranchStatus("track_rp_105.*", 1);
		ch->SetBranchAddress("track_rp_105.", &rp_R_1_F);
	}

	if (diagonal == d45b_56t || diagonal == ad45t_56t)
	{
		ch->SetBranchStatus("track_rp_100.*", 1);
		ch->SetBranchAddress("track_rp_100.", &rp_R_1_N);

		ch->SetBranchStatus("track_rp_104.*", 1);
		ch->SetBranchAddress("track_rp_104.", &rp_R_1_F);
	}

	// horizontals
	/*
	ch->SetBranchStatus("track_rp_23.*", 1);
	ch->SetBranchAddress("track_rp_23.", &rp_L_FH);

	ch->SetBranchStatus("track_rp_22.*", 1);
	ch->SetBranchAddress("track_rp_22.", &rp_L_NH);

	ch->SetBranchStatus("track_rp_122.*", 1);
	ch->SetBranchAddress("track_rp_122.", &rp_R_NH);

	ch->SetBranchStatus("track_rp_123.*", 1);
	ch->SetBranchAddress("track_rp_123.", &rp_R_FH);
	*/

	// ouput file
	TFile *outF = new TFile((string("distill_") + argv[1] + "_new.root").c_str(), "recreate");

	// set up output tree
	EventRed ev;
	TTree *outT = new TTree("distilled", "bla");

	outT->Branch("v_L_1_N", &ev.h.L_1_N.v); outT->Branch("x_L_1_N", &ev.h.L_1_N.x); outT->Branch("y_L_1_N", &ev.h.L_1_N.y);
	outT->Branch("v_L_1_F", &ev.h.L_1_F.v); outT->Branch("x_L_1_F", &ev.h.L_1_F.x); outT->Branch("y_L_1_F", &ev.h.L_1_F.y);

	outT->Branch("v_R_1_N", &ev.h.R_1_N.v); outT->Branch("x_R_1_N", &ev.h.R_1_N.x); outT->Branch("y_R_1_N", &ev.h.R_1_N.y);
	outT->Branch("v_R_1_F", &ev.h.R_1_F.v); outT->Branch("x_R_1_F", &ev.h.R_1_F.x); outT->Branch("y_R_1_F", &ev.h.R_1_F.y);

	outT->Branch("timestamp", &ev.timestamp);
	outT->Branch("run_num", &ev.run_num);
	outT->Branch("bunch_num", &ev.bunch_num);
	outT->Branch("event_num", &ev.event_num);
	outT->Branch("trigger_num", &ev.trigger_num);
	outT->Branch("trigger_bits", &ev.trigger_bits);

	// loop over the chain entries
	long int evi = 0;
	for (; evi < ch->GetEntries(); evi++)
	{
		ch->GetEvent(evi);

		ev.h.L_1_N.v = rp_L_1_N->valid; ev.h.L_1_N.x = rp_L_1_N->x; ev.h.L_1_N.y = rp_L_1_N->y;
		ev.h.L_1_F.v = rp_L_1_F->valid; ev.h.L_1_F.x = rp_L_1_F->x; ev.h.L_1_F.y = rp_L_1_F->y;
                                                                                         
		ev.h.R_1_N.v = rp_R_1_N->valid; ev.h.R_1_N.x = rp_R_1_N->x; ev.h.R_1_N.y = rp_R_1_N->y;
		ev.h.R_1_F.v = rp_R_1_F->valid; ev.h.R_1_F.x = rp_R_1_F->x; ev.h.R_1_F.y = rp_R_1_F->y;

		unsigned N_L = 0;
		if (ev.h.L_1_N.v) N_L++;
		if (ev.h.L_1_F.v) N_L++;

		unsigned N_R = 0;
		if (ev.h.R_1_N.v) N_R++;
		if (ev.h.R_1_F.v) N_R++;

		// compensate for the non-working 56-210-N-T
		if (diagonal == d45b_56t || diagonal == ad45t_56t)
			N_R++;

		bool save = (N_L >= 2 && N_R >= 2);
		if (!save)
			continue;

		ev.timestamp = metaData->timestamp - timestamp0;
		ev.run_num = metaData->run_no;
		ev.bunch_num = triggerData->bunch_num;
		ev.event_num = triggerData->event_num;
		ev.trigger_num = triggerData->trigger_num;
		ev.trigger_bits = triggerData->input_status_bits;

		outT->Fill();
	}
	printf(">> last event number: %li\n", evi);

	// save output tree
	outT->Write();

	delete outF;
	return 0;
}
