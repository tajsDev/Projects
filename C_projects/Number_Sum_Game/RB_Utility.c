// included headers
#include "RB_Utility.h"

/*
Name: displayStatus
Process: displays appropriately indented report of next attempt
         to place value, with ControlCodes as follows:
         VALID_ITEM, INVALID_ITEM, DUPLICATE_ITEM, OVER_SUM,
         OUT_OF_BOUNDS, TEST_LOCATION, and NO_SOLUTION
Function Input/Parameters: recursion level for indentation (int),
                           status string reporting action (const char *),
                           cell data being tested (CellDataType),
                           control code for reporting (ControlCode),
                           verbose flag turns reporting on or off (bool)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/---: none
Device Output/monitor: status of cell attempt
Dependencies: printf, cellToString
*/
void displayStatus( int recLevel, const char *status, CellDataType current,
                                      ControlCodes opSuccess, bool verboseFlag )
   {
    int index, recLevelIndent = recLevel * REC_LEVEL_INDENT;
    char tempStr[ STD_STR_LEN ];

    if( verboseFlag )
       {
        for( index = 0; index < recLevelIndent; index++ )
           {
            printf( "%c", SPACE );
           }
     
        printf( "%s", status );
     
        if( opSuccess == TEST_LOCATION )
           {
            printf( "(%d, %d)\n", current.xLocation, current.yLocation );
           }
         
        else if( opSuccess == OUT_OF_BOUNDS )
           {
            printf( "Location Not Found\n" );
           }
     
        else if( opSuccess == VALID_ITEM )
           {
            cellToString( tempStr, current );
            printf( "%s\n", tempStr );
           }
         
        else if( opSuccess == NO_SOLUTION )
           {
            printf( "Doesn't Support Solution\n" );
           }

        else if( opSuccess == DUPLICATE_ITEM )
           {
            printf( "Already In Set\n" );
           }
         
        else if( opSuccess == OVER_SUM )
           {
            printf( "Over Requested Sum\n" );
           }
       }
   }

/*
Name: dumpArray
Process: simple 2D array dump of array data
Function Input/Parameters: array data (ArrayType), title (const char *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/---: none
Device Output/monitor: display of 2D array
Dependencies: printf
*/
void dumpArray( const char *title, const ArrayType dispArray )
   {
    int rowIndex, colIndex;

    printf( "\n%s\n", title );

    for( rowIndex = 0; rowIndex < dispArray.rowSize; rowIndex++ )
       {
        for( colIndex = 0; colIndex < dispArray.colSize; colIndex++ )
           {
            if( colIndex > 0 )
               {
                printf( ", " );

               }
          
            printf( "%5d", dispArray.array[ rowIndex ][ colIndex ] );
           }
      
        printf( "\n" );
       }

    printf( "\n" );
   }

/*
Name: findSum
Process: Calls helper to find contiguous values
         adding to a specified number in an array

         Note: Displays success or failed results

         Rules of the searching process:

         - The search starts in the upper left corner, 
           reporting each valid location found. 
           The solution must start from a location in the top row
           and end in a location in the bottom row

         - The method must search to a current location's right,
           then below it, and then to its left, exactly in that order

         - The method must report what it finds, 
           either as a successful candidate value
           or a failed candidate value, and why it failed

         - The method must use recursive backtracking,
           it must backtrack the recursion upon any failure,
           but it must continue forward recursion upon any success
           until the solution is found

         - The method must be able to handle the condition
           that the value in the upper left corner does not support the solution 

Function Input/Parameters: data array (ArrayType),
                           value to sum up to (int), 
                           verbose flag controls description(bool)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/---: none
Device Output/monitor: display of process
Dependencies: initializeSet, printf, findSumHelper, displaySet

  */
void findSum( const ArrayType dataArray, int sumRequest, bool verbose )
    {
     int startingXIndex = 0, startingYIndex = 0;
     int startingTotal = 0, startingRecLevel = 0;
     int iterationCount = 0;
     int index, testSum = 0;
     SetType foundSet;

     initializeSet( &foundSet );
     
     printf( "Search for sum %d, start: \n\n", sumRequest );

     if( findSumHelper( sumRequest, startingTotal,
                        startingXIndex, startingYIndex, 
                        &foundSet, dataArray,
                        startingRecLevel, &iterationCount, verbose ) )
        {
         displaySet( "\nSearch End => Successful Set:", foundSet );

         for( index = 0; index < foundSet.size; index++ )
            {
             testSum += foundSet.setArray[ index ].dataValue;
            }

         printf( "\nSum Verified   : %d\n", testSum );

         printf( "\nIteration Count: %d\n", iterationCount );
        }
     
     else
       {
        printf( "\nSearch End => Solution Not Found\n" );

        printf( "\nIteration Count: %d\n", iterationCount );
       }  
    }
 
