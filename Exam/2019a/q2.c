#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if(argc == 3){
        FILE *inFile = fopen(argv[1],"r");
        FILE *outFile = fopen(argv[2], "w");
        char c;
        while((c=fgetc(inFile))!=EOF){
            fputc(c,outFile);
        }
    }
    else if(argc == 2){
        FILE *inFile = fopen(argv[1],"r");
        char c;
        while((c=fgetc(inFile))!=EOF){
            fputc(c,stdout);
        }
    }
    else{
        char c;
        while((c=fgetc(stdin))!=EOF){
            fputc(c,stdout);
        }
    }
    return 0;
}
