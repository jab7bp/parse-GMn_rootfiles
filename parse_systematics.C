#include <iostream>
#include <filesystem>
#include <vector>
#include <string> 
#include <cstring>
#include <dirent.h>
#include "TStopwatch.h"

#include "/work/halla/sbs/adr/GMn_analysis/physics_analysis/ElasticEventsStudy/includes/read_parsescript_config.h"
#include "/work/halla/sbs/adr/GMn_analysis/physics_analysis/ElasticEventsStudy/includes/beam_variables.h"

 
std::vector<int> makeRunnumvec(TString target, int kin_num, int sbsfieldscale);
std::vector<std::string> getFileNamesWithSubstring(TString input_dirpath, int runnum);
bool makeParsedROOTfile(TString input_ROOTfile_dirpath, std::string rootfile_name, TString output_dir_path, TCut globalcut);

int file_num = 1;
int Nfiles = 0;

std::vector<int> runnum_vec = {};

int parse_systematics(const char* configfilename = "parse_systematics.cfg")
{

	auto total_time_start = std::chrono::high_resolution_clock::now();
	TStopwatch *StopWatch = new TStopwatch();

	//// Read config file and copy the input parameres to local variable. ////
	Configfile configfile;
	int configfile_error = configfile.readin_parsescript_configfile(configfilename); // 0: Yes, -1: No.
	
	if ( configfile_error == -1) // Stop the program if the configuration file is incomplete/ has issues.
	{
		std::cerr << "Program stopping.\n";
		return 1;
	}

	int pass_num = configfile.return_pass_num();
	int kin_num = configfile.return_kin_num();
	int sbsfieldscale = configfile.return_sbsfieldscale();
	TString run_target = configfile.return_target();
	////////////////////////////////////////

	//// Make the run number vector as per the input parameters. ////
	// std::vector<int> runnum_vec = makeRunnumvec(target, kin_num, sbsfieldscale); // Vector to hold all the good run numbers for the input parameters.

	if( false ){
		for(int i = 0; i < lookup_parsed_runs_cnt(run_target.Data(), kin_num, sbsfieldscale); i++){
			runnum_vec.push_back(lookup_parsed_runnums(run_target.Data(), kin_num, sbsfieldscale, i));
		}		
	}


	//SBS4 mag30 LD2:
	// runnum_vec = { 11449, 11451, 11452};
	// runnum_vec = {11456};
	// runnum_vec = {11493};
	runnum_vec = {11494};
	// runnum_vec = { 11495, 11496 };
	// runnum_vec = { 11551 };
	// runnum_vec = {11554};
	// runnum_vec = {11562, 11563};
	// runnum_vec = { 11564 };
	runnum_vec = {11565, 11568};
	// runnum_vec = {11570, 11571};

	//SBS8 mag70 LD2:
	// runnum_vec = { 13453, 13454, 13455, 13491, 13492, 13493, 13494, 13495, 13496, 13497, 13502, 13503, 13504, 13505, 13558, 
	//13559, 13560, 13561, 13562, 13563, 13564, 13565, 13566, 13567, 13568, 13569, 13570, 13571, 13587, 13588, 
	//13589, 13590, 13591, 13592, 13593, 13596, 13597, 13608, 13609, 13610, 13612, 13613, 13614, 13615, 13616, 
	//13617, 13618, 13619, 13620 };

	// runnum_vec = { 13453, 13454, 13455, 13491, 13492, 13493 };
	// runnum_vec = { 13494, 13495, 13496, 13497, 13502, 13503 };
	// runnum_vec = { 13504, 13505, 13558, 13559, 13560, 13561 };
	// runnum_vec = { 13562, 13563, 13564, 13565, 13566, 13567 };
	// runnum_vec = { 13568, 13569, 13570, 13571, 13587, 13588 };
	// runnum_vec = { 13589, 13590, 13591, 13592, 13593, 13596 };
	// runnum_vec = { 13589, 13590, 13591, 13592, 13593, 13596 };
	// runnum_vec = { 13597, 13608, 13609, 13610, 13612, 13613 };
	// runnum_vec = { 13614, 13615, 13616, 13617, 13618, 13619 };
	// runnum_vec = { 13620 };


	//SBS9 mag70 LD2:
	// runnum_vec = {13660, 13661, 13662, 13664, 13665, 13666, 13677, 13678, 13679, 13680, 13681, 13682, 13684, 13685, 13686, 13687, 13688, 13689,
	// 13694, 13695, 13698, 13699, 13700, 13710, 13711, 13712, 13714, 13715, 13716, 13717, 13721, 13723, 13724, 13727, 13728, 13729, 13731, 13732,
	// 13734, 13736, 13737, 13746, 13748, 13749, 13753, 13754, 13755, 13756, 13757, 13758, 13760, 13761, 13764, 13765, 13766, 13767, 13770, 13771,
	// 13773, 13775, 13776, 13777, 13778, 13779, 13793, 13797, 13798, 13799};

	// runnum_vec = { 13660, 13661, 13662, 13664, 13665, 13666 };
	// runnum_vec = { 13677, 13678, 13679, 13680, 13681, 13682 };
	// runnum_vec = { 13684, 13685, 13686, 13687, 13688, 13689 };
	// runnum_vec = { 13694, 13695, 13698, 13699, 13700, 13710 };
	// runnum_vec = { 13711, 13712, 13714, 13715};
	// runnum_vec = {13716, 13717 };
	// runnum_vec = { 13721, 13723, 13724, 13727, 13728};
	// runnum_vec = {13729 };
	// runnum_vec = { 13731, 13732, 13734, 13736, 13737, 13746 };
	// runnum_vec = { 13748, 13749, 13753, 13754, 13755, 13756 };
	// runnum_vec = { 13757, 13758, 13760, 13761, 13764, 13765 };
	// runnum_vec = { 13766, 13767, 13770, 13771, 13773, 13775 };
	// runnum_vec = { 13776, 13777, 13778, 13779, 13793, 13797 };
	// runnum_vec = { 13798, 13799 };

	if (runnum_vec.size() == 0)
	{
		std::cerr << "Error: There are no replayed ROOT files for the given input parameters! Stopping the program.\n";
		return 1;
	};
	////////////////////////////////////////

	TString input_ROOTfile_dirpath = configfile.return_inputdir();
	TString output_dir_path = configfile.return_outputdir();
	TCut globalcut = configfile.return_globalcut();
	Nfiles = runnum_vec.size();
	//// Loop over each and every run number in the runnum_vec, and copy the ROOT file names into a another vector, run_segset_names_vec. ////

 	for (const auto& runnum : runnum_vec)
 	{
 		std::cout.flush();
		std::vector<std::string> run_segset_names_vec = getFileNamesWithSubstring(input_ROOTfile_dirpath, runnum); // The vector to hold the names of ROOT files for the given runnum.

		if( run_segset_names_vec.size() == 0)
		{
			std::cerr << "No replayed ROOT files for run number " << runnum << " in the directory: " << input_ROOTfile_dirpath << '\n';
			continue;
		}

		std::cout << "*Run number: " << runnum << "(File " << file_num << " of " << Nfiles << ")" << '\n';

		//// Loop over each and every ROOT file in the run_segset_names_vec and create a parsed ROOT file for each and every ROOT file in the vector ////
		

		int seg_file_cnt = 0;
		int num_segments = 0;
		num_segments = run_segset_names_vec.size();
		sort( run_segset_names_vec.begin(), run_segset_names_vec.end());

		std::cout << "Number of segment files: " << num_segments << endl;


		// for( int file = 100; file < 150; file++ ){
		// 	const auto& rootfile_name = run_segset_names_vec[file];
		// // }
		for(const auto& rootfile_name : run_segset_names_vec)
		{
			std::cout.flush();
			std::cout << "Segment " << seg_file_cnt << " of " << num_segments << "(File " << file_num << " of " << Nfiles << ")" <<  endl;
			//Making the parsed ROOT files.
			bool is_success = makeParsedROOTfile(input_ROOTfile_dirpath, rootfile_name, output_dir_path, globalcut);

			if(!is_success) continue; // Skip to the next file if there is an eroor with parsing the rootfile.

			seg_file_cnt++;
		}

		std::cout << '\n';

		file_num++;
	}
		

	auto total_time_end = std::chrono::high_resolution_clock::now();
	auto total_time_duration = std::chrono::duration_cast<std::chrono::minutes>(total_time_end - total_time_start);
	cout << endl << "---------------------------------------------------" << endl;
	cout << "Finished parsing rootfiles" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Total time: " << total_time_duration.count() << " minutes. " << endl;
	cout << "File output directory: " << endl;
	cout << output_dir_path.Data() << endl;
	return 0;
}


