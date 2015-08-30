#include <zlib.h>  
#include <stdio.h>  
#include "kseq.h"  

// reference: http://lh3lh3.users.sourceforge.net/parsefastq.shtml

// Tao Zhu 2015-08-30

// STEP 1: declare the type of file handler and the read() function  
KSEQ_INIT(gzFile, gzread)  
  
int main(int argc, char *argv[])  
{  
    gzFile fp;  
    kseq_t *seq;  
    int l;  
    if (argc == 1) {  
        fprintf(stderr, "Usage: %s <in.seq>\n", argv[0]);  
        return 1;  
    }
    long int n = 0, slen = 0;
    fp = gzopen(argv[1], "r"); // STEP 2: open the file handler  
    seq = kseq_init(fp); // STEP 3: initialize seq  
    while ((l = kseq_read(seq)) >= 0) { // STEP 4: read sequence  
        ++n, slen += seq->seq.l;
    }  
    printf("Num reads:%ld\tNum Bases: %ld\n", n, slen); 
    kseq_destroy(seq); // STEP 5: destroy seq  
    gzclose(fp); // STEP 6: close the file handler  
    return 0;  
}  
