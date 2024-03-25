/* src/parser.hh
   Written by, Q@khaa.pk */

#include "../parser/parser.hh" 
#include "parser.h"

#ifndef		CC_TOKENIZER_CSV_PARSER_HH
#define		CC_TOKENIZER_CSV_PARSER_HH

namespace cc_tokenizer 
{
template<class T, typename E>
class csv_parser;

template<>
class csv_parser<cc_tokenizer::String<char>, char> : public cc_tokenizer::parser<cc_tokenizer::String<char>, char>
{
   String<char> str;

   /**
		Both of these properties are used together and they are used to provide custom token delimeters.
		It is optional to set these properties and if they are not set(meaning when geotms ia zero) then the values of macros GRAMMAR_END_OF_LINE_MARKER and GRAMMAR_END_OF_LINE_MARKER_SIZE are used.
		Read about these two above mentioned macros in README.md file. 
     **/
   /**
		These properties are used together to customize token delimiters.
   		If not set (when geotms is zero), the values of macros GRAMMAR_END_OF_LINE_MARKER and GRAMMAR_END_OF_LINE_MARKER_SIZE are used.
     **/      	
   /* GRAMMAR_END_OF_TOKEN_MARKER (Custom end of token marker) */
   String<char> geotm;
   /* GRAMMAR_END_OF_TOKEN_MARKER_SIZE (Size of the custom end of token marker) */
   String<char>::size_type geotms;

   // Line related
   typename cc_tokenizer::string_character_traits<char>::int_type current_line_number;
   typename cc_tokenizer::string_character_traits<char>::int_type total_number_of_lines;
   typename cc_tokenizer::String<char>::size_type current_line_offset;
   typename cc_tokenizer::String<char>::size_type current_line_size;

   // Token related
   typename cc_tokenizer::string_character_traits<char>::int_type current_token_number;
   typename cc_tokenizer::string_character_traits<char>::int_type total_number_of_tokens;
   typename cc_tokenizer::string_character_traits<char>::size_type current_token_offset;
   typename cc_tokenizer::string_character_traits<char>::size_type current_token_size;
   
   public:
   
      csv_parser() : str(), geotm(), geotms(0)
	  {
          // Line related
          current_line_number = cc_tokenizer::string_character_traits<char>::int_type(0);
          current_line_offset = cc_tokenizer::String<char>::size_type(0);
          current_line_size = cc_tokenizer::String<char>::size_type(0);
          total_number_of_lines = cc_tokenizer::string_character_traits<char>::int_type(0);

	 	  // Token related
	 	  current_token_number = cc_tokenizer::string_character_traits<char>::int_type(0);
	 	  total_number_of_tokens = cc_tokenizer::string_character_traits<char>::int_type(0);
	 	  current_token_offset = cc_tokenizer::String<char>::size_type(0);
	 	  current_token_size = cc_tokenizer::String<char>::size_type(0);
      }
      
      csv_parser(String<char>& ref) : str(ref), geotm(), geotms(0)
	  {
          // Line related
          current_line_number = cc_tokenizer::string_character_traits<char>::int_type(0);
          current_line_offset = cc_tokenizer::String<char>::size_type(0);
          current_line_size = cc_tokenizer::String<char>::size_type(0);
	 	  total_number_of_lines = cc_tokenizer::string_character_traits<char>::int_type(0);
          get_total_number_of_lines();	  

	 	  // Token related
	 	  current_token_number = cc_tokenizer::string_character_traits<char>::int_type(0);
	 	  current_token_offset = cc_tokenizer::String<char>::size_type(0);
          current_token_size = cc_tokenizer::String<char>::size_type(0);
	 	  total_number_of_tokens = cc_tokenizer::string_character_traits<char>::int_type(0);
	 	  get_total_number_of_tokens();
      }

