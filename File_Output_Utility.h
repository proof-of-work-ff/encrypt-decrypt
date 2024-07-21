/*
Formatted file output utility, function prototypes

Copyright (c) 2021 by Michael E. Leverington

Code is free for use in whole or in part and may be modified for other
non-commercial use as long as the above copyright statement is included.
*/
/*
Rev 0.0: 30 June 2021, Initial creation of file

UTILITY USAGE INSTRUCTIONS:

1) This utility contains functions that may be used for file input operations
   using the C programming language with text files.
   The utility must be linked with the program code with which
   it will be used. 
      
2) Specifications for all the functions 
    are provided in a standardized format below.

3) Use this code at your own risk. There is no guarantee of any performance,
   implied or otherwise, for any part of this code

   END OF INSTRUCTIONS
*/

// PreProcessor directives
#ifndef FILE_OUTPUT_UTILITY_H
#define FILE_OUTPUT_UTILITY_H

// header files
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "StandardConstants.h"

// function prototypes

    /*
    Name: accessOutputFilePointer
    process: allows setting or accessing file pointer;
             note: pointer is maintained (static) value initialized to NULL
    Function input/parameters: control code (int), file pointer (FILE *)
                               DUMMY_OUTPUT_FILE_PTR used 
                               if not setting file pointer
    Function output/parameters: none
    Function output/returned: file pointer (FILE *)
    Device input/file: none
    Device output/monitor: none
    Dependencies: none
    */
    FILE *accessOutputFilePointer( int ctrlCode, const FILE *filePtr );

    /*
    Name: closeOutputFile
    Process: closes output file, returns true if successful, false otherwise
    Function input/parameters: none
    Function output/parameters: none
    Function output/returned: operation success (bool)
    Device input/file: none
    Device output/file: output file closed
    Dependencies: accessOutputFilePointer, fclose
    */
    bool closeOutputFile();

    /*
    Name: openOutputFile
    Process: opens input file, returns true if successful, false otherwise
    Function input/parameters: file name (c-string)
    Function output/parameters: none
    Function output/returned: operation success (bool)
    Device input/file: none
    Device output/file: output file opened
    Dependencies: accessOutputFilePointer, fopen
    */
    bool openOutputFile( const char *fileName );

    /*
    Name: writeCharacterToFile
    Process: writes individual character to file,
             returns true if successful, false otherwise
    Function input/parameters: character to output (char)
    Function output/parameters: none
    Function output/returned: operation success (bool)
    Device input/file: none
    Device output/file: character written to file
    Dependencies: accessOutputFilePointer, fprintf
    */
    bool writeCharacterToFile( char outChar );

    /*
    Name: writeCharactersToFile
    Process: writes multiple characters to file,
             returns true if successful, false otherwise
    Function input/parameters: number of characters to output (int),
                               character to output (char)
    Function output/parameters: none
    Function output/returned: operation success (bool)
    Device input/file: none
    Device output/file: multiple characters written to file
    Dependencies: writeCharacterToFile
    */
    bool writeCharactersToFile( int numChars, char outChar );

    /*
    Name: writeDoubleToFile
    Process: writes individual formatted double value to file,
             returns true if successful, false otherwise
    Function input/parameters: double value to output (double),
                             number of digits to right of radix point
                             (precision) (int)
    Function output/parameters: none
    Function output/returned: operation success (bool)
    Device input/file: none
    Device output/file: double written to file
    Dependencies: writeDoubleJustifiedToFile
    */
    bool writeDoubleToFile( double outVal, int precision );

    /*
    Name: writeDoubleToFileJustified
    Process: writes individual formatted double value to file justified,
             returns true if successful, false otherwise
             outVal - the double value to be output
             precision - number of digits to the right of the radix point
             blockSize - the width of the block within which
                         to print the integer value (int)
             justify - "LEFT," "RIGHT," or "CENTER" justification 
                       in block (c-string)
    Function output/parameters: none
    Function output/returned: operation success (bool)
    Device input/file: none
    Device output/file: double written to file as specified
    Dependencies: sprintf, writeStringJustifiedToFile
    */
    bool writeDoubleJustifiedToFile( double outVal, int precision, 
                                         int blockSize, const char *justified );

    /*
    Name: writeEndlineToFile
    Process: writes newline ('\n') to file,
             returns true if successful, false otherwise
    Function input/parameters: none
    Function output/parameters: none
    Function output/returned: operation success (bool)
    Device input/file: none
    Device output/file: newline written to file
    Dependencies: accessOutputFilePointer, fprintf
    */
    bool writeEndlineToFile();

    /*
    Name: writeEndlinesToFile
    Process: writes multiple carriage return ('\r')
             and newline ('\n') pairs to file,
             returns true if successful, false otherwise
    Function input/parameters: number of endline pairs to write (int)
    Function output/parameters: none
    Function output/returned: operation success (bool)
    Device input/file: none
    Device output/file: multiple newline characters written to file
    Dependencies: writeString
    */
    bool writeEndlinesToFile( int numEndlines );

    /*
    Name: writeIntegerToFile
    Process: writes individual integer to file,
             returns true if successful, false otherwise
    Function input/parameters: integer to output (int)
    Function output/parameters: none
    Function output/returned: operation success (bool)
    Device input/file: none
    Device output/file: integer written to file
    Dependencies: writeIntegerJustifiedToFile
    */
    bool writeIntegerToFile( int outVal );

    /*
    Name: writeIntegerJustifiedToFile
    Process: writes individual integer to file,
             returns true if successful, false otherwise
    Function input/parameters:
                    outVal - the integer value to be output
                    precision - number of digits to the right of the radix point
                    blockSize - the width of the block within which
                         to print the integer value (int)
                    justify - "LEFT," "RIGHT," or "CENTER" justification 
                       in block (c-string)
    Function output/parameters: none
    Function output/returned: operation success (bool)
    Device input/file: none
    Device output/file: integer written to file as specified
    Dependencies: sprintf, writeStringJustifiedToFile
    */
    bool writeIntegerJustifiedToFile( int outVal, int blockSize, 
                                                         const char *justified );

    /*
    Name: writeStringToFile
    Process: writes String value to file,
             returns true if successful, false otherwise
    Function input/parameters: double value to output (double),
                             number of digits to right of radix point
                             (precision) (int)
    Function output/parameters: none
    Function output/returned: operation success (bool)
    Device input/file: none
    Device output/file: String written to file
    Dependencies: writeStringJustifiedToFile
    */
    bool writeStringToFile( const char *outString );

    /*
    Name: writeStringJustifiedToFile
    Process: write string to file within specified block size
             and with specified justification
    Function input/parameters:
 		           outVal - the string value to be output
                   blockSize - the width of the block within which
                               to print the integer value (int)
                   justify - "LEFT," "RIGHT," or "CENTER" justification 
                             in block (c-string)
    Function output/parameters: None
    Function output/returned: success of output operation (bool)
    Function input/keyboard: None
    Device output/file: string written to file as specified
    Dependencies: strlen, strcmp, writeCharactersToFile, fprint
    */
    bool writeStringJustifiedToFile( const char *outStr,
                                            int blockSize, const char *justify );


#endif  // FILE_OUTPUT_UTILITY_H

