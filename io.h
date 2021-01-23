#ifndef io_h_
#define io_h_

class Board
{

	private:

	public:

  int nrows;
  int mcols;
  int **entry;
		
	Board(int n, int m);
		
	~Board();
	
	Board(const Board& board_in);

	bool check_valid(int j_col, int x, bool c);

	bool check_valid(int j_col, bool c);

	bool check_winner(bool c);

	void print();
	
	void set(int i_row, int j_col, int x);

	bool check_full(bool c);


};

#endif
