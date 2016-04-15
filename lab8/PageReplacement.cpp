#include <bits/stdc++.h>

using namespace std;
// Compile with flag: g++ PageReplacement.cpp -std=c++1y

int findPageOPT(const vector<int> ref, const vector<int> fr, int index)
{
	int n = fr.size();
	int l = ref.size();
	int maxVal = INT_MIN, maxInd = INT_MIN;
	int num = ref[index];
	// For each frame
	for (int i=0; i<n; i++)
	{
		//Checking the occurances in the future of that frame
		int j = index+1;
		for (; j<l; j++)
		{
			if (ref[j] == fr[i])
				break;

		}
		if (maxVal < j)
			maxVal = j, maxInd = i;
	}
	return maxInd;
}

bool search(vector <int>& fr, int target)
{
	for (auto& data: fr)
		if (data == target) return true;
	return false;
}

int pageRepOPT(vector<int> &fr, const vector<int> ref)
{
	int faults = 0;
	int n = fr.size(), l = ref.size();
	cout << "Frames : \n";
	for (int i=0; i<l; i++)
	{
		if (search(fr, ref[i]) == true)  cout << "Page Hit!\n";

		else if (fr[i%n] == INT_MAX)
			fr[i%n] = ref[i], ++faults;
		else
		{
			int f = 0;
			for (int k=0; k<n; k++)
				if (fr[k] == ref[i])
					f = 1;
			if (!f)
			{
				int replacePage = findPageOPT(ref, fr, i);
				fr[ replacePage ] = ref[i];
				faults++;
			}
		}

		// Print the frames at each stage
		for (int j=0; j<n; j++)
		{
			if (fr[j] != INT_MAX)
				cout << fr[j] << " ";
			else
				cout << "-" << " ";
		}
		cout <<"\n";
	}

	cout << "\nThe number of faults is : " << faults;

	return 0;
}

int pageRepLRU(vector<int> &fr, const vector<int> ref)
{
	int faults = 0;
	int n = fr.size(), l = ref.size();
	vector<int> timeF(n);

	cout << "Frames : \n";
	for (int i=0; i<l; i++)
	{
		if (fr[i%n] == INT_MAX)
			fr[i%n] = ref[i], timeF[i%n] = i, ++faults;
		else
		{
			int f = 0;
			for (int k=0; k<n; k++)
				if (fr[k] == ref[i])
					f = 1, timeF[k] = i;
			if (!f)
			{
				int min = INT_MAX;
				int minInd = INT_MAX;
				for (int k=0; k<n; k++)
					if (min > timeF[k])
						min = timeF[k], minInd = k;
				fr[minInd] = ref[i];
				timeF[minInd] = i;
				faults++;
			}
		}

		// Print the frames at each stage
		for (int j=0; j<n; j++)
		{
			if (fr[j] != INT_MAX)
				cout << fr[j] << " ";
			else
				cout << "-" << " ";
		}
		cout <<"\n";
	}

	cout << "\nThe number of faults is : " << faults;

	return 0;
}



int main()
{
	int faults = 0;
	int n;
	cout << "\nEnter the number of frames : ";
	cin >> n;
	vector <int> fr;
	int t;
	for (int i=0; i<n; i++)
		fr.push_back(INT_MAX);

	int l;
	cout << "\nEnter the length of the reference string : ";
	cin >> l;
	vector<int> ref;
	cout << "\nEnter the reference string page by page: \n";
	for (int i=0; i<l; i++)
	{
		cin >> t;
		ref.push_back(t);
	}

	cout << "\nApplying OPT : \n";
	pageRepOPT(fr, ref);
	cout << "\nApplying LRU : \n";
	pageRepLRU(fr, ref);

	return 0;
}