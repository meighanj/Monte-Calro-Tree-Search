#include <iostream>
#include "io.h"
#include "MCTS.h"
#include <string>
#include <cstdlib>

int main()
{
	std::string s;
	std::string k = "y";
  int a;
  int c = -1;
  int nrows = 6;
  int ncols = 7;

	Board A(nrows,ncols);

	A.print();

	std::cout << "Self play? (y/n)" << std::endl;
	std::cin >> s;
	
	if(s == k)
	{
		while(1)
		{
	    MCTS K(nrows, ncols);

  	  for(int i=0;i<1000000;i++)
    	{
      	Board B = A;
      	K.selection(c, &B);
    	}

      if( c == 1)
        c = -1;
      else
        c = 1;

    	K.choose_move(&A);

    	A.print();

    	if(A.check_full(0))
      	break;

    	if(A.check_winner(0))
      	break;

    	MCTS M(nrows, ncols);

    	for(int i=0;i<1000000;i++)
    	{
      	Board B = A;
      	M.selection(c, &B);
    	}

      if( c == 1)
        c = -1;
      else
        c = 1;

    	M.choose_move(&A);

    	A.print();

    	if(A.check_full(0))
      	break;

    	if(A.check_winner(0))
      	break;
		}
	}


	else
	{
	  std::cout << "Would you like to move first? (y/n)" << std::endl;
  	std::cin >> s;
		
		if( s != k)
		{
//			a = rand() % ncols;
			A.check_valid(3, c, 0); 
			A.print();

		}
		if( c == 1)
			c = -1;
		else
			c = 1;

		while(1)
		{
			std::cout << "Which column would you like to place in?" << std::endl;

			std::cin >> a;

			while(A.check_valid(a, c, 0) == 0)
			{
				std::cin >> a;
			}

    	A.print();

			if(A.check_full(0))
				break;

			if(A.check_winner(0))
				break;

    	MCTS K(nrows, ncols);

			for(int i=0;i<350000;i++)
			{
				Board B = A;
  			K.selection(c, &B);
			}

    	K.choose_move(&A);		

			A.print();

			if(A.check_full(0))
				break;

			if(A.check_winner(0))
				break;
		}
	}

	return 0;
}
