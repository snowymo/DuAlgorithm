#pragma once
#include "common.h"

namespace TestIntervals {
	// 56. Merge Intervals
	// Time: O(n log n)
	// Extra Space: O(1)
	// Given a collection of intervals, merge all overlapping intervals.
	// Input: [[1,3],[2,6],[8,10],[15,18]]
	// Output: [[1, 6], [8, 10], [15, 18]]
	// Sort then merge
	vector<Interval> merge(vector<Interval>& intervals) {
		auto &I = intervals;
		if (I.empty()) {
			return I;
		}
		sort(I.begin(), I.end(), [](const Interval& a, const Interval& b) {
			return a.start < b.start;
		});

		vector<Interval> res{ I[0] };
		const auto N = I.size();
		for (int i = 1; i < N; ++i) {
			// if there is overlap
			if (I[i].start <= res.back().end) {
				res.back().end = max(res.back().end, I[i].end);
			}
			else {
				res.emplace_back(I[i]);
			}
		}
		return res;
	}
// 	Mine
	// Time: O(n)
	// Extra Space: O(n)
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		vector<vector<int>> result;

		if(intervals.size() == 0)
		return result;

		int start = intervals[0][0], end = intervals[0][1];
		for(int i = 0; i < intervals.size(); i++){
		    start = min(start, intervals[i][0]);
		    end = max(end, intervals[i][1]);
		}
		// 
		end = end*2;
		start = start*2;

		unsigned char* temp = new unsigned char[end-start+2];
		memset((void*)(temp), 0, end-start+2);
		for(int i = 0; i < intervals.size(); i++){
		    // if(intervals[i].start > 450)
			// cout << "for " << intervals[i].start << " from " << intervals[i].start*2 - start << " by " << intervals[i].end*2 - intervals[i].start*2 << "\n";
		    memset((void*)(temp + intervals[i][0]*2 - start), 1, max(1,intervals[i][1]*2 - intervals[i][0]*2));
		}

		bool isInInterval = false;
		int curStart;
		for(int i = 0; i < end-start+2; i++){
		    if(!isInInterval && (temp[i]==1)){
			curStart = i+start;
			isInInterval = !isInInterval;
		    }else if(isInInterval && (temp[i]!=1)){
			result.push_back(vector<int>{curStart/2, (i+start)/2});
			isInInterval = !isInInterval;
			// cout << "add [" << curStart/2 << "," << (i+start)/2 << "]\t";
		    }
		}
		// if continues to the end, usually yes
		if(isInInterval){
		    result.push_back(vector<int>{curStart/2, end/2});
		}
		return result;
	    }

	// count union length of intervals
	// Time: O(n log n)
	// [1, 4] [2, 5], [7, 9], [7, 2], [8, 10]
	// prev = [1, 4]
	// prev = [1, 5]
	// res = 4, prev = [7, 9]
	int getUnionLength(vector<Interval> &intervals) {
		auto &a = intervals;
		if (a.empty()) {
			return 0;
		}
		sort(a.begin(), a.end(), [](const Interval& a, const Interval& b) {
			return a.start < b.start;
		});

		// scan and merge
		int res = 0; 
		auto prev = intervals[0];
		const auto N = intervals.size(); 
		for (int i = 1; i < N; ++i) {
			if (intervals[i].start < prev.end) {
				if (intervals[i].end > prev.end) {
					prev.end = intervals[i].end;
				}
			}
			else {
				res += prev.end - prev.start;
				prev = intervals[i];
			}
		}
		res += prev.end - prev.start;
		return res;
	}

	// 57. Insert Interval
	// Given a set of sorted non-overlapping intervals, 
	// insert a new interval into the intervals (merge if necessary).
	// Time: O(N)
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		auto &I = intervals;
		const auto N = I.size();
		auto &X = newInterval;
		vector<Interval> res;

		size_t i = 0;
		while (i < N && X.start > I[i].end) {
			res.emplace_back(I[i]);
			++i;
		}

		while (i < N && X.end >= I[i].start) {
			X = { min(X.start, I[i].start),
				max(X.end, I[i].end) };
			++i;
		}
		res.emplace_back(X);

		// insert the rest of the invervals
		while (i < N) {
			res.emplace_back(I[i]);
			++i;
		}
		//res.insert(res.end(), I.cbegin() + i, I.cend());
		return res;
	}

	// Time: O(n log n)
	int eraseOverlapIntervals(vector<Interval>& intervals) {
		//[1, 4], [1, 2], [2, 5], [2, 4], [3, 4] 
		auto& I = intervals;
		sort(I.begin(), I.end(), [](const Interval& a, const Interval& b) {
			return a.start < b.start;
		});
		int res = 0, prev = 0;
		const auto N = I.size();
		for (int i = 1; i < N; ++i) {
			// the current interval overlaps with the previous one
			if (I[i].start < I[prev].end) {
				// the current interval is shorter than the previous one, remove previous
				if (I[i].end < I[prev].end) {
					prev = i;
				}
				// remove the current
				++res;
			}
			else {
				prev = i;
			}
		}
		return res;
	}
	
	// 	mine 825. Friends Of Appropriate Ages
