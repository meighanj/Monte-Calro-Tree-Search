#include <iostream>
#include "io.h"
#include "MCTS.h"
#include <cmath>
#include <cstdlib>

MCTS::MCTS(int i, int j)
{
	root=NULL;

	nrows = i;
	
	ncols = j;	

	std::cout << "MCTS Constructer" << std::endl;
}

MCTS::~MCTS()
{
  destroy_tree(root);
}

void MCTS::destroy_tree(node *leaf)
{
  if(leaf!=NULL)
  {
		for(int i=0;i<ncols;i++)
			destroy_tree(leaf->p[i]);	
		
//		delete leaf -> prev;
    delete leaf; //not sure if this works properly
  }
}

void MCTS::selection(int c, Board *B)
{
	if(root!=NULL)
		selection(root, B);
		
	else
	{
		root = new node;
		root -> value 	= 0.0;
		root -> wins  	= 0;
		root -> games 	= 0;
		root -> visited = 0;
		root -> colour  = c; //root node has same colour as opponent

		root -> prev = NULL; //can use this to find root.

		for(int i=0;i<ncols;i++)
			root -> p[i] = NULL;
	}
}


void MCTS::selection(node *leaf, Board *B)
{
	leaf -> games += 1; //if we get to a leaf we +1 to it's games played

	for(int i=0; i<ncols;i++)
	{
		if(leaf -> p[i] == NULL) //is it a leaf node?
		{
			if(B -> check_valid(i, 1)) // do i need to check it 
																					// without setting??
			{
//				std::cout << "Valid column" << std::endl;
				if(leaf -> visited == 0)
				{
					leaf -> visited = 1;
					simulation(leaf, B);	
					//std::cout << "Simulating from leaf" << std::endl;
					//from leaf or leaf -> p[i] ??
					return;
				}						
				else
				{
					expansion(i, leaf); // if visited previously expand 
					B -> check_valid(i, leaf -> p[i] -> colour, 1); //add it to the board
					

//					B -> print();

				  if(B -> check_full(1)) //full means draw
  				{
						leaf -> games += 1;
    				//std::cout << "B FULL FULL NULL" << std::endl;
    				backpropagation(leaf -> p[i], leaf -> p[i] -> colour, 1);
    				return;
  				}

  				if(B -> check_winner(1))
  				{
						leaf -> games += 1;
    				//std::cout << "B WINNER FROM NULL" << std::endl;
    				backpropagation(leaf -> p[i], leaf -> p[i] -> colour, 0);
    				return;
  				}
					selection(leaf -> p[i], B);
					return; //do i need this??
				}
			}
		}
		else
		{
    	if(leaf -> p[i] -> games == 0)
    	{
      	if(B -> check_valid(i, 1))
      	{
        	B -> check_valid(i, leaf -> p[i] -> colour, 1);
//        	B -> print();

        	if(B -> check_full(1)) //full means draw
        	{
          	//std::cout << "B FULL" << std::endl;
						expansion(i, leaf);	
   	      	backpropagation(leaf -> p[i], leaf -> p[i] -> colour, 1);
						leaf -> p[i] -> games = 1;	
          	return;
        	}

        	if(B -> check_winner(1))
        	{
          	//std::cout << "B WINNER" << std::endl;
          	backpropagation(leaf -> p[i], leaf -> p[i] -> colour, 0);
						leaf -> p[i] -> games = 1;
          	return;
        	}
        	selection(leaf -> p[i], B);
				}
			}
		}		
	}
	for(int i=0; i<ncols;i++)
	{	
		if(leaf -> p[i] != NULL)
			leaf -> p[i] -> value = ((float)leaf -> p[i] -> wins / (float)leaf -> p[i] -> \
				games) + 2*std::sqrt(std::log(root -> games) / leaf -> p[i] -> games);
	}


  int position = 0;
  float max; 
	while(leaf -> p[position] == NULL)
	{
		position++;
	}

	max = leaf -> p[position] -> value;

	for(int i=1;i<ncols;i++)
	{
		if(leaf -> p[i] != NULL)
		{	
			if(leaf -> p[i] -> value > max)
			{
				if(B -> check_valid(i, 1)) //check if valid but don't set
				{
					max = leaf -> p[i] -> value;			
					position = i;
				}
			}
		}	
	}

//	std::cout << "Entering at column " << position << std::endl;

	B -> check_valid(position, leaf -> p[position] -> colour, 1); //sets position into B	

//	leaf -> p[position] -> games += 1;

//	B -> print();

	if(B -> check_full(1)) //full means draw
	{
		leaf -> p[position] -> games += 1;
//		std::cout << "B FULL" << std::endl;
		backpropagation(leaf -> p[position], leaf -> p[position] -> colour, 1);
		return;
	}

	if(B -> check_winner(1))
	{
		leaf -> p[position] -> games += 1;
//		std::cout << "B WINNER" << std::endl; //this isn't enough!!
		backpropagation(leaf -> p[position], leaf -> p[position] -> colour, 0);//need to backprogate from child 
		return;
	}


//	std::cout << "Calling selection" << std::endl;
	selection(leaf -> p[position], B);         
}


