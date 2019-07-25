#include "extract.h"

using namespace std;
#define PARAMETER_CHECK(param, paramLen, actualLen) (strncmp(argv[i], param, min(actualLen, paramLen)) == 0) && (actualLen == paramLen)
void extractHelp();
int extract_main(int argc, char** argv){
	bool showHelp = false;
	string gtfFile = "stdin";
	string feature = "";
	string chrom = "";
	bool byFeature = false;
	bool byChrom = false;
	int extractChoise = 0;
	bool printHeader = false;
	string transcriptsList = "stdin";
	bool byTranscriptsList = false;
	string geneList = "stdin";
	bool byGeneList = false;


	if (argc == 1) showHelp = true;

	for (int i = 1; i< argc; i++){
		int parameterLength = (int)strlen(argv[i]); //calculating parameter length
		if ((PARAMETER_CHECK("-h",2,parameterLength)) || (PARAMETER_CHECK("-help",5,parameterLength)))
		{
			showHelp = true;
			break;
		}
	}
	if (showHelp == true) {
		extractHelp(); 
		exit(1);
	} 

	// parsing parameters
	for (int i = 1; i < argc; i++){
		int parameterLength = (int)strlen(argv[i]);
		if (PARAMETER_CHECK("-i", 2, parameterLength)){
			gtfFile = argv[i + 1];
			i++;
		}
		else if (PARAMETER_CHECK("-feature", 8, parameterLength)){
			byFeature = true;
			feature = argv[i+1];
			extractChoise++;
			i++;
		}
		else if (PARAMETER_CHECK("-chrom", 6, parameterLength)){
			chrom = argv[i+1];
			byChrom = true;
			extractChoise++;
			i++;
		}
		else if (PARAMETER_CHECK("-header", 7, parameterLength)){
			printHeader = true;
			extractChoise++;
		}
		else if (PARAMETER_CHECK("-transcript", 11, parameterLength)){
			byTranscriptsList = true;
			transcriptsList = argv[i+1];
			extractChoise++;
			i++;
		}
		else if (PARAMETER_CHECK("-gene", 9, parameterLength)){
			byGeneList = true;
			geneList = argv[i+1];
			extractChoise++;
			i++;
		}
		else {
			cerr << endl << "*****ERROR: Unrecognized parameter: " << argv[i] << " *****"<<endl;
			showHelp = true;
		}
	}
	//make sure only one choose for sort
	if (extractChoise > 1) {
		cerr << endl << "*****" << endl << "*****ERROR: Extracting options are mutually exclusive.  Please choose just one. " << endl << "*****" << endl;
		showHelp = true;
	}
	if (showHelp) extractHelp();
	if (!showHelp){
		//core program
		if (printHeader){
			Extract *em = new Extract(gtfFile);
			em->printHeader();
			delete em;
			return 0;
		}
		else if (byFeature){
			Extract *em = new Extract(gtfFile);
			em->printByFeature(feature);
			delete em;
			return 0;
		}
		else if (byTranscriptsList) {
			Extract *em = new Extract(gtfFile, transcriptsList);
			delete em;
		}
		else if (byGeneList){
			Extract *em = new Extract(gtfFile);
			em->printByGeneList(geneList);
			em->printBytranscript();
			delete em;
		}
		else if (byChrom){
			Extract *em = new Extract(gtfFile);
			em->printByChrom(chrom);
			delete em;
		}
	}
	return 0;
}
void extractHelp(){
	cerr << "\nTool:    gtftools extract" << endl;   
	cerr << "Summary: extract gtf in various and useful ways." << endl << endl;
	cerr << "Usage:   " << "gtftools" << " [OPTIONS] -i <gtf>" << endl << endl;

	cerr << "Options: " << endl;
	cerr << "\t" << "-feature\t\t"<< "Extract by feature such as exon, gene, and transcript." << endl;
	cerr << "\t" << "-header\t\t\t"    << "Extract header line of gtf File." << endl;
	cerr << "\t" << "-chrom\t\t\t"   << "Extract gtf of gtf File by chromosome." << endl;
	cerr << "\t" << "-transcript\t\t"   << "Extract gtf of gtf File by transcript list." << endl;
	cerr << "\t" << "-gene\t\t\t"  << "Extract gtf of gtf File by gene list." << endl<<endl;

	exit(1);

}