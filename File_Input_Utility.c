/*
Formatted file input utility, function implementations

Copyright (c) 2021 by Michael E. Leverington

Code is free for use in whole or in part and may be modified for other
non-commercial use as long as the above copyright statement is included.
*/

// header files
#include "File_Input_Utility.h"
#include <stdlib.h> //////////////////////////test

// local global constants, used only in this file

    // dummy file pointer for accessInputFilePointer
    const FILE *DUMMY_INPUT_FILE_PTR = NULL;

    // dummy Boolean for accessEndOfInputFileFlag, accessOpenFlag
    const char DUMMY_INPUT_FLAG = false;

    // control code for accessing file pointer, accessInputFilePointer
    const int GET_INPUT_FILE_PTR = 3003;

    // control code for accessing flag value, 
    //   accessEndOfInputFileFlag, accessOpenFlag
    const int GET_INPUT_FLAG = 2002;

    // control code for setting file pointer, accessInputFilePointer
    const int SET_INPUT_FILE_PTR = 4004;

    // control code for setting flag value, accessEndOfInputFileFlag, 
    //   accessOpenFlag
    const int SET_INPUT_FLAG = 1001;


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
    bool accessEndOfInputFileFlag( int ctrlCode, bool setFlag )
       {
        // initialize end of file flag to false
        static bool endOfFileFlag = false;

        // test for set flag
        if( ctrlCode == SET_INPUT_FLAG )
           {
            // set flag to given state
            endOfFileFlag = setFlag;
           }
    
        // return flag state
        return endOfFileFlag;
       }

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
    FILE *accessInputFilePointer( int ctrlCode, const FILE *filePtr )
       {
        // initialize file pointer to null
        static FILE *filePointer = NULL;

        // check for set new pointer
        if( ctrlCode == SET_INPUT_FILE_PTR )
           {
            // set file pointer to parameter
            filePointer = (FILE *)filePtr;
           }
 
        // return file pointer
        return filePointer;
       }

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
    bool checkForEndOfInputFile()
       {
        // return access to end of file flag
           // function: accessEndOfInputFileFlag
        return accessEndOfInputFileFlag( GET_INPUT_FLAG, DUMMY_INPUT_FLAG );
       }

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
    bool checkForInputFileOpen()
       {
        // return access to end of file flag
           // function: accessInputFilePointer
        return accessInputFilePointer( GET_INPUT_FLAG, 
                                                 DUMMY_INPUT_FILE_PTR ) != NULL;
       }

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
    int clearLeadingWhiteSpace( FILE *filePtr, bool clearSpace )
       {
        // initialize character input value
           // function: fgetc
        int charInt = fgetc( filePtr );

        while( 
        // continue if not at end of file
        ( charInt != EOF )

        // AND
        // continue if character is non printable
        && ( ( charInt < SPACE )

        // OR
        // continue if clear space flag set and space is found
        || ( clearSpace && charInt == SPACE ) )
             )
           {
            // capture next character
               // function: fgetc
            charInt = fgetc( filePtr );
           }

        // return input value as character
        return (char)charInt;
       }

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
    bool closeInputFile()
       {
        // set local file pointer to working file pointer
           // function: accessInputFilePointer
        FILE *filePtr = accessInputFilePointer( GET_INPUT_FILE_PTR, 
                                                         DUMMY_INPUT_FILE_PTR );

        // check for valid file pointer
        if( filePtr != NULL )
           {
            // close file
            fclose( filePtr );

            // set pointer to NULL
               // function: accessInputFilePointer
            accessInputFilePointer( SET_INPUT_FILE_PTR, NULL );

            // set end of file flag to false
               // function: accessEndOfInputFileFlag
            accessEndOfInputFileFlag( SET_INPUT_FLAG, false );

            // return successful operation
            return true;
           }  

        // return failed  operation
        return false;
       }

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
    bool openInputFile( const char *fileName )
       {
        // initialize variables
        FILE *filePtr = NULL;
        char readOnlyCharacter[] = "r";

        // check for file not open
           // function: checkForInputFileOpen
        if( !checkForInputFileOpen() )
           {
            // open file
               // function: fopen
            filePtr = fopen( fileName, readOnlyCharacter );

            // check for success of file open
            if( filePtr != NULL )
               {
                // set pointer in access function
                   // function: accessInputFilePointer
                accessInputFilePointer( SET_INPUT_FILE_PTR, filePtr );

                // reset end of file flag, if needed
                   // accessEndOfInputFileFlag
                accessEndOfInputFileFlag( SET_INPUT_FLAG, false );

                // return operation success
                return true;
               }
           }
        // end of file not previously opened block

        // return operation failure
        return false;
       }
    
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
    char readCharacterFromFile()
       {
        // initialize parameter to not allow space
        bool noSpaceCapture = false;

        // capture character, return
           // function: getCharFromFileConfigured
        return readCharacterFromFileConfigured( noSpaceCapture );
       }

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
    char readCharacterFromFileConfigured( bool captureSpace )
       {
        // initialize variables
        FILE *filePtr;
        int intChar = ZERO_CHAR;

        // check for file open and data accessible
           // function: checkForInputFileOpen, checkForEndOfInputFile
        if( checkForInputFileOpen() && !checkForEndOfInputFile() )
           {
            // set file pointer
               // function: accessInputFilePointer
            filePtr = accessInputFilePointer( GET_INPUT_FILE_PTR, 
                                                         DUMMY_INPUT_FILE_PTR );

            // get character
               // function: clearLeadingWhiteSpace
            intChar = clearLeadingWhiteSpace( filePtr, !captureSpace );

            // check for end of file found
            if( intChar == EOF )
               {
                // set end of file flag
                   // function: accessEndOfInputFileFlag
                accessEndOfInputFileFlag( SET_INPUT_FLAG, true );

                // set return value to zero
                intChar = ZERO_CHAR;
               }
           }

        // return value as character
        return intChar;
       }

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
    double readDoubleFromFile()
       {
        // initialize variables
        FILE *filePtr = NULL;
        int fscanfReturn = EOF;
        double doubleVal = ZERO_VALUE;

        // check for file open and data accessible
           // function: checkForInputFileOpen, checkForEndOfInputFile
        if( checkForInputFileOpen() && !checkForEndOfInputFile() )
           {
            // set file pointer
               // function: accessInputFilePointer
            filePtr = accessInputFilePointer( GET_INPUT_FILE_PTR, 
                                                         DUMMY_INPUT_FILE_PTR );

            // get double value
               // function: fscanf
            fscanfReturn = fscanf( filePtr, "%lf", &doubleVal );

            // check for end of file found
            if( fscanfReturn == EOF )
               {
                // set end of file flag
                   // function: accessEndOfInputFileFlag
                accessEndOfInputFileFlag( SET_INPUT_FLAG, true );

                // set return value to zero
                doubleVal = ZERO_VALUE;
               }
           }
 
        // return acquired value
        return doubleVal;
       }
      
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
    int readIntegerFromFile()
       {
        // initialize variables
        FILE *filePtr = NULL;
        int fscanfReturn = EOF;
        int intVal = ZERO_VALUE;

        // check for file open and data accessible
           // function: checkForInputFileOpen, checkForEndOfInputFile
        if( checkForInputFileOpen() && !checkForEndOfInputFile() )
           {
            // set file pointer
               // function: accessInputFilePointer
            filePtr = accessInputFilePointer( GET_INPUT_FILE_PTR, 
                                                         DUMMY_INPUT_FILE_PTR );

            // get integer value
               // function: fscanf
            fscanfReturn = fscanf( filePtr, "%d", &intVal );

            // check for end of file found
            if( fscanfReturn == EOF )
               {
                // set end of file flag
                   // function: accessEndOfInputFileFlag
                accessEndOfInputFileFlag( SET_INPUT_FLAG, true );

                // set return value to zero
                intVal = ZERO_VALUE;
               }
           }
 
        // return acquired value
        return intVal;
       }
      
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
    long readLongFromFile()
       {
        // initialize variables
        FILE *filePtr = NULL;
        int fscanfReturn = EOF;
        long longVal = ZERO_VALUE;

        // check for file open and data accessible
           // function: checkForInputFileOpen, checkForEndOfInputFile
        if( checkForInputFileOpen() && !checkForEndOfInputFile() )
           {
            // set file pointer
               // function: accessInputFilePointer
            filePtr = accessInputFilePointer( GET_INPUT_FILE_PTR, 
                                                         DUMMY_INPUT_FILE_PTR );

            // get long value
               // function: fscanf
            fscanfReturn = fscanf( filePtr, "%ld", &longVal );

            // check for end of file found
            if( fscanfReturn == EOF )
               {
                // set end of file flag
                   // function: accessEndOfInputFileFlag
                accessEndOfInputFileFlag( SET_INPUT_FLAG, true );

                // set return value to zero
                longVal = ZERO_VALUE;
               }
           }
 
        // return acquired value
        return longVal;
       }
      
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
    char readRawCharFromFile()
       {
        // initialize variables
        FILE *filePtr = NULL;
        int intChar = (int)ZERO_CHAR;

        // check for file open and data accessible
           // function: checkForInputFileOpen, checkForEndOfInputFile
        if( checkForInputFileOpen() && !checkForEndOfInputFile() )
           {
            // set file pointer
               // function: accessInputFilePointer
            filePtr = accessInputFilePointer( GET_INPUT_FILE_PTR, 
                                                         DUMMY_INPUT_FILE_PTR );

            // get character
               // function: fgetc
            intChar = fgetc( filePtr );

            // check for end of file found
            if( intChar == EOF )
               {
                // set end of file flag
                   // function: accessEndOfInputFileFlag
                accessEndOfInputFileFlag( SET_INPUT_FLAG, true );

                // set return value to zero
                intChar = (int)ZERO_CHAR;
               }
           }
 
        // return acquired value
        return (char)intChar;
       }

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
                                      char *capturedString )
      {
       // initialize variables
       int intChar = EOF, index = 0;
       FILE *filePtr = NULL;
       
        // initialize output string
        capturedString[ index ] = NULL_CHAR;

        // check for file open and data accessible
           // function: checkForInputFileOpen, checkForEndOfInputFile
       if( checkForInputFileOpen() && !checkForEndOfInputFile() )
          {
           // get file pointer
              // function: accessFilePtr
           filePtr = accessInputFilePointer( GET_INPUT_FILE_PTR, 
                                                         DUMMY_INPUT_FILE_PTR );

           // check for clearing non printable
           if( clearLeadingNonPrintable )
              {
               // clear leading white space, with clear space character flag
                  // function: clearLeadingWhiteSpace
               intChar = clearLeadingWhiteSpace( filePtr, clearLeadingSpace );
              }

           // otherwise, assume non printable not cleared
           else
              {
               // get first character
                  // function: fgetc
               intChar = fgetc( filePtr );

               // check for clearing spaces
               if( clearLeadingSpace )
                  {
                   // loop while spaces found and end of file not found
                   while( intChar != EOF && intChar == (int)SPACE )
                      {
                       // capture new character
                          // function: fgetc
                       intChar = fgetc( filePtr );
                      }
                  }
              }  // end leading character clearing process

            // check for end of file found
            if( intChar == EOF )
               {
                // set end of file flag
                   // function: accessEndOfInputFileFlag
                accessEndOfInputFileFlag( SET_INPUT_FLAG, true );

                // return failed operation
                return false;
               }

            // loop to capture input
            while( 
            // continues if not at end of file and max string length not reached
            ( intChar != EOF && index < MAX_STR_LEN - 1 )  

            // AND
            // continues if not printable flag set and characters are printable
            // OR not printable flag not set
            && ( ( stopAtNonPrintable && intChar >= (int)SPACE ) 
                   || ( !stopAtNonPrintable ) )

            // AND
            // continues if specified delimiter is not found
            && ( intChar != (char)delimiter ) 
                 )
               {
                // place character in array element
                capturedString[ index ] = (char)intChar;

                // increment array index
                index++;

                // set next element to null character / end of c-string
                capturedString[ index ] = NULL_CHAR;

                // get next character as integer
                   // function: fgetc
                intChar = fgetc( filePtr );
               }
            // end loop

            // return successful operation
            return true;
           }  
       // end of open file and accessible data block

       return false;  // temporary stub return
      }

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
    bool readStringSegmentFromFile( char *capturedString )
       {
        // initialize variables
        bool clearLeadingNonPrintable = true;
        bool clearLeadingSpace = true;
        bool stopAtNonPrintable = true;
        char delimiter = SPACE;

        // call utility function, return
        return readStringConfiguredFromFile( clearLeadingNonPrintable, 
                                             clearLeadingSpace, 
                                             stopAtNonPrintable, 
                                             delimiter,
                                             capturedString );
       }

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
    bool readStringToLineEndFromFile( char *capturedString )
       {
        // initialize variables
        bool clearLeadingNonPrintable = true;
        bool clearLeadingSpace = true;
        bool stopAtNonPrintable = true;
        char delimiter = NON_PRINTABLE;

        // call utility function, return
        return readStringConfiguredFromFile( clearLeadingNonPrintable, 
                                             clearLeadingSpace, 
                                             stopAtNonPrintable, 
                                             delimiter,
                                             capturedString );
       }

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
    bool readStringToDelimiterFromFile( char delimiter, char *capturedString )
       {
        // initialize variables
        bool clearLeadingNonPrintable = true;
        bool clearLeadingSpace = true;
        bool stopAtNonPrintable = true;

        // call utility function, return
        return readStringConfiguredFromFile( clearLeadingNonPrintable, 
                                             clearLeadingSpace, 
                                             stopAtNonPrintable, 
                                             delimiter,
                                             capturedString );
       }



