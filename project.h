#ifndef PROJECT_8_H
#define PROJECT_8_H

// header files
#include "StandardConstants.h"
#include "Console_IO_Utility.h"
#include "File_Input_Utility.h"
#include "File_Output_Utility.h"
#include <stdlib.h>  // for srand, rand
#include <time.h>  // for srand

// constants

typedef enum { LOOKUP_ROWS = 8, LOOKUP_COLUMNS = 8, 
                  ENCRYPTED_COLUMNS = 5, ENCRYPTED_ROWS = 50 } ArrayCapacities;
typedef enum { FIRST_MULTIPLIER_DIGIT = 10, 
                                      SECOND_MULTIPLIER_DIGIT = 100 } DigitType;
typedef enum { DECRYPT, ENCRYPT, GET_ROW_INDEX, GET_COLUMN_INDEX } ControlCodes;
typedef enum { LOW_SINGLE_DIGIT = 0, HIGH_SINGLE_DIGIT = 7 } DigitLimits;

// prototypes

/*
Name: decryptCharacter
process: translates integer value to character, using look up table,
         first digit is random, second digit is row index,
         third digit is column index
Function input/parameters: look up array (char [][]), 
                           value to be decyrypted (int)
Function output/parameters: none
Function output/returned: decrypted character (char)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
char decryptCharacter( char lookupArray[][ LOOKUP_COLUMNS ], int toDecrypt );

/*
Name: decryptdata
process: iterates through encrypted array of integers,
         translates all to characters
Function input/parameters: look up array (char [][]), 
                           integer array with encrypted values (int [][]),
                           number of rows (int)
Function output/parameters: decrypted string (char [])
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: decryptCharacter
*/
void decryptData( char lookupArray[][ LOOKUP_COLUMNS ],
             int array[][ ENCRYPTED_COLUMNS ], int numRows, char decryptStr[] );

/*
Name: downloadEncryptedFile
process: opens file for download, 
         downloads number of rows and columns with leader text,
         downloads the integer array in formatted structure,
         assumes ENCRYPTED_COLUMNS number of columns
         then closes file
Function input/parameters: array to be downloaded (int [][]),
                           number of rows (int),
                           file name (const char *)
Function output/parameters: none
Function output/returned: none
Device input/file: none
Device output/file: data output to file as specified
Dependencies: File Output utilities, sprintf
*/
void downloadEncryptedFile( int array[][ ENCRYPTED_COLUMNS ], 
                                            int numRows, const char *fileName );

/*
Name: encryptCharacter
process: encrypts character using look up table,
         first digit is random, 
         second digit is the row number of the character 
         found in the lookup array,
         third digit is the column number of the character 
         found in the lookup array
Function input/parameters: look up array (char [][]), 
                           value to be encyrypted (char)
Function output/parameters: none
Function output/returned: encrypted value (int)
Device input/file: none
Device output/monitor: none
Dependencies: getLookupIndex, getRandBetween
*/
int encryptCharacter( char lookupArray[][ LOOKUP_COLUMNS ], char toEncrypt );

/*
Name: encryptData
process: encrypts given string as a series of 2- or 3- digit integers,
         if string characters do not fill out a row in the array,
         spaces are added as encrypted values to fill out the row
Function input/parameters: look up array (char [][]), 
                           string to be encrypted (const char [])
Function output/parameters: array to which encrypted data is loaded (int [][])
Function output/returned: number of rows used in array (int)
Device input/file: none
Device output/monitor: none
Dependencies: encryptCharacter
*/
int encryptData( char lookupArray[][ LOOKUP_COLUMNS ],
                 int array[][ ENCRYPTED_COLUMNS ], const char encryptString[] );

/*
Name: getLookupIndex
process: finds either row or column index of character in lookup array,
         returns appropriate index or zero if the character is not found
         in the array
Function input/parameters: control code (ControlCodes), 
                           look up array (char [][]), 
                           search character (char)
Function output/parameters: none
Function output/returned: row or column index as specified
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
int getLookupIndex( ControlCodes ctrl, 
                        char lookupArray[][ LOOKUP_COLUMNS ], char searchChar );

/*
Name: getRandBetween
process: calculates a random number between low and high limits, inclusive
Function input/parameters: low and high limits (int)
Function output/parameters: none
Function output/returned: random value generated (int)
Device input/file: none
Device output/monitor: none
Dependencies: rand
*/
int getRandBetween( int lowVal, int highVal );

/*
Name: getUserChoices
process: prompts user for choice of operations: encrypt or decrypt,
         processes answer and returns control code (ENCRYPT, DECRYPT)
         as appropriate,
         repeats prompt if incorrect user response
Function input/parameters: none
Function output/parameters: none
Function output/returned: encrypt or decrypt control code as specified
                          (ControlCodes)
Device input/file: none
Device output/monitor: none
Dependencies: Console I/O tools, isInString
*/
ControlCodes getUserChoice();

/*
Name: isInString
process: accepts a list of characters and one test character,
         reports if test character is in the given list
Function input/parameters: test string (const char []), test character (char)
Function output/parameters: none
Function output/returned: result of specified test (bool)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
bool isInString( const char testStr[], char testChar );

/*
Name: uploadEncryptedData
process: opens file for input, acquires row and column limits,
         then uploads all integers thereafter placing them into an array,
         then closes file and returns number of rows found,
         assumes ENCRYPTED_COLUMNS number of columns
Function input/parameters: file name (const char *)
Function output/parameters: array to which data is loaded (int [][])
Function output/returned: number of rows found in file
Device input/file: data input from file as specified
Device output/monitor: none
Dependencies: File I/O utilities 
*/
int uploadEncryptedData( const char *fileName, 
                                             int array[][ ENCRYPTED_COLUMNS ] );

#endif   //  PROJECT_8_H


