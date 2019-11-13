#pragma once
#include "common.h"
namespace SortMisc {

	// 280. Wiggle Sort [L][M]
	// Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]...
	// O(n) time and O(1) space
	void wiggleSort(vector<int> &nums) {
		if (nums.size() <= 1) return;
		for (int i = 1; i < nums.size(); ++i) {
			if ((i % 2 == 1 && nums[i] < nums[i - 1]) || (i % 2 == 0 && nums[i] > nums[i - 1])) {
				swap(nums[i], nums[i - 1]);
			}
		}
	}

	// 324. Wiggle Sort II [M]
	// Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
	// O(n) time and O(1) space
	void wiggleSortStrict(vector<int>& nums) {
#define A(i) nums[(1 + 2 * i) % (n | 1)]
		int n = (int)nums.size(), i = 0, j = 0, k = n - 1;
		auto midptr = nums.begin() + n / 2;
		nth_element(nums.begin(), midptr, nums.end());
		int median = *midptr;
		while (j <= k) {
			if (A(j) > median)
				swap(A(i++), A(j++));
			else if (A(j) < median)
				swap(A(j), A(k--));
			else
				++j;
		}
	}
	// Mine
	    void wiggleSort(vector<int>& nums) {
		if(nums.size() <= 1)
		    return ;
		if(nums.size() == 2){
		    if(nums[0] > nums[1])
			swap(nums[0], nums[1]);
		    return ;
		}

		vector<int> vect2 = nums; 
		sort(vect2.begin(), vect2.end());
		// for(int i = 0; i < nums.size(); i++){
		//     if(i%2 == 1){
		//         nums[i] = vect2[vect2.size()-(i-1)/2-1];
		//     }else{
		//         nums[i] = nums.size()%2==1?vect2[vect2.size()/2-i/2]:vect2[vect2.size()/2-1-i/2];
		//     }
		// }
		if(nums.size() % 2 == 1)
		    nums[nums.size()-1] = vect2[0];
		int size = nums.size();
		int halfsize = (size+1)/2;
		for(int i = 0; i < nums.size()/2 ;i++){
		    nums[i*2] = vect2[halfsize-1-i];
		    nums[i*2+1] = vect2[size-1-i];
		}
		// int lastEven = (nums.size()/2-1)*2;
		// int lastOdd = nums.size()%2==0?lastEven+1:lastEven-1;
		// if(nums[lastEven] == nums[lastOdd])
		//     swap(nums[0], nums[lastEven]);
	    }

	// Time and Space: O(N)
	string frequencySort(string &s) {
		unordered_map<char, int> freq;
		for (const auto& c : s) {
			++freq[c];
		}

		const auto n = s.size();
		vector<string> counts(n + 1);
		for (const auto& kvp : freq) {
			counts[kvp.second].push_back(kvp.first);
		}
		string result;
		for (int count = n - 1; n >= 0; --count) {
			for (const auto& c : counts[count]) {
				result += string(count, c);
			}
		}
		return result;
	}

	// 165. Compare Version Numbers
	// Compare two version numbers version1 and version2.
	int compareVersion(string version1, string version2) {
		const int n1 = version1.length(), n2 = version2.length();
		for (int i = 0, j = 0; i < n1 || j < n2; ++i, ++j) {
			int v1 = 0, v2 = 0;
			while (i < n1 && version1[i] != '.') {
				v1 = v1 * 10 + version1[i++] - '0';
			}
			while (j < n2 && version2[j] != '.') {
				v2 = v2 * 10 + version2[j++] - '0';
			}
			if (v1 != v2) {
				return v1 > v2 ? 1 : -1;
			}
		}
		return 0;
	}
	// Mine
	int compareVersion(string version1, string version2) {
		int index1 = version1.find("."), index2 = version2.find(".");
		int prev1 = 0, prev2 = 0;
		bool end1 = false, end2 = false;
		while(index1 != string::npos || index2 != string::npos){
		    int i1 = 0;
		    if(!end1 && index1 == string::npos){
			i1 = stoi(version1.substr(prev1), 0,10);
			end1 = true;
		    }else if(!end1 && index1 != string::npos){
			i1=stoi(version1.substr(prev1, index1-prev1), 0,10);
		    }
		    int i2 = 0;
		    if(!end2 && index2 == string::npos){
			i2 = stoi(version2.substr(prev2), 0,10);
			end2 = true;
		    }else if(!end2 && index2 != string::npos){
			i2=stoi(version2.substr(prev2, index2-prev2), 0,10);
		    }
		    //cout << s1 << " " << s2 << "\n";
		    //cout << i1 << " " << i2 << "\n";
		    if(i1 == i2){
			// the same, continue
			prev1 = index1+1;
			prev2 = index2+1;
			index1 = version1.find(".", prev1);
			index2 = version2.find(".", prev2);
		    }else if(i1 < i2)
			return -1;
		    else
			return 1;
		}
		int i1 = 0, i2 = 0;
		if(!end1)
		    i1 = stoi(version1.substr(prev1), 0,10);
		if(!end2)
		    i2 =  stoi(version2.substr(prev2), 0,10);
		if(i1 > i2)
		    return 1;
		if(i1 == i2)
		    return 0;
		if(i1 < i2)
		    return -1;
		return 0;
	    }
	
	// No.1122 Relative Sort Array
	// Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all elements in arr2 are also in arr1.

