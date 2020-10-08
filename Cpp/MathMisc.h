#pragma once
#include "common.h"

class MathMisc {
	// 258. Add Digits
	// Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.
	// Solution: Digital root https://en.wikipedia.org/wiki/Digital_root
	// The digital root (also repeated digital sum) of a non-negative integer is the (single digit) value obtained by an iterative process of summing digits, on each iteration using the result from the previous iteration to compute a digit sum. The process continues until a single-digit number is reached.
	int addDigits(int num) {
		return num > 0 ? (num - 1) % 9 + 1 : 0;
		// 10 = 19 = 1
		// 110 = 58 = 47 = 38 = 29 = 20 = 11 = 2
		// 99999 = 45 = 9
		// 99999999996 = 96 = 15 = 6
	}

	// 268. Missing Number
	// Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.
	int missingNumber(vector<int>& nums) {
		int n = (int)nums.size();
		int s = accumulate(nums.begin(), nums.end(), 0);
		return n * (n + 1) / 2 - s;
	}

	// 319. Bulb Switcher [M]
	// There are n bulbs that are initially off. You first turn on all the bulbs. Then, you turn off every second bulb. On the third round, you toggle every third bulb (turning on if it's off or turning off if it's on). For the i-th round, you toggle every i bulb. For the n-th round, you only toggle the last bulb. Find how many bulbs are on after n rounds.
	// Find out how many bulbs are operated for odd times
	// 
	int bulbSwitch(int n) {
		return (int)(sqrt(n));
	}


	// 321. Create Maximum Number [H]
	// Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits. Note: You should try to optimize your time and space complexity.
	using bigint = vector<int>;
	bigint maxNumber(bigint& nums1, bigint& nums2, int k) {
		int n = (int)nums1.size(), m = (int)nums2.size();
		bigint ans;
		for (int i = max(0, k - m); i <= min(k, n); ++i) {
			ans = max(ans, mergeVector(maxVector(nums1, i), maxVector(nums2, k - i)));
		}
		return ans;
	}

	bigint maxVector(bigint& nums, int reserved) {
		int drop = (int)nums.size() - reserved;
		bigint res;
		// 9 6
		for (int x : nums) {
			while (drop && res.size() && res.back() < x) {
				res.pop_back();
				--drop;
			}
			res.push_back(x);
		}
		res.resize(reserved);
		return res;
	}


	bigint mergeVector(bigint a, bigint b) {
		bigint res;
		while (a.size() + b.size()) {
			bigint& c = a > b ? a : b;
			res.push_back(c[0]);
			c.erase(c.begin());
		}
		return res;
	}

