A CSV parser library. It has two dependencies..

1) github.com/KHAAdotPK/parser.git
2) github.com/KHAAdotPK/string.git

# Usage...
```C++
cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> parser(text);
// Iterate through each line of the CSV data
for (cc_tokenizer::string_character_traits<char>::size_type l = 1; l < parser.get_total_number_of_lines(); l++)
{
    /*
        Traverse each line   
     */
    parser.get_line_by_number(l);

    // Iterate through each token on the current line
    for (cc_tokenizer::string_character_traits<char>::size_type t = 1; t <= parser.get_total_number_of_tokens(); t++)
    {
        /*
            Traverse each token
         */
        cc_tokenizer::String<char> theToken = parser.get_token_by_number(t);

        /*
            This format of while loop is used here so that we still remain on the current line
         */
        do {
            /*
                While being on the current line, move to the next token 
                and then from there move to each next token on the current line   
             */
            while (parser.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())
            {
                cc_tokenizer::String<char> token = parser.get_current_token();

                // Process the current token

                if (!theToken.compare(token))
                {
                    std::cout<< theToken.c_str() << " -- " << token.c_str() << std::endl;
                }
            }

        } while (parser.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof());
                
        // Reset parser to process next line's tokens
        parser.reset(TOKENS);

        // Retrieve the current line again for the next iteration
        parser.get_line_by_number(l);
    }            
}
```

# Notes:- Related to compilation...
```c++
/*
    Note: The delimiter used to separate the elements in the COMMAND macro can be customized.
    The first definition uses commas (,) as delimiters, while the second definition uses whitespace. 
    If you wish to change the delimiter or adjust its size, you can modify the corresponding settings in the file...
    lib/csv/parser.h or in your CMakeLists.txt.
    Alternatively, you can undefine and redefine the delimiter after including the lib/argsv-cpp/lib/parser/parser.hh 
    file according to your specific requirements.

    Please note that the macros mentioned below are by default or originally defined in the file lib/csv/parser.h
    #define GRAMMAR_END_OF_TOKEN_MARKER ","
    #define GRAMMAR_END_OF_TOKEN_MARKER_SIZE 1
    #define GRAMMAR_END_OF_LINE_MARKER "\n"
    #define GRAMMAR_END_OF_LINE_MARKER_SIZE 1

    The following two macros are defined in file  lib\argsv-cpp\lib\parser\parser.hh
    #define HELP_STR_START    "("
    #define HELP_STR_END      ")"
 */
/*
    To change the default parsing behaviour of the CSV parser using CMakeLists.txt and msbuild project file
        
    Snippet from CMakeLists.txt file
    # Add a definition for the GRAMMAR_END_OF_TOKEN_MARKER macro
    #add_definitions(-DGRAMMAR_END_OF_TOKEN_MARKER=" ")
    #add_definitions(-DGRAMMAR_END_OF_TOKEN_MARKER_SIZE=1)

    Snippet from CMakeLists.txt file
    # Add a definition for the GRAMMAR_END_OF_TOKEN_MARKER macro for the replika target
    #target_compile_definitions(replika PRIVATE GRAMMAR_END_OF_TOKEN_MARKER=" ")
    #target_compile_definitions(replika PRIVATE GRAMMAR_END_OF_TOKEN_MARKER_SIZE=1)

    Snippet from MSBuild project file
    <ItemDefinitionGroup>
        <ClCompile>
            <PreprocessorDefinitions Condition="'$(CSVPreprocessorDefinitions)'=='yes'">GRAMMAR_END_OF_TOKEN_MARKER=" ";GRAMMAR_END_OF_TOKEN_MARKER_SIZE=1</PreprocessorDefinitions>
        </ClCompile>                
    </ItemDefinitionGroup>
 */
```

### License
This project is governed by a license, the details of which can be located in the accompanying file named 'LICENSE.' Please refer to this file for comprehensive information.