std::vector<int> makeRunnumvec(TString target, int kin_num, int sbsfieldscale)
{
	std::cout << "\n--------------------------------------\n";
	std::cout << "Building runnum vector...\n"; 
	int nruns = lookup_parsed_runs_cnt(target, kin_num, sbsfieldscale);
	std::cout << "Number good of runs per the input parameters: " << nruns << '\n';
	std::cout << "--------------------------------------\n" << '\n';


	std::vector<int> runnum_vec;

	for( int i = 0; i < nruns; i++ )
	{
		runnum_vec.push_back(lookup_parsed_runnums(target, kin_num, sbsfieldscale, i));
	}

	return runnum_vec;
}

std::vector<std::string> getFileNamesWithSubstring(TString input_dirpath, int runnum) 
{
    const char* directoryPath = input_dirpath.Data();
    const char* substring = std::to_string(runnum).c_str();

    std::vector<std::string> fileNames;

    DIR* dir = opendir(directoryPath);
    if (dir == nullptr) 
    {
        std::cerr << "Error opening directory: " << directoryPath << std::endl;
        return fileNames;
    }

    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) 
    {
        if (entry->d_type == DT_REG) 
        {  // Only consider regular files
            std::string fileName = entry->d_name;
            if (fileName.find(substring) != std::string::npos) 
            {
                fileNames.push_back(fileName);
            }
        }
    }

    closedir(dir);

    return fileNames;
}

