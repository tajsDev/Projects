// header files
#include "project_8.h"

// main program
int main()
   {
    // initialize function

       // initialize variables, function
       char encryptedFileName[ STD_STR_LEN ];
       char encryptString[ HUGE_STR_LEN ];
       char decryptedString[ HUGE_STR_LEN ];
       char downloadChoice;
       int numRows;
       ControlCodes encryptDecrypt;

       // seed random generator
          // function: srand
       srand( time( NULL ) );

       // initialize lookup array
       char lookupArray[ LOOKUP_ROWS ][ LOOKUP_COLUMNS ] = { { "&ABCDEF." },
                                                             { "*GHIJKL," },
                                                             { "$MNOPQR?" },
                                                             { "!STUVWX:" },
                                                             { " YZabcd;" },
                                                             { "efghijk(" },
                                                             { "lmnopqr)" },
                                                             { "stuvwxyz" } };

       // initialize data array
       int encryptedDataArray[ ENCRYPTED_ROWS ][ ENCRYPTED_COLUMNS ];

       // show title
          // function: printf
       printf( "\nDATA ENCRYPTION PROGRAM\n" );
       printf( "=======================\n\n" );

    // get input

       // get original choice, require correct response
          // function: getUserChoice
       encryptDecrypt = getUserChoice() ;

       // check for file request
       if( encryptDecrypt == DECRYPT )
          {
           // prompt for encrypted file name
              // function: promptForString
           promptForString( "Enter encrypted file name: ", encryptedFileName );
          }

       // otherwise, assume user input of string
       else
          {
           // prompt for string to be encrypted
              // function: promptForString
           promptForString( "Enter string to be encrypted: ", encryptString );
          }

    // combined processing

       // check for encrypt action
       if( encryptDecrypt == ENCRYPT )
          {
           // encrypt data
              // function: encryptData
           numRows = encryptData( lookupArray, 
                                            encryptedDataArray, encryptString );
          }

       // otherwise, assume decrypt
       else
          {
           // show uploading action
              // function: printf
           printf( "\nUploading encrypted string from file . . ." );

           // upload encrypted data
              // function: uploadEncryptedData
           numRows = uploadEncryptedData( encryptedFileName, 
                                                           encryptedDataArray );

           // show completing uploading action
              // function: printf
           printf( "Upload complete.\n" );

           // check for data available
           if( numRows > 0 )
              {
               // decrypt the data found
                  // function: decryptData
               decryptData( lookupArray, 
                                 encryptedDataArray, numRows, decryptedString );
              }
          }

    // output/display results

       // check for available data
       if( numRows > 0 )
          {
           // check for encrypt action
           if( encryptDecrypt == ENCRYPT )
              {
               // prompt user for download
                  // function: promptForCharacter
               downloadChoice = promptForCharacter( 
                      "\nDo you want to download this encrypted string (Y/N)? " );
           
               // check for user selection
               if( downloadChoice == 'y' || downloadChoice == 'Y' )
                  {
                   // prompt for file name
                      // function: promptForString
                   promptForString( "Enter file name: ", encryptedFileName );

                   // display download operation
                      // function: printf
                   printf( "\nDownloading encrypted string to file . . ." );

                   // download encrypted file
                      // function: downloadEncryptedFile
                   downloadEncryptedFile( encryptedDataArray, 
                                                   numRows, encryptedFileName );

                   // display completed download operation
                      // function: printf
                   printf( "Download complete.\n" );
                  }
              }

           // otherwise, assume decrypt action
           else
              {
               // display decrypted string
                  // function: printf
               printf( "The decrypted string is: %s\n", decryptedString );
              }  
          }

       // otherwise, assume failed file access
       else
          {
           // print error message
             // function: printf
           printf( "\nERROR: Program encryption/decryption failed, " );
           printf( "program aborted\n" );
          }
       
    // end program

       // show program end
          // function: printf
       printf( "\nProgram End\n" );

       // return successful program
       return 0;
   }

