#include <iostream>
#include <vector>
using namespace std;

int front = 0;
struct Page
{
	bool replace,valid;		// replace bit 1 => replace, initially it is 0 => dont replace
	int data;	
};

void display(vector <Page> table)
{
	cout << "Index\tValid\tReplace\tData\n------\t------\t------\t----\n";
	for (int i = 0; i < table.size(); ++i)
	{
		cout << i <<'\t'<< table[i].valid <<'\t'<< table[i].replace <<'\t'<< table[i].data <<endl;
	}
}

int search(vector <Page>& table, int target)
{
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i].valid && table[i].data == target) 
		{
			table[i].replace = false;
			return i;
		}
	}
	return -1;
}

void pageFault(vector <Page>& table,int data)
{
	bool emptyBlockFound = false;
	for (int i = 0; i < table.size(); ++i)
	{
		if (table[i].valid == false) 
		{
			table[i].data = data;
			table[i].valid = true;
			table[i].replace = false;
			emptyBlockFound = true;
			break;
		}
	}
	if (emptyBlockFound == false)
	{
		while (table[front].replace == false)
		{
			table[front].replace = true;
			front = (front + 1)%(table.size());
		}
		table[front].data = data;
		table[front].replace = false;
		front = (front + 1)%(table.size());
	}
	display(table);
}

int main()
{
	int n;
	cout << "Enter Page Table size: ";
	cin >> n;
	vector <Page> table(n);
	for (int i = 0; i < n; ++i)
		table[i].replace = table[i].valid = false;

	cout << "Now you can start querying the page table: ";
	while (true)
	{
		int data;
		cout << "Query Page table for integer: ";
		cin >> data;
		int queryResult = search(table,data);
		if (queryResult == -1) pageFault(table,data);
		else
		{
			cout << "Page Hit! At position: " << queryResult << endl;
		}
	}
	return 0;
}