// Medium
// Some people will make friend requests. The list of their ages is given and ages[i] is the age of the ith person. 

// Person A will NOT friend request person B (B != A) if any of the following conditions are true:

// age[B] <= 0.5 * age[A] + 7
// age[B] > age[A]
// age[B] > 100 && age[A] < 100
// Otherwise, A will friend request B.

// Note that if A requests B, B does not necessarily request A.  Also, people will not friend request themselves.

// How many total friend requests are made?
	int numFriendRequests(vector<int>& ages){
        int ans = 0;
        vector<int> count(121,0);
        
        for(int i = 0; i < ages.size(); i++){
            // if(ages[i] = 120 && ages[1] >= 16)
                count[ages[i]]++;
        }
            
        for(int a = 15; a <= 120; a++){
            for(int b = a/2 + 8; b <= a; b++){
                ans += count[a] * count[b];
                if(a == b) ans -= count[a];
            }
        }
        return ans;
        
    }
//     int numFriendRequest1s(vector<int>& ages) {
//         // 
//         int ret = 0;
//         int lastRet = 0;
//         sort(ages.begin(), ages.end());
//         // for(int i = 0; i < ages.size(); i++){
//         //     cout << ages[i] << ",";
//         // }
//         // cout << "\n";
//         unordered_map<int,int> cache;
//         for(int i = 1; i < ages.size(); i++){
//             if((i < ages.size()-1) && (ages[i] == ages[i+1])){
//                 continue;
//             }
                
//             // find 0.5*ages[i]+7
//             float youngestFriend = 0.5 * ages[i] + 7;
//             // (youngestFriend, ages[i]]
//             int start = 0, end = i-1;
//             int index = i;
//             while(start <= end){
//                 if((float)ages[start] == youngestFriend){
//                     index = start;
//                     break;
//                 }
//                 if((float)ages[end] <= youngestFriend){
//                     index = end;
//                     break;
//                 }
                
//                 index = (start+end) >> 1;
//                 if((float)ages[index] == youngestFriend){
//                     break;
//                 }
//                 else if((float)ages[index] < youngestFriend){
//                     start = index+1;
//                 }else{
//                     end = index-1;
//                 }
//             }
            
//             if(ages[index] <= youngestFriend){
//                 while(index < ages.size()-1 && index < i-1 && ages[index] == ages[index+1])
//                     ++index;
//                 ++index;
//             }
                