	  // geotm  GRAMMAR_END_OF_TOKEN_MARKER
	  // geotms GRAMMAR_END_OF_TOKEN_MARKER_SIZE
	  csv_parser(String<char>& ref, String<char> geotm, String<char>::size_type geotms = 0) : str(ref), geotm(geotm), geotms(geotms)
	  {
		  //std::cout<<"--> "<<str.c_str()<<" -- "<<geotms<<std::endl;

		  // Line related
          current_line_number = cc_tokenizer::string_character_traits<char>::int_type(0);
          current_line_offset = cc_tokenizer::String<char>::size_type(0);
          current_line_size = cc_tokenizer::String<char>::size_type(0);
	 	  total_number_of_lines = cc_tokenizer::string_character_traits<char>::int_type(0);
          get_total_number_of_lines();

	 	  // Token related
	 	  current_token_number = cc_tokenizer::string_character_traits<char>::int_type(0);
	 	  current_token_offset = cc_tokenizer::String<char>::size_type(0);
          current_token_size = cc_tokenizer::String<char>::size_type(0);
	 	  total_number_of_tokens = cc_tokenizer::string_character_traits<char>::int_type(0);
	 	  get_total_number_of_tokens();
	  }
	  
	  csv_parser(const char *ptr) : str(ptr), geotm(), geotms(0)
	  {
		  // Line related
          current_line_number = cc_tokenizer::string_character_traits<char>::int_type(0);
          current_line_offset = cc_tokenizer::String<char>::size_type(0);
          current_line_size = cc_tokenizer::String<char>::size_type(0);
	 	  total_number_of_lines = cc_tokenizer::string_character_traits<char>::int_type(0);
          get_total_number_of_lines();

	 	  // Token related
	 	  current_token_number = cc_tokenizer::string_character_traits<char>::int_type(0);
	 	  current_token_offset = cc_tokenizer::String<char>::size_type(0);
          current_token_size = cc_tokenizer::String<char>::size_type(0);
	 	  total_number_of_tokens = cc_tokenizer::string_character_traits<char>::int_type(0);
	 	  get_total_number_of_tokens();
	  }
	        
      cc_tokenizer::String<char> get_current_line(void) 
      {
		  cc_tokenizer::String<char> line = cc_tokenizer::String<char>(str.data() + current_line_offset, current_line_size);

		  typename cc_tokenizer::String<char>::size_type pos_begin = line.find(GRAMMAR_END_OF_LINE_MARKER, 0);	
          /* 
	      TODO, put the correct size of GRAMMREND_OF_LINE_MARKER here instead of 1 
	   	  */ 
          //return cc_tokenizer::String<char>(str.data() + current_line_offset, current_line_size - 1);

//#ifdef	_WIN32
//		  return cc_tokenizer::String<char>(str.data() + current_line_offset, current_line_size - 1);
//#else
		  //return cc_tokenizer::String<char>(str.data() + current_line_offset, current_line_size - GRAMMAR_END_OF_LINE_MARKER_SIZE); 			  
//#endif
		  if (pos_begin != cc_tokenizer::String<char>::npos)
		  {
			  return cc_tokenizer::String<char>(str.data() + current_line_offset, current_line_size - GRAMMAR_END_OF_LINE_MARKER_SIZE); 
		  }
		  else
		  {
			  return cc_tokenizer::String<char>(str.data() + current_line_offset, current_line_size); 
		  }
		  									  
      }

      cc_tokenizer::string_character_traits<char>::int_type remove_line_by_number(cc_tokenizer::string_character_traits<char>::int_type n)
      {
          cc_tokenizer::string_character_traits<char>::int_type ret = n;
   
          if (n && !(n > get_total_number_of_lines())) 
	  	  {
	      	  cc_tokenizer::String<char> line = get_line_by_number(n);
	      	  if (line.size())
	      	  {
		  		  //std::cout<<str.erase(current_line_offset, line.size() + cc_tokenizer::String<char>(GRAMMAREND_OF_LINE_MARKER).size()).c_str();
		  		  cc_tokenizer::String<char> foo = str.erase(current_line_offset, line.size() + cc_tokenizer::String<char>(GRAMMAR_END_OF_LINE_MARKER).size());

		  		  //std::cout<<foo.c_str();

		  		  reset(LINES);
		  		  get_total_number_of_lines();

		  		  //std::cout<<"--> "<<get_line_by_number(4).c_str()<<std::endl;
	      	  }
	      	  else
	      	  {
	          	  ret = 0;
	      	  }
	  	   }
           
           return ret;
      }

