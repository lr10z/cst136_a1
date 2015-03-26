
//
// Assignment  :  #1
// Class       :  CST 136
//
// Author      :  Michael Hoffman (Instructor)
//
// File        :  flipitMain.cpp
//
//
// Description :  Main program for the text-based version of
//                the FlipIt game.
//

#define  _CRT_SECURE_NO_DEPRECATE

#include  <iostream>
#include  <stdlib.h>
#include  <string.h>
#include  <limits.h>
#include  "flipit.h"
#include  "flipitDisplay.h"


using  namespace  std;


//
// Macros/constants
//

#define  INVALID_ENTRY   cout  <<  "*** Invalid entry."  <<  endl

#define  SCREEN_ROWS  24

#define  RC_REDRAW  RowCol(-2, -2)
#define  RC_ABORT   RowCol(-1, -1)

#define  INPUT_LINE_SZ  10


//
// Type definitions
//
typedef  pair<int, int>  RowCol;



//
// Determine if the user wants to play again. Returns
// true if yes.
//
static bool  playAgain()
{
  while(true)
  {
    cout  <<  endl  <<  "Play again (y/n): ";

    char  line[INPUT_LINE_SZ];
    cin.getline(line, INPUT_LINE_SZ);

    switch(tolower(line[0]))
    {
      case  'y'  :  return  true;
      case  'n'  :  return  false;
    }

    INVALID_ENTRY;
  }
}


//
// Get a number from the user. Returns the number.
//
//
// Get a number from the user
//
static int  getNumber( const char  *prompt,
                       int         min = INT_MIN,
                       int         max = INT_MAX )
{
  int  number;


  //
  // Loop until a valid value is entered
  //
  while(true)
  {
    //
    // Display prompt and get a value from the user
    //
    cout  <<  endl  <<  prompt  <<  ": ";

    char  input[INPUT_LINE_SZ];

    cin.getline(input, INPUT_LINE_SZ);

    number  =  atoi( input );


    //
    // Make sure the user's value is within the valid range
    //
    if  ( number >= min  &&  number <= max )
      break;

    cout  <<  "*** Out of range!"  <<  endl;
  };


  return  number;
}


//
// Get the click pattern from the user. Returns the
// pattern identifier.
//
static FlipIt::Pattern  getPattern()
{
  while(true)
  {
    cout  <<  endl
          <<  "  1 - Cross"          <<  endl
          <<  "  2 - X"              <<  endl
          <<  "  3 - Square"         <<  endl
          <<  "  4 - Hollow square"  <<  endl
          <<  "  5 - Corners"        <<  endl;

    switch( getNumber( "Pattern (1-5)", 1, 5 ) )
    {
      case  1  :  return  FlipIt::cross_;
      case  2  :  return  FlipIt::x_;
      case  3  :  return  FlipIt::square_;
      case  4  :  return  FlipIt::hollowSquare_;
      case  5  :  return  FlipIt::corners_;
    }

    INVALID_ENTRY;
  }
}


//
// Get the wrap flag from the user. Returns true
// if the user wants the wrap feature.
//
static bool  getWrap()
{
  while(true)
  {
    cout  <<  endl
          <<  "Wrap (y/n): ";

    char  line[INPUT_LINE_SZ];
    cin.getline(line, INPUT_LINE_SZ);

    switch(tolower( line[0] ))
    {
      case  'y'  :  return  true;
      case  'n'  :  return  false;
    }

    INVALID_ENTRY;
  }
}



//
// Get a row/column entry from the user. Prompts
// using 1-based numbers. Returns 0-based numbers
// in a row/column pair object.  RC_ABORT is returned
// if the user wants to quit the game. RC_REFRESH
// is returned if the user wants to refresh the screen.
//
static RowCol  getRowCol(const FlipIt  &game)
{
  RowCol  rc;
  int     &row  =  rc.first;
  int     &col  =  rc.second;


  cout  <<  "   Redraw: 0,0   Quit: -1,-1"  <<  endl;


  while(true)
  {
    cout  <<  endl  <<  "Row,Column: ";


    //
    // Get input and parse it
    //
    char  line[INPUT_LINE_SZ];
    cin.getline(line, INPUT_LINE_SZ);


    char  *rowStr  =  strtok( line, "," );
    char  *colStr  =  strtok( 0, "" );


    //
    // Verify correct format was entered
    //
    if  ( ! strlen(line)  ||  ! rowStr  ||  ! colStr )
    {
      INVALID_ENTRY;
      continue;
    }


    //
    // Convert to intregral values
    //
    row  =  atoi( rowStr );
    col  =  atoi( colStr );


    //
    // Check for quiting the game and redrawing the screen
    //
    if  ( row == -1  &&  col == -1 )
      return  RC_ABORT;

    if  ( row == 0  &&  col == 0 )
      return  RC_REDRAW;


    //
    // Validate the row/col values are within range for
    // the game board
    //
    if  ( row > 0  &&  row <= game.numRows()  &&
          col > 0  &&  col <= game.numCols() )
      break;

    INVALID_ENTRY;
  }


  //
  // Convert to zero-based values
  //
  --row;
  --col;


  return  rc;
}


//
// Clear the screen.
//
static void  clearScreen()
{
  for( int  i = 0;  i < SCREEN_ROWS;  ++i )
    cout  <<  endl;
}


//
// Play a game.
//
static void  play( FlipIt  &game )
{
  int  numClicks = 0;


  //
  // Loop until solved or aborted.
  //
  while( true )
  {
    //
    // Clear the screen and display the grid.
    //
    clearScreen();

    display( game );


    //
    // Break out of the loop if the game is complete.
    //
    if  ( game.done() )  break;


    //
    // Get the row/column value from the user
    //
    RowCol  rc = getRowCol( game );


    //
    // Check for a refresh request
    //
    if  ( rc == RC_REDRAW )
      continue;


    //
    // Check for quitting
    //
    if  ( rc == RC_ABORT )
    {
      cout  <<  "Game aborted!"  <<  endl;
      return;
    }


    //
    // Process the request and increment the number of clicks.
    //
    game.click( rc.first, rc.second );

    ++numClicks;
  }


  //
  // Game was solved. Display the results.
  //
  cout  <<  "Solved it in "  <<  numClicks
        <<  " clicks."       <<  endl;

  return;
}


//
// Main program
//
int  main()
{
  //
  // Loop for as long as the user wants to keep playing the game.
  //
  do
  {
    clearScreen();


    //
    // Get game settings
    //
    int              numRows     =  getNumber( "# of rows (3-9)", 3, 9 );
    int              numCols     =  getNumber( "# of cols (3-9)", 3, 9 );
    int              gameNum     =  getNumber( "Game number" );
    int              complexity  =  getNumber( "Complexity (1-999)", 1, 999 );
    FlipIt::Pattern  pattern     =  getPattern();
    bool             wrap        =  getWrap();


    //
    // Play the game
    //
    FlipIt  game( numRows, numCols, gameNum, complexity, pattern, wrap );

    play( game );


  } while (playAgain() );


  return  0;
}
