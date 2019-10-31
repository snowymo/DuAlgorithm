#pragma once
#include "common.h"

namespace SortInsert {
	// 147. Insertion Sort List
	ListNode* insertionSortList(ListNode* head) {
		if (!head) return head;
		ListNode* dummy = new ListNode(-1);
		dummy->next = head;
		// calc length of list
		int N = 0;
		ListNode *node = head;
		while (node) {
			node = node->next;
			++N;
		}
		ListNode* curHead = dummy;
		for (int i = 0; i < N; ++i) {
			// find minimum from [i ?N - 1]
			ListNode* minNode = curHead;
			ListNode* curNode = curHead;
			int curMin = INT_MAX;
			for (int j = i; j < N; ++j) {
				if (curNode->next->val < curMin) {
					curMin = curNode->next->val;
					minNode = curNode;
				}
				curNode = curNode->next;
			}
			// ...curHead-> ?     minNode-> trueMinNode -> ?
			ListNode* trueMinNode = minNode->next;
			cout << trueMinNode->val << endl;
			minNode->next = trueMinNode->next;
			trueMinNode->next = curHead->next;
			curHead->next = trueMinNode;
			curHead = trueMinNode;
		}
		return dummy->next;
	}
	// Miine
	ListNode* insertionSortList(ListNode* head) {
		ListNode* ans = NULL;
		// print(head);
		while(head){

		    ListNode* cur = head;
		    head = head->next;
		    if(ans == NULL){
			ans = cur;
			ans->next = NULL;
		    }   
		    else{
			// find the correct place for it
			// cout << "insert " << cur->val << "\n";
			ListNode* cur2 = ans, *prev = NULL;
			while(cur2){
			    if(cur->val < cur2->val){
				// insert it
				if(prev){
				    prev->next = cur;
				    cur->next = cur2;
				}else{
				    prev = cur;
				    prev->next = cur2;
				    ans = prev;
				}
				break;
			    }
			    prev = cur2;
			    cur2 = cur2->next;
			}
			if(cur2 == NULL){
			    prev->next = cur;
			    cur->next = NULL;
			}
		    }
		    // print(head);
		    // print(ans);
		}
		return ans;
	    }
}
