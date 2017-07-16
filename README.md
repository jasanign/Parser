# Parser

This project is a basic interpreter in C language for arithmetic expressions as defined by a particular grammar that is implemented using a recursive descent parser. This parser is a language recognizer in which determines whether each expression that is input is syntactically correct (it also catches any lexical errors). This parser is also an  interpreter which evaluates and returns the resulting value when the input expressions are syntactically correct.

## Grammar

This parser uses the following grammar:

	<bexpr> ? <expr>;
	<expr> ? <term> <ttail>
	<ttail> ? <add_sub_tok> <term> <ttail> | epsilon
	<term> ? <stmt> <stail>
	<stail> ? <mult_div_tok> <stmt> <stail> | epsilon
	<stmt> ? <factor> <ftail>
	<ftail> ? <compare_tok> <factor> <ftail> | epsilon
	<factor> ? <expp> ^ <factor> | <expp>
	<expp> ? ( <expr> ) | <num>
	<add_sub_tok> ? + | -
	<mul_div_tok> ? * | /
	<compare_tok> ? < | > | <= | >= | != | ==
	<num> ? {0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 }+