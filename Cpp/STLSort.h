#pragma once
#include "common.h"

namespace STLSort {
	/*
		75. Sort Colors
		Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
		Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
		Note:
		You are not suppose to use the library's sort function for this problem.
	*/
	void sortColorsSTL(vector<int>& nums) {
		partition(
			partition(nums.begin(), nums.end(), bind1st(equal_to<int>(), 0)),
			nums.end(), bind1st(equal_to<int>(), 1)
			);
	}
	// Mine
	void sortColors2(vector<int>& nums) {
		int lastBlue = nums.size()-1;
		int lastWhite = nums.size()-1;
		for(int i = 0; i < nums.size(); i++){
		    if(nums[i] == 2){
			for(int j = lastBlue; j > i; j--){
			    if(nums[j] < 2){
				swap(nums[i], nums[j]);
				//cout << "swap " << i << " with " << j << "\n";
				lastBlue = j-1;
				lastWhite = j-1;
				break;
			    }
			}
		    }
		    if(nums[i] == 1){
			for(int j = lastWhite; j > i; j--){
			    if(nums[j] == 0){
				swap(nums[i], nums[j]);
				//cout << "swap " << i << " with " << j << "\n";
				lastWhite = j-1;
				break;
			    }
			}
		    }
		}
	    }
	// Other fast solution
	void sortColors(vector<int>& nums) {
		int i = 0, j = nums.size() - 1, x = 0; 
		while (x <= j) {
		    if (nums[x] == 0) { // Meet a 0? Send it back !
			swap(nums[x++], nums[i++]);
		    } else if (nums[x] == 2) { // Meet a 2? Send it forward, but don't move forward yourself,
			swap(nums[j--], nums[x]); // You might have just swapped a two with a 0.
		    } else { // In that case, you'd need to swap it back. If I wrote nums[x++], I would have missed it!
			x++; // Keep walking, x.
		    }
		}
		return;
	    }
}
