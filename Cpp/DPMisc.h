#pragma one
#include "common.h"

class DPMisc{
  // No.392 Is Subsequence (Mine)
  bool isSubsequence(string s, string t) {
        if(s.size() == 0)
            return true;
        if(s.size() > t.size())
            return false;
        int i = 0;
        for(int j = 0; i < s.size() && j < t.size(); j++){
            if(s[i] == t[j])
                ++i;
        }
        if(i == s.size())
            return true;
        return false;
    }
  
   // No.1025 Divisor Game (Mine)
// Alice and Bob take turns playing a game, with Alice starting first.
// Initially, there is a number N on the chalkboard.  On each player's turn, that player makes a move consisting of:
// Choosing any x with 0 < x < N and N % x == 0.
// Replacing the number N on the chalkboard with N - x.
// Also, if a player cannot make a move, they lose the game.
// Return True if and only if Alice wins the game, assuming both players play optimally. 

// Example 1:
// Input: 2
// Output: true
// Explanation: Alice chooses 1, and Bob has no more moves.
  
// Example 2:
// Input: 3
// Output: false
// Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.
// Note:

// 1 <= N <= 1000
  bool divisorGame(int N) {
        return !(N&1);
    }
  
  // No.28 Implement strStr()(Mine)
  // Implement strStr().
  // Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
  // Example 1:
  // Input: haystack = "hello", needle = "ll"
  // Output: 2

  // Example 2:
  // Input: haystack = "aaaaa", needle = "bba"
  // Output: -1
  int strStr(string haystack, string needle) {
        int n = needle.size();        
        if(n == 0)
            return 0;        
        if(haystack.size() < n)
            return -1;
        
        for(int i = 0; i <= (haystack.size()-n); i++){            
            int j = 0;
            for(; j < n; j ++){
                if(haystack[i+j] != needle[j])
                    break;
            }
            if(j == n)
                return i;
        }
        return -1;
    }
  
  // No.520 Detect Capital (Mine)
// Given a word, you need to judge whether the usage of capitals in it is right or not.
// We define the usage of capitals in a word to be right when one of the following cases holds:

// All letters in this word are capitals, like "USA".
// All letters in this word are not capitals, like "leetcode".
// Only the first letter in this word is capital, like "Google".
// Otherwise, we define that this word doesn't use capitals in a right way. 

// Example 1:
// Input: "USA"
// Output: True 

// Example 2:
// Input: "FlaG"
// Output: False
  
  bool detectCapitalUse(string word) {
        if(word.size() <= 1)
            return true;
        bool sec = (word[1] < 'a');
        cout << sec;
        for(int i = 2; i < word.size(); i++){
            if(word[i] < 'a' != sec )
                return false;
        }
        if(sec && ( word[0] >= 'a'))
            return false;
        return true;
    }
}