	// Sort the elements of arr1 such that the relative ordering of items in arr1 are the same as in arr2.  Elements that don't appear in arr2 should be placed at the end of arr1 in ascending order.
	// Example 1:
	// Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
	// Output: [2,2,2,1,4,3,3,9,6,7,19]

	// Constraints:
	// arr1.length, arr2.length <= 1000
	// 0 <= arr1[i], arr2[i] <= 1000
	// Each arr2[i] is distinct.
	// Each arr2[i] is in arr1.
	vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
		unordered_map<int,int> mymap;
		for(int i = 0; i < arr2.size(); i++){
		    mymap[arr2[i]] = 1;
		}
		vector<int> ret1, ret2;
		ret1 = arr2;
		for(int i = 0; i < arr1.size(); i++){
		    if(mymap.find(arr1[i]) != mymap.end()){
		      if(mymap[arr1[i]] == 1){
			  mymap[arr1[i]] = 0;
		      }  else{
			auto p = find(ret1.begin(), ret1.end(), arr1[i]);
			  ret1.insert(p, arr1[i]);
		      }
		    } else{
			// insert into ret2 in sorted order
			binaryInsert(arr1[i], ret2);
		    }
		}
		// insert ret2 to ret1
		//cout << ret2[0] << " " << ret2[1];
		std::move(ret2.begin(), ret2.end(), std::back_inserter(ret1));
		return ret1;
	    }
	    void binaryInsert(int element, vector<int>& ret2){
		if(ret2.size() == 0){
		    ret2.push_back(element);
		    return;
		}
		int left = 0, right = ret2.size()-1;
		while(left <= right){
		    int mid = (left+right) >> 1;
		    if(ret2[mid] < element){
			left = mid+1;
		    }else
			right = mid-1;
		}
		ret2.insert(ret2.begin()+left, element);

	    }
	// No.242  Valid Anagram
//Given two strings s and t , write a function to determine if t is an anagram of s.

// Example 1:

// Input: s = "anagram", t = "nagaram"
// Output: true
// Example 2:

// Input: s = "rat", t = "car"
// Output: false
// Note:
// You may assume the string contains only lowercase alphabets.

// Follow up:
// What if the inputs contain unicode characters? How would you adapt your solution to such case?
	bool isAnagram(string s, string t) {
		if(s.size() != t.size())
		    return false;
		unordered_map<int, int> map1, map2;
		for(int i = 0; i < s.size(); i++){
		    ++map1[s[i] - 'a'];
		    ++map2[t[i] - 'a'];
		}

		for(const auto & item : map1){
		    if(item.second != map2[item.first])
			return false;
		}
		return true;
	    }
	
	// No.922 Sort Array By Parity II
// 	Given an array A of non-negative integers, half of the integers in A are odd, and half of the integers are even.

// Sort the array so that whenever A[i] is odd, i is odd; and whenever A[i] is even, i is even.

// You may return any answer array that satisfies this condition.

 

// Example 1:

// Input: [4,2,5,7]
// Output: [4,5,2,7]
// Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
 

// Note:

// 2 <= A.length <= 20000
// A.length % 2 == 0
// 0 <= A[i] <= 1000
	vector<int> sortArrayByParityII(vector<int>& A) {
		vector<int> ret(A.size());
		int oddIndex = 1, evenIndex = 0;
		for(int i = 0; i < A.size(); i++){
		    if(A[i] % 2 == 0){
			ret[evenIndex] = A[i];
			evenIndex += 2;
		    }else{
			ret[oddIndex] = A[i];
			oddIndex += 2;
		    }
		}
		return ret;
	    }
	
	// No.976 Largest Perimeter Triangle
// Given an array A of positive lengths, return the largest perimeter of a triangle with non-zero area, formed from 3 of these lengths.

// If it is impossible to form any triangle of non-zero area, return 0.
	int largestPerimeter(vector<int>& A) {
		sort(A.begin(), A.end());
		int i = A.size()-1;
		while(i-2 >= 0){
		    if(A[i] < A[i-1] + A[i-2]){
			return A[i] + A[i-1] + A[i-2];
		    }
		    --i;
		}
		return 0;
	    }
	
	// No.1030 Matrix Cells in Distance Order
// We are given a matrix with R rows and C columns has cells with integer coordinates (r, c), where 0 <= r < R and 0 <= c < C.

// Additionally, we are given a cell in that matrix with coordinates (r0, c0).

// Return the coordinates of all cells in the matrix, sorted by their distance from (r0, c0) from smallest distance to largest distance.  Here, the distance between two cells (r1, c1) and (r2, c2) is the Manhattan distance, |r1 - r2| + |c1 - c2|.  (You may return the answer in any order that satisfies this condition.)
	vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
		unordered_map<int, vector<vector<int>>> mymap;
		for(int i = 0; i < R; i++){
		    for(int j = 0; j < C; j++){
			int dis = abs(i-r0) + abs(j-c0);
			if(mymap.find(dis) == mymap.end()){
			    mymap[dis] = vector<vector<int>>(1, vector<int>{i,j});
			}else{
			    mymap[dis].push_back(vector<int>{i,j});
			}
		    }
		}
		int largest = max(r0, abs(r0-R)) + max(c0, abs(c0-C));
		vector<vector<int>> ret;
		for(int i = 0; i <= largest; i++){
		    ret.insert(ret.end(), mymap[i].begin(), mymap[i].end());
		}
		return ret;
	    }
}
