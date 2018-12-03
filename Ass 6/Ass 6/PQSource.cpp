//Helped by Seif Eldin Hani
#include "header.h"
#include "PQ.cpp"
#include <iostream>
#include<fstream>
using namespace std;

int getcount(int a[], int size) {
	int count = 0;
	for (int i = 0; i < size*size - 1; i++) {
		for (int j = i + 1; j < size*size; j++) {
			if (a[j] && a[i] && a[i] > a[j]) count++;
		}
	}
	return count;
}
int findpos(int **bArray, int n) {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			if (bArray[i][j] == 0) return n - i;
		}
	}
}
//Creates a copy of the board in order to edit it
bool checksolvalibilty(int **bArray,int a[],int arrsize) {
	int inversions = getcount(a, arrsize);
	if (arrsize & 1) return !(inversions & 1);
	else {
		int pos = findpos(bArray,arrsize);
		if (pos & 1) return !(inversions & 1);
		else return inversions & 1;
	}
}
void createdup(E<int> & x, E<int>& y, int n)
{
	x.arr = new int*[n];
	for (int i = 0; i < n; i++) {
		x.arr[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			x.arr[i][j] = y.arr[i][j];
		}
	}
}
//Prints the contents of the array(puzzle)
void print(E<int> in, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << in.arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	bool check = true;
	int movements = 0;
	E<int> puzzle;
	ifstream ifile;
	int n;
	int arr[100];
	ifile.open("puzz.txt");
	//if (ifile.is_open()) {
	ifile >> n;
	int **bArray = new int *[n];
	for (int i = 0; i < n; i++)
		bArray[i] = new int[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ifile >> bArray[i][j];
			arr[i*n + j] = bArray[i][j];
		}

	}
	ifile.close();
	//int s = n * n;
	if (checksolvalibilty(bArray, arr, n)) {
		//}
		PQ<int> H(bArray, n);
		while (check) {
			if (!H.PQIsEmpty()) {
				puzzle = H.remove();
				print(puzzle, n);
			}

			if (puzzle.h == 0) {
				check = false;
				cout << "Moves:  " << puzzle.g << endl;
			}
			else {
				movements++;
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
					{
						if (i != 0)
						{
							if (puzzle.arr[i - 1][j] == 0)
							{
								E<int>duplicate;
								createdup(duplicate, puzzle, n);
								swap(duplicate.arr[i - 1][j], duplicate.arr[i][j]); //move up
								H.insert(duplicate, movements);
								//print(duplicate, n);
							}
						}
						if (i < n - 1)
						{
							if (puzzle.arr[i + 1][j] == 0) //If the tile below the present one
							{
								E<int>duplicate; //Create duplicate to add the puzzle
								createdup(duplicate, puzzle, n); //This duplicate is the one we will edit in as we cannot edit in an already removed puzzle
								swap(duplicate.arr[i + 1][j], duplicate.arr[i][j]); //move down
								H.insert(duplicate, movements);
								//print(duplicate, n);
							}
						}
						if (j != 0)
						{
							if (puzzle.arr[i][j - 1] == 0)
							{
								E<int>duplicate;
								createdup(duplicate, puzzle, n);
								swap(duplicate.arr[i][j - 1], duplicate.arr[i][j]); //move left
								H.insert(duplicate, movements);
								//print(duplicate, n);
							}
						}
						if (j < n - 1)
						{
							if (puzzle.arr[i][j + 1] == 0)
							{
								E<int>duplicate;
								createdup(duplicate, puzzle, n);
								swap(duplicate.arr[i][j + 1], duplicate.arr[i][j]); // move right
								H.insert(duplicate, movements);
								//print(duplicate, n);
							}
						}
					}
			}
		}
	}
	else cout << " it is not solvable " << endl;
	system("pause");
	return 0;
}
