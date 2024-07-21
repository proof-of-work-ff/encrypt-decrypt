// This project is created by Michael Leverington
// header files
#include "project.h"
#include <ctype.h>

ControlCodes getUserChoice()
{
   char userInput;
   ControlCodes choice;

   // Prompt user for input
   printf("Choose an action:\n");
   printf("E: Encrypt\n");
   printf("D: Decrypt\n");
   printf("Enter your choice (E/D): ");
   scanf(" %c", &userInput); // Note the space before %c to consume any newline characters

   // Convert user input to uppercase
   char userResponse = toupper(userInput);

   // Validate user input
   if (userInput == 'E')
   {
      choice = ENCRYPT;
   }
   else if (userInput == 'D')
   {
      choice = DECRYPT;
   }
   else
   {
      printf("Invalid choice. Please enter 'E' for encryption or 'D' for decryption.\n");
      // Recursively call the function until a valid choice is made
      choice = getUserChoice();
   }

   return choice;
}

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
int getRandBetween(int lowVal, int highVal)
{
   return lowVal + rand() % (highVal + 1 - lowVal);
}

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
bool isInString(const char testStr[], char testChar)
{
   for (int j = 0; j < LOOKUP_COLUMNS; j++)
   {
      if (testStr[j] == testChar)
      {
         return true;
      }
   }

   return false;
}

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
int getLookupIndex(ControlCodes ctrl,
                   char lookupArray[][LOOKUP_COLUMNS], char searchChar)
{
   int i, j;

   switch (ctrl)
   {
   case GET_ROW_INDEX:
      for (i = 0; i < LOOKUP_ROWS; i++)
      {
         if (isInString(lookupArray[i], searchChar))
         {
            return i + 1;
         }
      }
      return 0;
   case GET_COLUMN_INDEX:
      i = getLookupIndex(GET_ROW_INDEX, lookupArray, searchChar) - 1;
      if (i < 0)
      {
         return 0;
      }

      for (j = 0; j < strlen(lookupArray[i]); j++)
      {
         if (lookupArray[i][j] == searchChar)
         {
            return j + 1;
         }
      }
   }

   return 0;
}

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
int encryptCharacter(char lookupArray[][LOOKUP_COLUMNS], char toEncrypt)
{
   return 100 * getRandBetween(1, 9) + 10 * getLookupIndex(GET_ROW_INDEX, lookupArray, toEncrypt) + getLookupIndex(GET_COLUMN_INDEX, lookupArray, toEncrypt);
}

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
int encryptData(char lookupArray[][LOOKUP_COLUMNS],
                int array[][ENCRYPTED_COLUMNS], const char encryptString[])
{
   int i, j, k;

   k = 0;
   for (i = 0; i < ENCRYPTED_ROWS && k < strlen(encryptString); i++)
   {
      for (j = 0; j < ENCRYPTED_COLUMNS && k < strlen(encryptString); j++)
      {
         array[i][j] = encryptCharacter(lookupArray, encryptString[k++]);
      }

      for (; j < ENCRYPTED_COLUMNS; j++)
      {
         array[i][j] = encryptCharacter(lookupArray, ' ');
      }
   }

   return i;
}

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
char decryptCharacter(char lookupArray[][LOOKUP_COLUMNS], int toDecrypt)
{
   return lookupArray[((toDecrypt / 10) % 10) - 1][(toDecrypt % 10) - 1];
}

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
void decryptData(char lookupArray[][LOOKUP_COLUMNS],
                 int array[][ENCRYPTED_COLUMNS], int numRows, char decryptStr[])
{
   int k = 0;
   for (int i = 0; i < numRows; i++)
   {
      for (int j = 0; j < ENCRYPTED_COLUMNS; j++)
      {
         decryptStr[k++] = decryptCharacter(lookupArray, array[i][j]);
      }
   }

   decryptStr[k] = '\0';
}

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
void downloadEncryptedFile(int array[][ENCRYPTED_COLUMNS],
                           int numRows, const char *fileName)
{
   char str[HUGE_STR_LEN];

   if (!openOutputFile(fileName))
   {
      return;
   }

   sprintf(str, "Number of Rows   : %d\n", numRows);
   writeStringToFile(str);
   sprintf(str, "Number of Columns: %d\n", ENCRYPTED_COLUMNS);
   writeStringToFile(str);
   writeEndlineToFile();

   for (int i = 0; i < numRows; i++)
   {
      writeIntegerJustifiedToFile(array[i][0], 1, "LEFT");
      for (int j = 1; j < ENCRYPTED_COLUMNS; j++)
      {
         writeStringToFile(", ");
         writeIntegerToFile(array[i][j]);
      }
      writeEndlineToFile();
   }
   writeEndlinesToFile(3);
   closeOutputFile();
}

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
int uploadEncryptedData(const char *fileName,
                        int array[][ENCRYPTED_COLUMNS])
{
   char str[HUGE_STR_LEN];
   int rows, cols;
   int i, j;

   if (!openInputFile(fileName))
   {
      return 0;
   }

   if (!readStringConfiguredFromFile(true, true, true, ':', str))
   {
      return 0;
   }

   if (NULL != strstr(str, "Number of Rows"))
   {
      rows = readLongFromFile();
   }

   if (!readStringConfiguredFromFile(true, true, true, ':', str))
   {
      return 0;
   }

   if (NULL != strstr(str, "Number of Columns"))
   {
      cols = readLongFromFile();
   }

   for (i = 0; i < rows && !checkForEndOfInputFile(); i++)
   {
      array[i][0] = readLongFromFile();
      for (j = 1; j < ENCRYPTED_COLUMNS; j++)
      {
         readStringConfiguredFromFile(true, true, true, ',', str);
         array[i][j] = readLongFromFile();
      }
   }

   closeInputFile();

   return i;
}

