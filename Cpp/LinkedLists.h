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
	// Mine
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* beforeHead = new ListNode(0);
		beforeHead->next = head;
		ListNode* firstHalf = beforeHead, * secondHalf = beforeHead;
		int len = 0;
		while(secondHalf != NULL){
		    if(secondHalf->next == NULL){
			break;
		    }
		    if(secondHalf->next->next == NULL){
			++len;
			break;
		    }
		    firstHalf = firstHalf->next;
		    secondHalf = secondHalf->next->next;
		    len += 2;
		}
		n = len - n; // count from the beginning
		if(n > len/2){
		    // loop from firstHalf
		    for(int i = len/2; i < n; i++){
			firstHalf = firstHalf->next;
		    }
		    firstHalf->next = firstHalf->next->next;
		}else{
		    ListNode* cur = beforeHead, *prev= beforeHead;
		    for(int i = 0; i < n; i++){
			prev = cur;
			cur = cur->next;
		    }
		    if(cur->next)
			cur->next = cur->next->next;
		    else{
			prev->next = NULL;   
		    }
		}
		return beforeHead->next;
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
	// Mine
	ListNode* rotateRight(ListNode* head, int k) {
		// get the length first
		if(head == NULL)
		    return head;
		int length = 0;
		for(ListNode* node = head; node != NULL; node = node->next){
		    ++length;
		}
		k = k % length;
		if(k == 0)
		    return head;
		// then we need to rotate k times
		// that means the first element is (length - k)th 
		ListNode* curNode = head, *prev = NULL;
		for(int i = 0; i < (length-k); i++ ){
		    prev = curNode;
		    curNode = curNode->next;
		}
		prev->next = NULL;
		ListNode* returnNode = curNode;
		for(;curNode->next != NULL; curNode = curNode->next){

		}
		curNode->next = head;
		return returnNode;
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
	// Mine
	ListNode* deleteDuplicates(ListNode* head) {
		if(head== NULL || head->next == NULL)
		    return head;
		ListNode* beforeHead = new ListNode(head->val-1);
		beforeHead->next = head;
		ListNode* cur = beforeHead;
		int lastValue = cur->val;
		ListNode* prev = beforeHead, *tbd;
		while(cur != NULL){
		    // cout << lastValue << "\t" << cur->val << "\n";
		    if(cur->val == lastValue){
			tbd = NULL;
			cur = cur->next;
		    }else{
			if(tbd != NULL){
			    prev->next = tbd;
			    prev = tbd;
			}
			tbd = cur;
			lastValue = cur->val;
			cur = cur->next;
		    }
		}
		prev->next = tbd;
		return beforeHead->next;
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
	// Mine
	ListNode* partition(ListNode* head, int x) {
		ListNode* beforeFirst = new ListNode(0), *beforeSecond = new ListNode(0);
		ListNode* ptrFirst = beforeFirst, *ptrSecond = beforeSecond;
		while(head){
		    if(head->val < x){
			ptrFirst->next = head;
			ptrFirst = head;
		    }else{
			ptrSecond->next = head;
			ptrSecond = head;
		    }
		    head = head->next;
		}
		ptrFirst->next = beforeSecond->next;
		ptrSecond->next = NULL;
		return beforeFirst->next;
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
	// Mine
	bool hasCycle(ListNode *head) {
		if(!head)
		    return false;
		ListNode* ptr1 = head->next;
		if(!ptr1)
		    return false;
		ListNode* ptr2 = head->next->next;
		while(ptr1 != ptr2 && ptr1 && ptr2){
		    ptr1 = ptr1->next;
		    ptr2 = ptr2->next;
		    if(!ptr2)
			return false;
		    ptr2 = ptr2->next;
		}
		if(ptr1 == ptr2)
		    return true;
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
	// Mine. Read Du's approach of finding the pos
	ListNode *detectCycle(ListNode *head) {
		ListNode* slow = head, *fast = head;
		while(slow && fast){
		    slow = slow->next;
		    fast = fast->next;
		    if(!fast)
			return NULL;
		    fast = fast->next;
		    if(slow == fast){
			while(head != slow){
			    head = head->next;
			    slow = slow->next;
			}    
			return slow;
		    }
		}
		return NULL;
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
	// Mine, Du's is smart, the sum of two list length must be the same
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		// get the length first
		int nA = 0;
		ListNode* recordA = headA;
		while(headA){
		    headA = headA->next;
		    ++nA;
		}
		int nB = 0;
		ListNode* recordB = headB;
		while(headB){
		    headB = headB->next;
		    ++nB;
		}
		headA = recordA;
		headB = recordB;
		// start at the same position from the end
		while(nA > nB){
		    headA = headA->next;
		    --nA;
		}
		while(nA < nB){
		    headB = headB->next;
		    --nB;
		}
		// Now we start to move until we found the same node
		while(headA){
		    if(headA == headB){
			return headA;
		    }
		    headA = headA->next;
		    headB = headB->next;
		}
		return NULL;
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
	// mine
	ListNode* oddEvenList(ListNode* head) {
		ListNode* lastOddNode = head, *curNode = head;
		ListNode* firstEvenNode = NULL, *lastEvenNode = NULL;
		ListNode* temp;
		int originalIndex = 1;
		while(curNode != NULL){
		    if(originalIndex % 2 == 1){
			if(curNode != lastOddNode){
			    // curNode should be the next one to lastOddNode
			    // curNode->next should be firstEvenNode
			    temp = curNode;
			    lastEvenNode->next = temp->next;
			    lastOddNode->next = temp;
			    temp->next = firstEvenNode;
			    lastOddNode = lastOddNode->next;
			    curNode = lastEvenNode->next;
			}else{
			    curNode = curNode->next;
			}
		    }else {
			if(firstEvenNode == NULL){
			    firstEvenNode = curNode;
			}
			lastEvenNode = curNode;
			curNode = curNode->next;
		    }

		    ++originalIndex;
		}
		return head;
	    }
	
	// No.725 Split Linked List in Parts[M] (Mine)
	// Given a (singly) linked list with head node root, write a function to split the linked list into k consecutive linked list "parts".
	// The length of each part should be as equal as possible: no two parts should have a size differing by more than 1. This may lead to some parts being null.
	// The parts should be in order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal parts occurring later.
	// Return a List of ListNode's representing the linked list parts that are formed.
	// Examples 1->2->3->4, k = 5 // 5 equal parts [ [1], [2], [3], [4], null ]
	vector<ListNode*> splitListToParts(ListNode* root, int k) {
		// we should know how many elements in each vector
		int length = 0;
		for(ListNode* curNode = root; curNode != NULL; curNode = curNode->next){
		    ++ length;
		}
		int vectorLength = length / k + 1;
		int vectorWithMoreE = k-(vectorLength*k-length);
		vector<ListNode*> returnVector;
		ListNode* curNode = root, *temp = NULL, *head = NULL;
		for(int i = 0; i < vectorWithMoreE; i++){
		    head = curNode;
		    for(int j = 0; j < vectorLength-1; j++){
			curNode = curNode->next; 
		    }
		    temp = curNode;
		    curNode = curNode->next;
		    temp->next = NULL;
		    returnVector.push_back(head);
		}
		for(int i = 0; i < (k-vectorWithMoreE); i++){
		    head = curNode;
		    for(int j = 0; j < vectorLength-2; j++){
			curNode = curNode->next; 
		    }
		    temp = curNode;
		    if(curNode != NULL){
			curNode = curNode->next;
			temp->next = NULL;
		    }
		    returnVector.push_back(head);
		}
		return returnVector;
	    }
	
	// No.234 Palindrome Linked List[E] Mine
	// Given a singly linked list, determine if it is a palindrome.
	ListNode* reverseList(ListNode* head, int n){
		// cout << "reversing\n";
		if(n == 1)
		    return head;
		ListNode* prev=NULL, *next,* cur = head;
		for(int i = 0; i < n; i++){
		    if(cur->next == NULL){
			cur->next = prev;
			// cout << "after:" << cur->val << "\n";
			return cur;
		    }

		    next = cur->next;
		    // if(next != NULL)
		    // cout << "next " << next->val << "\t";
		    // cur->next->next = cur;
		    cur->next = prev;
		    // if(cur->next != NULL)
		    // cout << "cur->next " << cur->next->val << "\t";
		    prev = cur;
		    // if(prev != NULL)
		    // cout << "prev " << prev->val << "\n";
		    cur = next;
		    // if(cur!=NULL)
		    // cout << "cur " << cur->val << "\t";

		}
		// if(prev != NULL)
		    // cout << "after:" << prev->val << "\n";
		return prev;
	    }
	    bool isPalindrome(ListNode* head) {
		if(head == NULL || head->next == NULL)
		    return true;

		ListNode* beforeHead = new ListNode(0);
		beforeHead->next = head;
		ListNode* firstHalf = beforeHead, *secondHalf = beforeHead;
		int isEven = false;
		int len = 0;
		while(true){
		    if(secondHalf->next == NULL){
			isEven = true;
			break;
		    }
		    if(secondHalf->next->next == NULL){
			isEven = false;
			break;
		    }
		    firstHalf = firstHalf->next;
		    secondHalf = secondHalf->next->next;
		    ++len;
		}
		// cout << "len " << len << "\n";
		if(isEven){
		    secondHalf = firstHalf->next;
		}else{
		    secondHalf = firstHalf->next->next;
		}
		firstHalf->next = NULL;
		// cout << "iseven " << (isEven?"true":"false") << " secondHalf:" << secondHalf->val << "\n";
		// reverse head-firstHalf
		// cout << "head " << head << "->val:" << head->val;
		ListNode* newFirstHalf = reverseList(head, len);
		// printList(newFirstHalf, len);
		// compare reversed head-firstHalf and secondHalf
		for(int i = 0; i < len && newFirstHalf != NULL; i++){
		    if(newFirstHalf->val != secondHalf->val){
			return false;
		    }
		    newFirstHalf = newFirstHalf->next;
		    secondHalf = secondHalf->next;
		}
		return true;
	    }
	    // void printList(ListNode* head, int len){
	    //     ListNode*cur = head;
	    //     cout << "printing\t";
	    //     for(int i = 0; i < len && cur != NULL; i++){
	    //         cout << cur->val << "\t";
	    //         cur = cur->next;
	    //     }
	    //     cout << "\n";
	    // }
	
	// No.21 Merge Two Sorted Lists[E] Mine
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if(!l1)
		    return l2;
		if(!l2)
		    return l1;
		ListNode* beforeHead = new ListNode(0);
		ListNode*prev = beforeHead;
		beforeHead->next = l2;
		if(l1->val < l2->val){
		    beforeHead->next = l1;
		}
		for(;l1 != NULL && l2 != NULL;){

		    if(l1->val < l2->val){
			    prev->next = l1;
			prev = l1;
			l1 = l1->next;
		    }else{
			    prev->next = l2;
			prev = l2;
			l2 = l2->next;
		    }

		}
		if(l1 != NULL)
		    prev->next = l1;
		if(l2 != NULL)
		    prev->next = l2;

		return beforeHead->next;
	    }
	// No.876 Middle of the linked list[E] Mine
	ListNode* middleNode(ListNode* head) {
		if(head == NULL || head->next == NULL)
			    return head;

			ListNode* beforeHead = new ListNode(0);
			beforeHead->next = head;
			ListNode* firstHalf = beforeHead, *secondHalf = beforeHead;
			int isEven = false;
			int len = 0;
			while(true){
			    if(secondHalf->next == NULL){
				    isEven = true;
				    break;
			    }
			    if(secondHalf->next->next == NULL){
				    isEven = false;
				    break;
			    }
			    firstHalf = firstHalf->next;
			    secondHalf = secondHalf->next->next;
			    ++len;
			}
		return firstHalf->next;
	    }
	
	// No.1290 [E] Convert Binary Number in a Linked List to Integer mine
	int getDecimalValue(ListNode* head) {
		ListNode* cur = head;
		int ret = 0;
		while(cur){
		    ret *= 2;
		    ret += cur->val;
		    cur = cur->next;
		}
		return ret;
	    }
	// No.707 [M] Mine Design Linked List
	// https://leetcode.com/problems/design-linked-list/
	class MyNode{
		public:
		    int val;
		    MyNode* next;
		    MyNode* prev;
		    MyNode(){
			val = 0;
			next = NULL;
			prev = NULL;
		    }
		    MyNode(int v){
			val = v;
			next = NULL;
			prev = NULL;
		    }
		};

		class MyLinkedList {
		    private:
		    int len;
		    MyNode* head;
		    MyNode* tail;
		public:
		    /** Initialize your data structure here. */
		    MyLinkedList() {
			head = NULL;
			tail = NULL;
			len = 0;
		    }

		    void print(){
			MyNode* ptr = head;
			cout << "len:" << len << "\t";
			for(int i = 0; i < len; i++){
			    if(ptr){
				cout << ptr->val << "\t";
				ptr = ptr->next;
			    }
			}
			cout << "\n";
		    }

		    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
		    int get(int index) {
			// cout << "get " << index << "\t";
			if(index >= len){
			    // cout << "NULL\n";
			    return -1;
			}
			MyNode* ptr = head;
			for(int i = 0; i < index; i++){
			    if(ptr)
				ptr = ptr->next;    
			}
			if(ptr){
			    // cout << ptr->val << "\n";
			    return ptr->val;
			}
			// cout << "NULL\n";
			return -1;
		    }

		    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
		    void addAtHead(int val) {
			MyNode* newhead = new MyNode(val);
			newhead->next = head;
			if(head){
			    head->prev = newhead;    
			}
			head = newhead;
			if(!tail)
			    tail = head;
			++len;
			// cout << "addAtHead\t";
			// print();
		    }

		    /** Append a node of value val to the last element of the linked list. */
		    void addAtTail(int val) {
			// cout << "addAtTail\t";
			MyNode* newtail = new MyNode(val);
			// cout << newtail->val << "\t";
			if(tail)
			    tail->next = newtail;
			newtail->prev = tail;
			tail = newtail;
			// cout << tail->val << "\t";
			if(!head)
			    head = tail;
			++len;

			// print();
		    }

		    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
		    void addAtIndex(int index, int val) {
			if(index > len){
			    return;
			}
			MyNode* newnode = new MyNode(val);
			if(index == 0){
			    newnode->next = head;
			    if(head){
				head->prev = newnode;
			    }
			    head = newnode;
			}else if(index == len){
			    if(tail)
				tail->next = newnode;
			    newnode->prev = tail;
			    tail = newnode;
			}
			else{
			    MyNode* ptr;
			    if(len < 10 || index < len/2){
				ptr = head;
				for(int i = 0; i < index-1; i++){
				    ptr = ptr->next;
				}
			    }else{
				ptr = tail;
				for(int i = len; i > index; i--){
				    ptr = ptr->prev;
				}
			    }
			    newnode->next = ptr->next;
			    newnode->prev = ptr;
			    if(ptr->next)
				ptr->next->prev = newnode;
			    ptr->next = newnode;  
			}

			++len;
			// cout << "insert at " << index << "\t";
			// print();
		    }

		    /** Delete the index-th node in the linked list, if the index is valid. */
		    void deleteAtIndex(int index) {
			if(index >= len){
			    return;
			}
			if(len == 1){
			    delete head;
			    head = NULL;
			    tail = NULL;
			    return;
			}
			if(index == 0){
			    MyNode* ptr = head->next;
			    // delete head;
			    head = ptr;
			    head->prev = NULL;
			    --len;
			    // cout << "delete " << index << "\t";
			    // print();
			    return;
			}
			if(len-1 == index){
			    MyNode* ptr = tail->prev;
			    // delete tail;
			    tail = ptr;
			    tail->next = NULL;
			    --len;
			    // cout << "delete " << index << "\t";
			    // print();
			    return;
			}
			MyNode* ptr = head;

			for(int i = 0; i < index-1; i++){
			    ptr = ptr->next;
			}
			MyNode* todelete = ptr->next;
			if(ptr->next && ptr->next->next){
			    ptr->next->next->prev = ptr;
			}
			if(ptr->next)
			    ptr->next = ptr->next->next;
			--len;
			// if(todelete)
			    // delete todelete;
			todelete = NULL;
			// cout << "delete " << index << "\t";
			// print();
		    }
		};

		/**
		 * Your MyLinkedList object will be instantiated and called as such:
		 * MyLinkedList* obj = new MyLinkedList();
		 * int param_1 = obj->get(index);
		 * obj->addAtHead(val);
		 * obj->addAtTail(val);
		 * obj->addAtIndex(index,val);
		 * obj->deleteAtIndex(index);
		 */
	
	// Mine No.16 [M] Reorder List
// 	Given a singly linked list L: L0→L1→…→Ln-1→Ln,
// reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

// You may not modify the values in the list's nodes, only nodes itself may be changed.

// Example 1:

// Given 1->2->3->4, reorder it to 1->4->2->3.
// Example 2:

// Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
	void reorderList(ListNode* head) {
		// find n
		// reverse the second half
		// merge 2 linked list to 1
		if(!head)
		    return;
		if(!head->next)
		    return;
		ListNode* mid = head, *cur = head, *prevMid = NULL;
		int n = 0;
		while(cur){
		    prevMid = mid;
		    mid = mid->next;
		    cur = cur->next;
		    ++n;
		    if(cur){
			++n;
			cur = cur->next;
		    }                
		}
		prevMid->next = NULL;
		// cout << "n=" << n << " mid " << mid->val << "\n";
		// reverse from mid to the end
		ListNode* temp, *next, *prev = NULL;
		while(mid){
		    temp = mid;
		    next = mid->next;
		    temp->next = prev;

		    mid = next;
		    prev = temp;
		}
		// cout << "prev " << prev->val << "\n";
		// merge head and prev
		cur = head;
		for(int i = 0; i < n; i+=2){
		    // cout << "i-" << i << "\n";
		    temp = cur->next;
		    cur->next = prev;
		    // cout << "\tcur " << cur->val << "\n";
		    cur = temp;            
		    if(prev){
			temp = prev->next;
			prev->next = cur;
			// cout << "\tprev " << prev->val << "\n";
			prev = temp;                
		    }
		}
		// cur->next = NULL;
		// cout << "cur " << cur <<  " prev " << prev << "\n";
		// for(ListNode* ptr = head; ptr!=NULL; ptr = ptr->next){
		//     cout << ptr->val << "\t";
		// }
	    }
}
