#pragma once
#include "common.h"

class CountSort {
	// 75. Sort Colors [M]
	// Given an array with n objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue. (0, 1, 2)
	void sortColors(vector<int>& nums) {
		int red = 0, blue = (int)nums.size() - 1;
		for (int i = 0; i <= blue; ++i) {
			if (nums[i] == 0) {
				swap(nums[i], nums[red++]);
			}
			else
				if (nums[i] == 2) {
					swap(nums[i--], nums[blue--]);
				}
		}
	}

	// 318. Maximum Product of Word Lengths
	// Time:  O(n) ~ O(n^2)
	// Space: O(n)
	// Counting Sort + Pruning + Bit Manipulation
	int maxProduct(vector<string>& words) {
		words = counting_sort(words);
		vector<int> bits(words.size());
		for (int i = 0; i < words.size(); ++i) {
			for (const auto& c : words[i]) {
				bits[i] |= (1 << (c - 'a'));
			}
		}
		int max_product = 0;
		for (int i = 0; i + 1 < words.size() && pow(words[i].length(), 2) > max_product; ++i) {
			for (int j = i + 1; j < words.size() && words[i].length() * words[j].length() > max_product; ++j) {
				if (!(bits[i] & bits[j])) {
					max_product = (int)(words[i].length() * words[j].length());
				}
			}
		}
		return max_product;
	}

	vector<string> counting_sort(const vector<string>& words) {
		const int k = 1000;  // k is max length of words in the dictionary
		vector<vector<string>> buckets(k);
		for (const auto& word : words) {
			buckets[word.length()].emplace_back(word);
		}
		vector<string> res;
		for (int i = k - 1; i >= 0; --i) {
			if (!buckets[i].empty()) {
				move(buckets[i].begin(), buckets[i].end(), back_inserter(res));
			}
		}
		return res;
	}
	// Mine
	map<string, int> cache;
	    int maxProduct(vector<string>& words) {
		if(words.size() <= 1)
		    return 0;
		int ans = 0;
		for(int i = 0; i < words.size(); i++){
		    turnToInt(words[i]);
		}
		for(int i = 0; i < words.size(); i++){
		    for(int j = i+1; j < words.size(); j++){
			if((cache[words[i]] & cache[words[j]]) == 0)
			    ans = max(ans, (int)words[i].size() * (int)words[j].size());
		    }
		}
		return ans;
	    }

	    int turnToInt(string s){

		int ans = 0;
		for(int i = 0; i < s.size(); i++){
		    int cur = s[i]-'a';
		    ans |= (1 << cur);
		}
		cache[s] = ans;
		//cout << s << ":" << ans << "\n";
		return ans;
	    }
	// optimization: access in map is slow, vector is faster; adding condition for size is not faster
	int maxProduct(vector<string>& words) {
		if(words.size() <= 1)
		    return 0;
		int ans = 0;
		// for(int i = 0; i < words.size(); i++){
		//     turnToInt(words[i]);
		// }
			vector<int> bits(words.size());
			for (int i = 0; i < words.size(); ++i) {
				for (const auto& c : words[i]) {
					bits[i] |= (1 << (c - 'a'));
				}
			}
		for(int i = 0; i < words.size(); i++){
		    for(int j = i+1; j < words.size(); j++){
			if((bits[i] & bits[j]) == 0)
			//if((words[i].size() * words[j].size() > ans) && (bits[i] & bits[j]) == 0)
			//if((cache[words[i]] & cache[words[j]]) == 0)
			    ans = max(ans, (int)words[i].size() * (int)words[j].size());
		    }
		}
		return ans;
	    }

	    void turnToInt(string s){

		int ans = 0;
		for(int i = 0; i < s.size(); i++){
		    int cur = s[i]-'a';
		    ans |= (1 << cur);
		}
		cache[s] = ans;
		//cout << s << ":" << ans << "\n";
		//return ans;
	    }
};
