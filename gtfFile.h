#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <algorithm>
using namespace std;

// GTF data structures
struct GTF
{
	string chrom;
	string source;
	string featureName;
	unsigned int start;
	unsigned int end;
	string score;
	string srand;
	string phase;
	string attributes;
public:
	// constructor
	GTF(): 
		chrom(""),
		source(""),
		featureName(""),
		start(0),
		end(0),
		score(""),
		srand(""),
		phase("")

	{}
	// print GTF objective.
	inline void printGTFLine(){
		cout<<chrom<<'\t'<<source<<'\t'<<featureName<<'\t'<<start<<'\t'<<end<<'\t'<<score<<'\t';
		cout<<srand<<'\t'<<phase<<'\t'<<attributes<<endl;
	}
};

// GTFfile elements and methods
class GTFfile{
private:
	// data
	string _gtfFile;
	istream *_gtfStream;
	string _gtfLine;
	vector<string> _gtfFields;
	string _commentLine;
	vector<string> _commentFileds;
	string _transcriptName;
	string _geneName;
	int _transcript_idPos;
	int _FPKMPos;
	float _FPKMvalue;
	int _classCodePos;
	string _classCode;
	
	
public:
	map<string, vector<GTF> > _transcriptMapToGtf;
	map<string, vector<GTF> > _geneMapToGtf;
	vector<string> _selectedTranscripts;

	// constructor
	GTFfile(string & gtfFile);
	// destructor
	~GTFfile();


	// load _gtfLine into vector _gtfFields
	void TokenizeLine();

	// initialize a GTF struct 
	void initialGTF(GTF & gtf);

	// load _commentLine into vector _commentFileds
	void TokenizeComment(GTF & gtfterm);

	// read gtf file into a ifstream objective  *_gtfStream
	void Open();

	// parsing a comment line
	inline void parseCommment();

	// print header line which were begin with char '#' 
	void printHeader();

	// print special chrom correspond transcripts
	void printByChrom(string &chrom);
	
	// print exon lines, transcript lines, or gene line
	void printByFeature(string &feature);

	// load GTF int map {transcript name : vector<GTF obj>}
	void loadIntoMap();
	
	// load GTF int map {gene name : vector<GTF obj>}
	void loadIntoMapByGene();

	// load input transcript list or gene list into member of _selectedTranscripts
	void loatListVector(string &transcriptList);

	// print transcript in the _selectedTranscripts
	void printSelectedTranscript();

	//*******************************************************************
	// four screen rule FPKM, exon num, transcript length, and class code.
	void selectTranscript(float & FPKM);
	void selectTranscriptByExonNum(int & exonNumthreshold);
	void selectTranscriptByLength(unsigned int &lengthThreshold);
	void selectTranscriptByClassCode(string &classCode);
	//*******************************************************************
};