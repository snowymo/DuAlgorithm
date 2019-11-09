#pragma once
#include "common.h"

namespace BucketSort {
	// 164. Maximum Gap
	// Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
	int maximumGap(vector<int>& nums) {
		int N = (int)nums.size();
		if (N < 2)
			return 0;
		auto max_val = *max_element(nums.cbegin(), nums.cend());
		auto min_val = *min_element(nums.cbegin(), nums.cend());
		int gap = max(1, (max_val - min_val) / (N - 1));
		int B = (max_val - min_val) / gap + 1;
		vector<int> bucket_min(B, INT_MAX), bucket_max(B, INT_MIN);

		// Find the bucket where each num should be put
		for (auto x : nums) {
			int i = (x - min_val) / gap;
			bucket_min[i] = min(bucket_min[i], x);
			bucket_max[i] = max(bucket_max[i], x);
		}

		// Count each bucket gap between the first and the last bucket
		int max_gap = 0, pre_bucket_max = min_val;
		for (int i = 0; i < B; ++i) {
			if (bucket_min[i] == INT_MAX)
				continue;
			max_gap = max(max_gap, bucket_min[i] - pre_bucket_max);
			pre_bucket_max = bucket_max[i];
		}

		// count the last bucket
		return max(max_gap, max_val - pre_bucket_max);
	}
	// Mine
	int maximumGap(vector<int>& nums) {
		if(nums.size() < 2)
		    return 0;
		vector<int> process;
		int ret = 0;
		for(int i = 0; i < nums.size(); i++){
		    binaryInsert(nums[i], process);
		}
		for(int i = 0; i < process.size()-1; i++){
		    ret = max(ret, abs(process[i] - process[i+1]));
		}
		return ret;
	    }
	    void binaryInsert(int element, vector<int> & process){
		int left = 0, right = process.size()-1;
		while(left <= right){
		    int mid = (left+right) >> 1;
		    if(element < process[mid]){
			right = mid-1;
		    }else if(element > process[mid]){
			left = mid+1;
		    }else
			return ;
		}
		process.insert(process.begin()+left, element);
		return;
	    }
}
