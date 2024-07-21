// Header files included
#include "Console_IO_Utility.h"

// Function Implementations

/*
Name: clearLeadingCharacters
Process: Clears all leading non-printable characters from the console stream
Function input/parameters: allow space return (Boolean)
Function output/parameters: none
Function output/returned: first printable character as integer
Device input/keyboard: none
Device output/monitor: none
Dependencies: getchar
*/
int clearLeadingCharacters( bool allowSpaceReturn )
   {
    // initialize data, set input character to getChar, set count to zero
       // function: getchar
    int intChar = getchar();
    int charCount = 0;

    // loop while non-printable characters and space if not set
    // also limits looping to constant limit
    while( ( intChar < (int)SPACE
                     || ( !allowSpaceReturn && intChar == SPACE ) )
                                                     && charCount < MAX_STR_LEN )
       {
        // update character count
        charCount++;

        // get new input character
           // function: getchar
        intChar = getchar();
       }

     // return captured character
     return intChar;
    }

/*

Name: getChar
Process: returns next character in stream,
         ignores all white space (including SPACE)  prior to character
Function input/parameters: flag to accept space (Boolean)
Function output/parameters: none
Function output/returned: one character (char) is returned to calling method
Device input/keyboard: places one or more characters in stream
Device output/monitor: none
Dependencies: getCharFiltered
*/
char getChar()
   {
    // initialize variables, set space accept flag to false
    bool dontAcceptSpace = false;

    // call filtered function with space accept flag
       // function: getCharFiltered
    return getCharFiltered( dontAcceptSpace );
   }

/*
Name: getCharFiltered
Process: returns next character in stream,
         ignores non printable characters prior to input character
         but may accept space depending on flag
Function input/parameters: flag to accept space (boolean)
Function output/parameters: none
Function output/returned: first printable character or space (if configured)
                          returned (char)
Device input/keyboard: places one or more characters in stream
Device output/monitor: none
Dependencies: getchar(), clearLeadingCharacters
*/
char getCharFiltered( bool acceptSpace )
   {
    //Initialize variables
    int inCharInt;

    // clear leading characters, capture first usable character
       // function: clearLeadingCharacters
    inCharInt = clearLeadingCharacters( acceptSpace );

    // check for input character set to end of file
    if( inCharInt == EOF )
       {
        // return character zero
        return '0';
       }

    // return input character as character
    return (char)inCharInt;
   }

/*
Name: getInputString
Process: acquires input string from keyboard, if clear white space flag set,
         ignores all white space, including space character
Function input/parameters: clear white space control (Boolean)
Function output/parameters: character array (char[])
Function output/returned: none
Device input/keyboard: user entry of a character stream
Device output/monitor: none
Dependencies: getchar(), clearLeadingCharacters
*/
void getInputString( char inputArr[], bool clearWhiteSpace )
   {
    //Initialize Variables, set character count and index to zero
    int charCount = 0;
    int index = 0;
    int intChar;

    // check for clear white space flag
    if( clearWhiteSpace )
       {
        // clear leading characters, set flag to ignore space
           // function: clearLeadingCharacters
        intChar = clearLeadingCharacters( !clearWhiteSpace );
       }

    // otherwise, assume white space flag not set
    else
       {
        // get first character
           // function: getchar
        intChar = getChar();
       }

    // loop until enter key found, limit loop to constant
    while( intChar != (int)NEWLINE_CHAR && charCount < MAX_STR_LEN )
       {
        // set current value to array element
        inputArr[ index ] = (char)intChar;

        // increment string array index
        index++;

        // add null character to end of string array
        inputArr[ index ] = NULL_CHAR;

        // increment character count
        charCount++;

        // get next character
           // function: getchar
        intChar = getchar();
      }
   }

/*
Name: printCharacter
Process: prints a single character
Function input/parameters: character to be printed (char)
Function output/parameters: None
Function output/returned: None
Device input/keyboard: None
Device output/monitor: character printed as specified
Dependencies: printCharacters
*/
void printCharacter( char outputChar )
   {
    // initialize number of characters to one
    int numberOfChars = 1;

    // print one character
       // function: printChars
    printCharacters( numberOfChars, outputChar );
   }

/*
Name: printCharacters
Process: prints given number of characters
Function input/parameters: number of characters (int),
                           character to be printed (char)
Function output/parameters: None
Function output/returned: None
Device input/keyboard: None
Device output/monitor: Number of specified characters printed
Dependencies: printf
*/
void printCharacters( int numChars, char outputChar )
   {
    // check for reminaing characters to print
    if( numChars > 0 )
       {
        // print one character
           // function: printf
        printf( "%c", outputChar );

        // (recursive) print remaining characters
           // function: printChars
        printCharacters( numChars - 1, outputChar );
       }
   }

