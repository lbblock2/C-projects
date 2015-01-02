/* DECOMMENT
 * Author: Lauren Bayldon Block
 * Date: 1 January 2015
 * -------------------------------------
 * Decomment takes in a code file and creates a new version without the
 * comments. This is so that the user can recomment any code file.
 * Pro tip: run this code on itself!
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* copy_file
 * ---------------
 * Goes through the initial file and copies non-commented lines into the
 * new file.
 */
void copy_file(FILE *infile, FILE *outfile, int type)
{
	//Create strings for common types of comment markers (C, C++, Java)
	char *com0 = "//";
	char *com1 = "/*";
	char *com2 = "*/";
	char *com3 = "#";
	//mallocs a string to store the line, of no more than 100 chars (80 + buffer)
	char *currline = malloc(sizeof(char)*100);
	//While there are still lines in the infile, checks each line to see if a 
	// comment marker is a substring. If so, skips these lines

	//If Python (go by python comment marks)
	if (type == 2) {
		while (fgets(currline, 100, infile)) {
			if (strstr(currline, com3)) continue;
			//If it's a valid line, print it
			else fprintf(outfile, "%s", currline);
		}
	} 
  //If C or C++ or Java, go by their comment marks
	else if (type == 1) {
		while(fgets(currline, 100, infile)) {
			if (strstr(currline, com0)) continue;
			//for multi-line comments, waits until comment-closer
			else if(strstr(currline, com1)) {
				while (!strstr(currline, com2)) {
					fgets(currline, 100, infile);
				}
			}
			//If it's a valid line, prints it.
			else fprintf(outfile, "%s", currline);
		}
	}
	//Free malloced data
	free(currline);
}

/* get_type
 * --------------
 * Determines file type, whether .c, .cpp, .h, .java, .py) 
 */
int get_type(char filename[])
{
  int type = 0;
	for (int i = 29; i >= 0; i--) {
		if (filename[i] == '.') {
			char next = filename[i+1];
			if (next == 'c' || next == 'h' || next == 'j') type = 1;
			else if (next == 'p') type = 2;
			break;
		}
	}
	return type;
}

/* main
 * ----------------
 * Initializes, opens, and closes files. Runs the program. 
 */
int main(int argc, char *argv[])
{
	//Initializes a file for the original and a file for the new version
	FILE *infile;
	FILE *outfile;
	//Takes in the filename and makes sure it is valid (not too long for our max)
	char filename[30];
	printf("filename: ");
	scanf("%s", filename);
	if ((unsigned)strlen(filename) > 29) {
		return 1;
	}
	//gets type of file
	int type = get_type(filename);
	if (type == 0) return 1;
	//Creates a new filename, with added extension
	char newfile[38];
	strcpy(newfile, filename);
	strcat(newfile, "dcmt.txt");
	//Opens both files, the first to read, the second to write.
	infile = fopen(filename, "r");
	outfile = fopen(newfile, "w");
	//Calls copy_file
	copy_file(infile, outfile, type);
	//Closes both files and lets user know it has worked.
	fclose(infile);
	fclose(outfile);
	printf("done!\n");
	return 0;
}
