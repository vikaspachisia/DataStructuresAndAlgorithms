#pragma once
//#include <string>
//#include <map>
//#include <filesystem>
//using namespace std;
//
//struct programdata_filenames {
//	string input_filename;
//	string output_filename;
//	string expectedoutput_filename;
//};
//
//class programdata_mapper
//{
//public:
//	void buildMap()
//	{
//		
//	}
//private:
//	/*
//	if datafile folder is found then build a cahce of programs and the associated datafiles.
//	The pattern followed is "<programname>_<filepurpose>.txt" where <filepurpose> can be:
//	1. input: contains the input data for the program.
//	2. output: will contain the output data by the program.
//	3. output_expected: contains the expected output from the program.	
//	*/
//	void buildCache() 
//	{
//		auto datafileFolder = getDatafilesFolder();
//		if (!datafileFolder.empty()) {
//			programdata_filenames programdata_filenames;
//			
//			for (auto it = filesystem::directory_iterator(datafileFolder); it != filesystem::directory_iterator(); ++it) {				
//				if (it->path().has_filename()) {
//					string datafilename = it->path().filename().string();
//					auto idx = datafilename.find("_input");
//					string programname = 
//					if ( != -1) { programdata_filenames.input_filename = datafilename; }
//					else if(datafilename.find("_output_expected") != -1){ programdata_filenames.expectedoutput_filename = datafilename; }
//					else if(datafilename.find("_output") != -1) { programdata_filenames.output_filename = datafilename; }
//					else { clog << "purpose of datafile " << datafilename << " not known!" << endl; }
//				}
//			}
//		}
//	}
//
//	/*
//	get the list of programs (program names) available in the datafiles folder.	
//	*/
//	vector<string> getProgramNames(string datafilesFolderPath)
//	{
//		vector<string> retVal;
//		for (auto it = filesystem::directory_iterator(datafilesFolderPath); it != filesystem::directory_iterator(); ++it) {
//			if (it->path().has_filename()) {
//				auto filename = it->path().filename().string();
//				auto idx = filename.find("_input.txt");
//				if(file)
//			}
//		}
//	}
//
//	/*
//	Search for the presence of the datafiles folder in the parent chain upto the nesting level defined by this class.
//	Search starts from the current level and the nesting level should include this count.
//	*/
//	string getDatafilesFolder() {
//		string retVal;
//
//		string datafileFolder = ".\\" + m_datafiles_foldername;
//		for (int i = 0; i < m_datafiles_folder_nesting_level && retVal.empty(); i++) {
//			if (filesystem::exists(datafileFolder)) retVal = datafileFolder;
//			else datafileFolder = "..\\" + datafileFolder;
//		}
//		return retVal;
//	}
//private:
//	map<string, programdata_filenames> m_ProgramdataFilenamesCache;
//	string m_datafiles_foldername = "DataFiles";
//	string m_programname_filter_token = "_input.txt"; //token used to filter out filenames that will correspond to program names.
//	const int m_datafiles_folder_nesting_level = 5; //go upto 4 levels up the parent chain. The 5th one is the current level.
//};