/*
Name: printDouble
Process: simple print double function
Function input/parameters:
        outVal - the double value to be output (double)
        precision - the number of digits to the right of the decimal point (int)
Function output/parameters: none
Function output/returned: none
Device input: none
Device output/monitor: one double value displayed
Dependencies: printDoubleJustified
*/
void printDouble( double outVal, int precision )
   {
    // initialize variables, set block size to zero and justified to "LEFT"
    int blockSize = 0;
    char justified[] = "LEFT";

    // call justified function with specified parameters
       // function: printDoubleJustified
    printDoubleJustified( outVal, precision, blockSize, justified );
   }

/*
Name: printDoubleJustified
Process: the precision is set for the double value, then the pre-spaces
         and post-spaces are calculated for the requested justification,
         and then the pre-spaces are printed, the double value is printed,
         and then the post-spaces are printed
Function input/parameters:
 		  outVal - the double value to be output (double)
      blockSize - the width of the block within which
                  to print the integer value (int)
      justify - "LEFT," "RIGHT," or "CENTER" justification in block (c-string)
Function output/parameters: none
Function output/returned: none
Device input: none
Device output/monitor: one double value displayed, justified, with precision
Dependencies: formatDouble, printStringJustified
*/
void printDoubleJustified( double outVal, int precision,
                                            int blockSize, const char* justify )
   {
    // initialize variables, create temp string for configuration string
    char specStr[ MIN_STR_LEN ];

    // initialize variables, create temporary output string
    char outStr[ MIN_STR_LEN ];

    // set configuration string with precision value
       // function: sprintf
    sprintf( specStr, "%s0.%dlf", "%", precision );

    // set output string
       // function: sprintf
    sprintf( outStr, specStr, outVal );

    // print string justified
       // function: printStringJustified
    printStringJustified( outStr, blockSize, justify );
   }

/*
Name: printEndline
Process: prints single endline character to end a line or create vertical space
Function input/parameters: none
Function output/parameters: none
Function output/returned: none
Device input: none
Device output/monitor: one endline character output
Dependencies: printf
*/
void printEndline()
   {
    // print one newline character
       // function: printf
    printf( "\n" );
   }

/*
Name: printEndlines
Process: prints the specified number of endline characters
         to end a line and/or create vertical space(s)
Function input/parameters: number of endlines (int)
Function output/parameters: none
Function output/returned: none
Device input: none
Device output/monitor: endline characters output as specified
Dependencies: printEndline
*/
void printEndlines( int numEndlines )
   {
    // check for number of end lines remaining
    if( numEndlines > 0 )
       {
        // print one endling
           // function: printEndline
        printEndline();

        // (recursive) print remaining end lines
        printEndlines( numEndlines - 1 );
       }
   }

/*
 Name: printInteger
 Process: prints integer value
Function input/parameters: outVal - the integer value to be output
 Output: None
 Device Input: None
 Device Output: Integer is displayed as specified
 Dependencies: printIntegerJustified
 */
void printInteger( int outVal )
   {
    // initialize variables, set block size to zero, justifification to "LEFT"
    int blockSize = 0;
    char justified[] = "LEFT";

    // print justified integer with specified parameters
       // function: printIntegerJustified
    printIntegerJustified( outVal, blockSize, justified );
   }

/*
 Name: printIntegerJustified
 Process: prints integer value with the specified justification
          within the specified blockSize
Function input/parameters:
 		  outVal - the integer value to be output
      blockSize - the width of the block within which
                  to print the integer value (int)
      justify - "LEFT," "RIGHT," or "CENTER" justification in block (c-string)
 Output: None
 Device Input: None
 Device Output: Integer is displayed as specified
 Dependencies: sprintf, printStringJustified
 */
void printIntegerJustified( int outVal, int blockSize, const char *justify )
   {
    // initialize variables, create temporary output string
    char outStr[ MIN_STR_LEN ];

    // convert integer to string
       // function: sprintf
    sprintf( outStr, "%d", outVal );

    // print justified string
       // function: printStringJustified
    printStringJustified( outStr, blockSize, justify );
   }

/*
Name: printLongInteger
Process: prints long integer
Function input/Parameters: outVal - the long integer value to be output
Function output/parameters: None
Function output/returned: None
Device Input/keyboard: None
Device Output/Monitor: integer is displayed as specified
Dependencies: printLongIntJustified
*/
void printLongInteger( long outVal )
   {
    // initialize variables, set block size to zero, justification to "LEFT"
    int blockSize = 0;
    char justified[] = "LEFT";

    // print justified long integer with specified parameters
       // function: printLongIntegerJustified
    printLongIntegerJustified( outVal, blockSize, justified );
   }

/*
Name: printLongIntegerJustified
Process: prints long integer with the specified justification
         within the specified blockSize
Function input/Parameters:
 		  outVal - the long integer value to be output
      blockSize - the width of the block within which
                  to print the integer value (int)
      justify - "LEFT," "RIGHT," or "CENTER" justification in block (c-string)
Function output/parameters: None
Function output/returned: None
Device Input/keyboard: None
Device Output/Monitor: integer is displayed as specified
Dependencies: sprintf, printStringJustified
*/
void printLongIntegerJustified( long outVal,
                                            int blockSize, const char *justify )
   {
    // initialize variables, create temporary output string
    char outStr[ MIN_STR_LEN ];

    // convert long integer to string
       // function: sprintf
    sprintf( outStr, "%ld", outVal );

    // print justified string
       // function: printStringJustified
    printStringJustified( outStr, blockSize, justify );
   }

