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
	// mine, read Du's

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
	// Mine
	// Think too complicated

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
	
	// Mine
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		if(accumulate(gas.begin(), gas.end(), 0) < accumulate(cost.begin(), cost.end(), 0))
		    return -1;
		bool round = false;
		for(int tryIndex = 0; tryIndex < gas.size() && !round; ){
		    int remainGas = 0;
		    bool isSuccess = true;
		    //cout << tryIndex << "\t";
		    for(int i = 0; i < gas.size(); i++){
			int cur = (i+tryIndex) % (int)(gas.size());
			if((i+tryIndex) > ((int)gas.size()))
			    round = true;
			remainGas += (gas[cur] - cost[cur]);
			if(remainGas < 0){
			    tryIndex = cur+1;
			    isSuccess = false;
			    //cout << "failed\n";
			    break;
			}
		    }
		    //cout << isSuccess << "\n";
		    if(isSuccess)
			return tryIndex;
		}
		return -1;
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
	
	// No.1005 Maximize Sum Of Array After K Negations (Mine)
	// Given an array A of integers, we must modify the array in the following way: we choose an i and replace A[i] with -A[i], and we repeat this process K times in total.  (We may choose the same index i multiple times.)

	// Return the largest possible sum of the array after modifying it in this way.



	// Example 1:

	// Input: A = [4,2,3], K = 1
	// Output: 5
	// Explanation: Choose indices (1,) and A becomes [4,-2,3].
	// Example 2:

	// Input: A = [3,-1,0,2], K = 3
	// Output: 6
	// Explanation: Choose indices (1, 2, 2) and A becomes [3,1,0,2].
	// Example 3:

	// Input: A = [2,-3,-1,5,-4], K = 2
	// Output: 13
	// Explanation: Choose indices (1, 4) and A becomes [2,3,-1,5,4].


	// Note:

	// 1 <= A.length <= 10000
	// 1 <= K <= 10000
	// -100 <= A[i] <= 100
	int largestSumAfterKNegations(vector<int>& A, int K) {
		// replace all the negative numbers as many as we can, let us say we have N negative numbers
		// if N <= K, then we replace (K-N)%2 (either 0 or 1) positive(or 0) numbers.
		// if n > K, we stop

		int smallest = INT_MAX;
		int sum = 0;
		sort(A.begin(), A.end());
		auto lower = lower_bound(A.begin(), A.end(), 0);
		int N = lower - A.begin();
		if(K >= N){
		    // flip all
		    if((K-N)%2==0){
			return abs(accumulate(A.begin(), lower, 0)) + accumulate(lower, A.end(), 0);
		    }else{
			// find the smallest absolute to substract
			int toBeSub = A[N];
			if(N>0 && abs(A[N-1]) < A[N])
			    toBeSub = abs(A[N-1]);
			return abs(accumulate(A.begin(), lower, 0)) - toBeSub*2 + accumulate(lower, A.end(), 0);
		    }
		}else{
		    // flip K
		    return abs(accumulate(A.begin(), A.begin()+K, 0)) + accumulate(A.begin()+K, A.end(), 0);
		}
	    }
	
	// No.455 Assign Cookies (Mine)
// 	Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie. Each child i has a greed factor gi, which is the minimum size of a cookie that the child will be content with; and each cookie j has a size sj. If sj >= gi, we can assign the cookie j to the child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.

// Note:
// You may assume the greed factor is always positive.
// You cannot assign more than one cookie to one child.

// Example 1:
// Input: [1,2,3], [1,1]

// Output: 1

// Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
// And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
// You need to output 1.
// Example 2:
// Input: [1,2], [1,2,3]

// Output: 2

// Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2. 
// You have 3 cookies and their sizes are big enough to gratify all of the children, 
// You need to output 2.
	int findContentChildren(vector<int>& g, vector<int>& s) {
		sort(g.begin(), g.end());
		sort(s.begin(), s.end());
		int ret = 0;
		for(int i = 0, j=0; i < g.size() && j < s.size();){
		    if(g[i] <= s[j]){
			++ret;
			++j;
			++i;
		    }else{
			++j;
		    }
		}
		return ret;
	    }
	
	// No.874 Walking Robot Simulation(Mine)
// 	A robot on an infinite grid starts at point (0, 0) and faces north.  The robot can receive one of three possible types of commands:

// 	-2: turn left 90 degrees
// 	-1: turn right 90 degrees
// 	1 <= x <= 9: move forward x units
// 	Some of the grid squares are obstacles. 

// 	The i-th obstacle is at grid point (obstacles[i][0], obstacles[i][1])

// 	If the robot would try to move onto them, the robot stays on the previous grid square instead (but still continues following the rest of the route.)

// 	Return the square of the maximum Euclidean distance that the robot will be from the origin.



// 	Example 1:

// 	Input: commands = [4,-1,3], obstacles = []
// 	Output: 25
// 	Explanation: robot will go to (3, 4)
// 	Example 2:

// 	Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
// 	Output: 65
// 	Explanation: robot will be stuck at (1, 4) before turning left and going to (1, 8)


// 	Note:

