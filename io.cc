#include <iostream>
#include "io.h"

Board::Board(int n, int m)
{
	nrows = n;
	mcols = m;

  entry    = new int*[nrows];
  entry[0] = new int[nrows * mcols];
  for(int i=1;i<nrows;i++)
    entry[i] = entry[i-1] + mcols;

	for(int i=0;i<nrows;i++)
		for(int j=0;j<mcols;j++)
			entry[i][j] = 0;

}

Board::~Board()
{
	delete[] entry[0];
	delete[] entry;
}

Board::Board(const Board& board_in)
{
//  std::cout << "Using deep copy constructor" << std::endl;

  if (board_in.entry[0] != 0)
    {

      nrows = board_in.nrows;
      mcols = board_in.mcols;

      entry    = new int*[nrows];
      entry[0] = new int[nrows * mcols];
      for(int i=1;i<nrows;i++)
      	entry[i] = entry[i-1] + mcols;

      for(int i=0;i<nrows;i++)
      	for(int j=0;j<mcols;j++)
          entry[i][j] = board_in.entry[i][j];
    }

  else
    {
      entry = 0;
    }
}


bool Board::check_valid(int j_col, int x, bool c)
{
	if(j_col < 0)
	{
		if(c == 0)
 			std::cout << "Chosen column too small please choose another move" << std::endl;

		return 0;	
	}	

	else if(j_col >= mcols)
	{
		if(c == 0)
			std::cout << "Chosen column too large please choose another move" << std::endl;

		return 0;
	}

	else if(entry[0][j_col] != 0)
	{
		if(c == 0)
    	std::cout << "Column full please choose another move" << std::endl;
		
		return 0;	
	}

	else
	{	
  	for(int i=nrows-1;i>=0;i--)
  	{ 
    	if(entry[i][j_col] == 0)
    	{
      	set(i,j_col,x);
      	break;
    	}
  	}
	}
	return 1;
}

bool Board::check_valid(int j_col, bool c)
{
  if(j_col < 0)
  {
		if(c == 0)
    	std::cout << "Chosen column too small please choose another move" << std::endl;

    return 0;
  }

  else if(j_col >= mcols)
  {
		if(c == 0)
    	std::cout << "Chosen column too large please choose another move" << std::endl;

    return 0;
  }

  else if(entry[0][j_col] != 0)
  {
		if( c == 0)
    std::cout << "Column full please choose another move" << std::endl;
    return 0;
  }

	return 1;
}

bool Board::check_full(bool c)
 
{
  for(int i=0;i<mcols;i++)
 	{
   	if(entry[0][i] == 0)
     	break;

   	if(i == mcols-1)
   	{
				if( c == 0)
       std::cout << "\033[1;33mBOARD FULL NO WINNER!!\033[0m" << std::endl;

     	return 1;
   	}
 	}

	return 0;
}

bool Board::check_winner(bool c)
{

	//across 4
  for(int i=0;i<nrows;i++)
  {
    for(int j=0;j<=mcols-4;j++)
    {
      if(entry[i][j] == -1 && entry[i][j+1] == -1 && entry[i][j+2] == -1 && entry[i][j+3] == -1)
      {
				if( c == 0)
    	    std::cout << "\033[1;31mRED WINS!!\033[0m" << std::endl;
        return 1;
      }

      if(entry[i][j] == 1 && entry[i][j+1] == 1 && entry[i][j+2] == 1 && entry[i][j+3] == 1)
      {
				if( c == 0 )
  	      std::cout << "\033[1;33mYELLOW WINS!!\033[0m" << std::endl;
        return 1;
      }
    }
  }

	//vertical 4
  for(int i=nrows-1;i>nrows-4;i--)
  {
    for(int j=0;j<mcols;j++)
    {
			if(entry[i][j] == -1 && entry[i-1][j] == -1 && entry[i-2][j] == -1 && entry[i-3][j] == -1)
      {
				 if( c == 0 )
	        std::cout << "\033[1;31mRED WINS!!\033[0m" << std::endl;
        return 1;
      }

      if(entry[i][j] == 1 && entry[i-1][j] == 1 && entry[i-2][j] == 1 && entry[i-3][j] == 1)
      {
				if( c == 0 )
				  std::cout << "\033[1;33mYELLOW WINS!!\033[0m" << std::endl;
        return 1;
      }
    }
  }


	//up diagonal
	for(int i=nrows-1;i>nrows-4;i--)
	{
		for(int j=0;j<=mcols-4;j++)
		{ 
			if(entry[i][j] == -1 && entry[i-1][j+1] == -1 && entry[i-2][j+2] == -1 && entry[i-3][j+3] ==-1)
			{
				if( c == 0 )
        	std::cout << "\033[1;31mRED WINS!!\033[0m" << std::endl;
        return 1;
			}

		if(entry[i][j] == 1 && entry[i-1][j+1] == 1 && entry[i-2][j+2] == 1 && entry[i-3][j+3] ==1)
      {
				if( c == 0 )
					std::cout << "\033[1;33mYELLOW WINS!!\033[0m" << std::endl;
       	return 1;
			}
		}
	}

	//down diagonal 4
	for(int i=0;i<=nrows-4;i++)
	{
		for(int j=0;j<=mcols-4;j++)
		{
      if(entry[i][j] == -1 && entry[i+1][j+1] == -1 && entry[i+2][j+2] == -1 && entry[i+3][j+3] ==-1)
      {
				if( c == 0 )
	        std::cout << "\033[1;31mRED WINS!!\033[0m" << std::endl;
        return 1;
      }
      if(entry[i][j] == 1 && entry[i+1][j+1] == 1 && entry[i+2][j+2] == 1 && entry[i+3][j+3] ==1)
      {
				if( c == 0 )
	        std::cout << "\033[1;33mYELLOW WINS!!\033[0m" << std::endl;
        return 1;
      }
		}	



	}
	return 0;
}

void Board::print()
{
	std::cout << std::endl;

	for(int i=0;i<nrows;i++)
	{
		for(int j=0;j<mcols;j++)
			{
				if(entry[i][j] == 0)
					std::cout << "| |";
					
				else if(entry[i][j] == -1)
					std::cout << "|\033[1;31m0\033[0m|";

				else
					 std::cout << "|\033[1;33m0\033[0m|";
			}
		std::cout << std::endl;
	}

	std::cout << std::endl;

}

void Board::set(int i_row, int j_col, int x)
{
	entry[i_row][j_col] = x;
}



