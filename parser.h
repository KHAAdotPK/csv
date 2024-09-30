/*
    src/parser.h
    Written by, Q@khaa.pk
 */

#include "../parser/parser.hh" 

#ifndef	CC_TOKENIZER_CSV_PARSER_H
#define	CC_TOKENIZER_CSV_PARSER_H

/*
    This is temporary replace white space with ,
 */
#ifndef GRAMMAR_END_OF_TOKEN_MARKER
#define	GRAMMAR_END_OF_TOKEN_MARKER  ' '
#endif

#ifndef GRAMMAR_END_OF_TOKEN_MARKER_SIZE
#define	GRAMMAR_END_OF_TOKEN_MARKER_SIZE    1
#endif

#ifndef GRAMMAR_START_OF_LINE_MARKER
#define	GRAMMAR_START_OF_LINE_MARKER ':'
#endif

#ifndef GRAMMAR_END_OF_LINE_MARKER    
/* On a Windows machine it is "\n\r" */
#define		GRAMMAR_END_OF_LINE_MARKER	'\n'
#endif
#ifndef GRAMMAR_END_OF_LINE_MARKER_SIZE    
#define	GRAMMAR_END_OF_LINE_MARKER_SIZE	1
#endif

#ifndef GRAMMAR_START_OF_COMMENT_MARKER
#define	GRAMMAR_START_OF_COMMENT_MARKER	'#'
#endif
#ifndef GRAMMAR_START_OF_COMMENT_MARKER_SIZE
#define	GRAMMAR_START_OF_COMMENT_MARKER_SIZE  1
#endif

// reset() method, argument values  
#define   	LINES 				0
#define		TOKENS				1

#endif