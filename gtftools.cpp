/************************************************
A group of tools for analysis of GTF file.
(c) 2019.7.22 - KunDu.
Farm Animal Genetic Resource Exploration and 
Innovation Key Laboratory of SiChuan Province.
SiChuan Agricultural University
Chengdu China
611130
E-mail: 303160294@qq.com
************************************************/

#include <iostream>
#include <string>
using namespace std;

// define program name
#define PROGRAM_NAME "GTFtools"
void help();

//sub programs
int extract_main(int argc, char** argv);
int STscreenByFPKM(int argc, char** argv);

//argc refer to argument count, **argv refer to argument array 
int main(int argc, char** argv)
{
	// parsing sub-commands

	if (argc < 2){
		help();
	    return 0;
	}
	// read subcommand from command line
	string subcommand = argv[1];
	
	if (argc >= 2){
		// GTF extract tools
		if (subcommand == "extract"){
			return extract_main(argc-1, argv+1);
			}
		// for handle StringTie output style GTFs
		else if (subcommand == "STscreen"){
			return STscreenByFPKM(argc-1 , argv+1);
		}
		// unknown sub command
		else{
			cerr << "No such sub-program:"<< subcommand<< endl;
			help();
			return 0;
		}
	}
}
void help(){
	cout<<PROGRAM_NAME<<": a tool for analysis of GTF files.\n";
	cout<<"The GTFtools include sub-commmands include:\n\n";
	cout<<"extract\t\t\t-Extract sub-GTF by designated feature or designated gene name\n";
	cout<<"covert\t\t\t-For screen StringTie output GTFFiless\n";
}