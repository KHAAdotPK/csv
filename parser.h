/*
    src/parser.h
    Written by, Q@khaa.pk
 */

#ifndef		CC_TOKENIZER_CSV_PARSER_H
#define		CC_TOKENIZER_CSV_PARSER_H

#ifndef     GRAMMAR_END_OF_TOKEN_MARKER
#define		GRAMMAR_END_OF_TOKEN_MARKER     ","
#endif

#ifndef     GRAMMAR_END_OF_TOKEN_MARKER_SIZE
#define		GRAMMAR_END_OF_TOKEN_MARKER_SIZE    1
#endif

/* On a Windows machine it is "\n\r" */
#define		GRAMMAR_END_OF_LINE_MARKER	"\n"
#define		GRAMMAR_END_OF_LINE_MARKER_SIZE	1

// reset() method, argument values  
#define   	LINES 				0
#define		TOKENS				1

#define		GRAMMAR_START_OF_COMMENT	'#'
#define		GRAMMAR_START_OF_LINE_MARKER	":"

#endif