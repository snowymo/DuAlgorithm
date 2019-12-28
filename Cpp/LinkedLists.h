#pragma once
#include "common.h"

namespace TestLinkedList {
	// 206. Reverse Linked List
	// Input: 1->2->3->4->5->NULL
	// Output: 5->4->3->2->1->NULL
	ListNode* reverseList(ListNode* head) {
		auto h = ListNode{0};
		while (head) {
			auto t = head->next;
			head->next = h.next;
			h.next = head;
			head = t;
		}
		return h.next;
	}
	// Mine
	ListNode* reverseList(ListNode* head) {
		ListNode* cur = head;
		ListNode* pre = NULL;
		while(cur){
		    ListNode* curNext = cur->next;
		    cur->next = pre;
		    pre = cur;
		    cur = curNext;
		}
		return pre;
	    }

	// 92. Reverse Linked List II
	// Reverse a linked list from position m to n. Do it in one-pass.
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		auto dummy = ListNode{ 0 };
		dummy.next = head;
		auto *p = &dummy;
		for (int i = 0; i < m - 1; ++i) {
			p = p->next;
		}

		// head
		//       head2    
		//   0, 1, 2, 3, 4, 5
		//   |        p  cur
		// dummy
		auto *head2 = p;
		p = p->next;
		auto *cur = p->next;

