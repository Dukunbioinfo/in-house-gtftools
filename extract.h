#pragma once

#include "gtfFile.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Extract{
private:
	// a GTFfile objective.
	GTFfile * _pGtfFile;

	// a transcript list of gene list istream objective. 
	istream *_list;
	
	vector<string> _listVctor;
public:
	Extract(string & filename);
	Extract(string & filename, string & transcriptList);
	~Extract();
	void printHeader();
	void printByFeature(string &feature);
	void printByGeneList(string & geneList);
	void printBytranscript();
	void printByChrom(string & chrom);
};