/*
 Name: printString
 Process: prints string
Function input/parameters: outVal - the string value to be output
Function output/parameters: None
Function output/returned: None
Function input/keyboard: None
Device output/monitor: string is displayed as specified
Dependencies: printStringJustified
*/
void printString( const char *outStr )
   {
    // initialize variables, set block size to zero, justification to "LEFT"    
    int blockSize = 0;
    char justified[] = "LEFT";

    // print justified string with specified parameters
       // function: printStringJustified
    printStringJustified( outStr, blockSize, justified );
   }

/*
 Name: printStringJustified
 Process: prints string within specified block size
          and with specified justification
Function input/parameters:
 		  outVal - the string value to be output
      blockSize - the width of the block within which
                  to print the integer value (int)
      justify - "LEFT," "RIGHT," or "CENTER" justification in block (c-string)
Function output/parameters: None
Function output/returned: None
Function input/keyboard: None
Device output/monitor: string is displayed as specified
Dependencies: strlen, strcmp, printCharacters, printf
*/
void printStringJustified ( const char *outStr,
                                            int blockSize, const char *justify )
   {
    // initialize variables, set pre-, post- spaces to zero
    int preSpaces = 0, postSpaces = 0, strLength;

    // find length of string
       // function: strlen
    strLength = strlen( outStr );

    // check justification for "LEFT"
       // function: strcmp
    if( strcmp( justify, "LEFT" ) == 0 )
       {
        // set post spaces for left justification
        postSpaces = blockSize - strLength;
       }

    // otherwise, check justification for "RIGHT"
       // function: strcmp
    else if( strcmp( justify, "RIGHT" ) == 0 )
       {
        // set pre spaces for right justification
        preSpaces = blockSize - strLength;
       }

    // Otherwise, assume "CENTER" justification
    else
       {
        // set pre spaces for centered
        preSpaces = blockSize / 2 - strLength / 2;

        // set post spaces for centered
        postSpaces = blockSize - strLength - preSpaces;
       }

    // print pre spaces
       // function: printChars
    printCharacters( preSpaces, SPACE );

    // print string
       // function: printf
    printf( "%s", outStr );

    // print post spaces
       // function: printChars
    printCharacters( postSpaces, SPACE );
   }

/*
Name: promptForCharacter
Process: prompts user for character, then returns it
Function input/parameters: text to prompt user (c-string)
Function output/parameters: None
Function output/returned: one character (chars
Device input/keyboard: user entry of a character
Device output/monitor: prompt string displayed
Dependencies: printf, getChar
*/
char promptForCharacter( const char *promptString )
   {
    // initialize variables
    char outChar;

    // print prompt string
       // function: printf
    printf( "%s", promptString );

    // get character from stream
       // function: getChar
    outChar = (char)getChar();

    // return captured character
    return outChar;
   }

/*
Name: promptForDouble
Process: prompts user for double, then returns it
Function input/parameters: test to prompt user (c-string)
Function output/parameters: None
Function output/returned: value (double)
Device input/keyboard: user entry of an integer value
Device output/monitor: prompt string displayed
Dependencies: printf, scanf
 */
double promptForDouble( const char *promptString )
   {
    // initialize variables
    double outDouble;

    // print prompt string
       // function: printf
    printf( "%s", promptString );

    // get double value
       // function: scanf
    scanf( "%lf", &outDouble );

    // return captured double
    return outDouble;
   }

/*
Name: promptForInteger
Process: prompts user for integer, then returns it
Function input/parameters: text to prompt user (c-string)
Function output/parameters: none
Function output/returned: integer value (int)
Device input/keyboard: user entry of a double value
Device output/monitor: prompt string displayed
Dependencies: printf, scanf
*/
int promptForInteger( const char *promptString )
   {
    // initialize variables
    int outInt;

    // print prompt string
       // function: printf
    printf( "%s", promptString );

    // input integer
       // function: scanf
    scanf( "%d", &outInt );

    // return captured integer
    return outInt;
   }

/*
Name: promptForString
Process: prompts user for string, then returns it
Function input/parameters: text to prompt user (c-string)
Function output/parameters: input string from user(c-string)
Function output/returned: none
Device input/keyboard: user entry of a string value
Device output/monitor: prompt string displayed
Dependencies: printf, getInputString
*/
void promptForString( const char *promptString, char returnStr[] )
   {
    // initialize variables, don't allow white space capture
    bool dontClearWhitespace = false;

    // pring prompt string
       // function: printf
    printf( "%s", promptString );

    // get input string from user (returned via parameter)
       // function: getInputString
    getInputString( returnStr, dontClearWhitespace );
   }


