#pragma once
#include "common.h"

// Longest Common Subsequence (LCS)
// Find the longest subsequence common to all sequences in a set of sequences (often just two sequences).
// Time: O(M)
// Space: O(MN) => O(N)
namespace LCSProblems {
	//No. 1143
	int LCS(string &a, string &b) {
		int n = (int)a.size(), m = (int)b.size();
		Grid f(n + 1, Vector(m + 1, 0));
		
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= m; ++j) {
				if (a[i - 1] == b[j - 1])
					f[i][j] = f[i - 1][j - 1] + 1;
				else
					f[i][j] = max(f[i - 1][j], f[i][j - 1]);
			}
		}
		return f[n][m];
	}
	// Mine
	int longestCommonSubsequence(string text1, string text2) {
		vector<vector<int>> lcs(text1.size()+1, vector<int>(text2.size()+1));
		for(int i = 1; i <= text1.size(); i++){
		    for(int j = 1; j <= text2.size(); j++){
			lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]);
			if(text1[i-1] == text2[j-1]){
			    lcs[i][j] = max(lcs[i][j], lcs[i-1][j-1]+1);
			}
		    }
		}
		return lcs.back().back();
	    }

	// 14. Longest Common Prefix
	string longestCommonPrefix(vector<string>& strs) {
		int n = (int)strs.size();
		if (n == 0)
			return "";
		if (n == 1)
			return strs[0];
		int ans = 0;
		while (true) {
			bool are_same = true;
			char c = strs[0][ans];
			for (int i = 1; i < n; ++i) {
				if (ans >= strs[i].size() || strs[i][ans] != c) {
					are_same = false;
					break;
				}
			}
			if (!are_same) break;
			++ans;
		}
		return strs[0].substr(0, ans);
	}
	// Mine
	string longestCommonPrefix(vector<string>& strs) {
		if(strs.size() == 0)
		    return "";
		// int length = strs[0].size();
		// for(int i = 1; i < strs.size(); i++){
		//     if(length < strs[i].size())
		//         length = strs[i].size();
		// }
		string ans = "";
		for(int i = 0; i < strs[0].size(); i++){
		    char ch = strs[0][i];
		    int j;
		    for(j = 1; j < strs.size() && i < strs[j].size(); j++){
			if(ch != strs[j][i])
			    break;
		    }
		    if(j == strs.size())
			ans += ch;
		    else
			break;
		}
		return ans;
	    }
}