	// 335. Self Crossing [H]
	// Time:  O(n)
	// Space: O(1)
	bool isSelfCrossing(vector<int>& x) {
		const int n = (int)x.size();
		if (n >= 5 && x[3] == x[1] && x[4] + x[0] >= x[2]) {
			// Crossing in a loop:
			//     2
			// 3 ┌────┐
			//   └─══>┘1
			//   4  0  (overlapped)  
			return true;
		}

		for (int i = 3; i < n; ++i) {
			if (x[i] >= x[i - 2] && x[i - 3] >= x[i - 1]) {
				// Case 1:
				//    i-2
				// i-1┌─┐
				//    └─┼─>i
				//     i-3
				return true;
			}
			else if (i >= 5 && x[i - 4] <= x[i - 2] && x[i] + x[i - 4] >= x[i - 2] &&
				x[i - 1] <= x[i - 3] && x[i - 1] + x[i - 5] >= x[i - 3]) {
				// Case 2:
				//    i-4
				//    ┌──┐ 
				//    │i<┼─┐
				// i-3│ i-5│i-1
				//    └────┘
				//      i-2
				return true;
			}
		}
		return false;
	}
	
// 	Mine No.794[M] Valid Tic-Tac-Toe
// 	A Tic-Tac-Toe board is given as a string array board. Return True if and only if it is possible to reach this board position during the course of a valid tic-tac-toe game.

// The board is a 3 x 3 array, and consists of characters " ", "X", and "O".  The " " character represents an empty square.

// Here are the rules of Tic-Tac-Toe:

// Players take turns placing characters into empty squares (" ").
// The first player always places "X" characters, while the second player always places "O" characters.
// "X" and "O" characters are always placed into empty squares, never filled ones.
// The game ends when there are 3 of the same (non-empty) character filling any row, column, or diagonal.
// The game also ends if all squares are non-empty.
// No more moves can be played if the game is over.
// Example 1:
// Input: board = ["O  ", "   ", "   "]
// Output: false
// Explanation: The first player always plays "X".

// Example 2:
// Input: board = ["XOX", " X ", "   "]
// Output: false
// Explanation: Players take turns making moves.

// Example 3:
// Input: board = ["XXX", "   ", "OOO"]
// Output: false

// Example 4:
// Input: board = ["XOX", "O O", "XOX"]
// Output: true
	bool validTicTacToe(vector<string>& board) {
		int numX = 0;        int numO = 0;
		unordered_map<int,int> countRowX, countRowO, countColX, countColO, countDiaX, countDiaO, winX, winO; // first index is 0-r 1-c 2-d0 3-d2
		for(int i = 0; i < board.size(); i++){
		   for(int j = 0; j < board[i].length(); j++){
		       if(board[i][j] == 'X'){
			   ++numX;  
			   countRowX[i]+=1;
			   countColX[j]+=1;
			   if(i == j)
				countDiaX[0]+=1;
			   if(i + j == 2){
			       countDiaX[2] += 1;
			   }                       

			   if(countRowX[i] == 3){
			       if(winX.count(0) > 0){
				   return false;
			       }
			       winX[0] = i;
			   }
			   if(countColX[j] == 3){
			       if(winX.count(1) > 0){
				   return false;
			       }
			       winX[1] = j;
			   }
			   if(i == j && countDiaX[0] == 3){
			       if(winX.count(2) > 0){
				   return false;
			       }
			       winX[2] = 0;
			   }
			   if(i + j == 2 && countDiaX[2] == 3){
			       if(winX.count(3) > 0){
				   return false;
			       }
			       winX[3] = 2;
			   }
		       }else if(board[i][j] == 'O'){
			   ++ numO;
			   countRowO[i]+=1;
			   countColO[j]+=1;
			   if(i == j)
				countDiaO[0]+=1;
			   if(i + j == 2)
			       countDiaO[2] += 1;

			   if(countRowO[i] == 3){
			       if(winO.count(0) > 0){
				   return false;
			       }
			       winO[0] = i;
			   }
			   if(countColO[j] == 3){
			       if(winO.count(1) > 0){
				   return false;
			       }
			       winO[1] = j;
			   }
			   if(countDiaO[0] == 3){
			       if(winO.count(2) > 0){
				   return false;
			       }
			       winO[2] = 0;
			   }
			   if(countDiaO[2] == 3){
			       if(winO.count(3) > 0){
				   return false;
			       }
			       winO[3] = 2;
			   }
		       }
		   }
		}
		// cout << "rule 1 \n";
		if(numX < numO || numX > numO+1)
		    return false;
	//         rule 2, if both win
		// cout << "rule 2 \n";
		if(numX > numO){
	//             at most X win
		    if(winO.count(0)+winO.count(1)+winO.count(2)+winO.count(3) > 0)
			return false;
		}
		if(numX == numO){
		    if(winX.count(0)+winX.count(1)+winX.count(2)+winX.count(3) > 0)
			return false;
		}
		if((winX.count(0)+winX.count(1)+winX.count(2)+winX.count(3) > 0)
		   && (winO.count(0)+winO.count(1)+winO.count(2)+winO.count(3) > 0)){
		       return false;
		    }
	//             rule 2.2 if one win requires more than one move
	//             aka both row and col win is fine but
	//             if dia is win with row and col, then the row or col should share the same cell
		    if(winX.count(0)+winX.count(1)+winX.count(2) == 3){
			if(winX[0] != 0 || winX[1] != 0)
			    return false;
		    }
		    if(winX.count(0)+winX.count(1)+winX.count(3) == 3){
			if(winX[0] != 0 || winX[1] != 2)
			    return false;
		    }
		    if(winO.count(0)+winO.count(1)+winO.count(2) == 3){
			if(winO[0] != 0 || winO[1] != 0)
			    return false;
		    }
		    if(winO.count(0)+winO.count(1)+winO.count(3) == 3){
			if(winO[0] != 0 || winO[1] != 2)
			    return false;
		    }
	//         rule 3 only the one who makes the last move can win
		return true;
	    }
	
	// Mine No.670 Maximum Swap [M]
// Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get.

// Example 1:
// Input: 2736
// Output: 7236
// Explanation: Swap the number 2 and the number 7.
	static bool myfunction (int i,int j) { return (i>=j); }
	    int maximumSwap(int num) {
	//         try switch from left to right
		int count = log10 (num);
		int ret = num;
		vector<int> digits, optimal;
		unordered_map<int,vector<int>> position;
		for(int i = count; i >= 0; i--){
		    int cur = num / (pow(10.0, (double)(i)));
		    num -= cur * pow(10.0,(double)i);
		    digits.push_back(cur);
		    optimal.push_back(cur);
		    position[cur].push_back(i);
		    // cout << "position[" << cur << "]=" << position[cur] << "\n";
		}
	//         
		sort(optimal.begin(), optimal.end(), myfunction);
		// printVec(digits);
		// printVec(optimal);
		for(int i = 0; i < digits.size(); i++){
		    if(digits[i] < optimal[i]){
	//                 swap!
			// digits[position[optimal[i]]] = digits[i];
			// digits[i] = optimal[i];
			cout << "swap " << digits[i] << "to" << optimal[i] << "\n";
			vector<int> beswap = position[optimal[i]];
			sort(beswap.begin(), beswap.end());
	//                 find the smallest

			// cout << "(" << optimal[i] << "-" << digits[i] << ")*(pow," << digits.size()-1-i << ")-pow(10," << beswap[0] << ")\n";
			ret += (optimal[i] - digits[i]) * 
			    (pow(10, (double)(digits.size()-i-1)) 
			     - pow(10,(double)beswap[0]));
			return ret;
		    }
		}
		return ret;
	    }
	
};
