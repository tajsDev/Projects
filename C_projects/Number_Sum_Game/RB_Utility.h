#ifndef RB_UTILITY_H
#define RB_UTILITY_H

// included headers
#include "StandardConstants.h"
#include "SetUtilitiesFour.h"

// local constants
typedef enum { REC_LEVEL_INDENT = 3, MAX_ROWS = 10, MAX_COLS = 10 } OperationalData;
typedef enum { VALID_ITEM = 101, INVALID_ITEM = 102, 
               DUPLICATE_ITEM, OVER_SUM, 
               OUT_OF_BOUNDS, TEST_LOCATION, NO_SOLUTION } ControlCodes;

// data structure for array
typedef struct ArrayStruct
   {
    int array[ MAX_ROWS ][ MAX_COLS ];

    int rowSize, colSize;    
   } ArrayType;

// prototypes

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
                                      ControlCodes opSuccess, bool verboseFlag );

/*
Name: dumpArray
Process: simple 2D array dump of array data
Function Input/Parameters: title (const char *)array data (ArrayType)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/---: none
Device Output/monitor: display of 2D array
Dependencies: printf
*/
void dumpArray( const char *title, const ArrayType dispArray );

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
void findSum( const ArrayType dataArray, int sumRequest, bool verbose );
 
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
                    bool verbose );
 
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
bool isInBounds( ArrayType dataArray, int xLocTest, int yLocTest );

#endif  // RB_UTILITY_H
