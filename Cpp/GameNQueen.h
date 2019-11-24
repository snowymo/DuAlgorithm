#pragma once
#include "common.h"
class NQueens {
	vector<vector<string>> NQresult;
	vector<int> NQpath;
	int NQtotal;
	int NQn;

	// 51. N-Queens
	// Given an integer n, return all distinct solutions to the n-queens puzzle.
	vector<vector<string>> solveNQueens(int n)
	{
		NQresult.clear();
		NQpath.clear();
		NQn = n;
		NQtotal = 0;
		bitNQueens(0, 0, 0);
		cout << NQtotal << endl;
		return NQresult;
	}	
	
	// col: whether this col is occupied
	// ld: left diagnal for the current row
	// rd: right diagnal for the current row
	void bitNQueensSimple(int col, int ld, int rd) {
		int allOccupied = (1 << NQn) - 1;
		if (col == allOccupied) {
			++NQtotal;
			return;
		}
		int pos = allOccupied & (~(col | ld | rd));
		while (pos != 0) {
			int p = pos & (-pos);		// which way to go
			pos = pos - p;					// get the rightmost 1 of position position
			bitNQueensSimple(col + p, (ld + p) << 1, (rd + p) >> 1);
		}
	}

	void addNQueenSolution() {
		vector<string> v; 
		for (int i = 0; i < NQn; ++i)
			v.emplace_back(string(NQn, '.'));
		for (int i = 0; i < NQn; ++i) {
			v[i][NQpath[i]] = 'Q';
			//cout << v[i] << endl; 
		}
		//cout << endl; 
		NQresult.emplace_back(v);
	}

	// col: whether this col is occupied
	// ld: left diagnal for the current row
	// rd: right diagnal for the current row
	void bitNQueens(int col, int ld, int rd) {
		int allOccupied = (1 << NQn) - 1;
		if (col == allOccupied) {
			++NQtotal;
			addNQueenSolution();
			return;
		}
		int pos = allOccupied & (~(col | ld | rd));
		while (pos != 0) {
			int p = pos & (-pos);		// which way to go
			pos = pos - p;					// get the rightmost 1 of position position
			NQpath.emplace_back(p == 1 ? 0 : (int)round(log(p) / log(2)));
			bitNQueens(col + p, (ld + p) << 1, (rd + p) >> 1);
			NQpath.pop_back();
		}
	}
	
	// Mine, slow
	vector<vector<string>> ret;
	    vector<vector<string>> solveNQueens(int n) {
		string str(n, '.');
		vector<string> curSol(n,str);
		vector<int> assignment(n, -1);
		bool findSol = solveHelper(assignment, 0, n, curSol);
		return ret;
	    }

	    void addSol(int n, vector<int>& assignment, vector<string> curSol){

		for(int i = 0; i < n; i++){
		    curSol[i][assignment[i]] = 'Q';
		}
		ret.push_back(curSol);
	    }

	    bool solveHelper(vector<int>& assignment, int col, int n, vector<string> & curSol){
		if(col == n)
		    return true;
		bool isCurCol = false;
		for(int i = 0; i < n; i++){
		    // try i for column col
		    assignment[col] = i;
		    // check if col will break or not
		    if(!isValid(assignment, col))
			continue;
		    // if not, move to next col
		    bool nextCol = solveHelper(assignment, col+1, n, curSol);
		    if(nextCol && col == (n-1)){
			// this one is one solution
			addSol(n, assignment, curSol);
			isCurCol = true;
		    }
		}
		return isCurCol;
	    }

	    bool isValid(vector<int>& assignment, int col){
		//cout << "check ";
		// for(int a:assignment)
		//     cout << a << " ";
		for(int i = 0; i < col; i++){
		    // by row
		    if(assignment[i] == assignment[col]){
			//cout << "F\n";
			return false;
		    }

		    // by cross
		    if((assignment[i] + i) == (assignment[col] + col)){
			//cout << "F\n";
			return false;
		    }

		    if((assignment[i] - i) == (assignment[col] - col)){
			//cout << "F\n";
			return false;
		    }
		}
		//cout << "T\n";
		return true;
	    }

public:
	// 52. N-Queens II
	// Given an integer n, return the number of distinct solutions to the n-queens puzzle.
	int totalNQueens(int n) {
		NQresult.clear();
		NQn = n;
		NQtotal = 0;
		bitNQueensSimple(0, 0, 0);
		return NQtotal;
	}
};
