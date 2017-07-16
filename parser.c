/*
 * parser.c - recursive descent parser for a simple expression language.
 *            Most of the functions in this file model a Non-terminal in the
 *            grammar listed below
 * Author: William Kreahling and Mark Holliday and Gajjan Jasani
 * Date:   Modified 9-29-08 and 3-25-15 and 4-12-2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "parser.h"

/* Global declarations */
char *next_token; // hold next token of expression
extern char* get_token();

/*
 * <bexpr> ::= <expr> ;
 * <expr> ::=  <term> <ttail>
 * <ttail> ::=  <add_sub_tok> <term> <ttail> | e
 * <term> ::=  <stmt> <stail>
 * <stail> ::=  <mult_div_tok> <stmt> <stail> | e
 * <stmt> ::=  <factor> <ftail>
 * <ftail> ::=  <compare_tok> <factor> <ftail> | e
 * <factor> ::=  <expp> ^ <factor> | <expp>
 * <expp> ::=  ( <expr> ) | <num>
 * <add_sub_tok> ::=  + | -
 * <mul_div_tok> ::=  * | /
 * <compare_tok> ::=  < | > | <= | >= | ! = | ==
 * <num> ::=  {0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9}+
 */


/*
 * bexpr : Application of rule <bexpr> -> <expr>
 * arg   : token - token needing to be parsed
 * Return: return value of expr function
 */
int bxper(char *token){
	return expr(token);
}

/*
 * expr  : Application of rule <expr> -> <term> <ttail>
 * arg   : token - token needing to be parsed
 * Return: return value of ttail function if not error
 */
int expr(char *token){

   int subtotal = term(token);
   if (subtotal == ERROR)
      return subtotal;
   else
      return ttail(next_token, subtotal);
}

/*
 * term  : Application of rule <expr> -> <term> <ttail>
 * arg   : token - token needing to be parsed
 * Return: return value of stail function if not error
 */
int term(char *token){

   int subtotal = stmt(token);
   if (subtotal == ERROR)
	  return subtotal;
   else
	  return stail(next_token, subtotal);
}

/*
 * stmt  : Application of rule <stmt> ->  <factor> <ftail>
 * arg   : token - token needing to be parsed
 * Return: return value of ftail function if not error
 */
int stmt(char *token){

   int subtotal = factor(token);
   if (subtotal == ERROR)
	  return subtotal;
   else
	  return ftail(next_token, subtotal);
}
/*
 * factor: Application of rule <factor> ->  <expp> ^ <factor> | <expp>
 * arg   : token - token needing to be parsed
 * Return: return result of exponentiation/return val of expp() if not error
 */
int factor(char* token){

	int subtotal = expp(token);

	if (subtotal != ERROR){
	   if(!strncmp(next_token, "^", 1)){
		   expon_tok(token);
		   return ( exponentiation(subtotal, factor(next_token)));
	   } else {
		   return subtotal;
	   }
	} else{
		return ERROR;
	}
}

/*
 * expp  : Application of rule <expp> ->  ( <expr> ) | <num>
 * arg   : token - token needing to be parsed
 * Return: return result of expression in ()/return val of num() if not error
 */
int expp(char *token){

	int subtotal;
	if(!strncmp(token, "(", 1)){
		next_token = get_token();
		subtotal = expr(next_token);
		if(!strncmp(next_token, ")", 1)){
			next_token = get_token();
			return subtotal;
		} else {
			printf("===> ')' expected\n");
			printf("Syntax Error");
			exit(0);
		}
	} else {
		return num(token);
	}

	return 0;
}

/*
 * num   : Application <num> ->  {0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9}+
 * arg   : token - token needing to be parsed
 * Return: return val of is_number function
 */
int num(char *token){

	int subtotal = is_number(token);
	return subtotal;
}
/*
 * is_number : helper function for num()
 * 			   Checks if the token needing to be parsed is a number or not
 * 			   if it is a number, converts it to a number
 * arg   : token - token needing to be parsed
 * Return: return token as an int if token is a number else error
 */
int is_number(char *token){

	int subtotal;

	if(isdigit(*token)){
		subtotal = strtol(token, &token, 10);
		next_token = get_token();
		return subtotal;
	} else {
		return ERROR;
	}
}

/*
 * add_sub_tok : Application of rule <add_sub_tok> ->  + | -
 * 				 Consumes + | - and updates next_token
 * arg   : token - token needing to be parsed
 */
void add_sub_tok(char *token){

	next_token = get_token();
}

/*
 * mul_div_tok : Application of rule <mul_div_tok> ->  * | /
 * 				 Consumes * | / and updates next_token
 * arg   : token - token needing to be parsed
 */
void mul_div_tok(char *token){

	next_token = get_token();
}