// 	0 <= commands.length <= 10000
// 	0 <= obstacles.length <= 10000
// 	-30000 <= obstacle[i][0] <= 30000
// 	-30000 <= obstacle[i][1] <= 30000
// 	The answer is guaranteed to be less than 2 ^ 31.
	unordered_map<int, vector<int> > obstaclesByRow, obstaclesByCol;
	    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
		int direction = 0;// 0-N, 1-W, 2-S, 3-E
		vector<int> origin(2,0);
		vector<int> target(2,0);
		vector<int> result(2,0);
		int dis = 0;

		for(int i = 0; i < obstacles.size(); i++){
		    if(obstaclesByRow.find(obstacles[i][0]) == obstaclesByRow.end()){
			obstaclesByRow[obstacles[i][0]] = {obstacles[i][1]};
		    }else{
			obstaclesByRow[obstacles[i][0]].push_back(obstacles[i][1]);
		    }
		    if(obstaclesByCol.find(obstacles[i][1]) == obstaclesByCol.end()){
			obstaclesByCol[obstacles[i][1]] = {obstacles[i][0]};
		    }else{
			obstaclesByCol[obstacles[i][1]].push_back(obstacles[i][0]);
		    }
		}
		for(auto obr : obstaclesByRow){
		    sort(obr.second.begin(), obr.second.end());
		    obstaclesByRow[obr.first] = obr.second;
		}
		for(auto obr : obstaclesByCol){
		    sort(obr.second.begin(), obr.second.end());
		    obstaclesByCol[obr.first] = obr.second;
		}
		// stage 2
		for(int i = 0; i < commands.size(); i++){
		    if(commands[i] == -1){
			direction = (direction+1)%4;
		    }else if(commands[i] == -2){
			direction = (direction+3)%4;
		    }else{
			switch(direction){
			    case 0:
				target = {origin[0], origin[1]+commands[i]};
				break;
			    case 1:
				target = {origin[0] + commands[i], origin[1]};
				break;
			    case 2:
				target = {origin[0], origin[1]-commands[i]};
				break;
			    case 3:
				target = {origin[0] - commands[i], origin[1]};
			    default:
				break;
			}
			//cout << direction << " " << target[0] << "," << target[1] << "\t";
			meetObstacles(origin, target, result);

			dis = max(dis, result[0] * result[0]+result[1]*result[1]);
			//cout << " after " << result[0] << "," << result[1] << "=" << dis << "\n";
			origin = result;
		    }
		}
		return dis;
	    }

	    int bsearch(vector<int>& arr, int val){
		int left = 0, right = arr.size()-1;
		while(left <= right){
		    int mid = (left+right) >> 1;
		    if(arr[mid] < val){
			left = mid+1;
		    }else if(arr[mid] > val){
			right = mid-1;
		    }else
			return mid;
		}
		return left-1;
	    }

	    int findClosest(vector<int>& arr, int origin, int target){
		int ret;
		// if origin < target, find the smallest one larger than origin
		if(origin < target){
		    ret = INT_MAX;
		    for(int a: arr){
			if(a > origin && a <= target)
			    ret = min(ret, a);
		    }
		}else if(origin > target){
		    // find the largest one smaller than origin
		    ret = INT_MIN;
		    for(int a: arr){
			if(a < origin && a >= target)
			    ret = max(ret, a);
		    }
		}
		return ret;
	    }

	    void meetObstacles(vector<int>& origin, vector<int>& target, vector<int>& result){
		result = target;
		for(int i = 0; i <= 1; i++){
		    if(origin[i] == target[i]){
			// go through the row map
			vector<int> os = i == 0 ? obstaclesByRow[origin[i]] : obstaclesByCol[origin[i]];
			// if(os.size() > 0){
			//     cout << "obstacles size " << os.size() << ":";
			//     for(auto o : os)
			//         cout << o << "\t";
			//     cout << "\n";
			// }

			if(target[1-i] > origin[1-i]){
			    // find the last element that smaller than target[1]
			    int obs = findClosest(os, origin[1-i], target[1-i]);
			    if(obs != INT_MAX && obs != INT_MIN){
				//cout << obs << "\n";
				if(i == 1)
				    result =  {obs-1, origin[i]};
				else
				    result = { origin[i], obs-1};
			    }

			    // auto lower = upper_bound(os.begin(), os.end(), origin[1]);
			    // if(lower != os.end()){
			    //     cout << os[lower-os.begin()] << "\n";
			    //     result = {origin[0], os[lower-os.begin()]-1};
			    // }
			}else{
			    // find the last element that smaller than target[1]
			    //auto lower = lower_bound(os.begin(), os.end(), target[1-i]);
			    int obs = findClosest(os, origin[1-i], target[1-i]);
			    if(obs != INT_MAX && obs != INT_MIN){
				//cout << obs << "\n";
				if(i == 1)
				    result =  {obs+1, origin[i]};
				else
				    result = { origin[i], obs+1};
			    }
			    // if(lower != os.end() && os[lower-os.begin()] < origin[1-i]){
			    //     cout << os[lower-os.begin()] << "\n";
			    //     if(i == 1)
			    //         result = {os[lower-os.begin()]+1, origin[i]};
			    //     else
			    //         result = {origin[1-i], os[lower-os.begin()]+1};
			    // }
			}
		    }
		}
	    }
}
