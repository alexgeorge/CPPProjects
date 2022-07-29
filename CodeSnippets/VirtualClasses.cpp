#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

class Person
{
public:
	//ctor
	Person() {}
	//dtor
	virtual ~Person() {}
	virtual void getdata() = 0;
	virtual void putdata() = 0;

protected:
	char name[256];
	int age;
};

class Professor : public Person
{
public:
	Professor() :cur_id(0) { seq_id++; }
	virtual ~Professor() {}
	void getdata() {
		//should get the input from the user: the name, age and publications of the professor. 				
		scanf("%s", name);
		scanf("%d", &age);
		scanf("%d", &publications);
		cur_id = seq_id;
	}
	void putdata() {
		//should print the name, age, publications and the cur_id of the professor.    
		printf("%s %d %d %d\n", name, age, publications, cur_id);
	}
private:
	int publications;
	int cur_id;
	static int seq_id;
};

class Student : public Person
{
public:
	Student() :cur_id(0) { seq_id++; }
	virtual ~Student() {}
	void getdata() {
		scanf("%s", name);
		scanf("%d", &age);
		for (int i = 0; i < 6; i++) {
			scanf("%d", &marks[i]);
		}
		cur_id = seq_id;
	}
	void putdata() {
		int totalmarks = 0;
		for (int i = 0; i < 6; i++) totalmarks += marks[i];
		printf("%s %d %d %d \n", name, age, totalmarks, cur_id);
	}
private:
	int marks[6];
	int cur_id;
	static int seq_id;
};

int Student::seq_id = 0;
int Professor::seq_id = 0;

int VCmain() {

	int n, val;
	//cin >> n; //The number of objects that is going to be created.
	Person *per[4];
	n = 4;
	for (int i = 0; i < n; i++) {
		cin >> val;
		if (val == 1) {
			// If val is 1 current object is of type Professor
			per[i] = new Professor;
		}
		else per[i] = new Student; // Else the current object is of type Student
		per[i]->getdata(); // Get the data from the user.
	}
	for (int i = 0; i<n; i++)
		per[i]->putdata(); // Print the required output for each object.
	return 0;

}