// main program
int main()
{
   // initialize function

   // initialize variables, function
   char encryptedFileName[STD_STR_LEN];
   char encryptString[HUGE_STR_LEN];
   char decryptedString[HUGE_STR_LEN];
   char downloadChoice;
   int numRows;
   ControlCodes encryptDecrypt;

   // seed random generator
   // function: srand
   srand(time(NULL));

   // initialize lookup array
   char lookupArray[LOOKUP_ROWS][LOOKUP_COLUMNS] = {{"&ABCDEF."},
                                                    {"*GHIJKL,"},
                                                    {"$MNOPQR?"},
                                                    {"!STUVWX:"},
                                                    {" YZabcd;"},
                                                    {"efghijk("},
                                                    {"lmnopqr)"},
                                                    {"stuvwxyz"}};

   // initialize data array
   int encryptedDataArray[ENCRYPTED_ROWS][ENCRYPTED_COLUMNS];

   // show title
   // function: printf
   printf("\nDATA ENCRYPTION PROGRAM\n");
   printf("=======================\n\n");

   // get input

   // get original choice, require correct response
   // function: getUserChoice
   encryptDecrypt = getUserChoice();

   // check for file request
   if (encryptDecrypt == DECRYPT)
   {
      // prompt for encrypted file name
      // function: promptForString
      promptForString("Enter encrypted file name: ", encryptedFileName);
   }

   // otherwise, assume user input of string
   else
   {
      // prompt for string to be encrypted
      // function: promptForString
      promptForString("Enter string to be encrypted: ", encryptString);
   }

   // combined processing

   // check for encrypt action
   if (encryptDecrypt == ENCRYPT)
   {
      // encrypt data
      // function: encryptData
      numRows = encryptData(lookupArray,
                            encryptedDataArray, encryptString);
   }

   // otherwise, assume decrypt
   else
   {
      // show uploading action
      // function: printf
      printf("\nUploading encrypted string from file . . .");

      // upload encrypted data
      // function: uploadEncryptedData
      numRows = uploadEncryptedData(encryptedFileName,
                                    encryptedDataArray);

      // show completing uploading action
      // function: printf
      printf("Upload complete.\n");

      // check for data available
      if (numRows > 0)
      {
         // decrypt the data found
         // function: decryptData
         decryptData(lookupArray,
                     encryptedDataArray, numRows, decryptedString);
      }
   }

   // output/display results

   // check for available data
   if (numRows > 0)
   {
      // check for encrypt action
      if (encryptDecrypt == ENCRYPT)
      {
         // prompt user for download
         // function: promptForCharacter
         downloadChoice = promptForCharacter(
             "\nDo you want to download this encrypted string (Y/N)? ");

         // check for user selection
         if (downloadChoice == 'y' || downloadChoice == 'Y')
         {
            // prompt for file name
            // function: promptForString
            promptForString("Enter file name: ", encryptedFileName);

            // display download operation
            // function: printf
            printf("\nDownloading encrypted string to file . . .");

            // download encrypted file
            // function: downloadEncryptedFile
            downloadEncryptedFile(encryptedDataArray,
                                  numRows, encryptedFileName);

            // display completed download operation
            // function: printf
            printf("Download complete.\n");
         }
      }

      // otherwise, assume decrypt action
      else
      {
         // display decrypted string
         // function: printf
         printf("The decrypted string is: %s\n", decryptedString);
      }
   }

   // otherwise, assume failed file access
   else
   {
      // print error message
      // function: printf
      printf("\nERROR: Program encryption/decryption failed, ");
      printf("program aborted\n");
   }

   // end program

   // show program end
   // function: printf
   printf("\nProgram End\n");

   // return successful program
   return 0;
}

// function implementation
