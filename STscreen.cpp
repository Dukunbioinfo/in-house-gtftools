#include "STscreen.h"

// constructor, initialize member of _gtfFile
STscreen::STscreen(string &gtfFile): _gtfFile(gtfFile) 
{}

//destructor
STscreen::~STscreen() {}

void STscreen::screenByFPK(float & FPKM){
	_pGTFfile = new GTFfile(_gtfFile);
	_pGTFfile->loadIntoMap();
	_pGTFfile->selectTranscript(FPKM);
	_pGTFfile->printSelectedTranscript();

	delete _pGTFfile;
}
void STscreen::screenByExonNum(int & exonNumThreshold){
	_pGTFfile = new GTFfile(_gtfFile);
	_pGTFfile->loadIntoMap();
	_pGTFfile->selectTranscriptByExonNum(exonNumThreshold);
	_pGTFfile->printSelectedTranscript();

	delete _pGTFfile;
}
void STscreen::screenBylength(unsigned int & lengthThreshod){
	_pGTFfile = new GTFfile(_gtfFile);
	_pGTFfile->loadIntoMap();
	_pGTFfile->selectTranscriptByLength(lengthThreshod);
	_pGTFfile->printSelectedTranscript();
	
	delete _pGTFfile;
}
void STscreen::screenByClassCode(string & classCode){
	_pGTFfile = new GTFfile(_gtfFile);
	_pGTFfile->loadIntoMap();
	_pGTFfile->selectTranscriptByClassCode(classCode);
	_pGTFfile->printSelectedTranscript();

	delete _pGTFfile;
}
