//
// CST 136 - Assignment #1
//
// Author: Leander Rodriguez
//
// File: flipit.cpp
//
// Due date:  Sunday, April 14th by 11:59pm
//



#include  <iostream>
#include  <string>
#include  <stdlib.h>
#include  "flipit.h"
#include  "grid.h"


using  namespace  std;


//
// Constants
//
#define  GREATER_THAN_RANGE(c)  ( (c) + 1 > m_grid.numRows()  ||  (c) + 1 > m_grid.numCols()  )
#define  LESS_THAN_RANGE(c)		( (c) < 0 )



//
// Constructor
//
FlipIt::FlipIt( int      nRows,
				int      nCols,
				int      gameNum,
				int      complexity,
				Pattern  pattern,
				bool     wrap  ) : m_grid( nRows, nCols ), 
								   m_gameNum( gameNum ),
								   m_complexity( complexity ), 
								   m_pattern( pattern ), 
								   m_wrap( wrap ) 
{

	//
	// Random number is generated; game number used as seed
	//
	srand( m_gameNum );


	//
	// Initial gameboard is set according to user selected
	// complexity
	//
	for( int count = 0; count < m_complexity; ++count )
	{

		int row = 0,
			col = 0;

		//
		// Initial user row and column values are randomly selected
		//
		row = rand() % nRows;
		col = rand() % nCols;


		//
		// Random row and column values are used to set
		// initial state of the board and begin game
		//
		click( row, col );

	}

}



//
// Returns the number of rows in the grid.
//
int FlipIt::numRows() const { return m_grid.numRows(); }



//
// Returns the number of columns in the grid.
//
int FlipIt::numCols() const  { return  m_grid.numCols(); }



//
// Checks if both rows and columns are out of range and
// adjusts to stay within grid
//
int FlipIt::checkCorners( int row ) const
{

	if( GREATER_THAN_RANGE( row ) )
	{
		row = row - m_grid.numRows();
	}

	if( LESS_THAN_RANGE( row ) )
	{
		row = row + m_grid.numRows();
	}

	return row;

}



//
// Toggle cell color
//
void FlipIt::toggleCell( int row, int col )
{

	if( fetch( row, col ) == clear_ )
	{
		m_grid.set( row, col );
	}
	else
	{
		m_grid.clear( row, col );
	}

}



//
// Checks if selected row and/or column is out of grid range
// and adjusts accordingly 
//
void FlipIt::checkRange( int row, int col )
{

	if( GREATER_THAN_RANGE( col ) || LESS_THAN_RANGE( col )  
								  || GREATER_THAN_RANGE( row ) 
								  || LESS_THAN_RANGE( row ) )
	{

		if( m_wrap == true )
		{

			if( GREATER_THAN_RANGE( col ) )
			{ 
				col = col - m_grid.numCols();

				row = checkCorners( row );
			}

			else if( LESS_THAN_RANGE( col ) ) 
			{ 
				col = col + m_grid.numCols();

				row = checkCorners( row );
			}

			else if( GREATER_THAN_RANGE( row ) )
			{ 
				row = row - m_grid.numRows();
			}

			else if( LESS_THAN_RANGE( row ) ) 
			{ 
				row = row + m_grid.numRows();
			}

		}
		else
		{
			return;
		}

	}


	toggleCell( row, col );

}



//
// X pattern is processed, cells on grid are 
// set or cleared accordingly
//
void FlipIt::xPattern( int row, int col ) 
{
	
	checkRange( row - 1, col - 1 );
	checkRange( row - 1, col + 1 );
	checkRange( row + 1, col - 1 );
	checkRange( row + 1, col + 1 );
	
}



//
// Cross pattern is processed, cells on grid are 
// set or cleared accordingly
//
void FlipIt::crossPattern( int row, int col )
{

	checkRange( row, col + 1 );
	checkRange( row, col - 1 );
	checkRange( row + 1, col );
	checkRange( row - 1, col );

}



//
// Checks pattern and processes it
//
void FlipIt::checkPattern( int row, int col, Pattern m_pattern  )
{

	switch( m_pattern )
		{

		  case  cross_			:  crossPattern( row, col ); 
								   break;

		  case  x_				:  xPattern( row, col ); 
								   break;

		  case  square_			:  crossPattern( row, col );
								   xPattern( row, col ); 
								   break;

		  case  hollowSquare_	:  m_grid.clear( row, col );
								   crossPattern( row, col );
								   xPattern( row, col ); 
								   break;

		  case  corners_		:  m_grid.clear( row, col );
								   xPattern( row, col ); 
								   break;
		}

}



//
// Updates internal engine data based on the 
// user-selected cell
//
void FlipIt::click ( int row, int col )
{

	checkRange( row, col );

	checkPattern( row, col, m_pattern );
	

	//
	// Checks to see if game is over
	//
	done();
	
}



//
// Returns whether the cell at the specified grid position
// is currently clear or solid
//
FlipIt::Color FlipIt::fetch ( int row, int col ) const
{
	
	if( m_grid.fetch( row, col ) == solid_ )
	{
      return solid_;
	}
    else
	{
      return clear_;
	}

}



//
// Returns true if all grid positions are clear, indicating
// the game is over, otherwise game continues
//
bool FlipIt::done() const
{

	int row = 0,
		col = 0,
		total = 0;

	while( fetch( row, col ) == clear_ )
	{

		total += 1;
		++col;

		if( col == m_grid.numCols() )
		{
			col = 0;
			++row;
		}

		if( total == m_grid.numRows() * m_grid.numCols() ) 
		{
			return true;
		}

	}


	return false;

}


