/**
 * tokenizer.c - A simple token recognizer.
 *
 * NOTE: The terms 'token' and 'lexeme' are used interchangeably in this
 *       program.
 *
 * @author Gajjan Jasani
 * @version 03/08/2016
 * @modified 04/10/2016
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"


int expression_pointer = 0;
extern char expression[100];


/**
* Function: get_token
* Purpose : To find one token or one error at a time from the input line
* and record that token or error on the output file
* Return  : next token in the expression/entered line
*/
char* get_token(){
	char c;		// holding char from input line
	char* token = calloc(sizeof(char), 20);
	c = expression[expression_pointer];

	if(isdigit(c)){		// if the first char is a digit
		token = handle_digit_token(c);
	}else if(check_lexeme(c)){ 	// If the char is part of our lexemes array
		token = handle_special_char_token(c);
	}else { 	// if the char is not a digit or a defined lexeme
		handle_error(c);
	}

	return token;
}

//==================== HELPER FUNCTIONS =========================

/**
 * Function: check_lexeme
 * Purpose : Check if the char read from input line is part of our
 * lexeme definition (lexems array)
 * c: The char that needs to be checked
 * Return: 1 if c is part of our lexeme definition, 0 if not
 */
int check_lexeme(char c){

	int i = 0;
	while(i < strlen(lexemes)){
		if(lexemes[i] == c){
			return 1;	// early termination if c is part of our definition
		}
		i++;
	}
	return 0;
}

/**
 * Function: handle_digit_token
 * Purpose : If the char read from input line is a digit, check for more
 * subsequent digits to find the whole integer
 * c		: the first char that is a digit
 * Return  : number token
 */
char* handle_digit_token(char c){

	char* token = calloc(sizeof(char), 20);
	int j;	// counters
	j = 0;
	token[j]= c; // put the first digit on token array
	j++;
	expression_pointer++;
	while(expression_pointer < strlen(expression)){ // keep looking for
													// next chars until we find
							 	 	 	 	 	 	// a char that is not digit
		c = expression[expression_pointer];	// next char on the input line
		if(!isdigit(c)){
			return token; // if next char is not a digit
					// end the token
		} else {	// if next char is a digit, keep looking
			token[j] = c;
			j++;
			expression_pointer++;
		}
	}
	return token;
}

/**
 * Function: handle_special_char_token
 * Purpose : If the char read from input line is a lexeme defined on our
 * lexemes array, write that on the output file
 * c		: the first char that is a legit lexeme
 * Return  : special char (operation) token
 */
char* handle_special_char_token(char c){

	char* token = calloc(sizeof(char), 20);
	token[FIRST_ELE] = c;
	expression_pointer++;
	// Special case: if the first char is <, >, !, or = then
	// check if the next char is = or not
	if((c == '<' || c == '>' || c == '!' || c == '=') &&
			(expression_pointer < strlen(expression))){
		if(expression[expression_pointer] == '='){
			token[FIRST_ELE+1] = '=';
			expression_pointer++;
			return token;
		} else if(c == '!'){
			printf("===> '%s'\n", token);
			printf("Lexical Error: not a lexeme\n");
			exit(0);
		}
	}
	return token;
}

/**
 * Function: handle_error
 * Purpose : If the char read from input line is not a lexeme defined on our
 * lexemes array, or not a digit, denote it as an error on the output file
 * c		: the first char that is a legit lexeme
 */
void handle_error(char c){

	if(expression_pointer == 0 && c == 'q'){
		printf("Goodbye!");
		exit(0);
	}
	char* token = calloc(sizeof(char), 20);
	int j;	// counters
	j = 0;
	token[j]= c; // put the first digit on token array
	j++;
	expression_pointer++;
	while(expression_pointer < strlen(expression)){
		c = expression[expression_pointer];
		if(isdigit(c) || check_lexeme(c)){
			printf("===> '%s'\n", token);
			printf("Lexical Error: not a lexeme\n");
			exit(0);
		} else {
			token[j] = c;
			j++;
			expression_pointer++;
		}
	}

}
