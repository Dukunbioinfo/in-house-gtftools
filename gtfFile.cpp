#include "gtfFile.h"

GTFfile::GTFfile(string & gtfFile):
	_gtfFile(gtfFile)
{}
GTFfile::~GTFfile() {}

void GTFfile::TokenizeLine(){
	_gtfFields.clear();
	char delimiter = '\t';
	stringstream ss(_gtfLine); //read line into a stringstream 
	string item; 
	while(getline(ss, item, delimiter)){ //function getline read temporary string from stringstream by '\t', default '\n'
		_gtfFields.push_back(item);
	}
}
void GTFfile::initialGTF(GTF & gtf){
	gtf.chrom = _gtfFields[0];
	gtf.source = _gtfFields[1];
	gtf.featureName = _gtfFields[2];
	gtf.start = atoi(_gtfFields[3].c_str());
	gtf.end = atoi(_gtfFields[4].c_str());
	gtf.score = _gtfFields[5];
	gtf.srand = _gtfFields[6];
	gtf.phase = _gtfFields[7];
	gtf.attributes = _gtfFields[8];
}
void GTFfile::TokenizeComment(GTF & gtfterm){
	_commentFileds.clear();
	char delimiter = ';';
	stringstream ss(_commentLine); //read line into a stringstream 
	string item; 
	while(getline(ss, item, delimiter)){ //function getline read temporary string from stringstream by '\t', default '\n'
		_commentFileds.push_back(item);
	}
}
void GTFfile::Open(){
	_gtfLine.reserve(12);//数据可以在成员函数内部初始化
	if (_gtfFile == "stdin" || _gtfFile == "-")
		_gtfStream = &cin;
	else{
		_gtfStream = new ifstream(_gtfFile.c_str(), ios::in); //ifstream 是从外部文件输入
		if (_gtfStream->fail()){cerr<<"Can not open this File"<<endl;}
	}
}
void GTFfile::printHeader(){
	Open();
	string buf;
	while (getline(*_gtfStream, buf))
	{
		if(buf[0] == '#')
			cout<<buf<<endl;
		else
			break;
	}
}
void GTFfile::printByFeature(string & feature){
	Open();
	while (getline(*_gtfStream, _gtfLine))
	{
		if(_gtfLine[0] == '#')
			continue;
		else{
			TokenizeLine();
			if (_gtfFields[2] == feature)
				cout<<_gtfLine<<endl;
		}
	}
}
void GTFfile::loadIntoMap(){
	GTF term;
	Open();
	while (getline(*_gtfStream, _gtfLine))
	{
		if(_gtfLine[0] == '#')
			continue;
		else{
			TokenizeLine();
			initialGTF(term);
			if (_gtfFields[2] != "gene"){
				_commentLine = _gtfFields[8];
				TokenizeComment(term);
				parseCommment();
				_transcriptName.clear();
				for (int i = 16; i < _commentFileds[_transcript_idPos].size()-1; i++)
					_transcriptName += _commentFileds[_transcript_idPos][i];
				
			_transcriptMapToGtf[_transcriptName].push_back(term);
			}	
		}
	}
}
void GTFfile::loadIntoMapByGene(){
	GTF term;
	Open();
	while (getline(*_gtfStream, _gtfLine))
	{
		if(_gtfLine[0] == '#')
			continue;
		else{
			TokenizeLine();
			initialGTF(term);
			_commentLine = _gtfFields[8];
			TokenizeComment(term);
			_geneName.clear();
			for (int i = 9; i < _commentFileds[0].size()-1; i++)
				_geneName += _commentFileds[0][i];
		    _geneMapToGtf[_geneName].push_back(term);
		}
	}
}
void GTFfile::printByChrom(string &chrom){
	Open();
	while (getline(*_gtfStream,_gtfLine))
	{
		if(_gtfLine[0] == '#')
			continue;
		else{
			TokenizeLine();
			if (_gtfFields[0] == chrom)
				cout<<_gtfLine<<endl;
		}
	}
}
void GTFfile::parseCommment(){
	for (int i = 0; i < _commentFileds.size(); i++)
	{
		if (_commentFileds[i].find("transcript_id") == 1){
			_transcript_idPos = i;
		}
		if (_commentFileds[i].find("FPKM") == 1){
			_FPKMPos = i;
		}
	}
}
void GTFfile::loatListVector(string & transcriptList){
	istream *_list = new fstream(transcriptList.c_str(), ios::in);
	string buf;
	_selectedTranscripts.clear();
	while(getline(*_list, buf)){
		_selectedTranscripts.push_back(buf);
	}
	sort(_selectedTranscripts.begin(), _selectedTranscripts.end());
	vector<string>::iterator tmp = unique(_selectedTranscripts.begin(), _selectedTranscripts.end());
	_selectedTranscripts.erase(tmp, _selectedTranscripts.end());
}
void GTFfile::selectTranscript(float & FPKM){
	GTF term;
	Open();
	while (getline(*_gtfStream, _gtfLine))
	{
		if(_gtfLine[0] == '#')
			continue;
		else{
			TokenizeLine();
			initialGTF(term);
			if (_gtfFields[2] == "transcript"){
				_commentLine = _gtfFields[8];
				TokenizeComment(term);
				parseCommment();
				string FPKMtmp = "";
				for (int i = 7; i < _commentFileds[_FPKMPos].size()-1; i++){
					FPKMtmp += _commentFileds[_FPKMPos][i];
				}
				_FPKMvalue = atof(FPKMtmp.c_str());
				_transcriptName.clear();
				for (int i = 16; i < _commentFileds[_transcript_idPos].size()-1; i++)
					_transcriptName += _commentFileds[_transcript_idPos][i];

				if (_FPKMvalue > FPKM){
					_selectedTranscripts.push_back(_transcriptName);
				}
			}

		}
	}
}
void GTFfile::selectTranscriptByExonNum(int & exonNumThreshold){
	for (map<string, vector<GTF> >::iterator it = _transcriptMapToGtf.begin();it != _transcriptMapToGtf.end(); it++){
		if (it->second.size() > exonNumThreshold){
			_selectedTranscripts.push_back(it->first);
		} 
	}
}
void GTFfile::selectTranscriptByLength(unsigned int &lengthThreshold){
	for (map<string, vector<GTF> >::iterator it = _transcriptMapToGtf.begin();it != _transcriptMapToGtf.end(); it++){
		unsigned int countLength = 0;
		for (int i = 0; i< it->second.size(); i++){
			if (it->second[i].featureName == "exon"){
				countLength += it->second[i].end - it->second[i].start;
			}
		}
		if (countLength >= lengthThreshold)
			_selectedTranscripts.push_back(it->first);
	}
}
void GTFfile::selectTranscriptByClassCode(string &classCode){
	for (map<string, vector<GTF> >::iterator it = _transcriptMapToGtf.begin();it != _transcriptMapToGtf.end(); it++){
		unsigned int countLength = 0;
		for (int i = 0; i< it->second.size(); i++){
			if (it->second[i].featureName == "transcript"){
				_classCodePos = it->second[i].attributes.find("class_code ");
				_classCode = it->second[i].attributes[_classCodePos+12];
				for (int j = 0; j <classCode.size(); j++){
					//_classCode.c_str() was a char*
					if (_classCode.c_str()[0] == classCode[j]) 
						_selectedTranscripts.push_back(it->first);
				}
			}
		}
    }
}
void GTFfile::printSelectedTranscript(){
	for (int i = 0; i < _selectedTranscripts.size(); i++){
		vector<GTF> s = _transcriptMapToGtf[_selectedTranscripts[i]];
		for (int j = 0; j < s.size(); j++)
			s[j].printGTFLine();
	}
}
