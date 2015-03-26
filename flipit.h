//
// CST 136 - Assignment #1
//
// Author: Leander Rodriguez
//
// File: flipit.h
//
// Due date:  Sunday, April 14th by 11:59pm
//



#ifndef  flipit_H
#define  flipit_H


#include  "grid.h"



class  FlipIt
{
  public  :

    enum  Color  { clear_ = false, solid_ = true };

    enum  Pattern  { cross_, x_, square_, hollowSquare_, corners_ };

    FlipIt( int      nRows,
            int      nCols,
            int      gameNum,
            int      complexity,
            Pattern  pattern,
            bool     wrap );

    int  numRows()  const;
    int  numCols()  const;

    void  click( int  row, int  col );

    Color  fetch( int  row, int  col ) const;

    bool  done() const;

  private  :


	//
	// Member data that keeps track of the state of the board
	//


	//
	// Gameboard grid object is created
	//
    Grid m_grid;


	//
	// Member variables
	//
	const int		m_gameNum;
	const int		m_complexity;
	const Pattern	m_pattern;
	const bool		m_wrap;

	
	//
	// Methods 
	//
	int  checkCorners( int row ) const;

	void toggleCell( int row, int col );

	void checkRange( int row, int col );

	void crossPattern( int row, int col );
	void xPattern( int row, int col );

	void checkPattern( int row, int col, Pattern m_pattern );

};


#endif
