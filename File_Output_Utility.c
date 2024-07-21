/*
Formatted file ouput utility, function implementations

Copyright (c) 2021 by Michael E. Leverington

Code is free for use in whole or in part and may be modified for other
non-commercial use as long as the above copyright statement is included.
*/

// header files
#include "File_Output_Utility.h"

// local global constants, used only in this file

    // dummy file pointer for accessInputFilePointer
    const FILE *DUMMY_OUTPUT_FILE_PTR = NULL;

    // dummy Boolean for accessEndOfInputFileFlag, accessOpenFlag
//    const char DUMMY_OUTPUT_FLAG = false;

    // control code for accessing file pointer, accessInputFilePointer
    const int GET_OUTPUT_FILE_PTR = 6006;

    // control code for accessing flag value, 
    //   accessEndOfInputFileFlag, accessOpenFlag
    const int GET_OUTPUT_FLAG = 9009;

    // control code for setting file pointer, accessInputFilePointer
    const int SET_OUTPUT_FILE_PTR = 8008;

    // control code for setting flag value, accessEndOfInputFileFlag, 
    //   accessOpenFlag
//    const int SET_OUTPUT_FLAG = 1001;

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
    FILE *accessOutputFilePointer( int ctrlCode, const FILE *filePtr )
       {
        static FILE *filePointer = NULL;

        // check for set new pointer
        if( ctrlCode == SET_OUTPUT_FILE_PTR )
           {
            // set file pointer to parameter
            filePointer = (FILE *)filePtr;
           }

        // return file pointer
        return filePointer;
       }

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
    bool closeOutputFile()
       {
        // set local file pointer to working file pointer
           // function: accessOutputFilePointer
        FILE *filePtr = accessOutputFilePointer( GET_OUTPUT_FILE_PTR, 
                                                         DUMMY_OUTPUT_FILE_PTR );

        // check for valid file pointer
        if( filePtr != NULL )
           {
            // add two more endlines to verify that the data is ended
            // and has at least one extra newline after the data
               // function: fprintf
            fprintf( filePtr, "\n\n" );

            // flush all data to the device
               // function: fflush
            fflush( filePtr );

            // close file
               // function: fclose
            fclose( filePtr );

            // set pointer to NULL
               // function: accessOutputFilePointer
            accessOutputFilePointer( SET_OUTPUT_FILE_PTR, NULL );

            // return successful operation
            return true;
           }  

        // return failed operation
        return false;
       }

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
    bool openOutputFile( const char *fileName )
       {
        // initialize variables
        FILE *filePtr = accessOutputFilePointer( GET_OUTPUT_FILE_PTR, 
                                                        DUMMY_OUTPUT_FILE_PTR );
        char writeCharacter[] = "w";

        // check for file not open
        if( filePtr == NULL )
           {
            // open file
               // function: fopen
            filePtr = fopen( fileName, writeCharacter );

            // check for success of file open
            if( filePtr != NULL )
               {
                // set pointer in access function
                   // function: accessInputFilePointer
                accessOutputFilePointer( SET_OUTPUT_FILE_PTR, filePtr );

                // return operation success
                return true;
               }
           }
        // end of file not previously opened block

        // return operation failure
        return false;
       }

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
    bool writeCharacterToFile( char outChar )
       {
        // initialize variables, set file pointer
           // function: accessOutputFilePointer
        FILE *filePtr = accessOutputFilePointer( GET_OUTPUT_FILE_PTR, 
                                                        DUMMY_OUTPUT_FILE_PTR );

        // check for open file
           // function: checkForOutputFileOpen
        if( filePtr != NULL )
           {
            // write character
               // function: fprintf
            fprintf( filePtr, "%c", outChar );

            // return successful operation
            return true;
           }
      
        // return failed operation
        return false;
       }

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
    bool writeCharactersToFile( int numChars, char outChar )
       {
        // check for number of characters remaining,
        if( numChars > 0 )
           {
            // write character, check for success 
               // function: writeChar
            if( writeCharacterToFile( outChar ) )
               {
                // continue recursion, 
                // check for downstream success
                   // function: writeChars
                return writeCharactersToFile( numChars - 1, outChar );
               }

            // quit recursion
            // return unsuccessful operation - write operation failed
            return false;
           }

        // return successful operation - all characters have been written
        return true;
       }

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
    bool writeDoubleToFile( double outVal, int precision )
       {
        // initialize variables, set block size to zero and justified to "LEFT"
        int blockSize = 0;
        char justified[] = "LEFT";
        
        // call to justified function
           // function: writeDoubleJustifiedToFile
        return writeDoubleJustifiedToFile( outVal, precision, 
                                                         blockSize, justified );
       }

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
                                          int blockSize, const char *justified )
       {
        // initialize variables, create temp string for configuration string
        char specStr[ MIN_STR_LEN ];

        // initialize variables, create temporary output string
        char outStr[ MIN_STR_LEN ];

        // set configuration string with precision value
           // function: sprintf
        sprintf( specStr, "%s0.%dlf", "%", precision );

        // set double to string
           // function: sprintf
        sprintf( outStr, specStr, outVal );

        // write as string, return result
           // function: writeStringJustified
        return writeStringJustifiedToFile( outStr, blockSize, justified );
       }

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
    bool writeEndlineToFile()
       {
        // get file pointer, initialize variable
           // function: accessOutputFilePointer
        FILE *filePtr = accessOutputFilePointer( GET_OUTPUT_FILE_PTR, 
                                                        DUMMY_OUTPUT_FILE_PTR );

        // check for open file
        if( filePtr != NULL )
           {
            // print endline to file
               // function: fprintf
            fprintf( filePtr, "%c", NEWLINE_CHAR );

            // return successful operation
            return true;
           }

        // file not open, return failed operation
        return false;
       }

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
    bool writeEndlinesToFile( int numEndlines )
       {
        // check for number of characters remaining,
        if( numEndlines > 0 )
           {
            // write endline, check for success 
               // function: writeEndlineTofile
            if( writeEndlineToFile() )
               {
                // continue recursion, 
                // check for downstream success
                   // function: writeEndlinesToFile
                return writeEndlinesToFile( numEndlines - 1 );
               }

            // quit recursion
            // return unsuccessful operation - write operation failed
            return false;
           }

        // return successful operation - all endlines have been written
        return true;
       }

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
    bool writeIntegerToFile( int outVal )
       {
        // initialize variables, set block size to zero and justified to "LEFT"
        int blockSize = 0;
        char justified[] = "LEFT";
       
        // call to justified function
           // function: writeDoubleJustifiedToFile
        return writeIntegerJustifiedToFile( outVal, blockSize, justified );
       }

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
                                                         const char *justified )
       {
        // initialize variables, create temporary output string
        char outStr[ MIN_STR_LEN ];

        // set integer to string
           // function: sprintf
        sprintf( outStr, "%d", outVal );

        // write as string, return result
           // function: writeStringJustified
        return writeStringJustifiedToFile( outStr, blockSize, justified );
       }

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
    bool writeStringToFile( const char *outString )
       {
        // initialize variables, set block size to zero and justified to "LEFT"
        int blockSize = 0;
        char justified[] = "LEFT";
     
        // call to justified function
           // function: writeStringJustifiedToFile
        return writeStringJustifiedToFile( outString, blockSize, justified );
       }

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
                                            int blockSize, const char *justify )
      {
       // initialize variables, set pre-, post- spaces to zero
       int preSpaces = 0, postSpaces = 0, strLength;

       // get file pointer
          // function: accessFileOutputFilePointer
       FILE *filePtr = accessOutputFilePointer( GET_OUTPUT_FILE_PTR, 
                                                        DUMMY_OUTPUT_FILE_PTR );

       if( filePtr != NULL )
          {
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

           // print pre spaces, check for success
              // function: writeCharactersToFile
           writeCharactersToFile( preSpaces, SPACE );
              
           // print string
              // function: fprintf
           fprintf( filePtr, "%s", outStr );

           // print post spaces
              // function: printChars
           writeCharactersToFile( postSpaces, SPACE );

           // return successful operation
           return true;
          }

       // return failed operation
       return false;
      }





