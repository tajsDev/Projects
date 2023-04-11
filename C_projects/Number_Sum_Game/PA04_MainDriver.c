// included headers
#include "StandardConstants.h"
#include "File_Input_Utility.h"
#include "Console_IO_Utility.h"
#include "RB_Utility.h"

// prototypes
bool uploadData( const char *fileName, ArrayType *dataArray );

int main()
   {
    // initialize program

       // initialize variables
       int testValue = 896;
       ArrayType dataArray;
       bool verboseFlag = true;
       char fileName[ STD_STR_LEN ];

       // title
       printf( "\nNumber Path Game\n" );
       printf(   "================\n\n");

    // get file name
    promptForString( "Enter file name         : ", fileName ); 

    // get desired number
    testValue = promptForInteger( "Enter desired sum value : " );
   
    // get data
    if( uploadData( fileName, &dataArray ) )
       {
        dumpArray( "Input Verification Array Dump:", dataArray );

        findSum( dataArray, testValue, verboseFlag );
       }

    else
       {
        printf( "Data File Access Failed - Program Aborted\n" );
       }

    // end program

       // display end program
          // function: printf
       printf( "\nEnd Program\n");
   }
    
/*
Name: uploadData
Process: opens file, gets array sizes, uploads array, closes file
Function Input/Parameters: file name (const char *)
Function Output/Parameters: data array (ArrayType)
Function Output/Returned: operation success (bool)
Device Input/HD: data input from file
Device Output/---: none
Dependencies: File_Input_Utility tools
*/
bool uploadData( const char *fileName, ArrayType *dataArray )
   {
    int rowIndex, colIndex;
    char tempStr[ STD_STR_LEN ];
     
    // Open file, test for success
    if( openInputFile( fileName ) )
       {
        // get leader line ahead of array height
        readStringToDelimiterFromFile( COLON, tempStr );
        
        // get row height
        dataArray->rowSize = readIntegerFromFile();
         
        // get leader line ahead of array width
        readStringToDelimiterFromFile( COLON, tempStr );
        
        // get row width
        dataArray->colSize = readIntegerFromFile();
         
        for( rowIndex = 0; rowIndex < dataArray->rowSize; rowIndex++ )
           {                
            for( colIndex = 0; colIndex < dataArray->colSize; colIndex++ )
               {
                dataArray->array[ rowIndex ][ colIndex ] 
                                           = readIntegerFromFile();
               }
           }

        closeInputFile();

        return true;
       }
   
    return false;
   }
