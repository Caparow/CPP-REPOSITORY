#include "DoubleLinkedList.h"


using namespace std;

DoublyLinkedList::DoublyLinkedList() : head(NULL) {}

DoublyLinkedList::~DoublyLinkedList()
{
	if (!isEmpty())
	{
		ListNode *curr = head;
		while (head != NULL)
		{
			delete curr;
			head = head->next;
		}
	}
	
}

bool DoublyLinkedList::isEmpty()
{
	return (!head);
}

void DoublyLinkedList::clear()
{
	ListNode *temp = head;
	
	while (temp != NULL)
	{
		head = temp->next;
		pop_front();
		temp = head;
	}
}

int DoublyLinkedList::size()
{
	
	int n = 0;

		for (ListNode* curr = head; curr != NULL; curr = curr->next)
			n++;
	return n;
}

void DoublyLinkedList::push_front(const ListNode &node)
{
	ListNode *temp = new ListNode(node.data);
	
	if (isEmpty())
		head = temp;
	else
	{
		head->prev = temp;
		temp->next = head;
		head = temp;
	}
}

void DoublyLinkedList::push_back(const ListNode &node)
{

	ListNode *temp = new ListNode(node.data);

	if (isEmpty())
		head = temp;
	else
	{

		ListNode *end = head;

		while ((end->next) != NULL)
			end = end->next;

		temp->prev = end;
		end->next = temp;
		end = temp;

	}
}

void DoublyLinkedList::print()
{
	if (!head)
	{
		cout << "List is empty" << endl;
		return;		
	}
	cout << "Lets print our list:\n";
	int i = 0;
	for (ListNode *curr = head; curr != NULL; curr = curr->next)
		cout << "Node '" << i++ << "' -- " << curr->data << endl;
}

void DoublyLinkedList::print_bkw()
{

	if (!head)
	{
		cout << "List is empty" << endl;
		return;
	}
		

	std::cout << "Lets print our list backward:\n";
	int i = size() - 1;

	ListNode *end = head;

	while ((end->next) != NULL)
		end = end->next;

	for (ListNode *curr = end; curr != NULL; curr = curr->prev)
		cout << "Node '" << i-- << "' -- " << curr->data << endl;
}

void DoublyLinkedList::pop_front()
{
	if (!head)
		return;
	else
		if (size() == 1)
		{
			delete head;
			head = NULL;			
		}
		else
		{
			ListNode* temp = head;
			head = temp->next;
			delete (temp);
		}
	}

void DoublyLinkedList::pop_back()
{
	
	if (!head)
			return;
		else
			if (size() == 1)
			{				
				delete head;
				head = NULL;
			}
			else
			{
				ListNode *end = head;

				while ((end->next) != NULL)
					end = end->next;
					
				ListNode* temp = end;
				end = temp->prev;
				end->next = NULL;
				delete(temp);
			}

}

void DoublyLinkedList::erase(char *dat)
{

	ListNode *curr = head;
	while (curr)
	{
		if (strcmp(curr->data, dat) == 0)
		{
			if (curr == head)
			{
				curr = curr->next;
				pop_front();
				continue;
			}
			else
				if (curr->next == NULL)
				{
					pop_back();
					break;					
				}
				else
				{
					ListNode* temp = curr;
					curr = curr->next;
					(temp->prev)->next = temp->next;
					(temp->next)->prev = temp->prev;
					delete(temp);
					continue;		
				}
		}
		curr = curr->next;
	}
}
		
bool DoublyLinkedList::insert_after(char *dat, const ListNode &nd)
{
	bool flag = false;

	if (!head)
		return false;
	else
	{
		for (ListNode *curr = head; curr != NULL; curr = curr->next)
		{
			if (strcmp(curr->data, dat) == 0)
			{

				ListNode *temp = new ListNode(nd.data);


				if (curr->next == NULL)
					push_back(*temp);
				else
				{
					temp->next = curr->next;
					temp->next->prev = temp;
					curr->next = temp;
					temp->prev = curr;
				}

				flag = true;
			}
		}				
	}

	return flag;
}