//             // cout << i << ":" << ages[i] << "-" << index <<":" << ages[index]<< "\n";
//             cache[ages[i]] = 0;
//             if(index < i && (float)ages[index] > youngestFriend){
//                 // lastRet = i-1 - index + 1;
//                 cache[ages[i]] = i-1 - index + 1;
//                 // cout << "\tadd " << cache[ages[i]] << " to " << ages[i] << "\n";
//                 // ret += lastRet;
//             }
//         }
//         for(int i = 0; i < ages.size(); i++){
//             ret += cache[ages[i]];
//         }
//         return ret;
//     }
	
// 	No. 252 Meeting rooms https://www.lintcode.com/problem/meeting-rooms/description
// 	Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.

// (0,8),(8,10) is not conflict at 8
	bool canAttendMeetings1(vector<Interval> &intervals) {
		// write your code here
		vector<Interval> result;

		if(intervals.size() == 0)
		return true;

		int start = intervals[0].start, end = intervals[0].end;
		for(int i = 0; i < intervals.size(); i++){
		    start = min(start, intervals[i].start);
		    end = max(end, intervals[i].end);
		}
		// 
		end = end*2;
		start = start*2;

		unsigned char* temp = new unsigned char[end-start+2];
		memset((void*)(temp), 0, end-start+2);
		for(int i = 0; i < intervals.size(); i++){
		    // if(intervals[i].start > 450)
			// cout << "for " << intervals[i].start << " from " << intervals[i].start*2 - start << " by " << intervals[i].end*2 - intervals[i].start*2 << "\n";
		    memset((void*)(temp + intervals[i].start*2 - start), 1, max(0,intervals[i].end*2 - intervals[i].start*2 - 1));
		}

		bool isInInterval = false;
		int curStart;
		for(int i = 0; i < end-start+2; i++){
		    if(!isInInterval && (temp[i]==1)){
			curStart = i+start;
			isInInterval = !isInInterval;
		    }else if(isInInterval && (temp[i]!=1)){
			result.push_back(Interval(curStart, (i+start)));
			isInInterval = !isInInterval;
			// cout << "add [" << curStart/2 << "," << (i+start)/2 << "]\t";
		    }
		}
		// if continues to the end, usually yes
		if(isInInterval){
		    result.push_back(Interval(curStart, end));
		}
		if(intervals.size() == result.size())
		    return true;
		else
		    return false;
	    }

	    static bool sortInterval(Interval a, Interval b){
		return a.start < b.start;
	    }

	    bool canAttendMeetings(vector<Interval> &intervals) {
		// write your code here
		if(intervals.size() <= 1)
		    return true;

		sort(intervals.begin(), intervals.end(), sortInterval);


		for(int i = 0; i < intervals.size()-1; i++){
		    if(intervals[i].end > intervals[i+1].start)
			return false;
		}
		return true;
	    }
	
// 	No.253 Meeting Room II
// 	https://www.lintcode.com/problem/meeting-rooms-ii/description
// Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

// Have you met this question in a real interview?  
// Example
// Example1

// Input: intervals = [(0,30),(5,10),(15,20)]
// Output: 2
// Explanation:
// We need two meeting rooms
// room1: (0,30)
// room2: (5,10),(15,20)
// Example2

// Input: intervals = [(2,7)]
// Output: 1
// Explanation: 
// Only need one meeting room
	static bool compareInterval(Interval &a, Interval &b){
		return a.start < b.start;
	    }
	    int minMeetingRooms(vector<Interval> &intervals) {
		// Write your code here
		if(intervals.size() <= 1)
		    return intervals.size();

		sort(intervals.begin(), intervals.end(), compareInterval);
		priority_queue<int, vector<int>, greater<int>> rooms;

		int minNum = 0;
		rooms.push(intervals[0].end);
		for(int i = 1; i < intervals.size(); i++){
		    if(intervals[i].start >= rooms.top()){
			rooms.pop();
		    }
		    rooms.push(intervals[i].end);
		    minNum = max(minNum, (int)(rooms.size()));
		}
		return minNum;
	    }

}
