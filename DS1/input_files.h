#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

std::vector<std::string> input_files;

std::string input_ntuple_name;

void InitInputFiles()
{
	input_ntuple_name = "TotemNtuple";

	input_files.clear();

	// calibration run after TS2:
	//   2016_09_24_fill5322

	std::string prefix = "root://eostotem.cern.ch//eos/totem/user/j/jkaspar/reco/alignment_sr/";
	input_files.push_back(prefix + "run_10322.0_ntuple.root");
	input_files.push_back(prefix + "run_10324.0_ntuple.root");
	input_files.push_back(prefix + "run_10324.1_ntuple.root");
	input_files.push_back(prefix + "run_10325.0_ntuple.root");
	input_files.push_back(prefix + "run_10325.1_ntuple.root");
	input_files.push_back(prefix + "run_10325.2_ntuple.root");
	input_files.push_back(prefix + "run_10325.3_ntuple.root");
	input_files.push_back(prefix + "run_10325.4_ntuple.root");
	input_files.push_back(prefix + "run_10325.5_ntuple.root");
	input_files.push_back(prefix + "run_10326.0_ntuple.root");
	input_files.push_back(prefix + "run_10327.0_ntuple.root");
	input_files.push_back(prefix + "run_10327.1_ntuple.root");
	input_files.push_back(prefix + "run_10328.0_ntuple.root");
	input_files.push_back(prefix + "run_10329.0_ntuple.root");
	input_files.push_back(prefix + "run_10331.0_ntuple.root");
	input_files.push_back(prefix + "run_10331.1_ntuple.root");
	input_files.push_back(prefix + "run_10331.2_ntuple.root");
	input_files.push_back(prefix + "run_10331.3_ntuple.root");
	input_files.push_back(prefix + "run_10332.0_ntuple.root");
	input_files.push_back(prefix + "run_10332.1_ntuple.root");
}
