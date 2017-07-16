
/**
 * main.c - Entry point for the Recusrive Decent Parser Project
 * @author Gajjan Jasani
 * @version 04/08/2016
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINE 100
#define TSIZE 20
/* Global declarations */
char  expression[LINE];  /* expression entered by user */

/**
* Function prototypes
*/
void clean_input_line(char* );
extern char* get_token();
extern int bxper(char *);


/**
 *  Function: main
 *  Purpose : The entry point to this program. This function calls tokenizer
 *  and parser to parse and interpret the user entered expression and prints
 *  the result on console
 *  Return: 0
 */
int main() {

   char* token;      /* Spot to hold a token for test */
   int result;


  printf("Please enter expression: ");
  // Reading the user input for analyzation
  if (fgets(expression, LINE, stdin) != NULL){
      clean_input_line(expression);	// Clearing out white spaces from input line

      if(expression[0] != 'q' && expression[strlen(expression)-1] != ';'){
    	  printf("Syntax Error: Missing \";\" at the end\n");
    	  exit(0);
      }
      token = get_token();
      result = bxper(token);
      printf("Syntax OK\n");
      printf("Value is: %d\n", result);
   }
   return 0;
}

/**
 * Function: clean_input_line
 * Purpose : Remove all the white spaces from the input line
 */
void clean_input_line(char* line){

	int i=0, j=0;
	int len = (int)strlen(line);
	while (i != len) {
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'){
			line[j++] = line[i];
		}
		i++;
	}
	line[j]=0; // making sure there is a null character at the end of line
}