/*
 * compare_tok : Application of <compare_tok> -> < | > | <= | >= | ! = | ==
 * 				 Consumes < | > | <= | >= | ! = | == and updates next_token
 * arg   : token - token needing to be parsed
 */
void compare_tok(char *token){

	next_token = get_token();
}

/*
 * expon_tok   : Helper function for factor()
 * 				 Consumes ^ and updates next_token
 * arg   : token - token needing to be parsed
 */
void expon_tok(char *token){

	next_token = get_token();
}

/*
 * expon_tok   : Helper function for factor()
 * 				 instead of using Math.Pow() this works with integers
 * 				 instead of just double type variables
 * arg   : base, exponent for exponentiation
 * Return: result of exponentiation of base and exponent
 */
int exponentiation(int base, unsigned int exp){
	int i, result = 1;
	for (i = 0; i < exp; i++){
		result *= base;
	}
	return result;
}

/*
 * ttail : Application of rule <ttail> -> <add_sub_tok> <term> <ttail> | e
 * arg   : token - token needing to be parsed
 * Return: return recursive result of itself
 */
int ttail(char *token, int subtotal){

   int term_value;

   if (!strncmp(token, "+", 1)){
      add_sub_tok(token);
      term_value = term(next_token);

      // if term returned an error, give up otherwise call ttail
      if (term_value == ERROR)
         return term_value;
      else
         return ttail(next_token, (subtotal + term_value));
   }
   else if(!strncmp(token, "-", 1)){
      add_sub_tok(token);
      term_value = term(next_token);

      // if term returned an error, give up otherwise call ttail
      if (term_value == ERROR)
         return term_value;
      else
         return ttail(next_token, (subtotal - term_value));
   }
   /* empty string */
   else
      return subtotal;
}

/*
 * stail : Application of rule <stail> ->  <mult_div_tok> <stmt> <stail> | e
 * arg   : token - token needing to be parsed
 * Return: return recursive result of itself
 */
int stail(char *token, int subtotal){

   int stmt_value;

   if (!strncmp(token, "*", 1)){
	  mul_div_tok(token);
      stmt_value = stmt(next_token);

      // if term returned an error, give up otherwise call ttail
      if (stmt_value == ERROR)
         return stmt_value;
      else
         return stail(next_token, (subtotal * stmt_value));
   }
   else if(!strncmp(token, "/", 1)){
	  mul_div_tok(token);
      stmt_value = stmt(next_token);

      // if term returned an error, give up otherwise call ttail
      if (stmt_value == ERROR)
         return stmt_value;
      else
         return stail(next_token, (subtotal / stmt_value));
   }
   /* empty string */
   else
      return subtotal;
}

/*
 * ftail : Application of rule <ftail> ->  <compare_tok> <factor> <ftail> | e
 * arg   : token - token needing to be parsed
 * Return: return recursive result of itself
 */
int ftail(char *token, int subtotal){

   int factor_value;

   if (!strncmp(token, "<", 1)){
	  compare_tok(token); // updates next_token to next one by get_token()
	  factor_value = factor(next_token); //using the updated next_token

      // if term returned an error, give up otherwise call ttail
      if (factor_value == ERROR)
         return factor_value;
      else
         return ftail(next_token, (subtotal < factor_value));
   }else if(!strncmp(token, ">", 1)){
	  compare_tok(token);
	  factor_value = factor(next_token);

      // if term returned an error, give up otherwise call ttail
      if (factor_value == ERROR)
         return factor_value;
      else
         return ftail(next_token, (subtotal > factor_value));
   }else if(!strncmp(token, "<=", 1)){
	  compare_tok(token);
	  factor_value = factor(next_token);

	  // if term returned an error, give up otherwise call ttail
	  if (factor_value == ERROR)
		 return factor_value;
	  else
		 return ftail(next_token, (subtotal <= factor_value));
   }else if(!strncmp(token, ">=", 1)){
   	  compare_tok(token);
   	  factor_value = factor(next_token);

	  // if term returned an error, give up otherwise call ttail
	  if (factor_value == ERROR)
		 return factor_value;
	  else
		 return ftail(next_token, (subtotal >= factor_value));
   }else if(!strncmp(token, "!=", 1)){
	  compare_tok(token);
	  factor_value = factor(next_token);

	  // if term returned an error, give up otherwise call ttail
	  if (factor_value == ERROR)
		 return factor_value;
	  else
		 return ftail(next_token, (subtotal != factor_value));
   }else if(!strncmp(token, "==", 1)){
	  compare_tok(token);
	  factor_value = factor(next_token);

	  // if term returned an error, give up otherwise call ttail
	  if (factor_value == ERROR)
		 return factor_value;
	  else
		 return ftail(next_token, (subtotal == factor_value));
   }
   /* empty string */
   else
      return subtotal;
}

