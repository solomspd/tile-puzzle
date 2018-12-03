#ifndef PQ_H
#define PQ_H
template <class temp>
struct E {
	int g;
	int h;
	int sum;
	temp **arr;
	temp **prev;
};
//E x;


template<class temp>
class PQ
{
public:
	PQ(temp **bArray, int n);
	void insert(E<temp>, int);	// insert element into heap
	E<temp> remove();	// remove & return the top of the heap
	bool PQIsEmpty();

private: //find index i and index j of value x in the borad b
	int size;
	int findH(E<temp> b, int n); //find sum of all distances
	E<temp> *a;         //Heap array
	int N;	      //index of last element in the array
	int itemMin;  //Very small value at index 0

	bool optimize(E<temp>); //required optimization as defined in PDF
	bool is_equal(E<temp>, E<temp>);
	void print(E<temp>);

	void upheap(int k);
	void downheap(int k);
};
#endif // PQ_H
