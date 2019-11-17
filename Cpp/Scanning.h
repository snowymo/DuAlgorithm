#pragma once
#include "common.h"

class Scanning {
	// 209. Minimum Size Subarray Sum [M]
	// Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum >= s. If there isn't one, return 0 instead.
	// Solution: Linear scanning with a left pointer
	// Time: O(n)
	int minSubArrayLen(int s, vector<int>& nums) {
		int l = -1, res = INT_MAX, sum = 0, n = (int)nums.size();
		for (int i = 0; i < n; ++i) {
			sum += nums[i];
			while (sum >= s) {
				res = min(res, i - l);
				sum -= nums[++l];
			}
		}
		return res != INT_MAX ? res : 0;
	}
	// Mine
	int minSubArrayLen(int s, vector<int>& nums) {
		if(nums.size() == 0)
		    return 0;
		vector<int> sums(nums.size()+1);
		for(int i = 0; i < nums.size(); i++)
		    sums[i+1] = sums[i] + nums[i];
		// solution 1, use lower_bound since numbers are all positive
		int ret = INT_MAX;
		for(int i = 0; i < sums.size(); i++){
		    int to_find = s+sums[i];
		    auto lower = lower_bound(sums.begin()+i, sums.end(), to_find);
		    //cout << "i " << i << " index " << int(lower-sums.begin()) << "\n";
		    if(lower != sums.end())
			ret = min(ret, int(lower-sums.begin())-i);
		}
		return ret == INT_MAX ? 0 : ret;
	    }
	// Not using lower bound
	int minSubArrayLen(int s, vector<int>& nums){
		int sum = 0, start = 0;
		int ans = INT_MAX;
		for(int i = 0; i < nums.size(); i++){
		    sum += nums[i];
		    while(sum >= s){
			ans = min(ans, i-start+1);
			sum -= nums[start++];
		    }
		}
		return ans == INT_MAX ? 0 : ans;
	    }

	// 849. Maximize Distance to Closest Person
	int maxDistToClosest(vector<int>& seats) {
		int res = 0, cnt = 0;
		bool ends = true;
		for (const auto &seat : seats) {
			if (seat == 0) {
				cnt += 1;
			}
			else {
				if (!ends) {
					cnt = (cnt + 1) >> 1;
				}
				res = max(res, cnt);
				cnt = 0;
				ends = false;
			}
		}
		return max(res, cnt);
	}
	// Mine
	int maxDistToClosest(vector<int>& seats) {
		vector<int> dis(seats.size(), INT_MAX);
		int left = INT_MAX;
		for(int i = 0; i < seats.size(); i++){
		    if(seats[i] == 1)
			left = i;
		    dis[i] = left == INT_MAX ? INT_MAX : abs(left-i);
		}

		int right = INT_MAX;
		int ret = 0;
		for(int i = seats.size()-1; i >= 0; i--){
		    if(seats[i] == 1)
			right = i;
		    dis[i] = right == INT_MAX ? dis[i] : min(dis[i],abs(right-i));
		    ret = max(dis[i], ret);
		}
		return ret;//*max_element(dis.begin(), dis.end());
	    }

	// 11. Container With Most Water [M]
	// Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.
	// Input: [1,8,6,2,5,4,8,3,7]
	// Output: 49
	// Time: O(N)
	int maxArea(vector<int>& height) {
		int i = 0, j = (int)height.size() - 1, ans = 0;

		while (i < j) {
			auto hi = height[i], hj = height[j];
			ans = max(ans, min(hi, hj) * (j - i));
			if (hi < hj) {
				++i;
			}
			else if (hi > hj) {
				--j;
			}
			else {
				++i;
				--j;
			}
		}

		return ans;
	}
	// Mine
	int maxArea(vector<int>& height) {
		int ret = 0;
		for(int i = 0, j = height.size()-1; i < j;){
		    ret = max(ret,min(height[i], height[j]) * (j-i));
		    if(height[i] < height[j]){
			++i;
		    }else{
			--j;
		    }
		}
		return ret;
	    }

	// 53. Maximum Subarray
	// Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.
	// Time: O(n)
	int maxSubArray(vector<int>& nums) {
		const int n = (int)nums.size();
		if (n == 0) return 0;
		int ans = nums[0], curmax = ans;
		for (int i = 1; i < n; ++i) {
			curmax = max(curmax + nums[i], nums[i]);
			ans = max(ans, curmax);
		}
		return ans;
	}

