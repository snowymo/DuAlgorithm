#pragma once
#include "common.h"

namespace Greedy {
	// 630. Course Schedule III [H]
	// There are n different online courses numbered from 1 to n. Each course has some duration(course length) t and closed on dth day. A course should be taken continuously for t days and must be finished before or on the dth day. You will start at the 1st day.
	// Given n online courses represented by pairs(t, d), your task is to find the maximal number of courses that can be taken.
	// Solution: Greedy
	// Time: O(n)
	// Proof: Sort by end date, if the current course cannot be completed, we have to remove one course
	// if we remove something longer than the maximum one, 
	// it is possible we can have a smaller end date which yields the next one to the schedule -> contradictory!
	int scheduleCourse(vector<vector<int>>& courses) {
		sort(courses.begin(), courses.end(), [](const vector<int>& a, const vector<int>& b) {
			return a[1] < b[1];
		});

		// a max heap
		priority_queue<int> h;
		// time
		int t = 0;

		for (const auto &c : courses) {
			h.emplace(c[0]);
			t += c[0];
			if (t > c[1]) {
				t -= h.top();
				h.pop();
			}
		}
		return (int)h.size();
	}

	// 853. Car Fleet [M]
	// Given positions and speeds of cars and a target destination, count number of fleets
	// Time:  O(n log n)
	// Space: O(n)
	int carFleet(int target, vector<int>& position, vector<int>& speed) {
		using PosTime = pair<int, double>;
		vector<PosTime> cars;
		const int N = (int)position.size();
		for (int i = 0; i < N; ++i) {
			cars.emplace_back(position[i], (double)(target - position[i]) / speed[i]);
		}
		sort(cars.begin(), cars.end(), [](const PosTime& a, const PosTime &b) {
			return a.first == b.first ? a.second < b.second : a.first < b.first;
		});
		int res = 0;
		double cur = 0;
		for (int i = N - 1; i >= 0; --i) {
			if (cars[i].second > cur) {
				cur = cars[i].second;
				++res;
			}
		}
		return res;
	}

	// 134. Gas Station
	// There are N gas stations along a circular route, where the amount of gas at station i is gas[i]. You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station(i + 1).You begin the journey with an empty tank at one of the gas stations. Return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1.
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		const int n = (int)gas.size();
		int total_gas = 0, total_cost = 0, highest_cost = 0, start = 0;
		for (int i = 0; i < n; ++i) {
			total_gas += gas[i];
			total_cost += cost[i];
			if (cost[i] > highest_cost && gas[(i + 1) % n] > cost[(i + 1) % n]) {
				highest_cost = cost[i];
				start = (i + 1) % n;
			}
		}
		if (total_gas < total_cost) return -1; else return start;
	}

	// 330. Patching Array
	// Given a sorted positive integer array nums and an integer n, add/patch elements to the array such that any number in range [1, n] inclusive can be formed by the sum of some elements in the array. Return the minimum number of patches required.
	// Time: O(M + log N)
	// Space: O(1)
	int minPatches(vector<int>& nums, int n) {
		// nums = [1, 2, 4, 11, 30], n = 50
		// 1,2,4 => [0, 8), add 8
		// 1,2,4,8 => [0, 16), no need for 16 because 1+4+11
		// 1,2,4,8,11 => [0, 27), add 27
		const int M = (int)nums.size();
		int i = 0, res = 0;
		const long long N = (long long)n;
		long long miss = 1;
		while (miss <= N) {
			if (i < M && nums[i] <= miss) {
				miss += nums[i++];
			}
			else {
				miss += miss;
				++res;
			}
		}
		return res;
	}
	// --- EASY---
	// No.1221 Split a String in Balanced Strings (Mine)
// Balanced strings are those who have equal quantity of 'L' and 'R' characters.

// Given a balanced string s split it in the maximum amount of balanced strings.

// Return the maximum amount of splitted balanced strings.
	int balancedStringSplit(string s) {
		// seems there is only one solution, we just scan to get it
		int count = 0;
		int cntL = 0;
		for(int i = 0; i < s.size(); i++){
		    --cntL;
		    if(s[i] == 'L')
			cntL += 2;
		    if(cntL == 0)
			++count;
		}
		return count;
	    }
	
	// No.944 Delete Columns to Make Sorted (Mine)