	  cc_tokenizer::string_character_traits<char>::int_type get_current_line_number(void)
	  {
		  return current_line_number;
	  }

	  /*
	  	TODO(or not to do)
		If line number is not as same as the current line number then all the line related variables are reassigned values corresponding to the line at that specific line number
		This is not good if you are in a loop(using go_to_next_line method), don't call this method in the loop to traverse all lines one at a time
		So "what to do" here, it can be that provide way that while in a loop and after calling this method the loop gain back its state and go on looping 
	   */	
      cc_tokenizer::String<char> get_line_by_number(cc_tokenizer::string_character_traits<char>::int_type n)
      {
          cc_tokenizer::String<char> ret;
	   	  
          if (total_number_of_lines && n && n <= total_number_of_lines)
	  	  {		
	      	  if (n == current_line_number)
	      	  {
	        	  ret = get_current_line();
	      	  }
	      	  else
	      	  {
	          	  cc_tokenizer::string_character_traits<char>::int_type i = cc_tokenizer::string_character_traits<char>::int_type(0);

	          	  reset(LINES);
										
		  		  while (go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())
		  		  {
                      i = i + cc_tokenizer::string_character_traits<char>::int_type(1); 
		      		  if (i == n) 
		      		  {
		          		  ret = get_current_line();
			  			  break;
		      		  }
		  		  }
	      	  }
	  	  }

	  	  return ret;
      }
      
      cc_tokenizer::String<char> get_line_by_number_old(cc_tokenizer::string_character_traits<char>::int_type n) {

          cc_tokenizer::String<char> ret;
      
         if ( n > 0 && n != current_line_number && n <= total_number_of_lines ) {
         
            cc_tokenizer::string_character_traits<char>::int_type cln = current_line_number;
	    	cc_tokenizer::String<char>::size_type clo = current_line_offset;
	    	cc_tokenizer::String<char>::size_type cls = current_line_size;
            
            if ( n < current_line_number ) {
            
                current_line_number = cc_tokenizer::string_character_traits<char>::int_type(0);
                current_line_offset = cc_tokenizer::String<char>::size_type(0);
                current_line_size = cc_tokenizer::String<char>::size_type(0);               
            }
            
            while ( current_line_number != n ) {
            
               go_to_next_line();
	       current_line_number = current_line_number + 1;
            }              
         /*}*/

	 /*
	     TODO, replace that odd looking 1 with the size of GRAMMAREND_OF_LINE_MARKER
	  */
             //ret = cc_tokenizer::String<char>(str.data() + current_line_offset, current_line_size - 1);

	     ret = get_current_line();

	     //current_line_number = cln;
	     //current_line_offset = clo;
	     //current_line_size = cls;
         }	 

	 return ret;
      }
      
      cc_tokenizer::string_character_traits<char>::int_type get_total_number_of_lines(void) 
      {
          if (str.size())
		  {
		 	  cc_tokenizer::string_character_traits<char>::int_type cln = current_line_number;
			  cc_tokenizer::String<char>::size_type clo = current_line_offset;
			  cc_tokenizer::String<char>::size_type cls = current_line_size;

			  /* Never call method get_total_number_of_lines() from the following method */	
			  //reset(LINES);
			  current_line_number = 0;
			  current_line_offset = 0;
			  current_line_size = 0;

			  total_number_of_lines = 0;
	    		
              while (go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())			  
			  {				  
				  total_number_of_lines = total_number_of_lines + cc_tokenizer::string_character_traits<char>::int_type(1);				  
              }
            
              current_line_number = cln;
              current_line_offset = clo;
              current_line_size = cls;
          }
         
          return total_number_of_lines;
      }

