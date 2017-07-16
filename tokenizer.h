/**
 * tokenizer.h - Header file for the tokenizer project modified for
 * 				 parsing project
 *
 * @author Gajjan Jasani
 * @version 03/08/2016
 * @modified 4/12/2016
 *
 */
/* Constants */
#define LINE 100
#define TSIZE 20
#define FIRST_ELE 0



/* Lexemes array */
char lexemes[12] = {'+', '-', '*', '/', '(', ')', '^', '=', '<', '>', '!', ';'};

/**
* Function prototypes
*/
char* get_token();
int check_lexeme(char);
char* handle_digit_token(char);
char* handle_special_char_token(char);
void handle_error(char);


