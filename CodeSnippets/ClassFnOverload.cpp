//Why doesn't overloading work for derived classes?
/*
In other words, there is no overload resolution between D and B. 
The compiler looks into the scope of D, finds the single function 
"double f(double)" and calls it. It never bothers with the (enclosing) scope of B. 
In C++, there is no overloading across scopes - derived class scopes are not an exception to this general rule.
*/

#include<iostream>
using namespace std;

class B {
public:
	int f(int i) { cout << "f(int): "; return i+1; }
	// ...
};

#define OVERLOAD

#ifndef OVERLOAD
class D : public B {
public:
	double f(double d) { cout << "f(double): "; return d+1.3; }
	// ...
};
#endif //OVERLOAD

/*
But what if I want to create an overload set of all my f() 
functions from my base and derived class? That's easily done using a using-declaration:
*/

#ifdef OVERLOAD
class D : public B {
public:
	using B::f;	// make every f from B available
	double f(double d) { cout << "f(double): "; return d+1.3; }
	// ...
};
#endif // OVERLOAD

void checkUndefined()
{
	int i =0;
	int v[20];
	printf("%d %d \n",v[i],i);
	v[i] = ++i;
	printf("%d %d \n",v[i],i);
	v[i] = i++;
	printf("%d %d \n",v[i],i);
	i = 0;
	int k = i++ + i++;
	printf("%d %d \n",k,i);
	i = 0;
	int j = ++i + ++i;
	printf("%d %d \n",j,i);
	//k is assigned first as i, then i is incremented twice
	//It's undefined. Basically, in C and C++, if you read a variable twice in an expression where you also write it, 
	//the result is undefined. Don't do that.
}

using namespace std;
#include <vector>
#include <stdexcept>
#include <iostream>

void trycatch() {
	try {
		std::vector<int> vec;
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(3);
		vec.push_back(1);
		//vec = {3,4,3,1}; this initialisation fails to compile
		//but the following way is OK. Or use the boost libraries for the same
		/*
		static const int arr[] = {3,4,3,1};
		vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );
		*/
		//int i{vec.at(4)}; // Throws an exception, std::out_of_range (indexing for vec is from 0-3 not 1-4)
	}

	// An exception handler, catches std::out_of_range, which is thrown by vec.at(4)
	catch (std::out_of_range& e) {
		std::cerr << "Accessing a non-existent element: " << e.what() << '\n';
	}

	// To catch any other standard library exceptions (they derive from std::exception)
	catch (std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << '\n';
	}

	// Catch any unrecognised exceptions (i.e. those which don't derive from std::exception)
	catch (...) {
		std::cerr << "Some fatal error\n";
	}
}


int mainClassOverload()
{
	D* pd = new D;
	checkUndefined();
	cout << pd->f(2) << '\n';
	cout << pd->f(2.3) << '\n';
	return 0;
}