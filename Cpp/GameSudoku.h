#pragma once
#include "common.h"

class Sudoku {
public:
	// 36. Valid Sudoku
	// Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated.
	bool isValidSudoku(vector<vector<char>>& board) {
		// check each 3x3
		const int n = 3;
		const int m = n * n;
		for (int k = 0; k < m; ++k) {
			unordered_map<char, bool> visited;
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					int y = int(k / 3) * 3 + i;
					int x = int(k % 3) * 3 + j;
					char c = board[y][x];
					if (c == '.') continue;
					if (visited.find(c) != visited.end()) return false;
					visited[c] = true;
				}
			}
		}

		// check each row and column
		for (int k = 0; k < m; ++k) {
			unordered_map<char, bool> row_vd;
			for (int i = 0; i < m; ++i) {
				char c = board[k][i];
				if (c == '.') continue;
				if (row_vd.find(c) != row_vd.end()) return false;
				row_vd[c] = true;
			}

			unordered_map<char, bool> col_vd;
			for (int i = 0; i < m; ++i) {
				char c = board[i][k];
				if (c == '.') continue;
				if (col_vd.find(c) != col_vd.end()) return false;
				col_vd[c] = true;
			}
		}
		return true;
	}
	// Mine
	bool isValidSudoku(vector<vector<char>>& board) {
		vector<int> checkCol(board.size()), checkGrid(board.size());
		for(int i = 0; i < board.size(); i++){
		    int check = 0; // for row
		    for(int j = 0; j < board[i].size(); j++){

			if(board[i][j] == '.')
			    continue;
			int cur = (1 << (board[i][j] - '0'));
			if(cur & check)
			    return false;

			if(cur & checkCol[j])
			    return false;

			// how to check grid
			int gridIndex = i/3*3+j/3;
			if(cur & checkGrid[gridIndex])
			    return false;

			check = cur | check;
			checkCol[j] = cur | checkCol[j];
			checkGrid[gridIndex] = checkGrid[gridIndex] | cur;
		    }
		}
		return true;
	    }

	// 37. Sudoku solver
	// Write a program to solve a Sudoku puzzle by filling the empty cells.
public:
	void solveSudoku(vector<vector<char>>& board) {
		solveSudokuDFS(board);
	}

private:
	bool solveSudokuDFS(vector<vector<char>>& board) {
		const int n = 9;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (board[i][j] == '.') {
					for (int k = 0; k < n; ++k) {
						board[i][j] = '1' + k;
						if (isSudokuValid(board, i, j) && solveSudokuDFS(board)) return true;
						board[i][j] = '.';
					}
					return false;
				}
			}
		}
		return true;
	}

	bool isSudokuValid(const vector<vector<char>> &board, int x, int y) {
		const int n = 9;
		int i, j;
		for (int i = 0; i < n; ++i)
			if (i != x && board[i][y] == board[x][y]) return false;
		for (int j = 0; j < n; ++j)
			if (j != y && board[x][j] == board[x][y]) return false;
		for (i = 3 * (x / 3); i < 3 * (x / 3 + 1); i++)
			for (j = 3 * (y / 3); j < 3 * (y / 3 + 1); j++)
				if ((i != x || j != y) && board[i][j] == board[x][y])
					return false;
		return true;
	}
};
