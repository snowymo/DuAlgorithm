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
}
