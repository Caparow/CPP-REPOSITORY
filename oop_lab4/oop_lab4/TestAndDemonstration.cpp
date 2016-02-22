//***********************************************
//***************LIUBIMOV KV-42******************
//***************LAB 4:"CLASSES"*****************
//***********************************************
#include "DoubleLinkedList.h"

using namespace std;

int main()
{
	DoublyLinkedList *ls = new DoublyLinkedList();
	ls->push_back(*(new ListNode("100")));
	ListNode *n1 = new ListNode("5");
	ls->push_front(*n1);
	ls->push_front(*(new ListNode("1")));
	ls->push_front(*(new ListNode("3")));
	ls->push_front(*(new ListNode("4")));
	ls->push_front(*(new ListNode("0")));
	ls->push_back(*(new ListNode("1sdsd")));
	ls->print();
	cout << "\n";
	ls->print_bkw();
	cout << "\nLink list size is equal to " << ls->size() << endl;
	cout << "\n";
	cout << "Lets delete first and last nodes from list\n";
	ls->pop_back();
	ls->pop_front();
	ls->print();
	cout << "\nNow lets erase 4, 1 and 100: \n";
	ls->erase("4");
	ls->erase("1");
	ls->erase("100");
	ls->print();
	cout << "\nLets insert '6' after '3' and '7' after '5': \n";
	ls->insert_after("3", *(new ListNode("6")));
	ls->insert_after("5", *(new ListNode("7")));
	ls->print();
	cout << "\nLets clear linked list (check this with 'isEmpty' method): \n";
	ls->clear();
	if (ls->isEmpty())
		cout << "Our list is empty! \n";
	cout << "\nLets get new list: \n";
	ls->push_front(*(new ListNode("6")));
	ls->push_front(*(new ListNode("31")));
	ls->push_front(*(new ListNode("55")));
	ls->push_front(*(new ListNode("4")));
	ls->push_front(*(new ListNode("1")));
	ls->push_front(*(new ListNode("3")));
	ls->push_front(*(new ListNode("4")));
	ls->push_front(*(new ListNode("8"))); 
	ls->push_front(*(new ListNode("5")));
	ls->push_front(*(new ListNode("0")));
	ls->print();
	cout << "\nOur new sorted list: \n";
	ls->sort();
	ls->print();
	cout << "\nLets delete unique elements: \n";
	ls->unique();
	ls->print();
	cout << "\nLets insert '0', '2', '7' and '9' preserving list ordering: \n";
	ls->insert_ord(*(new ListNode("0")));
	ls->insert_ord(*(new ListNode("2")));
	ls->insert_ord(*(new ListNode("7")));
	ls->insert_ord(*(new ListNode("9")));
	ls->print();

	cout << "\nLets get new list 'temp_ls': \n";
	DoublyLinkedList *temp_ls = new DoublyLinkedList();
	temp_ls->push_front(*(new ListNode("b")));
	temp_ls->push_front(*(new ListNode("v")));
	temp_ls->push_front(*(new ListNode("a")));
	temp_ls->push_front(*(new ListNode("d")));
	temp_ls->print();
	cout << "\nLets 'merge' our lists (temp_ls in ls): \n";
	ls->merge(*temp_ls);
	ls->print();
	if (temp_ls->isEmpty())
		cout << "Our 'temp_ls' list is empty! \n";
	cout << "\nLets get new lists: \n";
	ls->clear();
	ls->push_front(*(new ListNode("6")));
	ls->push_front(*(new ListNode("3")));
	ls->push_front(*(new ListNode("5")));
	ls->push_front(*(new ListNode("4")));
	ls->push_front(*(new ListNode("1")));
	cout << "New 'ls': ";
	ls->print();
	temp_ls->push_front(*(new ListNode("b")));
	temp_ls->push_front(*(new ListNode("v")));
	temp_ls->push_front(*(new ListNode("a")));
	temp_ls->push_front(*(new ListNode("d")));
	cout << "New 'temp_ls': ";
	temp_ls->print();
	cout << "\nLets assign 'ls' to 'temp_ls' from 1 to 3: \n";
	ls->assign(*temp_ls, 1, 3);
	cout << "New 'ls': ";
	ls->print();
	cout << "New 'temp_ls': ";
	temp_ls->print();
	cout << "\nLets splice 'temp_ls' in 'ls' from index 3 with all list:\n ";
	ls->splice(3, *temp_ls);
	ls->print();
	ls->clear();
	temp_ls->clear();
	ls->push_front(*(new ListNode("6")));
	ls->push_front(*(new ListNode("3")));
	ls->push_front(*(new ListNode("5")));
	ls->push_front(*(new ListNode("4")));
	ls->push_front(*(new ListNode("1")));
	cout << "\nlets get new lists: \nNew 'ls': ";
	ls->print();
	temp_ls->push_front(*(new ListNode("b")));
	temp_ls->push_front(*(new ListNode("v")));
	temp_ls->push_front(*(new ListNode("b")));
	temp_ls->push_front(*(new ListNode("d")));
	cout << "New 'temp_ls': ";
	temp_ls->print();
	cout << "\nLets splice 'temp_ls' in 'ls' from index 2 from 1 to 2: ";
	ls->splice(2, *temp_ls, 1, 2);
	ls->print();
	
	return 0;
}