		for (int i = m; i < n; ++i) {
			// remove cur from the list
			p->next = cur->next;
			// add cur to the new head
			cur->next = head2->next;
			head2->next = cur;
			cur = p->next;
		}
		return dummy.next;
	}
	// Mine
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		ListNode* newHead = new ListNode(0);
		newHead->next = head;
		ListNode* start = head,* pre = newHead;
		for(int i = 0; i < m-1; i++){
		    pre = start;
		    start = start->next;
		}
		ListNode* newPre = pre,* newEnd = start,* endNext = start->next,* curNext = NULL;
		pre = NULL;
		for(int i = 0; i < n-m; i++){
		    endNext = start->next->next;
		    curNext = start->next;
		    start->next = pre;

		    pre = start;
		    start = curNext;
		}
		start->next = pre;
		newPre->next = start;
		newEnd->next = endNext;
		return newHead->next;
	    }

	// 25. Reverse Nodes in k-Group [H]
	// Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
	/*
	Given this linked list: 1->2->3->4->5
	For k = 2, you should return: 2->1->4->3->5
	For k = 3, you should return: 3->2->1->4->5
	*/
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (head == nullptr || head->next == nullptr || k <= 1) return head;
		ListNode *next_group = head;
		for (int i = 0; i < k; ++i) {
			if (next_group)
				next_group = next_group->next;
			else
				return head;
		}
		// next_group is the head of next group
		// new_next_group is the new head of next group after reversion
		ListNode *new_next_group = reverseKGroup(next_group, k);
		ListNode *prev = NULL, *cur = head;
		while (cur != next_group) {
			ListNode *next = cur->next;
			cur->next = prev ? prev : new_next_group;
			prev = cur;
			cur = next;
		}
		return prev; // prev will be the new head of this group
	}

	// 19. Remove Nth Node From End of List
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* node = head;
		if (node == NULL) return head;

		int total = 1;
		while (node->next != NULL) {
			node = node->next;
			++total;
		}

		int cur = 0;
		if (total < n) return head;
		if (cur == total - n) return head->next;
		node = head;
		while (node->next != NULL) {
			++cur;
			if (cur == total - n) {
				node->next = node->next->next;
				break;
			}
			node = node->next;
		}
		return head;
	}

	// 237. Delete Node in a Linked List [E]
	// Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
	void deleteNode(ListNode* node) {
		if (node && node->next) {
			auto v = node->next;
			node->val = v->val;
			node->next = v->next;
		}
	}
	// Mine, finished somewhere else
	void deleteNode(ListNode* node) {
		node->val = node->next->val;
		node->next = node->next->next;        
	    }

	// 138. Copy List with Random Pointer
	// A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null. Return a deep copy of the list.
	// deep copy of a linked list with an additional pointer
	RandomListNode* copyRandomList(RandomListNode* head) {
		// insert the copied node after the original one.
		for (auto p = head; p; p = p->next->next) {
			auto *node = new RandomListNode(p->label);
			node->next = p->next;
			p->next = node;
		}

		// update random node.
		for (auto p = head; p; p = p->next->next) {
			if (p->random) {
				p->next->random = p->random->next;
			}
		}

		// seperate the copied nodes from the original ones
		RandomListNode dummy{ 0 };
		for (auto p = head, q = &dummy; p; p = p->next, q = q->next) {
			q->next = p->next;
			p->next = p->next->next;
		}
		return dummy.next;
	}

	// Use three pointers to reverse a linked list
	ListNode* reverse(ListNode *head) {
		if (!head || !head->next) return head;
		ListNode *prev = head;
		for (ListNode *curr = head->next, *next = curr->next; curr; prev = curr, curr = next, next = next ? next->next : nullptr) {
			curr->next = prev;
		}
		head->next = nullptr;
		return prev;
	}

	// 143. Reorder List
	// Given a singly linked list L0 -> L1 -> Ln-1 -> Ln,
	// reorder it to: L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2
	// O(n) time
	// O(1) space
	void reorderList(ListNode* head) {
		if (head == nullptr || head->next == nullptr) return;
		// calc length
		ListNode* node = head;
		int N = 0;
		while (node) {
			++N;
			node = node->next;
		}

		// cut in the middle O(n)
		ListNode *slow = head, *fast = head, *prev = nullptr;
		while (fast && fast->next) {
			prev = slow;
			fast = fast->next->next;
			slow = slow->next;
		}
		prev->next = nullptr;


		slow = reverse(slow);


		// merge two lists
		ListNode *curr = head;
		while (curr->next) {
			ListNode *tmp = curr->next;
			curr->next = slow;
			slow = slow->next;
			curr->next->next = tmp;
			curr = tmp;
		}
		curr->next = slow;
	}

	// 24. Swap Nodes in Pairs [M]
	// Given a linked list, swap every two adjacent nodes and return its head.
	// Given 1->2->3->4, you should return the list as 2->1->4->3.
	ListNode* swapPairs(ListNode* head) {
		if (head == nullptr) return nullptr;
		ListNode* ans = head;
		ListNode* prev = ans;
		bool first = true;
		ListNode *p = head, *q = p->next;
		while (q != nullptr) {
			if (first) {
				ans = q;
			}
			else {
				prev->next = q;
			}
			p->next = q->next;
			q->next = p;
			prev = p;
			p = p->next;
			if (p == nullptr) break;
			q = p->next;
			first = false;
		}
		return ans;
	}

	// 61. Rotate List
	// Given a linked list, rotate the list to the right by k places, where k is non-negative.
	ListNode* rotateRight(ListNode* head, int k) {
		if (head == nullptr) return nullptr;
		ListNode *node = head, *nodeRotate = head;
		int cnt = 1;
		while (node->next != nullptr) {
			node = node->next;
			++cnt;
		}
		k = k % cnt;

		node = head;
		cnt = 0;
		while (node->next != nullptr) {
			node = node->next;
			if (cnt >= k) nodeRotate = nodeRotate->next;
			++cnt;
		}
		node->next = head;
		node = nodeRotate->next;
		nodeRotate->next = nullptr;
		return node;
	}

	// 203. Remove Linked List Elements [E]
	ListNode* removeElements(ListNode* head, int val) {
		while (head && head->val == val) {
			head = head->next;
		}
		auto v = head;
		while (v) {
			while (v->next && v->next->val == val) {
				v->next = v->next->next;
			}
			v = v->next;
		}
		return head;
	}
	
	// Mine, finished before
	ListNode* removeElements(ListNode* head, int val) {
		ListNode* headhead = new ListNode(val-1);
		headhead->next = head;
		ListNode* lastPtr = headhead, *curPtr = head;
		while(curPtr){
		    if(curPtr->val == val){
			lastPtr->next = curPtr->next;
		    }else
			lastPtr = lastPtr->next;
		    curPtr = curPtr->next;            
		}
		return headhead->next;
	    }

	// 83. Remove Duplicates from Sorted List [E]
	// Given a sorted linked list, delete all duplicates such that each element appear only once.
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == nullptr)
			return nullptr;
		ListNode* ans = new ListNode(0);
		ans->next = head;
		ListNode* prev = head;
		ListNode* node = head;
		int curval = head->val;
		while (node->next != NULL) {
			if (curval != node->next->val) {
				node = node->next;
				prev = node;
				curval = node->val;
				continue;
			}
			else {
				while (node->next != nullptr && curval == node->next->val)
					node = node->next;

				prev->next = node->next;
				if (node == nullptr)
					break;
				curval = node->val;
			}
		}
		return ans->next;
	}
	// Mine, finished 2 years ago
	ListNode* deleteDuplicates(ListNode* head) {
		std::map<int,int> dictionary;
		//ListNode * prev = NULL;
		if(head == NULL)
		    return head;

		/*ListNode * newhead = new ListNode(head->val);
		ListNode * ret = newhead;
		dictionary[newhead->val] = 1;

		ListNode * cur = head->next;

		while(cur != NULL){
		    std::map<int,int>::const_iterator it = dictionary.find(cur->val);
		    if(it == dictionary.end()){
			dictionary[cur->val] = 1;
			newhead->next = new ListNode(cur->val);
			newhead = newhead->next;
		    }

		    cur = cur->next;
		}*/

		ListNode * cur = head;
		ListNode * prev = NULL;
		while(cur){
		    std::map<int,int>::const_iterator it = dictionary.find(cur->val);
		    if(it == dictionary.end()){
			dictionary[cur->val] = 1;
			prev = cur;
		    }else{
			prev->next = cur->next;
		    }
		    cur = cur->next;
		}
		return head;
	    }

	// 82. Remove Duplicates from Sorted List II [M]
	// Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
	ListNode* deleteDuplicates2(ListNode* head) {
		if (head == nullptr)
			return nullptr;
		ListNode* ans = new ListNode(0);
		ans->next = head;
		ListNode* prev = ans;
		ListNode* node = head;
		int curval = head->val;
		while (node->next != nullptr) {
			if (curval != node->next->val) {
				prev = node;
				node = node->next;
				curval = node->val;
				continue;
			}
			else {
				while (node->next != nullptr && curval == node->next->val)
					node = node->next;
				node = node->next;
				prev->next = node;
				if (node == nullptr) break;
				curval = node->val;
			}
		}
		return ans->next;
	}

	// 86. Partition List
	// Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
	// You should preserve the original relative order of the nodes in each of the two partitions.
	// Input: head = 1->4->3->2->5->2, x = 3
	// Output: 1->2->2->4->3->5
	ListNode* partition(ListNode* head, int x) {
		ListNode* less = new ListNode(0);
		ListNode* lessNode = less;
		ListNode* more = new ListNode(0);
		ListNode* moreNode = more;

		ListNode* node = head;
		if (node == NULL) return node;

		while (node != NULL) {
			if (node->val < x) {
				lessNode->next = node;
				lessNode = node;
			}
			else {
				moreNode->next = node;
				moreNode = node;
			}
			node = node->next;
		}

		if (lessNode == NULL) return more->next;
		if (moreNode == NULL) return less->next;

		lessNode->next = more->next;
		moreNode->next = NULL;
		return less->next;
	}

	// 141. Linked List Cycle
	// Given a linked list, determine if it has a cycle in it.
	bool hasCycle(ListNode *head) {
		if (!head) return false;
		ListNode *fast = head, *slow = head;
		while (fast && slow && slow->next && fast->next) {
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow) return true;
		}
		return false;
	}

	// 142. Linked List Cycle II [M]
	// Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
	ListNode *detectCycle(ListNode *head) {
		ListNode *slow = head, *fast = head;
		while (fast && fast->next) {
			slow = slow->next; fast = fast->next->next;
			if (slow == fast) {
				ListNode *slow2 = head;
				while (slow2 != slow) {
					slow2 = slow2->next;
					slow = slow->next;
				}
				return slow2;
			}
		}
		return nullptr;
	}

	// 160. Intersection of Two Linked Lists
	// Write a program to find the node at which the intersection of two singly linked lists begins.
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		auto a = headA, b = headB;
		ListNode *tailA = nullptr, *tailB = nullptr;
		while (a && b) {
			if (a == b) {
				return a;
			}
			if (a->next)
				a = a->next;
			else if (!tailA) {
				tailA = a;
				a = headB;
			}
			else
				break;

			if (b->next)
				b = b->next;
			else if (!tailB) {
				tailB = b;
				b = headA;
			}
			else
				break;
		}
		return nullptr;
	}

	// 328. Odd Even Linked List [M][E]
	// Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.
	ListNode* oddEvenList(ListNode* head) {
		if (!head || !(head->next))
			return head;
		/*
		for (auto odd = head, cur = odd->next; cur && cur->next; cur = cur->next) {
		ListNode* even = odd->next;
		odd->next = cur->next;
		odd = odd->next;
		cur->next = odd->next;
		odd->next = even;
		}
		*/

		ListNode* odd = head, *even = head->next;
		ListNode* cur_odd = odd, *cur_even = even;
		bool is_odd = true;
		for (ListNode* cur = even->next; cur; cur = cur->next) {
			if (is_odd) {
				cur_odd->next = cur;
				cur_odd = cur;
			}
			else {
				cur_even->next = cur;
				cur_even = cur;
			}
			is_odd = !is_odd;
		}
		cur_odd->next = even;
		cur_even->next = nullptr;
		return odd;
	}
}
