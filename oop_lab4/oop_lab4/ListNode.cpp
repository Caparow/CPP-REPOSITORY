#include "ListNode.h"

ListNode::ListNode()
{
	prev = NULL;
	next = NULL;
	data = NULL;
}


ListNode::~ListNode()
{
	if (data != NULL)
		delete[] this->data;
}


ListNode::ListNode(char *_data)
{
	if (_data)
	{
		data = new char[strlen(_data) + 1];
		strcpy(data, _data);
	}
	else
		data = NULL;

	prev = NULL;
	next = NULL;
}
char* ListNode::ShowNode()
{
	return data;
}