bool makeParsedROOTfile(TString input_ROOTfile_dirpath, std::string rootfile_name, TString output_dir_path, TCut globalcut)
{
	// Open input root file. Copy the Trees.
	TFile* inputrootfile = new TFile(Form("%s/%s", input_ROOTfile_dirpath.Data(), rootfile_name.c_str()), "OPEN"); 
	TTree* in_T = (TTree*)inputrootfile->Get("T");
	
	if (in_T == nullptr) 
	{
		std::cout << "Problem with accessing the T tree. Skipping parsing the ROOT file: " << rootfile_name << '\n'; 
		return false; // We don't need to try continue and parse the root file if there is a problem with accessing the maing T event tree.
	}

	TTree* in_E = (TTree*)inputrootfile->Get("E");
	TTree* in_TSLeft = (TTree*)inputrootfile->Get("TSLeft");
	TTree* in_TSsbs = (TTree*)inputrootfile->Get("TSsbs");
	
	TString outrootfilename = Form("parsed_%s", rootfile_name.c_str());

	TFile* output_rootfile = new TFile(Form("%s/%s", output_dir_path.Data(), outrootfilename.Data()),"RECREATE");

	std::cout << "**Making the parsed ROOT file for file: " << rootfile_name << '\n';

	//Cloning the E, TSLeft, and TSsbs trees.
	TTree* E; 
	if(in_E != nullptr) E = in_E->CloneTree();

	TTree* TSLeft; 
	if(in_TSLeft != nullptr) TSLeft = in_TSLeft->CloneTree();

	TTree* TSsbs; 
	if(in_TSsbs != nullptr) TSsbs = in_TSsbs->CloneTree();

	//Making a copy of the main "T" tree with the provided global cuts applied.
	TTree* T; 
	T = in_T->CopyTree(globalcut);
		
	output_rootfile->Write();

	return true;
}