	// 55. Jump Game
	// Given an array of non-negative integers, you are initially positioned at the first index of the array.
	// Each element in the array represents your maximum jump length at that position.
	// Determine if you are able to reach the last index.
	bool canJump(vector<int>& nums) {
		size_t n = nums.size();
		int res = 0;
		bool* vd = new bool[n];
		memset(vd, false, n * sizeof(bool));

		for (int i = 0; i < n; ++i) if (nums[i] > 0 && i <= res) {
			res = max(res, nums[i] + i);
		}
		return res >= n - 1;
	}

	int removeDuplicatesTwice(vector<int>& nums) {
		int n = (int)nums.size();
		if (n <= 2) return n;
		int index = 2;

		for (size_t i = index; i < n; ++i) {
			if (nums[i] != nums[index - 2]) nums[index++] = nums[i];
		}
		return index;
	}

	// 169. Majority Element
	// Given an array of size n, find the majority element. The majority element is the element that appears more than n/2 times.
	int majorityElement(vector<int>& nums) {
		// O(n) time, O(1) space;
		//   "5,4,4,2,1,5,5,5,5,2,1"
		//    5 5 4 4 1 1 5 5 5 5 5
		//    1 0 1 0 1 0 1 2 3 2 1

		int majority = 0;
		int count = 0;

		for (int x : nums) {
			if (count == 0) {
				majority = x;
				++count;
			}
			else {
				if (majority == x) {
					++count;
				}
				else {
					--count;
				}
			}
		}
		return majority;
	}

	// 229. Majority Element II [M]
	// Given an integer array of size n, find all elements that appear more than |_ n/3 _| times.
	vector<int> majorityElementII(vector<int>& nums) {
		// 1,1,1,2,2,2,3,3,3,1,2
		// 3,2,1,3,2,1,3,2,1
		// 1,2,3,4
		const int n = (int)nums.size();
		int top1 = INT_MIN, top2 = INT_MIN;
		int cnt1 = 0, cnt2 = 0;

		for (int x : nums) {
			if (cnt2 <= 0 && x != top1) {
				top2 = x;
				cnt2 = 1;
			}
			else
			if (cnt1 <= 0 && x != top2) {
				top1 = x;
				cnt1 = 1;
			}
			else
			if (x == top1) {
				++cnt1;
				--cnt2;
			}
			else
			if (x == top2) {
				++cnt2;
				--cnt1;
			}
			else {
				--cnt1;
				--cnt2;
			}

			if (cnt2 > cnt1) {
				swap(top1, top2);
				swap(cnt2, cnt1);
			}
		}
		vector<int> ans;
		if (checkOneThird(nums, top2)) ans.push_back(top2);
		if (top2 != top1 && checkOneThird(nums, top1)) ans.push_back(top1);
		return ans;
	}

	bool checkOneThird(vector<int>& nums, int target) {
		const int n = (int)nums.size();
		int times = 0;
		for (int x : nums) if (x == target) {
			++times;
			if (times > floor((double)n / 3)) return true;
		}
		return false;
	}
	// Mine
	vector<int> majorityElement(vector<int>& nums) {
		unordered_map<int,int> count;
		vector<int> ret;
		for(int i = 0; i < nums.size(); i++){
		    ++count[nums[i]];
		    if((count[nums[i]]) > ((int)nums.size()/3)){
			ret.push_back(nums[i]);
			count[nums[i]]= -10 * nums.size();
		    }                
		}
		return ret;
	    }