      cc_tokenizer::string_character_traits<char>::int_type go_to_next_line(void) 
      {
    	  cc_tokenizer::string_character_traits<char>::int_type ret = cc_tokenizer::string_character_traits<char>::eof();

	 	  typename cc_tokenizer::String<char>::size_type pos_begin = str.find(GRAMMAR_END_OF_LINE_MARKER, current_line_offset + current_line_size);

		  // End of line marker found		
	 	  if (pos_begin != cc_tokenizer::String<char>::npos) 
	 	  {
	    	  current_line_offset = current_line_offset + current_line_size;

			  //#ifdef _WIN32
	    	  //current_line_size = (pos_begin - current_line_offset) + 1; // \n\r
			  //#else
			  current_line_size = (pos_begin - current_line_offset) + GRAMMAR_END_OF_LINE_MARKER_SIZE; // \n	
			  //#endif
			  
			  /* 
		  	 	Line size atleast equals to the size of GRAMMAR_END_OF_LINE_MARKER_SIZE, token atleast has the GRAMMAR_END_OF_LINE_MARKER
		     	End result is that before using the token, check its size aka get_current_line().size()
		   	   */	
			  if (current_line_size > GRAMMAR_END_OF_LINE_MARKER_SIZE)
			  {						  
	    	  	  current_line_number = current_line_number + 1;
			  }
			  
	    	  reset(TOKENS);

			  get_total_number_of_tokens();
			  			  
	    	  ret = ~ret;
	 	  }
		  // End of line marker was not found 		  
		  else
		  {	
			  if ((str.size() - (current_line_offset + current_line_size)) > 0)
			  {	
				  current_line_offset = current_line_offset + current_line_size;
				  current_line_size = str.size() - current_line_offset;
				  current_line_number = current_line_number + 1;
				  
				  reset(TOKENS);

				  get_total_number_of_tokens();

			  	  ret = ~ret;
		      }  
		  }
		  
		  
	 	  return ret;
      }

      cc_tokenizer::string_character_traits<char>::int_type go_to_next_line_old(void) {
      
         cc_tokenizer::string_character_traits<char>::int_type ret = cc_tokenizer::string_character_traits<char>::eof();
         
         typename cc_tokenizer::String<char>::size_type pos_begin = str.find(GRAMMAR_START_OF_LINE_MARKER, current_line_offset + current_line_size);
         
         if ( pos_begin != cc_tokenizer::String<char>::npos ) {
         
            typename cc_tokenizer::String<char>::size_type i = pos_begin;
            
            while ( i && cc_tokenizer::string_character_traits<char>::ne(str[i], '\n') ) {
            
               i = i - cc_tokenizer::String<char>::size_type(1);
            }
            
            if ( i ) {
            
               i = i + cc_tokenizer::String<char>::size_type(1);
            }
            
            current_line_offset = i;
            
            typename cc_tokenizer::String<char>::size_type pos_end = str.find(GRAMMAR_END_OF_LINE_MARKER, pos_begin + cc_tokenizer::String<char>::size_type(1));
            
            if ( pos_end != cc_tokenizer::String<char>::npos ) {
            
               typename cc_tokenizer::String<char>::size_type j = pos_end - cc_tokenizer::String<char>::size_type(1);
               
               while ( j && str[j] != '\n' ) {
               
                  j = j - cc_tokenizer::String<char>::size_type(1);
               }
               
               current_line_size = j - i;
            } 
            else {
            
               typename cc_tokenizer::String<char>::size_type j = str.size() - cc_tokenizer::String<char>::size_type(1);
               
               while ( j && str[j] != '\n' ) {
               
                  j = j - cc_tokenizer::String<char>::size_type(1);
               }    
                 
               current_line_size = j - current_line_offset;
            }
            
            /* We found a new line, remove the comment part of this line(if it has that part too) */    
            cc_tokenizer::String<char>::size_type cmt_byte_offset = cc_tokenizer::String<char>(str.data() + current_line_offset, current_line_size).find(GRAMMAR_START_OF_COMMENT);
          
            if ( cmt_byte_offset != cc_tokenizer::String<char>::npos ) {
           
               current_line_size = cmt_byte_offset; 
            }
            /* Finished dealing with the comment part of this line */

            /* TODO, */            
            /* Now remove all the new line characters */
            /* Finished dealing with the new line characters */
           
            /* TODO, */ 
            /* Now remove all the consecutive white spaces at the end of the line */            
            /* Finished dealing with all the extra white spaces at the end of the line */
           
            current_line_number = current_line_number + cc_tokenizer::string_character_traits<char>::int_type(1);
            ret = ~ret;              
         }         
         
         return ret;
      }

