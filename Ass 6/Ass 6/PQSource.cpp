//Helped by Seif Eldin Hani
// Helped by www.geeksforgeeks.org
#include "header.h"
#include "PQ.cpp"
#include <iostream>
#include<fstream>
using namespace std;

//Getting number of inversions in a certain puzzle
int getcount(int a[], int size) {
	int count = 0;
	for (int i = 0; i < size*size - 1; i++) {
		for (int j = i + 1; j < size*size; j++) {
			if (a[j] && a[i] && a[i] > a[j]) count++;
		}
	}
	return count;
}
//Finding position of empty tile
int findpos(int **bArray, int n) {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			if (bArray[i][j] == 0) return n - i; //position of empty tile starting from bottom-right
		}
	}
}
//Returns true if puzzle is solvable and false otherwise
bool checksolvalibilty(int **bArray,int a[],int arrsize) {
	int inversions = getcount(a, arrsize); //number of inversions
	if (arrsize & 1) return !(inversions & 1); // if grid odd return true if inversions are even
	else { //if grid even
		int pos = findpos(bArray,arrsize); //finding position of empty tile
		if (pos & 1) return !(inversions & 1); //if position odd return true if inversions are even
		else return inversions & 1;
	}
}
//Creates a copy of the board in order to edit it
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
	ifile.open("puzz.txt"); //Opening the file
	if (ifile.is_open()) {
		ifile >> n; //reading the size from the file
		int **bArray = new int *[n];
		for (int i = 0; i < n; i++)
			bArray[i] = new int[n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				ifile >> bArray[i][j]; //Reading elements into 2D
				arr[i*n + j] = bArray[i][j]; //Converting the 2D array into 1D 
			}

		}
		ifile.close(); //Close file
		if (checksolvalibilty(bArray, arr, n)) { //if solvable continue
			PQ<int> H(bArray, n); //Constructor with initial board and size
			while (check) {
				if (!H.PQIsEmpty()) {
					puzzle = H.remove(); //Dequeuing the puzzle with highest priority
					print(puzzle, n); // Outputting the stages of solving the puzzle
				}
				if (puzzle.h == 0) { //if Manhattan distance 0, then puzzle solved
					check = false; //so that loop is exited
					cout << "Moves:  " << puzzle.g << endl; //Outputting the number of movements
				}
				else {
					movements++;
					//Looping over the size of the puzzle
					for (int i = 0; i < n; i++)
						for (int j = 0; j < n; j++)
						{
							if (i != 0)
							{
								if (puzzle.arr[i - 1][j] == 0) //Comparing the current element with the one above it
								{
									E<int>duplicate;//Create duplicate to add the puzzle
									createdup(duplicate, puzzle, n); //This duplicate is the one we will edit in as we cannot edit in an already removed puzzle
									swap(duplicate.arr[i - 1][j], duplicate.arr[i][j]); //move up
									H.insert(duplicate, movements); //inserting the new puzzle with num of movements
									//print(duplicate, n);
								}
							}
							if (i < n - 1) 
							{
								if (puzzle.arr[i + 1][j] == 0) //Comparing the current element with the one below it
								{
									E<int>duplicate; //Create duplicate to add the puzzle
									createdup(duplicate, puzzle, n); //This duplicate is the one we will edit in as we cannot edit in an already removed puzzle
									swap(duplicate.arr[i + 1][j], duplicate.arr[i][j]); //move down
									H.insert(duplicate, movements);  //inserting the new puzzle with num of movements
									//print(duplicate, n);
								}
							}
							if (j != 0)
							{
								if (puzzle.arr[i][j - 1] == 0) //Comparing the current element with the one left to it
								{
									E<int>duplicate; //Create duplicate to add the puzzle
									createdup(duplicate, puzzle, n); //This duplicate is the one we will edit in as we cannot edit in an already removed puzzle
									swap(duplicate.arr[i][j - 1], duplicate.arr[i][j]); //move left
									H.insert(duplicate, movements);
									//print(duplicate, n);
								}
							}
							if (j < n - 1)
							{
								if (puzzle.arr[i][j + 1] == 0) //Comparing the current element with the one right to it
								{
									E<int>duplicate;  //Create duplicate to add the puzzle
									createdup(duplicate, puzzle, n); //This duplicate is the one we will edit in as we cannot edit in an already removed puzzle
									swap(duplicate.arr[i][j + 1], duplicate.arr[i][j]); // move right
									H.insert(duplicate, movements); //inserting the new puzzle with num of movements 
									//print(duplicate, n);
								}
							}
						}
				}
			}
		}
		else { //if not solvable
			cout << " it is not solvable " << endl;
		}
	}
	else {
		cout << "error opening file" << endl;
	}
	system("pause");
	return 0;
}
