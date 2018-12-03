#include <iostream>
#include "header.h"
using namespace std;

template <class temp>
PQ<temp>::PQ(temp **bArray, int n) //Constructor
{
	size = n;
	a = new E<temp>[800000];
	N = 0;
	itemMin = -32767; // Minimum Heap
	a[0].sum = itemMin;

	E<temp> initial;
	//Allocate memory for board 2D array
	initial.arr = new int *[n];
	for (int i = 0; i < n; i++)
		initial.arr[i] = new int[n];
	//Prepare initial element to be inserted in the heap
	//Copy received array to initial element array
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			initial.arr[i][j] = bArray[i][j];
		}
	}
	N++;
	initial.g = 0;
	//initial.h = distance(bArray);
	initial.h = findH(initial, n);
	initial.sum = initial.h + initial.g;
	initial.prev = a[N - 1].arr;

	a[N] = initial;
	//upheap(N);
	cout << endl << "Initial" << endl;
	insert(initial, 0);
}

// Insert element (v) in the heap and adjust heap
//find index i and index j of value x in the borad b
//template <class temp>
//void PQ<temp>::findIJ(E<temp> b, int x, int & i, int & j, int n)
//{
//	i = 0; j = 0;
//	int r, c;
//	for (r = 0; r < n; r++)
//	{
//		for (c = 0; c < n; c++)
//		{
//			if (b.arr[r][c] == x)
//			{
//				i = r;
//				j = c;
//			}
//		}
//	}
//}
//template<class temp>
//int PQ<temp>::distance(temp **Array)
//{
//
//	int dist = 0;
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < size; j++)
//			if (Array[i][j] != 0)
//			{
//				int xcord = (Array[i][j] - 1) / size;
//				int ycord = (Array[i][j] - 1) % size;
//
//				int 	t = (abs(i - xcord)) + (abs(j - ycord));
//				dist = dist + t;
//			}
//	}
//
//	return dist;
//}

//find sum of all distances

template <class temp>
bool PQ<temp>::is_equal(E<temp> in_1, E<temp> in_2) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (in_1.arr[i][j] != in_2.arr[i][j]) {
				return false;
			}
		}
	}
	return true;
}

template <class temp>
bool PQ<temp>::optimize(E<temp> in) {
	//cout << N;
	for (int i = 1; i <= N; i++) {
		if (is_equal(a[i], in)) {
			return true;
		}
	}
	return false;
}

template <class temp>
int PQ<temp>::findH(E<temp> b, int n) //returns manhattan distance (previous itteration was the the problem with it not running correctly)
{
	int sum_h = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (b.arr[i][j] != 0) {
				sum_h += abs(((b.arr[i][j] - 1) / n) - i);
				//cout << abs((b.arr[i][j] - 1) / n) << "	" << i << "	" << b.arr[i][j] << endl;
				if (b.arr[i][j] % n != 0) {
					sum_h += abs(((b.arr[i][j] % n) - 1) - j);
					//cout << abs((b.arr[i][j] % n) - 1) << "	" << j << "	" << b.arr[i][j] << endl;
				}
				else {
					sum_h += abs(n - 1 - j);
				}
			}
		}
	}
	//cout << sum_h;
	return sum_h;
}

//template <class temp>
//int PQ<temp>::findH(E<temp> b, int n)
//{
//	int difX, difY;
//	int s = 0;
//	int i, j;
//	for (i = 0; i < n; i++)
//	{
//		for (j = 0; j < n; j++)
//		{
//			generating values from 1 up to n*n: 1 2 3 4 5 ...
//			int value = j + n * i + 1;
//			cout << value;
//			if (value == n * n) //ignore value n*n
//				break;
//
//			int iC = 0, jC = 0; //i and j position of current value
//								find index i and index j of current value (its current position)
//			findIJ(b, value, iC, jC, n);
//			int iG = (value - 1) / n;   //Goal i position
//			int jG = (value - 1) % n;   //Goal j position
//										
//			difX = abs(iC - iG); //find horizontal distance from its goal position
//			difY = abs(jC - jG); //find vertical distance
//
//			s = s + difX + difY;
//		}
//	}
//	return s;
//}

template <class temp>
void PQ<temp>::insert(E<temp> s, int m)
{
	if (!optimize(s)) {////optimization to make sure we didnt add node to PQ previouisly
		E<temp> v = s;
		v.arr = s.arr;
		v.g = m;
		v.h = findH(v, size);
		v.sum = v.g + v.h;
		//if (!optimize(s)) {
		N++;
		a[N] = v;
		upheap(N);
	}
}
template <class temp>
void PQ<temp>::upheap(int k)
{
	E<temp> v = a[k];
	while (a[k / 2].sum >= v.sum)
	{
		a[k] = a[k / 2];   k = k / 2;
	}
	a[k] = v;
}
// remove and return top of the heap, then adjust heap
template <class temp>
E<temp> PQ<temp>::remove()
{
	E<temp> v = a[1];
	a[1] = a[N--]; downheap(1);
	return v;
}
template <class temp>
void PQ<temp>::downheap(int k)
{
	int j = 2 * k;     E<temp> v = a[k];
	while (j <= N) {
		if ((j < N) && (a[j].sum > a[j + 1].sum)) j++;
		if (v.sum <= a[j].sum) break;
		a[j / 2] = a[j];     j *= 2;
	}
	a[j / 2] = v;
}
template <class temp>
bool PQ<temp>::PQIsEmpty() {
	if (N == 0) return true;
	else return false;//return (N == 0);
}


