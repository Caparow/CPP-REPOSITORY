#include <iostream>
#include <string>


class ListNode{
	char *data;
	ListNode *prev;
	ListNode *next;
public:
	friend class DoublyLinkedList;
	ListNode();//default constructor
	ListNode(char *_data);
	char* ShowNode();
	~ListNode(void);
};
