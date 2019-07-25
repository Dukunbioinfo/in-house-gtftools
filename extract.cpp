#include "extract.h"

Extract::Extract(string & filename){	
	_pGtfFile = new GTFfile(filename);
}
Extract::Extract(string & fileName, string & transcriptList){
	_pGtfFile = new GTFfile(fileName);
	_pGtfFile->loatListVector(transcriptList);
}

Extract::~Extract() {delete _pGtfFile;}

void Extract::printHeader(){
	_pGtfFile->printHeader();
}
void Extract::printByFeature(string &feature){
	_pGtfFile->printByFeature(feature);
}

void Extract::printBytranscript(){
	_pGtfFile->printSelectedTranscript();
}


void Extract::printByGeneList(string &geneList){
	_pGtfFile->loadIntoMapByGene();
	_list = new fstream(geneList.c_str(), ios::in);
	string buf;
	_listVctor.clear();
	while(getline(*_list, buf)){
		_listVctor.push_back(buf);
	}
	sort(_listVctor.begin(), _listVctor.end());
	vector<string>::iterator tmp = unique(_listVctor.begin(), _listVctor.end());
	_listVctor.erase(tmp, _listVctor.end());
	for (int i = 0; i < _listVctor.size(); i++){
		vector<GTF> s = _pGtfFile->_geneMapToGtf[_listVctor[i]];
		for (int j = 0; j < s.size(); j++)
			s[j].printGTFLine();
	}
}
void Extract::printByChrom(string & chrom){
	_pGtfFile->printByChrom(chrom);
}