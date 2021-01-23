#ifndef MCTS_h_
#define MCTS_h_

struct node
{
	float value;
	int wins;
	int games;
	int visited;
	int colour;

	node *prev;
	
	node *p[7];
};

class MCTS
{
	private:

	void destroy_tree(node *leaf);

	node *root;

	int nrows;

	int ncols;

  void selection(node *leaf, Board *B);

	public:

	MCTS(int i, int j);

	~MCTS();

	void selection(int c, Board *B);

	void expansion(int choose, node *leaf);

	void simulation(node *leaf, Board *B);

	void backpropagation(node *leaf, int c, bool draw);

	void choose_move(Board *A);
};


#endif
