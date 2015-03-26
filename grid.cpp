
//
// Assignment  :  #1
// Class       :  CST 136
//
// Author      :  Michael Hoffman (Instructor)
//
// File        :  grid.cpp
//
//
// Description :  Definitions for the Grid class.
//


#include  "grid.h"
#include  <assert.h>
#include  <stdlib.h>


//
// Constructor
//
Grid::Grid( int  nRows, int  nCols )  :
  m_numRows(nRows),
  m_numCols(nCols),
  m_cells( new  bool[ m_numRows * m_numCols] )
{
  if  (! m_cells)
    exit(EXIT_FAILURE);


  //
  // Initialize all the cells
  //
  for( int  row = 0;  row < m_numRows;  ++row )
    for( int  col = 0;  col < m_numCols;  ++col )
      clear(row, col);
}


//
// Sets the state of the cell specified by row/col
// to set.
//
void  Grid::set( int  row, int  col )
{
  assert( row >= 0  &&  row < m_numRows );
  assert( col >= 0  &&  col < m_numCols );

  m_cells[ index(row, col) ]  =  true;
}


//
// Sets the state of the cell specified by row/col
// to clear.
//
void  Grid::clear( int  row, int  col )
{
  assert( row >= 0  &&  row < m_numRows );
  assert( col >= 0  &&  col < m_numCols );

  m_cells[ index(row, col) ]  =  false;
}


//
// Returns true if the cell specified by row/col
// is set. Otherwise returns false.
//
bool  Grid::fetch( int  row, int  col )  const
{
  assert( row >= 0  &&  row < m_numRows );
  assert( col >= 0  &&  col < m_numCols );

  return  m_cells[ index(row, col) ];
}


//
// Convert row/col values into an array index
//
int  Grid::index( int  row, int  col )  const
{
  return  row * m_numCols + col;
}


//
// Copy constructor
//
// This uses a "deep" copy scheme so that each grid
// object contains it's own set of cell data.
//
Grid::Grid( const Grid  &rhs )
{
  copy(rhs);
}


//
// Assignment operator
//
// This uses a "deep" assignment scheme so that each grid
// object contains it's own set of cell data.
//
const Grid  &Grid::operator=( const Grid  &rhs )
{
  if  ( this != &rhs )
  {
    cleanup();

    copy(rhs);
  }


  return  *this;
}


void  Grid::copy( const Grid  &rhs )
{
  m_numRows  =  rhs.m_numRows;
  m_numCols  =  rhs.m_numCols;

  m_cells  =  new  bool[ m_numRows * m_numCols ];

  if  (! m_cells)
    exit(EXIT_FAILURE);


  //
  // Copies the cell states from the original to this object.
  //
  for( int  idx = 0;  idx < m_numRows * m_numCols;  ++idx )
    m_cells[idx]  =  rhs.m_cells[idx];
}