      cc_tokenizer::string_character_traits<char>::int_type go_to_next_token(void)
      {
          cc_tokenizer::string_character_traits<char>::int_type ret = cc_tokenizer::string_character_traits<char>::eof();

		  // Find the end of token marker, the GRAMMAR_END_OF_TOKEN_MARKER	
	  	  typename cc_tokenizer::String<char>::size_type pos = 0;

		  if (geotm.size()) 
		  {
			  //std::cout<<get_current_line().c_str()<<std::endl;
			  pos = get_current_line().find(geotm, current_token_offset + current_token_size);
		  }
		  else 
		  {		
			  pos = get_current_line().find(GRAMMAR_END_OF_TOKEN_MARKER, current_token_offset + current_token_size);
		  }

		  	
          // Because the last token does'nt have the GRAMMAR_END_OF_TOKEN_MARKER
          if (pos == cc_tokenizer::String<char>::npos)
	  	  {
	      	  pos = get_current_line().size();	
				
	      	  /*if (pos)
	      	  {
	          	  current_token_number = current_token_number + 1;
	      	  }*/
	  	  }
	  	  /*else 
	  	  {
	      	  current_token_number = current_token_number + 1;
	  	  }*/
		  //else if ()
		  //std::cout<<get_current_line().data() + current_token_offset + current_token_size<<std::endl;

	  	  current_token_offset = current_token_offset + current_token_size;
		  if (geotm.size())
		  {
			  current_token_size = pos - current_token_offset + geotm.size();
			  //cc_tokenizer::String<char> obj(get_current_line().data() + current_token_offset + current_token_size, current_token_size);
		  }	
		  else
		  {				  		  	
	  	  	   current_token_size = pos - current_token_offset + GRAMMAR_END_OF_TOKEN_MARKER_SIZE;
		  }

		  /*
		  	//////////////////////////////////////////////////////////////////////
			// NOTE:- USE THIS COMMENTED CODE BLOCK TO DEBUG INDIVIDUAL TOKENS //
			/////////////////////////////////////////////////////////////////////
		  cc_tokenizer::String<char> obj(get_current_line().data() + current_token_offset + current_token_size, current_token_size);
		  std::cout<<obj.c_str()<<std::endl;
		   */

		  /* 
		  	 Token size atleast equals to the size of GRAMMAR_END_OF_TOKEN_MARKER_SIZE, token atleast has the GRAMMAR_END_OF_TOKEN_MARKER
		     End result is that before using the token, check its size aka get_current_token().size()
		   */ 			 
		  if (current_token_size)
		  {	
#ifdef CSV_NOT_ALLOW_EMPTY_TOKENS			  
			  // Only want to count legit tokens, tokens which not include the END_OF_TOKEN_MARKER(they are implied to be an empty tokens)
			  // The idea is to use the methods like get_line_by_number(), get_token_by_number() etc and the caller will provide the number of line/token to retrieve but even before that caller has to know how many legit token/lines are there, for all this the counter gets incremented only for legit tokens
			  // If caller is going through all the tokens/lines one by one as in the case of methods go_to_next_token and go_to_next_line and then retrieve them subsequently by calling get_current_line() or get_current_token() then it can be better for the caller to call the size() method on them before using them			  			  			  			  			  							  			  
			  if ((geotm.size() && (geotm.size() < current_token_size)) || (!geotm.size() && (current_token_size > GRAMMAR_END_OF_TOKEN_MARKER_SIZE)))
			  {				  
#endif				  
			  	  current_token_number = current_token_number + 1;
#ifdef	CSV_NOT_ALLOW_EMPTY_TOKENS					
			  }		
#endif			  
			  ret = ~ret;
		  }

		  //std::cout<<get_current_token().c_str()<<std::endl;	
		  			  		  	  		  	
		  return ret;		
      }