// function implementation
ControlCodes getUserChoice()
{
	//intilize vars and functions
	
	char input ; 
	
	//process data
	
	//prime input char 
		//function:promptForCharacter
	input = promptForCharacter("Operation: <D>ecrypt or <E>ncrypt? ");
	//create while loop for character
	while(!isInString("dDeE",input))
	{
		//reprime char
			//function:promptForCharacter
		input = promptForCharacter("Operation: <D>ecrypt or <E>ncrypt? ");
	 

	}


	//if statement for encrypt
	if (isInString("eE",input))
	{
		//return ENCRYPT
		return ENCRYPT ;
	}
	//return decryt as default 
	return DECRYPT ;
}
bool isInString( const char testStr[], char testChar )
{
	//intialize vars and functions
	int count ;

	//prime count
	count = 0 ;
	//process data
	
	//while not end of string
	while(testStr[count] != NULL_CHAR )
	{
		//if string char is  test char
		if (testStr[count] == testChar)
		{
			//return true 
			return true;
		}
		//reprime
		count++ ; 
		
	}
	//return results
	return false ;
	
}
int getRandBetween( int lowVal, int highVal )
{
	//intialize vars and functions
	int range ;
	//process data
	
	//get digits of random
	range = highVal - lowVal +1;
	

	//return random reminder of range and add lowest value 
	return rand() % range + lowVal ; 
}
int getLookupIndex( ControlCodes ctrl, 
                        char lookupArray[][ LOOKUP_COLUMNS ], char searchChar )
{
	//intilaze vars and fucntions
	int rowCount, columnCount;
	//proccess data
	//create loop for columns
	for (columnCount = 0 ; columnCount < 8 ; columnCount++)
	{
		//create loop for rows
		for(rowCount = 0 ; rowCount < 8 ; rowCount++)
		{
			//if array index match the character
			if (lookupArray[rowCount][columnCount] == searchChar)
			{
				//if ctrl needs row index
				if (ctrl == GET_ROW_INDEX) 
				{
					//return row index
					return rowCount ;
				}
				else
				{
					//return column index 
					return columnCount ; 
				}
			}
			
		}
	}
	//stub return 
	return 0 ;
	
	
	
}
char decryptCharacter( char lookupArray[][ LOOKUP_COLUMNS ], int toDecrypt )
{
	//intialize vars and function
	int columnAndRow,row,column ;
	//process data
	//get row and column 
	columnAndRow = toDecrypt % 100 ;
	//get row 
	column = toDecrypt % 10 ;
	//remove row from column and row and divide column by 10
	row = ( columnAndRow - column ) / 10 ;
	
	//return results 
	return lookupArray[row][column] ; 
	
}
int uploadEncryptedData( const char *fileName, 
                                             int array[][ ENCRYPTED_COLUMNS ] )
{
		//intailize vars and functions
		int countColumn,countRow,integer;
		char rowLine[STD_STR_LEN],delimiter;
		//process data
		

		//set delimiter
		delimiter = ':' ;
		//set count of rows to zero
		countRow = 0 ;
		
		//if file opens
		if(openInputFile(fileName))
		{
			//read row line up to string part
				//function:readStringToDelimiterFromFile
			readStringToDelimiterFromFile(  delimiter, rowLine ) ; 
			//read integer from row ling
				//function:readIntegerFromFile
			integer = readIntegerFromFile() ;
			//read row line up to string part
				//function:readStringToDelimiterFromFile
			readStringToDelimiterFromFile(  delimiter, rowLine );
			//read integer from row ling
				//function:readIntegerFromFile
			integer = readIntegerFromFile() ;
		
			//prime integer
				//function:readIntegerFromFile
			integer = readIntegerFromFile() ;
			//zero column 
			countColumn = 0 ;
			//create while loop so that the file does not end
			while(!checkForEndOfInputFile())
			{

				//if integer is not a single zero
				if (integer != 0)
				{
					//set array current index to integer
					array[countRow][countColumn] = integer ;

				}
				

				//add to column 
				 countColumn++ ; 
				 
				//reprime integer
					//function:readIntegerFromFile
				integer = readIntegerFromFile() ;
			//skip over comma 
				//function:readCharacterFromFile
				readCharacterFromFile() ; 
				
				//if columns has reached max
				if(countColumn == ENCRYPTED_COLUMNS )
				{
					//reset column
					countColumn = 0 ;
					//add to row
					countRow++ ;
					
				}
			}
			
			//close input file
				//function:closeInputFile
			closeInputFile() ;
		}
		//return results
	return countRow ;
}
void downloadEncryptedFile( int array[][ ENCRYPTED_COLUMNS ], 
                                            int numRows, const char *fileName )
{
	//intialize vars and functions 
	int cCol,cRow,index ;
	int blockSize = 3; 
	int lessThan = 100 ;
	char outStr[STD_STR_LEN] ;
	//process data
	
	//open output file
		//function:openOutputFile
	openOutputFile(fileName) ;
	//fomrat rows string 
		//function :sprintf
	sprintf(outStr,"Number of Rows   : %d",numRows);
	//add string of number of rows
		//function: writeStringToFile 
	writeStringToFile(outStr) ;
	//write endline to file
		//function : writeEndlineToFile 
	writeEndlineToFile() ;
	//fomrat columns string 
		//function :sprintf
	sprintf(outStr,"Number of Columns: %d",ENCRYPTED_COLUMNS);
	
	//add string of number of columns
		//function: writeStringToFile 
	writeStringToFile(outStr) ;
	
	//write endline to file
		//function : writeEndlineToFile 
	writeEndlineToFile() ;
	//write endline to file
		//function : writeEndlineToFile 
	writeEndlineToFile() ;
	
	//create a for loop for the rows
	for (cRow = 0 ;cRow < numRows ; cRow++)
	{
	//create a for loop for the columns
		for(cCol = 0 ; cCol < ENCRYPTED_COLUMNS ; cCol++)
		{
			//write space to file 
				//function:writeCharacterToFile
			writeCharacterToFile(SPACE);
			//set array index 
			index = array[cRow][cCol] ;
			//if index is less than 100
			if (index < lessThan )
			{
				//add zero to file
					//function: writeIntegerToFile
				writeIntegerToFile( LOW_SINGLE_DIGIT ) ;	
			}
			//add integer to file
				//function: writeIntegerToFile
			writeIntegerJustifiedToFile( index,blockSize,"RIGHT") ;
			//if column not at limit
			if (cCol != ENCRYPTED_COLUMNS - 1)
			{
				//write comma to file 
					//function: writeStringToFile
				writeCharacterToFile(COMMA);
				writeCharacterToFile(SPACE); 
			}
		}
		//write endline to file
			//function : writeEndlineToFile 
		writeEndlineToFile() ;
	}

	//close output file 
		//function: closeOutputFile 
		closeOutputFile() ;
	
	
}
int encryptCharacter( char lookupArray[][ LOOKUP_COLUMNS ], char toEncrypt )
{
	//intialize vars and functions
	ControlCodes ctrl ;
	int row,column, randNum,rowMuti,randMuti;
	//set ctrl to get row
	ctrl = GET_ROW_INDEX ;
	//get row
		//function:getLookupIndex
	row= getLookupIndex( ctrl, lookupArray, toEncrypt ) ;
	//set ctrl to get column
	ctrl = GET_COLUMN_INDEX ;
	//get column
		//function:getLookupIndex
	column= getLookupIndex( ctrl, lookupArray, toEncrypt ) ;
	//get the random number
		//function:getRandBetween
	randNum= getRandBetween( LOW_SINGLE_DIGIT, HIGH_SINGLE_DIGIT ) ;
	//get column mutiplied
	rowMuti = row * FIRST_MULTIPLIER_DIGIT ;
	//get random mutiplied
	randMuti = randNum * SECOND_MULTIPLIER_DIGIT ;
	
	//return integer
	return randMuti + rowMuti + column ; 
	
		
}
int encryptData( char lookupArray[][ LOOKUP_COLUMNS ],
                 int array[][ ENCRYPTED_COLUMNS ], const char encryptString[] )
{
	//intialize vars and functions
	int rowInd,columnInd,value,encVal;
	char stringInd ; 
	//process data
	
	//set value to zero
	
	//prime
	columnInd = 0 ;
	value= 0 ;
	//set row to zero
	rowInd = 0 ;
	
	//while loop for end of string
	while (encryptString[value] != NULL_CHAR)
	{

		//get string index
		stringInd = encryptString[value] ;
		//encrypt Character
			//function : encryptCharacter
		encVal = encryptCharacter(lookupArray,stringInd) ;
		//set new value to array
		array[rowInd][columnInd] = encVal ;
		//if column as reached 5 

		//reprime
		columnInd++ ;
		//add to value or length of string 
		value++ ;
		//if columns has reached limit 
		if (columnInd == ENCRYPTED_COLUMNS) 
		{
			//start new row
			rowInd++ ;
			//set column to zero
			columnInd = 0 ;
		}
	}
	//see if there is extra stops 
	
	//string length not divisible by column limit
	while(value % ENCRYPTED_COLUMNS!=0)
	{
		//set character as space
		stringInd = SPACE;
		//encrypt Character
			//function : encryptCharacter
		encVal = encryptCharacter(lookupArray,stringInd) ;
		//add to array 
		array[rowInd][columnInd] = encVal ;
		//reprime
		value++ ;
		//add to column 
		columnInd++ ;
	}
	
	//return rows
	return rowInd + 1; 
}
void decryptData( char lookupArray[][ LOOKUP_COLUMNS ],
             int array[][ ENCRYPTED_COLUMNS ], int numRows, char decryptStr[] )
{
	//intialize vars and functions
	int toDecrypt,iterCol,iterRow,value ;
	char arrayChar ; 
	//process data
	//set index to zero
	value = 0 ; 
	//set index of array to zero
	iterRow = 0 ;
	iterCol = 0 ;
	while (value != numRows*ENCRYPTED_COLUMNS)
	{

			//set index of array 
			toDecrypt = array[iterRow][iterCol] ; 
			
			//decrypts character
				//function: decryptCharacter
			arrayChar = decryptCharacter( lookupArray, toDecrypt );
			

				//add character to string 
			decryptStr[value] = arrayChar ;
				
			//add index value
			value++ ;
			//add column val
			iterCol++ ;
		//if column has reached limit 
			if (iterCol == ENCRYPTED_COLUMNS )
			{
				//add to row
				iterRow ++ ; 
				//set column to zero 
				iterCol = 0 ;
			}
	}	
		
	
	


	
	
}