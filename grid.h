
//
// Assignment  :  #1
// Class       :  CST 136
//
// Author      :  Michael Hoffman (Instructor)
//
// File        :  grid.h
//
//
// Description :  Declarations for the Grid class.
//

#ifndef  grid_H
#define  grid_H


class  Grid
{
  public  :

    Grid( int  nRows, int  nCols );
      //
      // Constructor
      //
      // This will use dynamic memory to set up an internal
      // data structure to store the state of all the cells
      // in the grid based on the number of rows and
      // columns provided as parameters. All cells are
      // initialized to the cleared state by this function.
      //


    ~Grid()  { cleanup(); }
      //
      // Destructor
      //
      // Cleans up the dynamic memory used by this class.
      // This is called automatically. Do not make an explicit
      // call to this function.
      //


    int  numRows()  const  {  return  m_numRows;  }
      //
      // Returns the number of rows in the grid.
      //


    int  numCols()  const  {  return  m_numCols;  }
      //
      // Returns the number of columns in the grid.
      //


    void  set( int  row, int  col );
      //
      // Sets a specific cell of the grid. The row and
      // column values are expected to be zero-based.
      //


    void  clear( int  row, int  col );
      //
      // Clears a specific cell of the grid. The row and
      // column values are expected to be zero-based.
      //


    bool  fetch( int  row, int  col )  const;
      //
      // Returns true if the specified cell is set, false
      // if is clear. The row and column values are expected
      // to be zero-based.
      //


    Grid( const Grid  &rhs );
      //
      // Copy Constructor
      //
      // This is needed so that objects of this class type
      // can be copied.
      //


    const Grid  &operator=( const Grid  &rhs );
      //
      // Assignment operator
      //
      // This is needed so that objects of this class type
      // can be assigned.
      //


  private  :

    int  m_numRows;
    int  m_numCols;

    bool  *m_cells;

    int  index( int  row, int  col )  const;

    void  copy( const Grid  &rhs );
    void  cleanup()                   { delete  []  m_cells; }
};


#endif
