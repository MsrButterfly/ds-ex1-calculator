#include <iostream>
#include <cstdlib>
template <typename _Ty>
class List {
public:
	List() : root (NULL) {}
	bool insert (const int &pos, const _Ty &x) {
		if (!root) {
			root = new ListNode (x, true);
			if (!root) {
				return false;
			}
			std::cout << "root init." << std::endl;
			return true;
		}
		ListNode *newNode = new ListNode (x);
		if (!newNode) {
			return false;
		}
		ListNode *p = root;
		for (int i = 0; i < pos; i++, p = p -> next);
		newNode -> prev = p -> prev;
		newNode -> next = p;
		p -> prev -> next = newNode;
		p -> prev = newNode;
		return true;
	}
	bool remove (const int &pos) {
		if (!root) {
			return false;
		}
		ListNode *p = root;
		for (int i = 0; i < pos; i++, p = p -> next);
		if (p == root) {
			delete root;
			root = NULL;
			return true;
		}
		p -> prev -> next = p -> next;
		p -> next -> prev = p -> prev;
		delete p;
		return true;
	}
	bool exists (const _Ty &x) const {
		if (root -> data = x) {
			return true;
		}
		for (ListNode *p = root -> next; p != root; p = p -> next) {
			if (p -> data = x) {
				return true;
			}
		}
		return false;
	}
	int search (const _Ty &x) const {
		int i = 1;
		if (root -> data = x) {
			return 0;
		}
		for (ListNode *p = root -> next; p != root; p = p -> next, i++) {
			if (p -> data = x) {
				return i;
			}
		}
		exit (EXIT_FAILURE);
	}
	void testShow() {
		int i = 1;
		std::cout << "[0] => " << root -> data << std::endl;
		for (ListNode *p = root -> next; p != root; p = p -> next, i++) {
			std::cout << '[' << i << "] => " <<  p -> data << std::endl;
		}
	}
private:
	class ListNode {
	public:
		ListNode (const _Ty &data, const bool &root = false) : data (data) {
			if (root) {
				this -> prev = this;
				this -> next = this;
			} else {
				this -> prev = NULL;
				this -> next = NULL;
			}
		}
		_Ty data;
		ListNode *prev;
		ListNode *next;
	};
	ListNode *root;
};