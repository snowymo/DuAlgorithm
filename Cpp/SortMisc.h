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
}