// We are given an array A of N lowercase letter strings, all of the same length.

// Now, we may choose any set of deletion indices, and for each string, we delete all the characters in those indices.

// For example, if we have an array A = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3}, then the final array after deletions is ["bef", "vyz"], and the remaining columns of A are ["b","v"], ["e","y"], and ["f","z"].  (Formally, the c-th column is [A[0][c], A[1][c], ..., A[A.length-1][c]].)

// Suppose we chose a set of deletion indices D such that after deletions, each remaining column in A is in non-decreasing sorted order.

// Return the minimum possible value of D.length.
	int minDeletionSize(vector<string>& A) {
		// go through each column and figure out if it is non-decreasing, if yes, add 1
		int ret = 0;
		for(int i = 0; i < A[0].size(); i++){
		    // check column i
		    for(int j = 1; j < A.size(); j++){
			if(A[j][i] < A[j-1][i]){
			    ++ret;
			    break;
			}
		    }
		}
		return ret;
	    }
	
	// No.1217 Play with Chips (Mine)
// There are some chips, and the i-th chip is at position chips[i].

// You can perform any of the two following types of moves any number of times (possibly zero) on any chip:

// Move the i-th chip by 2 units to the left or to the right with a cost of 0.
// Move the i-th chip by 1 unit to the left or to the right with a cost of 1.
// There can be two or more chips at the same position initially.

// Return the minimum cost needed to move all the chips to the same position (any position).
	int minCostToMoveChips(vector<int>& chips) {
		int oddCnt = 0;
		for(int i = 0; i < chips.size(); i++){
		    if(chips[i] % 2 == 1)
			++oddCnt;
		}
		return oddCnt > ((int)chips.size() - oddCnt) ? ((int)chips.size() - oddCnt) : oddCnt;
	    }
	
	// No.1046 Last Stone Weight (Mine)
// We have a collection of rocks, each rock has a positive integer weight.

// Each turn, we choose the two heaviest rocks and smash them together.  Suppose the stones have weights x and y with x <= y.  The result of this smash is:

// If x == y, both stones are totally destroyed;
// If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
// At the end, there is at most 1 stone left.  Return the weight of this stone (or 0 if there are no stones left.)
	int lastStoneWeight(vector<int>& stones) {
		int n = stones.size();
		while(n > 2){
		    int l1,l2, i1, i2;
		    findLargest2(stones, n, l1, l2, i1, i2);
		    int newValue = abs(l1-l2);

		    if(i2 == n-1)
			swap(stones[i1], stones[n-2]);
		    else
			swap(stones[i1], stones[n-1]);
		    stones.pop_back();
		    if(i2 != n-1)
			swap(stones[i2], stones[n-2]);
		    stones[n-2] = newValue;
		    stones[n-2] = newValue;
		    --n;
		    if(newValue == 0){
			--n;
		    }
		}
		if(n == 2)
		    return abs(stones[0] - stones[1]);
		return stones[0];
	    }

	    void findLargest2(vector<int>& stones, int& n, int& l1, int& l2, int&i1, int&i2){
		i1 = 1;
		i2 = 0;
		if(stones[0] > stones[1]){
		    i1 = 0;
		    i2 = 1;
		}
		l1 = stones[i1];
		l2 = stones[i2];

		for(int i = 2; i < n; i++){
		    if(stones[i] > l1){
			l2 = l1;
			i2 = i1;
			l1 = stones[i];
			i1 = i;
		    }else if(stones[i] > l2){
			l2 = stones[i];
			i2 = i;
		    }
		}
		//cout << i1 << " " << l1 << " " << i2 << " " << l2 << "\n";
	    }
	
	// No.1029 Two City Scheduling (Mine)
// There are 2N people a company is planning to interview. The cost of flying the i-th person to city A is costs[i][0], and the cost of flying the i-th person to city B is costs[i][1].

// Return the minimum cost to fly every person to a city such that exactly N people arrive in each city.

 

// Example 1:

// Input: [[10,20],[30,200],[400,50],[30,20]]
// Output: 110
// Explanation: 
// The first person goes to city A for a cost of 10.
// The second person goes to city A for a cost of 30.
// The third person goes to city B for a cost of 50.
// The fourth person goes to city B for a cost of 20.