	  // Token returned can be an empty token 
	  // Use get_current_token().size() to find out if the token is empty  	
      cc_tokenizer::String<char> get_current_token(void) 
      {
		  if (!geotm.size())
		  {
		  // Returned token does not include the GRAMMR_END_OF_TOKEN_MARKER
          	  return cc_tokenizer::String<char>(get_current_line().data() + current_token_offset, current_token_size - GRAMMAR_END_OF_TOKEN_MARKER_SIZE);
		  }
		  else
		  {
			  return cc_tokenizer::String<char>(get_current_line().data() + current_token_offset, current_token_size - geotm.size());
		  }
		  
      }

      cc_tokenizer::string_character_traits<char>::int_type get_total_number_of_tokens(void)
      {
          if (get_current_line().size())
	  	  {
	      	  cc_tokenizer::string_character_traits<char>::int_type ctn = current_token_number;
	      	  cc_tokenizer::string_character_traits<char>::size_type cto = current_token_offset;
	      	  cc_tokenizer::string_character_traits<char>::size_type cts = current_token_size;

          	  reset(TOKENS);
             
	      	  while (1)
	      	  {
	          	  cc_tokenizer::string_character_traits<char>::int_type ret = go_to_next_token();

				  // Method get_current_token() emmits a token without the GRAMMAR_END_OF_TOKEN_MARKER
				  // So total_number_of_tokens does not include those tokens which only have the GRAMMAR_END_OF_TOKEN_MARKER and nothing else 	
                  if (get_current_token().size())
		  		  {
		      		  total_number_of_tokens = total_number_of_tokens + 1;
		  		  }

		  		  if (ret == cc_tokenizer::string_character_traits<char>::eof())
		  		  {
		      		  break;
		  		  }
	      	  }

	      	  current_token_number = ctn;
	      	  current_token_offset = cto;
	      	  current_token_size = cts;
	  	  }

	  	  return total_number_of_tokens; 
      }
      
	  // This mathod should take into account the case of tokens only having the GRAMMR_END_OF_TOKEN_MARKER, these are empty tokens 
	  // The number returned by the method get_total_number_of_tokens() only returned the total number of those tokens which are non-empty      
	  // TODO, while implementing take into account above considerations
      cc_tokenizer::String<char> get_token_by_number(cc_tokenizer::string_character_traits<char>::int_type n)
      {
          cc_tokenizer::String<char> ret;

		  //std::cout<<"SONI -> get_token_by_number() total_number_of_tokens = "<<total_number_of_tokens<<std::endl;

	  	  if (current_line_number && total_number_of_tokens && n && n <= total_number_of_tokens)	   
	  	  {
			  //std::cout<<"SONI -> get_token_by_number() "<<std::endl;		
	      	  if (current_token_number == n)
	      	  {
	          	  ret = get_current_token();
	      	  }
              else
	      	  {
	          	  cc_tokenizer::string_character_traits<char>::int_type i = cc_tokenizer::string_character_traits<char>::int_type(0);

		  		  reset(TOKENS);
		  		  get_total_number_of_tokens();

		  		  while (1)
		  		  {
		      		  cc_tokenizer::string_character_traits<char>::int_type j = go_to_next_token();

		      		  if (get_current_token().size())
		      		  {
		          		  i = i + cc_tokenizer::string_character_traits<char>::int_type(1);
			  			  if (i == n)
			  			  {
			      			  ret = get_current_token();
			      			  break;
			  			  }
		      		  }
                      
		      		  if (j == cc_tokenizer::string_character_traits<char>::eof())
		      		  {
		          		  break;
		      		  }
		  		  }
	      	  }
	      }

	  	  return ret;
      }

