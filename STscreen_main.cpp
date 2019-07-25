#include "STscreen.h"

using namespace std;
// define parameter checking macro
#define PARAMETER_CHECK(param, paramLen, actualLen) (strncmp(argv[i], param, min(actualLen, paramLen)) == 0) && (actualLen == paramLen)
// function declarations
void screenHelp();

int STscreenByFPKM(int argc, char** argv){

	// configuration variables
	bool showHelp = false;
	// input files
	string gtfFile = "stdin";
	int screenChoise = 0;
	// screen by transcript FPKM value
	bool byFPKM = false;
	float FPKMthrshold = 0;
	// screen by exons number
	bool byExonNum = false;
	int exonNumThreshold = 0;
	// screen by transcript length
	bool byLength = false;
	unsigned int lengthThreshold = 0;
	//screen by class code output from GffCompare software
	bool byClassCode = false;
	string classCode;

	// sub command parameter checking
	if (argc == 1) 
		showHelp = true;
	for (int i = 1; i< argc; i++){
		int parameterLength = (int)strlen(argv[i]); //calculating parameter length
		if ((PARAMETER_CHECK("-h",2,parameterLength)) || (PARAMETER_CHECK("-help",5,parameterLength)))
		{
			showHelp = true;
			break;
		}
	}
	if (showHelp == true) {
		screenHelp(); 
		exit(1);
	} 

	// parsing STscreen sub parameters
	for (int i = 1; i < argc; i++){
		// get the length of parameter
		int parameterLength = (int)strlen(argv[i]);

		if (PARAMETER_CHECK("-i", 2, parameterLength)){
			gtfFile = argv[i + 1];
			i++;
		}
		else if (PARAMETER_CHECK("-FPKM", 5, parameterLength)){
			byFPKM = true;
			FPKMthrshold = atof(argv[i+1]);
			screenChoise++;
			i++;
		}
		else if (PARAMETER_CHECK("-exonNum", 8, parameterLength)){
			byExonNum = true;
			exonNumThreshold = atoi(argv[i+1]);
			screenChoise++;
			i++;
		}
		else if (PARAMETER_CHECK("-length", 7, parameterLength)) {
			byLength = true;
			lengthThreshold = atoi(argv[i+1]);
			screenChoise++;
			i++;
		}
		else if (PARAMETER_CHECK("-classCode", 10, parameterLength)) {
			byClassCode = true;
			classCode = argv[i+1];
			screenChoise++;
			i++;
		}
		else {
			cerr << endl << "*****ERROR: Unrecognized parameter: " << argv[i] << " *****"<<endl;
			showHelp = true;
		}
	}
	// make sure only one choose for screening
	if (screenChoise > 1) {
		cerr << endl << "*****" << endl << "*****ERROR: STscreen options are mutually exclusive.  Please choose just one. " << endl << "*****" << endl;
		showHelp = true;
	}
	if (showHelp) screenHelp();
	if (!showHelp){
		//core program
		if (byFPKM){
			STscreen *sm = new STscreen(gtfFile);
			sm->screenByFPK(FPKMthrshold);
			delete sm;
			return 0;
		}
		if (byExonNum){
			STscreen *sm = new STscreen(gtfFile);
			sm->screenByExonNum(exonNumThreshold);
			delete sm;
			return 0;
		}
		if (byLength){
			STscreen *sm = new STscreen(gtfFile);
			sm->screenBylength(lengthThreshold);
			delete sm;
			return 0;
		}
		if (byClassCode) {
			STscreen *sm = new STscreen(gtfFile);
			sm->screenByClassCode(classCode);
			delete sm;
			return 0;
		}
	}
	return 0;
}
// screening help messages
void screenHelp() {
	cerr << "\nTool:    gtftools STscreen" << endl;   
	cerr << "Summary: handle Stringtie style gtf in various and useful ways." << endl << endl;
	cerr << "Usage:   " << "gtftools STscreen" << " [OPTIONS] -i <gtf>" << endl << endl;

	cerr << "Options: " << endl;
	cerr << "\t" << "-FPKM\t\t"<< "Screen gtfs by FPKM value (> threshold)." << endl;
	cerr << "\t" << "-exonNum\t"    << "Screen gtfs base on how manny exons contained in a transcripts (> threshold)." << endl;
	cerr << "\t" << "-length\t\t"   << "Screen gtfs base on transcripts length size (> threshold)." << endl;
	cerr << "\t" << "-classCode\t"   << "Screen gtfs base on class code output from gffcompare (ig xuio)." << endl<<endl;

	exit(1);
}
