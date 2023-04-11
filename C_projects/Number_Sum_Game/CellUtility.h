#ifndef CELL_UTILITY_H
#define CELL_UTILITY_H

// included files
#include <stdbool.h>
#include <stdio.h>

// cell data structure
typedef struct CellDataStructure
   {
   	int dataValue;
   	 	
   	int xLocation, yLocation;
   } CellDataType;
   
// prototypes

/*
Name: cellsAreEqual
Process: returns true of data and location of two cells are equal
Function Input/Parameters: two cells (CellDataType)
Function Output/Parameters: none
Function Output/Returned: Boolean result of action
Device Input/---: none
Device Output/---: none
Dependencies: none
*/
int cellsAreEqual( const CellDataType one, const CellDataType other );

/*
Name: cellToSTring
Process: sets cell data to formatted string
Function Input/Parameters: cell (CellDataType)
Function Output/Parameters: pointer to string (char *)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: sprintf
*/
void cellToString( char *str, CellDataType cell );

/*
Name: copyCell
Process: copies one cell into another
Function Input/Parameters: source cell (CellDataType)
Function Output/Parameters: pointer to destination cell (CellDataType *)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: none
*/
void copyCell( CellDataType *dest, const CellDataType source );

/*
Name: setCellData
Process: sets cell data values
Function Input/Parameters: data, x & y locations (int)
Function Output/Parameters: pointer to cell (CellDataType *)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: none
*/
void setCellData( CellDataType *cell, int data, int xLoc, int yLoc );

/*
Name: setCellEmpty
Process: sets cell data values all to zero
Function Input/Parameters: none
Function Output/Parameters: pointer to cell (CellDataType *)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: setCellData
*/
void setCellEmpty( CellDataType *cell );

#endif  // CELL_UTILITY_H

