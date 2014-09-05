#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <error.h>


bool read_word(FILE *fp, char buf[])
{
   while(true) {
       if (fscanf(fp, " %32s", buf) == 1) {
           int ch = getc(fp);
           if (isspace(ch)) return true;
             ungetc(ch, fp);
       }
       if (feof(fp) || fscanf(fp, "%*s") == EOF) return false;
   }
}

int main(int argc, char *argv[])
{
   char filename[128];
   FILE *infile;
   int wcount = 0;
   char buf[32];
   printf("Welcome to Word Count!\nEnter filename: ");
   scanf("%s", filename);
   infile = fopen(filename, "r");
   if(infile == NULL) error(1, 0, "This file does not exist");
   while (read_word(infile, buf)) {
       wcount++;
   }
   printf("%s has %d words.\n", filename, wcount);
   fclose(infile);
   return 0;
}
