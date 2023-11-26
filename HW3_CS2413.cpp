//
// ========================================
// HW3: Implement a Vector Class
// ========================================
// 
// In this assignment, we will implement 
// a vector class based on array, pointer 
// and dynamic memory allocation. 
// 
// The class has two private member 
// variables and some member functions. 
// Their designs are explained below. 
// 
// You can add new member functions 
// but not new member variables. In 
// addition, you cannot use any existing 
// vector-related library or function. 
// 
// 


#include <iostream>
using namespace std;

// 
// ======= Task =======
// Design and implement all member 
// functions of the MyVector class. 
// 
class MyVector {

public:

	// The "vsize" function returns the size 
	// of the current vector.  
	int vsize();

	// The "empty" function returns 1 if the 
	// current vector has no element and 0 otherwise. 
	int empty();

	// The "at" function returns the idx_th element 
	// of the vector. It also returns -1 if "idx" 
	// is outside the range of the current vector.
	int at(int idx);

	// The "resize" function resizes the current 
	// vector into a vector of size n. Note there 
	// are two scenarios (in lecture slides) which 
	// may need to be addressed separately. 
	void resize(int n);

	// The "push_back" function adds a new element 
	// "x" to the end of the current vector. Note 
	// the vector size increases after addition. 
	void push_back(int x);

	// The "pop_back" function removes the last 
	// element from the current vector, but does 
	// nothing if the current vector is empty. 
	// Note the vector size decreases after pop. 
	void pop_back();

	// The "insert" function inserts a new element 
	// "x" as the idx_th element in the current vector.
	// It also does nothing if "idx" is outside the 
	// range of the current vector. 
	void insert(int idx, int x);

	// The "erase" function removes the idx_th element 
	// from the vector. It also does nothing if the 
	// current vector is empty or if "idx" is outside 
	// the range of the current vector. 
	void erase(int idx);

	// The constructor should initialize 
	// pointer "p" to NULL and "size" to 0. 
	MyVector();

private:

	int *p; // This pointer holds the vector (or,essentially, 
	// address of an array that holds the vector elements.)
	// Do remember to update it after some vector operations.

	int size; // This integer holds the size of the current 
	// vector. Do remember to update it after some 
	// vector operations. 
};


// Returns the size 
// of the current vector  
int MyVector::vsize()
{
	return size;
}

// Returns 1 if the current vector
// has no elements and 0 otherwise. 
int MyVector::empty()
{
	if(size = 0)
		return 1;
	else
		return 0;
}

// Returns the idx_th element 
// of the vector. It also returns -1 if "idx" 
// is outside the range of the current vector
int MyVector::at(int idx)
{
	if(idx >= size || idx < 0)
		return -1;

	return p[idx];
}

// Resizes the current vector
// into an vector of size n. If n is larger than
// the current size it adds zeros to the new spaces.
// If n is smaller than the current size it deletes the
// last elements of the vector that go over the new size
void MyVector::resize(int n)
{
	if(n > size)
	{
		int* temp = new int[n];
		for(int i = 0; i < size; i++)
			temp[i] = p[i];
		for(int i = size; i < n; i++)
			temp[i] = 0;
		delete [] p;
		p = temp;
	}
	else if(n < size)
	{
		int* temp = new int[n];
		for(int i = 0; i < n; i++)
			temp[i] = p[i];
		delete [] p;
		p = temp;
	}
	size = n;

}

// Adds a new element "x" to the end of the current vector
void MyVector::push_back(int x)
{
	int* temp = new int[size+1];
	for(int i = 0; i < size; i++)
		temp[i] = p[i];
	temp[size] = x;
	delete [] p;
	p = temp;
	size++;
}

// Removes the last element from the current vector, but does 
// nothing if the current vector is empty.
void MyVector::pop_back()
{
	if(size != 0)
	{
		int size2 = size -1;
		int* temp = new int[size2];
		for(int i = 0; i < size2; i++)
			temp[i] = p[i];
		delete [] p;
		p = temp;
		size = size2;
	}
		
}

// Inserts a new element "x" as the idx_th element 
// in the current vector. It also does nothing if "idx" 
// is outside the range of the current vector.
void MyVector::insert(int idx, int x)
{
	if(idx >= 0 && idx < size)
	{
		int* temp = new int[size+1];
		for(int i = 0; i < idx; i++)
			temp[i] = p[i];
		temp[idx] = x;
		for(int i = idx; i < size; i++)
			temp[i+1] = p[i];
		delete [] p;
		p = temp;
		size++;
	}
}

// Removes the idx_th element from the vector. It also does nothing if the 
// current vector is empty or if "idx" is outside 
// the range of the current vector.
void MyVector::erase(int idx)
{
	if(idx >= 0 && idx < size && size != 0)
	{
		int* temp = new int[size-1];
		for(int i = 0; i < idx; i++)
			temp[i] = p[i];
		for(int i = idx; i < size-1; i++)
			temp[i] = p[i+1];
		delete [] p;
		p = temp;
		size--;
	}
	
}

// Constructor that initializes
// pointer "p" to NULL and "size" to 0.
MyVector::MyVector()
{
	size = 0;
	p = NULL;                                                  
}

// The main function has been completed for you. 
// It is used to test your implmentation. 
// You should not modify it (unless there is typo).
int main()
{
	MyVector x;

	int mode;
	int new_size, idx, data;
	int temp;

	cin >> mode; // This decides which function to test. 
	cin >> new_size >> idx >> data;

	// Mode 0: test push_back(), vsize() and at()
	if (mode == 0) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 1: test resize()
	else if (mode == 1)
	{
		while (cin >> temp) {
			x.push_back(temp);
		}

		x.resize(new_size);

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 2: test pop_back()
	else if (mode == 2) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		x.pop_back();

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 3: test insert()
	else if (mode == 3) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		x.insert(idx, data);

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 4: test erase()
	else if (mode == 4) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		x.erase(idx);

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	else {
		cout << "Wrong Mode Input!";
	}

	return 0;
}
