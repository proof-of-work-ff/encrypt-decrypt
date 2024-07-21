/*
Formatted file input utility, function prototypes

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

// PreProcessor test
#ifndef FILE_INPUT_UTILITY_H
#define FILE_INPUT_UTILITY_H

// header files
#include <stdbool.h>
#include <stdio.h>
#include "StandardConstants.h"

// constants shared with other files

    // non printable flag, used in getStringConfigured
    static const char NON_PRINTABLE = (char)(127);

    // constant used for zero character return
    static const char ZERO_CHAR = '0';
    
    // constant used for zero int/double value return
    static const char ZERO_VALUE = 0;

// function prototypes

    /*
    Name: accessEndOfInputFileFlag
    process: allows accessing or modifying end of file flag state;
             note: flag is maintained (static) value initialized to false
    Function input/parameters: control code (int), flag state (bool)
    Function output/parameters: none
    Function output/returned: result of flag state (bool)
    Device input/file: none
    Device output/monitor: none
    Dependencies: none
    */
    bool accessEndOfInputFileFlag( int ctrlCode, bool setFlag );

    /*
    Name: accessInputFilePointer
    process: allows setting or accessing file pointer;
             note: pointer is maintained (static) value initialized to NULL
    Function input/parameters: control code (int), file pointer (FILE *)
                               DUMMY_INPUT_FILE_PTR used 
                               if not setting file pointer
    Function output/parameters: none
    Function output/returned: file pointer (FILE *)
    Device input/file: none
    Device output/monitor: none
    Dependencies: none
    */
    FILE *accessInputFilePointer( int ctrlCode, const FILE *filePtr );

    /*
    Name: checkForEndOfInputFile
    process: checks to see if end of file flag has been encountered,
             returns true if EOF has been encountered, false otherwise
    Function input/parameters: none
    Function output/parameters: none
    Function output/returned: result of specified test (bool)
    Device input/file: none
    Device output/monitor: none
    Dependencies: accessEndOfInputFileFlag
    */
    bool checkForEndOfInputFile();

    /*
    Name: checkForInputFileOpen
    process: checks to see if file is currently open
             returns true if file pointer not null, false otherwise
    Function input/parameters: none
    Function output/parameters: none
    Function output/returned: result of specified test (bool)
    Device input/file: none
    Device output/monitor: none
    Dependencies: accessInputFilePointer
    */
    bool checkForInputFileOpen();

    /*
    Name: clearLeadingWhiteSpace
    process: captures non printable characters,
             and space if flag set,
             returns first non white space value found as integer
    Function input/parameters: file pointer (FILE *), clear space flag (bool)
    Function output/parameters: none
    Function output/returned: first non WS character as integer
    Device input/file: value captured from file
    Device output/monitor: none
    Dependencies: fgetc
    */
    int clearLeadingWhiteSpace( FILE *filePtr, bool clearSpace );

    /*
    Name: closeInputFile
    process: closes input file, returns true if successful, false otherwise
    Function input/parameters: none
    Function output/parameters: none
    Function output/returned: none
    Device input/file: file closed
    Device output/monitor: none
    Dependencies: accessInputFilePointer, fclose, accessEndOfInputFileFlag
    */
    bool closeInputFile();

   /*
    Name: openInputFile
    process: opens input file, sets file pointer and unsets end of file flag,
             returns true if successful, false otherwise
    Function input/parameters: file name (c-string)
    Function output/parameters: none
    Function output/returned: success of operation (bool)
    Device input/file: file opened
    Device output/monitor: none
    Dependencies: fopen, accessInputFilePointer, accessEndOfInputFileFlag
    */
    bool openInputFile( const char *fileName );
    
    /*
    Name: readCharacterFromFile
    process: ignores leading unprintable characters, including space,
             captures first printable character
    Function input/parameters: allow space capture (bool)
    Function output/parameters: none
    Function output/returned: character found if successful, ZERO_CHAR otherwise
    Device input/file: character(s) captured from file as needed
    Device output/monitor: none
    Dependencies: readCharacterFromFileConfigured
    */
    char readCharacterFromFile();

    /*
    Name: readCharacterFromFileConfigured
    process: ignores leading unprintable characters,
             captures first printable character,
             including space if allowed
    Function input/parameters: allow space capture (bool)
    Function output/parameters: none
    Function output/returned: character found if successful, ZERO_CHAR otherwise
    Device input/file: character(s) captured from file as needed
    Device output/monitor: none
    Dependencies: checkForInputFileOpen, checkForEndOfInputFile, 
                  accessInputFilePointer, clearLeadingWhiteSpace, 
                  accessEndOfInputFileFlag
    */
    char readCharacterFromFileConfigured( bool captureSpace );

    /*
    Name: readDoubleFromFile
    process: ignores leading unprintable characters,
             captures first contiguous double value
    Function input/parameters: none
    Function output/parameters: none
    Function output/returned: double value found if successful (double)
    Device input/file: double value captured from file
    Device output/monitor: none
    Dependencies: checkForInputFileOpen, checkForEndOfInputFile, 
                  accessInputFilePointer, fscanf, accessEndOfInputFileFlag
    */
    double readDoubleFromFile();
      
    /*
    Name: readIntegerFromFile
    process: ignores leading unprintable characters,
             captures first contiguous integer
    Function input/parameters: none
    Function output/parameters: none
    Function output/returned: integer found if successful, ZERO_VALUE otherwise
    Device input/file: character(s) captured from file as needed
    Device output/monitor: none
    Dependencies: checkForInputFileOpen, checkForEndOfInputFile, 
                  accessInputFilePointer, fscanf, accessEndOfInputFileFlag
    */
    int readIntegerFromFile();
      
    /*
    Name: readLongFromFile
    process: ignores leading unprintable characters,
             captures first contiguous long int
    Function input/parameters: none
    Function output/parameters: none
    Function output/returned: long integer found if successful, 
                              ZERO_VALUE otherwise
    Device input/file: long value captured from file
    Device output/monitor: none
    Dependencies: checkForInputFileOpen, checkForEndOfInputFile, 
                  accessInputFilePointer, fscanf, accessEndOfInputFileFlag
    */
    long readLongFromFile();
      
    /*
    Name: readRawCharFromFile
    process: captures first character in file stream including non-printable
    Function input/parameters: none
    Function output/parameters: none
    Function output/returned: character found if successful, ZERO_CHAR otherwise
    Device input/file: character captured from file
    Device output/monitor: none
    Dependencies: checkForInputFileOpen, checkForEndOfInputFile, 
                  accessInputFilePointer, fgetc, accessEndOfInputFileFlag
    */
    char readRawCharFromFile();

    /*
    Name: readStringConfiguredFromFile
    Process: captures string with options:
             - clear leading non printable (bool)
             - clear leading space character (bool)
             - adquires characters up to any non-printable (bool)
             - adquires characters up to any printable delimiter (char)
               - use constant NON_PRINTABLE if no delimiter
             - also stops capture when full (MAX_STR_LEN)
             Note: This function consumes the last character input,
             including the space, delimiter, or non-printable character
    Function input/parameters: see process above
    Function output/parameters: captured string (char *), EMPTY_STRING otherwise
    Function output/returned: success of operation (bool)
    Device input/file: character(s) captured from file as needed
    Device output/monitor: none
    Dependencies: checkForInputFileOpen, checkForEndOfInputFile, 
                  clearLeadingWhiteSpace, fgetc, accessEndOfInputFileFlag
    */
   bool readStringConfiguredFromFile( bool clearLeadingNonPrintable, 
                                      bool clearLeadingSpace, 
                                      bool stopAtNonPrintable, 
                                      char delimiter,
                                      char *capturedString );

   /*
    Name: readStringSegmentFromFile
    process: ignores leading white space, including space character,
             captures series of characters up to first space,
             or end of line, or full string
    Function input/parameters: none
    Function output/parameters: captured string (char *), EMPTY_STRING otherwise
    Function output/returned: success of operation (bool)
    Device input/file: character(s) captured from file as needed
    Device output/monitor: none
    Dependencies: readStringConfigured with appropriate parameters
    */
    bool readStringSegmentFromFile( char *capturedString );

   /*
    Name: readStringToLineEndFromFile
    process: ignores leading white space, including space character,
             captures series of characters up to end of current line
             or full string
    Function input/parameters: none
    Function output/parameters: captured string (char *), EMPTY_STRING otherwise
    Function output/returned: string found if successful
    Device input/file: character(s) captured from file as needed
    Device output/monitor: none
    Dependencies: readStringConfigured with appropriate parameters
    */
    bool readStringToLineEndFromFile( char *capturedString );

   /*
    Name: readStringToDelimiterFromFile
    process: ignores leading white space, including space character,
             captures series of characters up to specified character
    Function input/parameters: none
    Function output/parameters: captured string (char *), EMPTY_STRING otherwise
    Function output/returned: string found if successful
    Device input/file: character(s) captured from file as needed
    Device output/monitor: none
    Dependencies: readStringConfigured with appropriate parameters
    */
    bool readStringToDelimiterFromFile( char delimiter, char *capturedString );

#endif  // FILE_INPUT_UTILITY_H