/*
Name: findSumHelper
Process: specifications in calling function
Function Input/Parameters: sum value result requested (int),
                           starting and then working total (int),
                           starting x and y indices (int),
                           pointer toresulting set (SetType *), 
                           data array (const ArrayType)
                           starting and then working recursion level (int),
                           pointer to iteration count (int *)
                           verbose flag (bool)
Function Output/Parameters: pointer to iteration count to be returned (int *)
Function Output/Returned: result of given attempt (bool)
Device Input/---: none
Device Output/monitor: operation of recursive backtracking
Dependencies: setCellData, displayStatus, isInBounds, isInSet, 
              addItem, findSumHelper (recursive),
              other functions in this file are allowed,
              Note: displayStatus is used exclusively, 
              no other printing functions are allowed
*/
bool findSumHelper( int sumRequest, int runningTotal,
                    int xIndex, int yIndex, 
                    SetType *foundSet, const ArrayType dataArray,
                    int recLevel, int *iterationCount, 
                    bool verbose )
   {
	 //intinalzie vars
	 char status[STD_STR_LEN] ;
	 CellDataType current ; 
		
		recLevel++; 
		
	 // update iteration count
		*iterationCount = *iterationCount +1 ; 
		
    // find working value
		//display status of location
		setCellData( &current , 
		dataArray.array[xIndex][yIndex], xIndex, yIndex);
		sprintf(status,"Trying Location: ");
			displayStatus( recLevel, status,  current,
					TEST_LOCATION,  verbose ) ;
		
       // check for not in bounds
		if (!isInBounds(  dataArray, xIndex, yIndex ))
		{
			sprintf(status, "Location failed: "); 
          // report failure, return false
			displayStatus( recLevel, status,  current,
					OUT_OF_BOUNDS,  verbose );
		 //return false
		 return false ; 
		}
	
		 
       // add the value to runningTotal
			runningTotal+= dataArray.array[xIndex][yIndex] ; 
       // check for over the sumRequest
		if( runningTotal > sumRequest) 
		{
			
			sprintf(status, "Location failed: ");  
          // report failure, return false
			displayStatus( recLevel, status,  current,
					OVER_SUM,  verbose );
			return false ;
		}
       // add the item, check for failure
		if(!addItem( foundSet, current ))
		{
			sprintf(status, "Location failed: ");  
          // report failure, return false
			displayStatus( recLevel, status,  current,
					DUPLICATE_ITEM,  verbose );
			return false ;
  
		}
		sprintf(status, "Valid Location found:"); 
       // report valid item
		displayStatus( recLevel, status,  current,
					VALID_ITEM,  verbose);
       // check for at sumRequest 
		if( runningTotal == sumRequest)
		{
           // check for at bottom row
			if( xIndex == dataArray.rowSize - 1 )
			{
              // return true
				return true ; 
			}
           // remove from set
			 deleteItem(foundSet , current);
			sprintf(status, "Location failed: "); 
           // report failure, return false
			displayStatus( recLevel, status,  current,
					NO_SOLUTION,  verbose ) ;
			return false ; 
		}
		
////////////////////////////////////////////////////// I have a valid item

    // recurse
			

       // check for success to the right
		if(findSumHelper( sumRequest,runningTotal,
                        xIndex, yIndex+1, 
                        foundSet, dataArray,
                        recLevel, iterationCount, verbose ))
		{
			
			sprintf(status, "Valid Location found:"); 
			// report valid item
			displayStatus( recLevel, status,  current,
					VALID_ITEM,  verbose);
          // return true  
		  return true ; 
		}
       // check for success down
		if(findSumHelper( sumRequest,runningTotal,
                        xIndex+1, yIndex, 
                        foundSet, dataArray,
                        recLevel, iterationCount, verbose ))
		{
			
          // report found
			sprintf(status, "Valid Location found:"); 
       // report valid item
			displayStatus( recLevel, status,  current,
					VALID_ITEM,  verbose);
          // return true  
		  return true ;
		}
       // check for success to the left
		if(findSumHelper( sumRequest,runningTotal,
                        xIndex, yIndex-1, 
                        foundSet, dataArray,
                        recLevel, iterationCount, verbose ))
		{
			
          // report found
			sprintf(status, "Valid Location found:"); 
       // report valid item
			displayStatus( recLevel, status,  current,
					VALID_ITEM,  verbose);
          // return true 
			return true ; 
		}
///////////////////////////////////////////////// value not a contributor

    // clean up and quit
		 
       // remove the cell from the set
		deleteItem( foundSet,  current ) ; 
		
       // check for recLevel zero AND not off the right end
		if(recLevel == 1 && yIndex < dataArray.colSize )
		{
          // reset everything
			runningTotal = 0;
			recLevel = 0 ; 
			// start over with recursion to the next one over
			findSumHelper( sumRequest,runningTotal,
                        xIndex, yIndex+1, 
                        foundSet, dataArray,
                        recLevel, iterationCount, verbose );
			return false ; 
			
		}
          
		  

		sprintf(status, "Location failed: ");   
           // report failure, return false
			displayStatus( recLevel, status,  current,
					NO_SOLUTION,  verbose ) ;
	
    // return false		
    return false;  
   }
 
/*
Name: isInBounds
Process: tests x and y locations for in array bounds
Function Input/Parameters: x & y locations (int),
                           data array (ArrayType)
Function Output/Parameters: none
Function Output/Returned: result of test (bool)
Device Input/---: none
Device Output/---: none
Dependencies: none
*/
bool isInBounds( ArrayType dataArray, int xLocTest, int yLocTest )
   {
    bool rowTest = xLocTest >= 0 && xLocTest < dataArray.colSize;
    bool colTest = yLocTest >= 0 && yLocTest < dataArray.rowSize;
     
    return rowTest && colTest;
   }
 
