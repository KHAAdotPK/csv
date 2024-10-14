### CSV parser

A CSV parser library for C++. This library facilitates the parsing of Comma-Separated Values (CSV) files. It offers customizable delimiters and seamless integration into your C++ projects.

#### Customizing Delimiters
By default, the CSV parser uses commas (`,`) as delimiters to separate values in the CSV file. However, the delimiter is fully configurable, allowing you to modify it according to your needs. The delimiter can be of any size, thanks to the `GRAMMAR_END_OF_TOKEN_MARKER_SIZE` macro.

For example, if you prefer using a space (`' '`) or a multi-character delimiter, you can adjust both the `GRAMMAR_END_OF_TOKEN_MARKER` and `GRAMMAR_END_OF_TOKEN_MARKER_SIZE` macros to fit your specific requirements.

#### Implementation details...
```C++
/*
    The CSV parser allows for flexible customization of delimiters used to separate elements within the COMMAND macro.
    By default, commas (`,`) are utilized as delimiters. However, an alternative option using whitespace is also available.
    Should you wish to modify the delimiter or adjust its size, navigate to the respective settings in either the 'lib/csv/parser.h' file or your 'CMakeLists.txt'.

    Additionally, you have the option to undefine and redefine the delimiter after including the 'lib/argsv-cpp/lib/parser/parser.hh' file to suit your specific requirements.

    Please note the default macro definitions as specified in 'lib/csv/parser.h':
    - #define GRAMMAR_END_OF_TOKEN_MARKER ","
    - #define GRAMMAR_END_OF_TOKEN_MARKER_SIZE 1
    - #define GRAMMAR_END_OF_LINE_MARKER "\n"
    - #define GRAMMAR_END_OF_LINE_MARKER_SIZE 1

    Furthermore, the following macros are defined in 'lib/argsv-cpp/lib/parser/parser.hh':
    - #define HELP_STR_START    "("
    - #define HELP_STR_END      ")"
*/
```

#### Dependencies

It has two dependencies..

1) [https://github.com/KHAAdotPK/parser.git](https://github.com/KHAAdotPK/parser.git)
2) [https://github.com/KHAAdotPK/string.git](https://github.com/KHAAdotPK/string.git)

Make sure to install these dependencies before using the CSV parser library.

#### Customizing Delimiters
The CSV parser allows customization of delimiters used for separating elements. By default, it uses commas (,), but you can modify it according to your requirements.
```C++
// Customizing Delimiters
#undef GRAMMAR_END_OF_TOKEN_MARKER
#undef GRAMMAR_END_OF_LINE_MARKER

#define GRAMMAR_END_OF_TOKEN_MARKER ' ' // Custom token delimiter
#define GRAMMAR_END_OF_LINE_MARKER '\n' // Custom line delimiter

#include "lib/csv/parser.hh"
```
#### Integration with CMakeLists.txt and MSBuild
```c++
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

#### Usage...
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

#### Controlling Parser Behavior with File Formatting
There is currently a known bug in the CSV parser where, if the input file does not have an empty line at the end, the parser may mistakenly read and process an additional line. This issue can be avoided by ensuring that the CSV file is properly formatted.

To avoid encountering this issue, follow these guidelines:

- Ensure that the last line of the CSV file is **empty**.
- The cursor should be positioned at the very **start of the empty line**.

This file formatting is a temporary workaround to avoid this issue.

### License
This project is governed by a license, the details of which can be located in the accompanying file named 'LICENSE.' Please refer to this file for comprehensive information.

