
/*
 * Author:  William Kreahling and Mark Holliday and Gajjan Jasani
 * Purpose: Function Prototypes for parser.c
 * Date:    Modified 9-26-08, 3-25-15, 4-12-2016
 */
#ifndef PARSER_H
   #define PARSER_H
#define ERROR -999999
int bexpr(char *);
int expr(char *);
int term(char *);
int ttail(char *, int);
int stmt(char *);
int stail(char *, int);
int factor(char *);
int ftail(char *, int);
int expp(char *);  

void add_sub_tok(char *);
void mul_div_tok(char *);
void compare_tok(char *);
void expon_tok(char *); // helper function
int num(char *);
int is_number(char *);  // helper function
int exponentiation(int , unsigned int );// helper function

#endif
