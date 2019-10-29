#pragma once
#include "common.h"

namespace GamesGo {
	// 130. Surrounded Regions
	// Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'. A region is captured by flipping all 'O's into 'X's in that surrounded region.
	/*
	X X X X
	X O O X
	X X O X
	X O X X

	X X X X
	X X X X
	X X X X
	X O X X
	*/
	void solve(vector<vector<char>>& board) {
		const int n = (int)board.size();
		if (n == 0) return;
		const int m = (int)board[0].size();
		if (m == 0) return;

		queue<pair<int, int>> q;
		for (int i = 0; i < n; ++i) {
			q.push({ i, -1 });
			q.push({ i, m });
		}
		for (int j = 0; j < m; ++j) {
			q.push({ -1, j });
			q.push({ n, j });
		}

		vector<pair<int, int>> dir = { { -1, 0 },{ 1, 0 },{ 0, 1 },{ 0, -1 } };

		while (!q.empty()) {
			auto cur = q.front();
			q.pop();
			for (const auto& v : dir) {
				pair<int, int> next = { cur.first + v.first, cur.second + v.second };
				if (next.first >= 0 && next.first < n &&
					next.second >= 0 && next.second < m &&
					board[next.first][next.second] == 'O') {
					board[next.first][next.second] = 'o';
					q.push(next);
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				auto& c = board[i][j];
				if (c == 'O') c = 'X';
				if (c == 'o') c = 'O';
			}
		}
	}
	// Mine
	void solve(vector<vector<char>>& board) {        
		int rowsize = board.size();
		if(rowsize == 0)
		    return;

		int colsize = board[0].size();
		vector<vector<char>> memo(rowsize, vector<char>(colsize, 'X'));
		//cout << memo[0][0] << "\n";
		for(int coli = 0; coli < colsize; coli ++){
		    solveHelper(board, memo, 0, coli);
		    solveHelper(board, memo, rowsize-1, coli);
		}
		for(int rowi = 1; rowi < rowsize-1; rowi ++){
		    solveHelper(board, memo, rowi, 0);
		    solveHelper(board, memo, rowi, colsize-1);
		}
		for(int i = 0; i < rowsize; i++){
		    for(int j = 0; j < colsize; j++){
			board[i][j] = memo[i][j];
		    }
		}
	    }
	    void solveHelper(vector<vector<char>>& board, vector<vector<char>>& memo, int row, int col){
		if(row < 0 || col < 0 || row == board.size() || col == board[0].size())
		    return;
		if(memo[row][col] == 'O' || board[row][col] == 'X')
		    return;
		memo[row][col] = 'O';

		solveHelper(board, memo, row-1, col);
		solveHelper(board, memo, row+1, col);
		solveHelper(board, memo, row, col-1);
		solveHelper(board, memo, row, col+1);
	    }
}