void MCTS::expansion(int column, node *leaf)
{
//	std::cout << "EXPANDING" << std::endl;

	node *child = new node;
	child -> value   = 0.0;
	child -> wins    = 0;
	child -> games   = 0;
	child -> visited = 0;
		
	if(leaf -> colour == 1)
		child -> colour  = -1;
	else
		child -> colour  = 1;
				
	child -> prev = leaf;

	for(int i=0;i<ncols;i++)
		child -> p[i] = NULL; 

  leaf -> p[column] = child;
}

void MCTS::simulation(node *leaf, Board *B)
{
	int column;	
	
	int c = leaf -> colour; 

	while(1)
	{
		column = rand() % ncols; //choose a move at random
    while(B -> check_valid(column, c, 1) == 0)
    {
			column = rand() % ncols;
    }

//    B -> print();

		
    if(B -> check_full(1)) //full means draw
		{
			backpropagation(leaf, c, 1); 
      return;
		}

    if(B -> check_winner(1))
		{
			backpropagation(leaf, c, 0);
      return;
		}
	

	if(c == 1)
		c = -1;
	else
		c = 1;
	}
}

void MCTS::backpropagation(node *leaf, int c, bool draw)
{

//	std::cout << "backpropagation" << std::endl;
//	std::cout << leaf -> games << std::endl;

	if(leaf -> prev != NULL)
	{	
		if(draw == 0)
		{
			if(c == leaf -> colour) //+1 to wins if say colour as winner in sim.
			{
				leaf -> wins += 1;
			}
			else
				leaf -> wins -= 1;
		}
		backpropagation(leaf -> prev, c, draw); // should go back until NULL
	}
}

void MCTS::choose_move(Board *A)
{
  int position = 0;
  while(root -> p[position] == NULL)
  {
    position++;
  }

  int max = root -> p[position] -> games;


  for(int i=1;i<ncols;i++)
  {

		if(root -> p[i] != NULL)
		{
			if(root -> p[i] -> games > max)
    	{
      	if(A -> check_valid(i, 1)) //check if valid but don't set
      	{
        	max = root -> p[i] -> games;
        	position = i;
      	}	
    	}
		}
	}

  A -> check_valid(position, root -> p[position] -> colour, 1);

/*
	for(int i=0;i<ncols;i++)
	{
		if(root -> p[i] != NULL)
			std::cout << "Games for column " << i << " = " << root -> p[i] -> games << std::endl;
		else
			std::cout << "Games for column "<< i<< " = " << 0 << std::endl;

	}

  for(int i=0;i<ncols;i++)
  {
    if(root -> p[i] != NULL)
      std::cout << "wins for column " << i << " = " << root -> p[i] -> wins << std::endl;
    else
      std::cout << "wins for column "<< i<< " = " << 0 << std::endl;
  }
*/
  std::cout << "Choosing column " << position << std::endl;
}

