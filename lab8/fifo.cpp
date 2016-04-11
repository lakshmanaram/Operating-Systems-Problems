#include <iostream>
#include <vector>
using namespace std;

struct Page
{
	bool valid;
	int data;
};

void display(vector <Page> table)
{
	cout << "Index\tValid\tData\n------\t------\t------\n";
	for (int i = 0; i < table.size(); ++i)
	{
		cout << i <<'\t'<< table[i].valid <<'\t'<< table[i].data <<endl;
	}
}

int search(vector <Page>& table, int target)
{
	for (int i = 0; i < table.size(); i++)
		if (table[i].valid && table[i].data == target) return i;
	return -1;
}

void pageFault(vector <Page>& table,int data)
{
	bool emptyBlockFound = false;
	for (int i = 0; i < table.size(); ++i)
		if (table[i].valid == false) 
		{
			table[i].data = data;
			table[i].valid = emptyBlockFound = true;
			break;
		}
		
	if (emptyBlockFound == false)
	{
		for (int i = 0; i < table.size() - 1; ++i)
			table[i] = table[i + 1];
		table[table.size() - 1].data = data;
	}
	display(table);
}

int main()
{
	int n;
	cout << "Enter number of frames: ";
	cin >> n;
	vector <Page> table(n);
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