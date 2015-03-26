
//
// Assignment  :  #1
// Class       :  CST 136
//
// Author      :  Michael Hoffman (Instructor)
//
// File        :  flipItDisplay.cpp
//
//
// Description :  Definitions for routines related to the
//                text display for the FlipIt game.
//


#include  "flipitDisplay.h"
#include  <iostream>

using  namespace  std;


//
// ASCII symbols for the various components of the
// the game grid display
//
#ifdef  WIN32
    //
    // For Windows systems
    //
    #define SYM_BLANK          ' '
    #define SYM_SOLID          char(219)
    #define SYM_HOR_LINE       char(205)
    #define SYM_VERT_LINE      char(186)
    #define SYM_L_SIDE         char(204)
    #define SYM_R_SIDE         char(185)
    #define SYM_TOP_SIDE       char(203)
    #define SYM_BOT_SIDE       char(202)
    #define SYM_INTERSECTION   char(206)
    #define SYM_UR_CORNER      char(187)
    #define SYM_LR_CORNER      char(188)
    #define SYM_LL_CORNER      char(200)
    #define SYM_UL_CORNER      char(201)
#else
    //
    // For non-Windows systems
    //
    #define SYM_BLANK          ' '
    #define SYM_SOLID          '*'
    #define SYM_HOR_LINE       '-'
    #define SYM_VERT_LINE      '|'
    #define SYM_L_SIDE         '|'
    #define SYM_R_SIDE         '|'
    #define SYM_TOP_SIDE       '-'
    #define SYM_BOT_SIDE       '-'
    #define SYM_INTERSECTION   '+'
    #define SYM_UR_CORNER      '+'
    #define SYM_LR_CORNER      '+'
    #define SYM_LL_CORNER      '+'
    #define SYM_UL_CORNER      '+'
#endif

//
// Grid cell dimensions (in characters)
//
#define  CELL_WIDTH   3
#define  CELL_HEIGHT  2


//
// Dispay a single output line for a cell
//
static void  displayCellLine( char  c, char  endSym )
{
  for( int  width = 0;  width < CELL_WIDTH;  ++width )
    cout  <<  c;

  cout  <<  endSym;
}


//
// Display a single output row for a column
//
static void  displayCol( FlipIt::Color  color )
{
  displayCellLine( color == FlipIt::solid_  ?  SYM_SOLID : SYM_BLANK, SYM_VERT_LINE );
}


//
// Display a row's worth of cells for the game grid.
//
static void  displayRow( const FlipIt  &game, int  rowNum )
{
  //
  // Loop once for each line of output for a cell row
  //
  for( int  height=0;  height < CELL_HEIGHT;  ++height )
  {
    if  (! height)
      cout  <<  ' '  <<  rowNum+1  <<  ' ';
    else
      cout  <<  "   ";

    cout  <<  SYM_VERT_LINE;

    //
    // Loop once for each cell in the row
    //
    for( int  col=0;  col < game.numCols();  ++col )
    {
      displayCol( game.fetch(rowNum, col) );
    }

    cout  <<  endl;
  }
}


//
// Display a horizontal line for the game grid
//
static void  displayHorLine( const FlipIt  &game,
                             char           firstSym,
                             char           midSym,
                             char           lastSym )
{
  cout  <<  "   "  <<  firstSym;

  for( int  col = 0;  col < game.numCols();  ++col )
  {
    if  ( col == game.numCols() - 1 )
      displayCellLine( SYM_HOR_LINE, lastSym );
    else
      displayCellLine( SYM_HOR_LINE, midSym );
  }

  cout  <<  endl;
}


//
// Display column headers for the game grid.
//
static void  displayHeader(const FlipIt  &game)
{
  cout  <<  "    ";

  for( int  col=0;  col < game.numCols();  ++col )
  {
    for( int  width=0;  width < CELL_WIDTH;  ++width )
    {
      if  (width == 1)
        cout  <<  col+1;
      else
        cout  <<  ' ';
    }

    cout  <<  ' ';
  }

  cout  <<  endl;
}


//
// Display the game grid
//
void  display( const FlipIt  &game )
{
  //
  // Display the top of the game grid
  //
  displayHeader( game );

  displayHorLine( game, SYM_UL_CORNER, SYM_TOP_SIDE, SYM_UR_CORNER );


  //
  // Display each row of data in the grid
  //
  for( int  row=0;  row < game.numRows();  ++row )
  {
    displayRow( game, row );

    if  ( row == game.numRows() - 1 )
      displayHorLine( game, SYM_LL_CORNER, SYM_BOT_SIDE, SYM_LR_CORNER );
    else
      displayHorLine( game, SYM_L_SIDE, SYM_INTERSECTION, SYM_R_SIDE );
  }
}