	  cc_tokenizer::string_character_traits<char>::int_type get_current_token_number(void)
	  {
		  return current_token_number;
	  }

// n should originate at 1
      cc_tokenizer::String<char> get_token_by_number_old(cc_tokenizer::string_character_traits<char>::int_type n)
      {
          if (get_current_line().size() && n && (current_token_number != n) && (total_number_of_tokens >= n))
	  {
	      typename cc_tokenizer::string_character_traits<char>::int_type ctn = current_token_number;
	      typename cc_tokenizer::string_character_traits<char>::int_type tnt = total_number_of_tokens;
	      typename cc_tokenizer::string_character_traits<char>::size_type cto = current_token_offset;
	      typename cc_tokenizer::string_character_traits<char>::size_type cts = current_token_size;

	      typename cc_tokenizer::string_character_traits<char>::int_type i = cc_tokenizer::string_character_traits<char>::int_type(0);

	      // TODO, n is either less or greater than current_token_number
	      reset(TOKENS);

	      while (1)
	      {
	          cc_tokenizer::string_character_traits<char>::int_type ret = go_to_next_token();

		  if (get_current_token().size())
		  {
		      i = i + cc_tokenizer::string_character_traits<char>::int_type(1);
		  }

		  if (ret == cc_tokenizer::string_character_traits<char>::eof() || i == n)
		  {
		      break;
		  }
	      }

	      cc_tokenizer::String<char> token = get_current_token();

	      current_token_number = ctn;
	      total_number_of_tokens = tnt;
	      current_token_offset = cto;
		  current_token_size = cts;

	      return token;
	  }

          return get_current_token();
      }

	  /*
   		This method resets certain attributes of the tokenizer object based on the provided parameter.
   
   		Parameters:
       	what - Specifies what aspect of the tokenizer object to reset. Can be either LINES or TOKENS.
             - LINES: Resets attributes related to lines such as current_line_offset, current_line_size,
                       current_line_number, and total_number_of_lines.
             - TOKENS: Resets attributes related to tokens such as current_token_offset, current_token_size,
                        current_token_number, and total_number_of_tokens.
   
   		Note: 
			When resetting LINES, total_number_of_lines is recalculated by calling get_total_number_of_lines().
       		Avoid calling this method from within get_total_number_of_lines() to prevent potential issues.
		*/
      void reset(const int what)
      {
          switch(what)
	  	  {
	      	  case LINES:
	          	  current_line_offset = cc_tokenizer::string_character_traits<char>::size_type(0);
		  		  current_line_size = cc_tokenizer::string_character_traits<char>::size_type(0);
		  		  current_line_number = cc_tokenizer::string_character_traits<char>::int_type(0);
			      /*
				     Remeber to never ever call this method from the get_total_number_of_lines method	     		
			       */				 		
		  		  total_number_of_lines = get_total_number_of_lines(); /*cc_tokenizer::string_character_traits<char>::int_type(0)*/;				   		
	      	  break;
	      	  case TOKENS:
	          	  current_token_offset = cc_tokenizer::string_character_traits<char>::size_type(0);
		  		  current_token_size = cc_tokenizer::string_character_traits<char>::size_type(0);
		  		  current_token_number = cc_tokenizer::string_character_traits<char>::int_type(0);
		  		  total_number_of_tokens = cc_tokenizer::string_character_traits<char>::int_type(0);
	      	  break;
	  	  }
      }	  
};
};
#endif  
