// Preprocessor directive
#ifndef CONSOLE_IO_UTILITY_H
#define CONSOLE_IO_UTILITY_H

//Header Files
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "StandardConstants.h"

//Global Constants

   // none

//Function Prototypes

/*
Name: clearLeadingCharacters
Process: Clears all leading non-printable characters from the console stream
Function input/parameters: allow space return (bool)
Function output/parameters: none
Function output/returned: first printable character as integer
Device input/keyboard: none
Device output/monitor: none
Dependencies: getchar
*/
int clearLeadingCharacters( bool allowSpaceReturn );

/*
Name: getChar
Process: returns next character in stream,
                 ignores all white space (including SPACE)  prior to character
Function input/parameters: flag to accept space (bool)
Function output/parameters: none
Function output/returned: one character (char) is returned to calling method
Device input/keyboard: places one or more characters in stream
Device output/monitor: none
Dependencies:
*/
char getChar();

/*
Name: getCharFiltered
Process: returns next character in stream,
         ignores non printable characters prior to input character
         but may accept space depending on flag
Function input/parameters: flag to accept space (bool)
Function output/parameters: none
Function output/returned: first printable character or space (if configured)
                          returned (char)
Device input/keyboard: places one or more characters in stream
Device output/monitor: none
Dependencies: getchar(), clearLeadingCharacters
*/
char getCharFiltered( bool acceptSpace );

/*
Name: getInputString
Process: acquires input string from keyboard, if clear white space flag set,
         ignores all white space, including space character
Function input/parameters: clear white space control (bool)
Function output/parameters: character array (char[])
Function output/returned: none
Device input/keyboard: user entry of a character stream
Device output/monitor: none
Dependencies: getchar(), clearLeadingCharacters
*/
void getInputString(char inputArr[], bool clearWhiteSpace );

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
void printCharacter( char outputChar );

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
void printCharacters( int numChars, char outputChar );

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
void printDouble( double outVal, int precision );

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
                                           int blockSize, const char* justify );

/*
Name: printEndline
Process: prints single endline character to end a line or create vertical space
Function input/parameters: none
Function output/parameters: none
Function output/returned: none
Device input: none
Device output/monitor: one endline character output
Dependencies: printEndline
*/
void printEndline();

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
void printEndlines( int numEndlines );

/*
 Name: printInteger
 Process: prints integer value
Function input/parameters: outVal - the integer value to be output
 Output: None
 Device Input: None
 Device Output: Integer is displayed as specified
 Dependencies: printIntegerJustified
 */
void printInteger( int outVal );

/*
 Name: printIntegerJustified
 Process: prints integer value with the specified justification
          within the specified blockSize
Function output/parameters:
 		  outVal - the integer value to be output (int)
      blockSize - the width of the block within which
                  to print the integer value (int)
      justify - "LEFT," "RIGHT," or "CENTER" justification in block (c-string)
 Output: None
 Device Input: None
 Device Output: Integer is displayed as specified
 Dependencies: sprintf, printStringJustified
 */
void printIntegerJustified( int outVal, int blockSize, const char *justify );

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
void printLongInteger( long outVal );

/*
Name: printLongIntegerJustified
Process: prints long integer with the specified justification
         within the specified blockSize
Function Input/Parameters:
 		  outVal - the long integer value to be output (long int)
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
                                           int blockSize, const char *justify );

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
void printString( const char *outStr );

/*
 Name: printStringJustified
 Process: prints string within specified block size
          and with specified justification
Function input/parameters:
 		  outVal - the string value to be output (c-string)
      blockSize - the width of the block within which
                  to print the integer value (int)
      justify - "LEFT," "RIGHT," or "CENTER" justification in block (c-string)
Function output/parameters: None
Function output/returned: None
Function input/keyboard: None
Device output/monitor: string is displayed as specified
Dependencies: strlen, strcmp, printCharacters, printf
*/
void printStringJustified( const char *outStr,
                                           int blockSize, const char *justify );

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
char promptForCharacter( const char *promptString );

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
double promptForDouble( const char *promptString );

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
int promptForInteger( const char *promptString );

/*
Name: promptForString
Process: prompts user for string, then returns it
Function input/parameters: text to prompt user (c-string)
Function output/parameters: none
Function output/returned: input string (c-string)
Device input/keyboard: user entry of a string value
Device output/monitor: prompt string displayed
Dependencies: printf, getInputString
*/
void promptForString( const char *promptString, char returnStr[] );

#endif  // end CONSOLE_IO_UTILITY_H
