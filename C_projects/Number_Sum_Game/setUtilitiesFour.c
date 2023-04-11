#include "SetUtilitiesFour.h"

/*
Name: addItem
Process: adds cell item to set, does not allow duplicates,
         does not allow data to be added to full list (MAX_SET_CAPACITY),
         returns true if successful, false otherwise
Function Input/Parameters: new item (CellDataType)
Function Output/Parameters: pointer to set data (SetType *)
Function Output/Returned: Boolean result of action
Device Input/---: none
Device Output/---: none
Dependencies: isInSet, copyCell
*/
bool addItem( SetType *setData, CellDataType newValue )
   {
    if( setData->size < setData->capacity && !isInSet( *setData, newValue ) )
       {
        copyCell( &setData->setArray[ setData->size ], newValue );

        setData->size++;

        return true;
       }

    return false;
   }

/*
Name: copySet
Process: copies all data of one set into other
Function Input/Parameters: source set (const SetType)
Function Output/Parameters: destination set (SetType)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: copyCell
*/
void copySet( SetType dest, const SetType source )
   {
    int index;

    for( index = 0; index < source.size; index++ )
       {
        copyCell( &dest.setArray[ index ], source.setArray[ index ] );
       }

    dest.capacity = source.capacity;

    dest.size = source.size;
   }

/*
Name: deleteItem
Process: searches for item by value, deletes if found,
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
bool deleteItem( SetType *setData, CellDataType itemToDelete )
   {
    int index = 0;
    bool found = false;

    while( index < setData->size && !found )
       {
        if( cellsAreEqual( setData->setArray[ index ], itemToDelete ) )
           {
            found = true;
           }
        else
           {
            index++;
           }
       }

    if( found )
       {
        setData->size--;

        while( index < setData->size )
           {
            setData->setArray[ index ] = setData->setArray[ index + 1 ];

            index++;
           }

        return true;
       }

    return false;
   }

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
void displaySet( const char *setName, const SetType setData )
   {
    int index, itemCount = 0, numOnLine = 5;
    char tempStr[ STD_STR_LEN ];

    printf( "\n%s", setName );

    if( setData.size == 0 )
       {
        printf( "     Empty Set\n" );
       }

    else
       {
        for( index = 0; index < setData.size; index++ )
           {
            if( itemCount > 0 )
               {
                printf( "," );
               }

            itemCount++;

            cellToString( tempStr, setData.setArray[ index ] );

            printf( "%s", tempStr );

            if( itemCount % numOnLine == 0 && index + 1 < setData.size )
               {
                printf( "\n                             " );

                itemCount = 0;
               }
           }
       }

    printf( "\n" );
   }

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
void initializeSet( SetType *set )
   {
    set->capacity = MAX_SET_CAPACITY;

    set->size = 0;
   }

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
bool isInSet( const SetType testSet, CellDataType searchVal )
   {
    int index;

    for( index = 0; index < testSet.size; index++ )
       {
        if( cellsAreEqual( testSet.setArray[ index ], searchVal ) )
           {
            return true;
           }
       }

    return false;
   }