# in-house-gtftools
A tool analysis of gtf file constructed in c++ languege 

linux command: 
g++ *.cpp -o inhouseGTFtools

./inhouseGTFtools --help


extract                 -Extract sub-GTF by designated feature or designated gene name

Usage:   gtftools [OPTIONS] -i gtfFile

Options:

        -feature                Extract by feature such as exon, gene, and transcript.
        
        -header                 Extract header line of gtf File.
        
        -chrom                  Extract gtf of gtf File by chromosome.
        
        -transcript             Extract gtf of gtf File by transcript list.
        
        -gene                   Extract gtf of gtf File by gene list.
        


STscreen                -For screen StringTie output GTFFiless

Usage:   gtftools STscreen [OPTIONS] -i gtfFile

Options:

        -FPKM           Screen gtfs by FPKM value (> threshold).
        
        -exonNum        Screen gtfs base on how manny exons contained in a transcripts (> threshold).
        
        -length         Screen gtfs base on transcripts length size (> threshold).
        
        -classCode      Screen gtfs base on class code output from gffcompare (ig xuio).
        