	int threeSumSmaller(vector<int>& nums, int target) {
		if (nums.size() < 3) return 0;
		int res = 0;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 2; ++i) {
			int left = i + 1, right = (int)nums.size() - 1;
			while (left < right) {
				if (nums[i] + nums[left] + nums[right] < target) {
					res += right - left;
					++left;
				}
				else {
					--right;
				}
			}
		}
		return res;
	}

	// 45. Jump Game II [H?]
	// Given an array of non-negative integers, you are initially positioned at the first index of the array.
	// Each element in the array represents your maximum jump length at that position.
	// Your goal is to reach the last index in the minimum number of jumps.
	/*
	Input: [2,3,1,1,4]
	Output: 2
	Explanation: The minimum number of jumps to reach the last index is 2.
    Jump 1 step from index 0 to 1, then 3 steps to the last index.
	*/
	int jump(vector<int>& nums) {
		const size_t n = nums.size();
		int steps = 0;
		int left = 0, right = 0;
		if (n == 1) return 0;
		while (left <= right) {
			++steps;
			const int prev_right = right;
			for (int i = left; i <= prev_right; ++i) {
				int new_right = i + nums[i];
				if (new_right >= n - 1) return steps;
				if (new_right > right) right = new_right;
			}
			left = prev_right + 1;
		}
		return 0;
	}

	// 76. Minimum Window Substring [H]
	// Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).
	// Input: S = "ADOBECODEBANC", T = "ABC"
	// Output: "BANC"
	// Solution: Sliding-window Scanning with two pointers, use a hash map to remember the counts in T
	// Time: O(n)
	string minWindow(string s, string t) {
		// Use a vector storing the counts of t's characters
		// +: uneliminated chars in t
		// -: overflow chars in s
		vector<int> d(128, 0);
		for (const auto &c : t)
			++d[(int)c];

		int n = (int)s.size(), m = (int)t.size();
		int l = 0, cnt = 0;
		int res = -1, len = INT_MAX;

		for (int r = 0; r < n; ++r) {
			if (--d[(int)s[r]] >= 0)
				++cnt;
			while (cnt == m) {
				if (len > r - l + 1) {
					len = r - l + 1;
					res = l;
				}
				if (++d[s[l++]] > 0)
					--cnt;
			}
		}
		return res >= 0 ? s.substr(res, len) : "";
	}

	// 632. Smallest Range [H][VH]
	// You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists. 
	/*
	Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
	Output: [20,24]
	Explanation: 
	List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
	List 2: [0, 9, 12, 20], 20 is in range [20,24].
	List 3: [5, 18, 22, 30], 22 is in range [20,24].
	*/
	vector<int> smallestRange(vector<vector<int>>& nums) {
		// merge everything to a sorted array with group id
		// the problem is converted to minimum window substring
		vector<pair<int, int>> a;
		for (int i = 0; i < (int)nums.size(); ++i) {
			for (int x : nums[i])
				a.push_back({ x, i });
		}
		sort(a.begin(), a.end());

		int l = 0, n = (int)a.size(), k = (int)nums.size(), cnt = 0, len = INT_MAX;
		vector<int> d(k, 0), res;

		// sliding window scanning with two pointers to find the minimum range
		for (int r = 0; r < n; ++r) {
			if (d[a[r].second]++ == 0)
				++cnt;
			while (cnt == k) {
				auto al = a[l].first, ar = a[r].first;
				if (len > ar - al) {
					len = ar - al;
					res = { al, ar };
				}
				if (--d[a[l++].second] == 0)
					--cnt;
			}
		}
		return res;
	}

	// 228. Summary Ranges [M]
	// Given a sorted integer array without duplicates, return the summary of its ranges.
	// Input:  [0,1,2,4,5,7]
	// Output: ["0->2", "4->5", "7"]
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> ans;
		if (nums.empty()) return ans;
		int l = nums[0], r = l;

		for (size_t i = 1; i < nums.size(); ++i) {
			if (nums[i] == r + 1) {
				++r;
			}
			else {
				if (r > l)
					ans.push_back(to_string(l) + "->" + to_string(r));
				else
					ans.push_back(to_string(l));
				l = nums[i];
				r = l;
			}
		}
		if (r > l)
			ans.push_back(to_string(l) + "->" + to_string(r));
		else
			ans.push_back(to_string(l));
		return ans;
	}
	// Mine
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> rets;
		if(nums.size() == 0)
		    return rets;

		int last = INT_MAX;
		int start = nums[0];
		for(int i = 0; i < nums.size(); i++){
		    if(last == INT_MAX || (long)((long)nums[i]-(long)last) == 1L){
			// continuous
			last = nums[i];
		    }else{
			// gap
			rets.push_back(generateRange(start, last));
			start = nums[i];
			last = nums[i];
		    }
		    if(i == ((int)nums.size()-1))
			rets.push_back(generateRange(start, last));
		}
		return rets;
	    }
	    string generateRange(int start, int end){
		string ret = to_string(start);
		if(end > start)
		    ret += "->" + to_string(end);
		return ret;
	    }

	// 904. Fruit Into Baskets [E]
	// You have two baskets, and each basket can carry any quantity of fruit, but you want each basket to only carry one type of fruit each.
	// What is the total amount of fruit you can collect with this procedure?
	int totalFruit(vector<int>& tree) {
		const int n = (int)tree.size();
		if (n <= 2)
			return n;

		int l = 0, r = 0;
		int A = tree[0], a = 1, B = -1, b = 0;
		int res = 1;

		while (r < n - 1) {
			int C = tree[++r];

			if (A == C)
				++a;
			else
			if (B == C)
				++b;
			else
			if (b == 0) {
				B = C;
				++b;
			}
			else
			if (a == 0) {
				A = C;
				++a;
			}
			else {
				while (a > 0 && b > 0) {
					if (tree[l++] == A)
						--a;
					else
						--b;
				}
				--r;
				continue;
			}
			res = max(res, r - l + 1);
		}
		return res;
	}
	// Mine
	int totalFruit(vector<int>& tree) {
		int ret = 0;
		int maxret = 0;
		int start1 = -1, end1 = -1, start2 = -1, end2 = -1;
		int fruit1 = -1, fruit2 = -1;
		for(int i = 0; i < tree.size(); i++){
		    if(fruit1 == tree[i]){
			end1 = i;
			++ret;
		    }else if(fruit2 == tree[i]){
			end2 = i;
			++ret;
		    }
		    else if(start1 == -1){
			start1 = end1 = i;
			fruit1 = tree[i];
			ret = 1;
		    }else if(start2 == -1){
			start2 = end2 = i;
			fruit2 = tree[i];
			++ret;
		    }else{
			// the third fruit
			maxret = max(ret, maxret);
			// fruit2 should be the third one, and fruit1 should be tree[i-1]
			if(fruit1 == tree[i-1]){
			    // keep fruit1 and discard fruit2
			    ret = i-max(start1, end2+1)+1;
			    fruit2 = tree[i];
			    start2 = end2 = i;
			}else{
			    // keep fruit2 and discard fruit1
			    ret = i-max(start2, end1+1)+1;
			    fruit1 = tree[i];
			    start1 = end1 = i;
			}        
		    }
		    // cout << fruit1 << ":" << start1 << " " << end1 << ";"
		    //     << fruit2 << ":" << start2 << " " << end2 << "=" << ret << "\n";
		}
		return max(ret,maxret);
	    }

	// 238. Product of Array Except Self [M]
	// Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
	// Solution: maintain l as the left product except itself
	// scan from right to left, maintain with the current product and multiple by it
	vector<int> productExceptSelf(vector<int>& nums) {
		const int n = (int)nums.size();
		vector<int> l(n, 1);
		if (nums.empty())
			return l;

		int r = 1;
		for (int i = 1; i < n; ++i)
			l[i] = l[i - 1] * nums[i - 1];
		for (int i = n - 2; i >= 0; --i) {
			r *= nums[i + 1];
			l[i] *= r;
		}
		return l;
	}
	// Mine
	vector<int> productExceptSelf(vector<int>& nums) {
		vector<int> ret(nums.size(), 1);
		vector<int> L(nums.size(), 1), R(nums.size(), 1);
		for(int i = 1; i < nums.size(); i++){
		    L[i] = L[i-1] * nums[i-1];
		}
		for(int i = nums.size()-2; i >= 0; i--){
		    R[i] = R[i+1] * nums[i+1];
		}
		for(int i = 0; i < ret.size(); i++){
		    ret[i] = L[i] * R[i];
		}
		return ret;
	    }
	vector<int> productExceptSelf(vector<int>& nums) {
		vector<int> ret(nums.size(), 1);
		for(int i = 1; i < nums.size(); i++){
		    ret[i] = ret[i-1] * nums[i-1];
		}
		int R = 1;
		for(int i = nums.size()-2; i >= 0; i--){
		    R *= nums[i+1];
		    ret[i] *= R;
		}
		return ret;
	    }

	// 274. H-Index
	int hIndex(vector<int>& citations) {
		const int n = (int)citations.size();
		int ans = 0;
		sort(citations.begin(), citations.end(), greater<int>());


		for (int i = 0; i < n; ++i) {
			if (i >= citations[i]) return i;
		}
		return n;
	}
	// Mine
	int hIndex(vector<int>& citations) {
		sort(citations.begin(), citations.end());
		int size = citations.size();
		if(size == 0)
		    return 0;
		if(size == 1)
		    return citations[0] > 0 ? 1 : 0;
		int left = 0, right = size;
		while(left <= right){
		    int mid = (left+right) >> 1;
		    //cout << left << " " <<right << " " << mid << "\n";
		    // let's check if mid meets requirement
		    if(mid == 0 || citations[size-mid] >= mid){
			left = mid+1;
		    }else{
			right = mid-1;
		    }
		}
		return max(0,left-1);
	    }

	// 275. H-Index II
	int hIndexII(vector<int>& citations) {
		const int n = (int)citations.size();
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			ans = max(ans, min(n - i, citations[i]));
		}
		return ans;
	}

	// 306. Additive Number [M]
	// Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.
	// 112358
	// Time:  O(n^3)
	// Space: O(n)
	bool isAdditiveNumber(string num) {
		const auto n = num.size();

		for (size_t i = 1; i < n; ++i) {
			for (size_t j = i + 1; j < n; ++j) {
				auto a = num.substr(0, i), b = num.substr(i, j - i);
				if ((a.size() > 1 && a[0] == '0') ||
					(b.size() > 1 && b[0] == '0'))
					continue;
				auto next = add(a, b);
				string cur = a + b + next;
				size_t p = a.size() + b.size();
				while (cur.size() < n) {
					if (num.substr(p, next.size()) != cur.substr(p, next.size()))
						break;
					p += next.size();
					a = b;
					b = next;
					next = add(a, b);
					cur += next;
				}
				if (cur.size() == n && num.substr(p, next.size()) == cur.substr(p, next.size()))
					return true;
				// if (cur == num) return true;
			}
		}
		return false;
	}

	string add(const string &a, const string &b) {
		string res;
		const int n = (int)a.size(), m = (int)b.size();

		int carry = 0;
		for (int i = 0; i < max(n, m); ++i) {
			int x = i < n ? a[n - i - 1] - '0' : 0;
			int y = i < m ? b[m - i - 1] - '0' : 0;
			int sum = carry + x + y;
			carry = sum / 10;
			sum %= 10;
			res.push_back('0' + sum);
		}
		if (carry)
			res.push_back('0' + carry);
		reverse(res.begin(), res.end());
		return res;
	}
	
	// Mine
	bool isAdditiveNumber(string num) {
		int size = num.size();

		for(int lastTry1 = 1; lastTry1 < size; lastTry1++){
		    for(int lastTry2 = 1; lastTry2+lastTry1+max(lastTry1,lastTry2)<=size; lastTry2++){
			bool ans = evaluate(num, 0, lastTry1, lastTry2);
			if(ans){
			   return true;
			}
		    }
		}
		return false;
	    }
	    bool evaluate(string & num, int start, int index1, int index2){
		//cout << start << " " << index1 << " " << index2 << "\n";
		if(start+index1+index2 == int(num.size()))
		    return true;
		if(start+index1+index2 > int(num.size()))
		    return false;
		if(start+index1+index2+max(index1,index2) > int(num.size()))
		    return false;
		string s1 = num.substr(start, index1);
		string s2 = num.substr(start+index1, index2);
		//cout << "s1 " << s1 << " s2 " << s2 << "\n";
		long long i1 = stoll(s1, 0, 10);
		long long i2 = stoll(s2, 0, 10);
		// make sure no prefix 0
		//cout << i1 << " index1 should be " << max(1, int(log(i1) / log(10)) + 1) << " now is " << index1 << "\n";
		//cout << i2 << " index2 should be " << max(1, int(log(i2) / log(10)) + 1) << " now is " << index2 << "\n";
		if(max(1, int(log(i1) / log(10)) + 1) != index1)
		    return false;
		// make sure no prefix 0
		if(max(1, int(log(i2) / log(10)) + 1) != index2)
		    return false;
		long long isum = i1+i2;
		int len = max(1, int(log(isum) / log(10)) + 1);
		//cout << "len " << len << "\n";
		if(start+index1+index2+len > long(num.size()))
		    return false;
		string s3 = num.substr(start+index1+index2, len);
		//cout << "s3 " << s3 << "\n";
		if(stol(s3, 0, 10) != isum)
		    return false;

		return evaluate(num, start+index1, index2, len);
	    }
};
