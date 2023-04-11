#ifndef SET_UTILITIES_H
#define SET_UTILITIES_H

// headers/libraries
#include <stdlib.h>
#include <stdbool.h>
#include "StandardConstants.h"
#include "CellUtility.h"

// derived data types
typedef enum { INCREMENTED = 101, ODD, EVEN, RANDOM } DataSelections;
typedef enum { MAX_SET_CAPACITY = 100, 
                                   MAX_INIT_SET_CAPACITY = 50 } ArrayCapacities;
typedef enum { THREE_DIGIT_LOW = 100, THREE_DIGIT_HIGH = 999 } RandomLimits;

typedef struct SetStruct
   {
    CellDataType setArray[ MAX_SET_CAPACITY ];

    int capacity;

    int size;
   } SetType;

// prototypes

/*
Name: addItem
Process: adds cell item to set, does not allow duplicates,
         does not allow data to be added to full list,
         returns true if successful, false otherwise
Function Input/Parameters: new item (CellDataType)
Function Output/Parameters: pointer to set data (SetType *)
Function Output/Returned: Boolean result of action
Device Input/---: none
Device Output/---: none
Dependencies: isInSet, copyCell
*/
bool addItem( SetType *setData, CellDataType newValue );

/*
Name: copySet
Process: copies all data of one set into other
Function Input/Parameters: source set (const SetType)
Function Output/Parameters: pointer to destination set (SetType)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: copyCell
*/
void copySet( SetType dest, const SetType source );

/*
Name: deleteItem
Process: searches for cell item, deletes if found,
         moves array data down by one from above the removed value,
         test loop must stop as soon as item is found (if it is found),
         returns true if item found and removed, false otherwise
Function Input/Parameters: item to delete (CellDataType)
Function Output/Parameters: pointer to setData (SetType *) 
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: cellsAreEqual
*/
bool deleteItem( SetType *setData, CellDataType itemToDelete );

/*
Name: displaySet
Process: displays series of set values, or displays "Empty Set" if no values
Function Input/Parameters: name of set array (const char *),
                           set data (CellDataType)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/---: none
Device Output/monitor: data displayed as specified
Dependencies: printf, cellToString
*/
void displaySet( const char *setName, const SetType setData );

/*
Name: initializeSet
Process: initializes empty set for use
Function Input/Parameters: pointer to set (SetType *)
Function Output/Parameters: pointer to set (SetType *)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: none
*/
void initializeSet( SetType *set );

/*
Name: isInSet
Process: searches for given value in set,
         if found, returns true, otherwise returns false,
         must return found result immediately upon finding value
Function Input/Parameters: set (const SetType), search value (CellDataType)
Function Output/Parameters: none
Function Output/Returned: Boolean result of test, as specified
Device Input/---: none
Device Output/---: none
Dependencies: cellsAreEqual
*/
bool isInSet( const SetType testSet, CellDataType searchVal );

#endif     // SET_UTILITIES_H