// The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.
	int twoCitySchedCost(vector<vector<int>>& costs) {
		multimap<int, vector<int>> mymap; // delta cost,{person, cityA, cityB}
		vector<bool> assigned(costs.size(), false); // if true, one city of the person is chosen
		// first fill the costs
		for(int i = 0; i < costs.size(); i++){
		    mymap.insert(pair<int, vector<int>>(-abs(costs[i][0]-costs[i][1]), {i, costs[i][0], costs[i][1]}));
		}
		// since it is map. it is already sorted
		int lastCost = INT_MAX;,lastPerson = -1,lastOtherCost = INT_MAX,numA = 0, numB = 0;
		int ret = 0;
		for(auto it = mymap.begin(); it != mymap.end() && (numA*2) != (int)costs.size() && (numB*2) != (int)costs.size(); it++){
		    //cout << it->first << " " << it->second[0] << "\n";
		    if(assigned[it->second[0]])
			continue;

		    if(lastCost != INT_MAX){
			// compare to see if we want to update last(same) or decide the last(different)
			if(lastCost == it->first){
			    if(lastOtherCost > (it->second[2]+it->second[1])){
				lastPerson = it->second[0];
				lastOtherCost = (it->second[2]+it->second[1]);

			    }
			}else{
			    // finalize the last option
			    if(costs[lastPerson][0] < costs[lastPerson][1]){
				++numA;
				ret += costs[lastPerson][0];

			    //cout << "pick " << lastPerson << " city A " << costs[lastPerson][0] << "\n";
			    }else{
				++numB;
				ret += costs[lastPerson][1];
				//cout << "pick " << lastPerson << " city B " << costs[lastPerson][1] << "\n";
			    }
			    assigned[lastPerson] = true;

			}
		    }

		    // assign the value
		    lastCost = abs(it->second[1] - it->second[2]);
		    lastPerson = it->second[0];
		    if(assigned[it->second[0]]){
			// the person was just assigned
			lastCost = INT_MAX;
		    }
		    lastOtherCost = min(lastOtherCost, (it->second[2]+it->second[1]));
		}

		for(int i = 0; i < costs.size(); i++){
		    if(!assigned[i]){
			if(numA*2 == (int)costs.size()){
			    //cout << "pick " << i << " city B" << costs[i][1] << "\n";
			    ret += costs[i][1];
			}else{
			    //cout << "pick " << i << " city A" << costs[i][0] << "\n";
			    ret += costs[i][0];
			}
		    }

		}

		return ret;
	    }
	
	// No.860 Lemonade Change (Mine)
// 	At a lemonade stand, each lemonade costs $5. 

// 	Customers are standing in a queue to buy from you, and order one at a time (in the order specified by bills).

// 	Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill.  You must provide the correct change to each customer, so that the net transaction is that the customer pays $5.

// 	Note that you don't have any change in hand at first.

// 	Return true if and only if you can provide every customer with correct change.
	bool lemonadeChange(vector<int>& bills) {
		unordered_map<int,int> current_cash; // only has[5] [10] and [20]
		for(int i = 0; i < bills.size(); i++){
		    switch(bills[i]){
			case 5:
			    // take it
			    ++current_cash[5];
			    //cout << "5 " << current_cash[5] << "\n";
			    break;
			case 10:
			    // let us see if we have 1 '5'
			    if(current_cash[5] < 1){
				return false;
			    }
			    ++current_cash[10];
			    --current_cash[5];
			    //cout << "5 " << current_cash[5] << "\n";
			    //cout << "10 " << current_cash[10] << "\n";
			    break;
			case 20:
			    // 3 '5' or 1 '5' + 1 '10'
			    if(current_cash[10] > 0 && current_cash[5] > 0){
				--current_cash[10];
				--current_cash[5];
			    }else if(current_cash[5] > 2){
				current_cash[5] -= 3;
			    }else
				return false;
			    //cout << "5 " << current_cash[5] << "\n";
			    //cout << "10 " << current_cash[10] << "\n";
			default:
			    break;
		    }
		}
		return true;
	    }
}