void DoublyLinkedList::sort()
{
	ListNode *curr = head;
	while (curr != NULL)
	{
		char *max_dat = curr->data;
		ListNode *max;

		for (ListNode *temp = curr; temp != NULL; temp = temp->next)
			if (strcmp(max_dat, temp->data) <= 0)
			{
				max = temp;
				max_dat = temp->data;
			}

		push_front(*max);

		if (curr == max)
			curr = curr->next;
		
		if (max->next == NULL)
			pop_back();
		else
		{
			(max->next)->prev = max->prev;
			(max->prev)->next = max->next;
			delete(max);
		}
	}
}

void DoublyLinkedList::insert_ord(const ListNode &dat)
{
	ListNode *curr = head;
	ListNode *temp = new ListNode(dat.data);

	while ((*(curr->data) < *(temp->data)) && (curr->next != NULL))
		curr = curr->next;

	if (*(curr->data) > *(temp->data))
		curr = curr->prev;

	if (curr->next == NULL)
		push_back(*temp);
	else
		if (curr == head)
			push_front(*temp);
		else
		{
			temp->next = curr->next;
			temp->next->prev = temp;
			curr->next = temp;
			temp->prev = curr;
		}
}

void DoublyLinkedList::unique()
{
	ListNode *curr = head;
	while (curr->next != NULL)
	{
		char *temp_char = curr->data;
		ListNode *temp = curr->next;
		while (temp != NULL)
		{
			if (strcmp(temp_char, temp->data) == 0)
			{
				if (temp->next == NULL)
				{
					pop_back();
					curr = curr->prev;
					break;
				}
				else
				{
					(temp->prev)->next = temp->next;
					(temp->next)->prev = temp->prev;
					ListNode *d_temp = temp;
					temp = temp->next;
					delete(d_temp);
				}
			}
			else
				break;
		}
		curr = curr->next;
	}
}

void DoublyLinkedList::operator=(const DoublyLinkedList &rhs)
{
	if (this == &rhs)
		return;

	this->clear();
	for (ListNode *curr = rhs.head; curr != NULL; curr = curr->next)
	{
		ListNode *temp = new ListNode(curr->data);
		this->push_back(*temp);
	}
}

void DoublyLinkedList::merge(DoublyLinkedList &rhs)
{
	if (!rhs.head)
		return;

	ListNode *curr = rhs.head;

	while (curr)
	{
		this->push_back(*curr);
		curr = curr->next;
		rhs.pop_front();
	}

	this->sort();
}

void DoublyLinkedList::assign(DoublyLinkedList &dl, int first, int last)
{
	if (!dl.head)
		return;

	ListNode *curr = dl.head;

	for (int i = 1; i <= first; i++)
		curr = curr->next;

	for (int i = first; i <= last; i++)
	{
		this->push_back(*curr);

		ListNode *temp = curr;
		curr = curr->next;
		
		if (temp->next == NULL)
			dl.pop_back();
		else
			if (temp == dl.head)
				dl.pop_front();
			else
			{
				(temp->prev)->next = temp->next;
				(temp->next)->prev = temp->prev;
				delete(temp);
			}
	}
}

void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl)
{
	ListNode *curr = this->head;
	ListNode *source = dl.head;

	if (source == NULL)
		return;

	if (curr != NULL)
		for (int i = 1; i <= where; i++)
			curr = curr->next;

	while (source!=NULL)
	{
		ListNode *temp = new ListNode(*source);
		if (curr->next == NULL)
			this->push_back(*temp);
		else
		{			
			temp->next = curr->next;
			temp->prev = curr;
			(curr->next)->prev = temp;
			curr->next = temp;
		}
		curr = temp;
		source = source->next;
	}

}

void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl, int first, int	last)
{
	ListNode *curr = this->head;
	ListNode *source = dl.head;

	if (source == NULL)
		return;

	if (curr != NULL)
		for (int i = 1; i <= where; i++)
			curr = curr->next;

	for (int i = 1; i <= first; i++)
		source = source->next;

	for (int i = first; i <= last; i++)
	{
		ListNode *temp = new ListNode(*source);
		if (curr->next == NULL)
			this->push_back(*temp);
		else
		{
			temp->next = curr->next;
			temp->prev = curr;
			(curr->next)->prev = temp;
			curr->next = temp;
		}
		curr = temp;
		source = source->next;
	}
}