#pragma once
#include "gtfFile.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
//***************************
// Class elements and methods
//***************************
class STscreen{
private:
	// instance a GTFfile class
	GTFfile* _pGTFfile;

	string _gtfFile;
public:
    // constructor
	STscreen(string & GTFfile);
	// destructor
	~STscreen();
	void screenByFPK(float & FPKM);
	void screenByExonNum(int & exonNumThreshold);
	void screenBylength(unsigned int & lengthThreshold);
	void screenByClassCode(string & classCode);
};