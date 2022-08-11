// SampleCPP.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

/*
The copy constructor is a constructor which creates an object by initializing it with an object of the same class, 
which has been created previously. The copy constructor is used to −
Initialize one object from another of the same type.
Copy an object to pass it as an argument to a function.
Copy an object to return it from a function.
If a copy constructor is not defined in a class, the compiler itself defines one.
If the class has pointer variables and has some dynamic memory allocations, 
then it is a must to have a copy constructor.
*/


class Line {
   public:
      virtual int getLength( void );
	  virtual void deleteMe(void);
	  Line(void);					//ctor
	  Line( int len );            // simple constructor
      Line( const Line &obj);		// copy constructor
      virtual ~Line();				// destructor

   private:
      int *ptr;
};

Line::Line(void)
{
	printf("Base ctor\n");
	ptr=0;
}

void Line::deleteMe(void)
{
	printf("Trying to delete the base \n");
	//delete this;
}



// Member functions definitions including constructor
Line::Line(int len) {
   cout << "Normal constructor allocating ptr" << endl;
	
   // allocate memory for the pointer;
   ptr = new int;
   *ptr = len;
}

//Don't write a copy constructor if shallow copies are ok
Line::Line(const Line &obj) {
   cout << "Copy constructor allocating ptr." << endl;
   ptr = new int;
   *ptr = *obj.ptr; // copy the value
}

//If you need a copy constructor, you also need a destructor and operator=
Line::~Line(void) {
   cout << "Base distructor! \n" << endl;
   delete [] ptr;
}



int Line::getLength( void ) {
   //return 200;
	return *ptr;
}

void display(Line obj) {
   cout << "Length of line : " << obj.getLength() <<endl;
}

//When we use virtual inheritance, we are guaranteed to get only a single instance of the common base class.
//otherwise there will be multiple copies when we have multiple inheritance. 
class MyLine : virtual public Line{
public:
	 MyLine(void);
	 MyLine(int length);
	 int getLength(void){
		return 100;
	 }
	 ~MyLine(){
		printf("Derviced dstor\n");
	 }

};

MyLine::MyLine()
{
	printf("Dervied ctor\n");
}

MyLine::MyLine(int length)
{
	
	printf("Special ctor %d \n", length);

}

void testDelete()
{
	Line li;
	li.deleteMe();
}


void testFunction()
{
	int i=0,j =0;
	printf("%d %d \n",++i,j++);

   MyLine mli;
   int len = mli.getLength();
   printf("Length = %d \n",len);

   Line* pLine = reinterpret_cast<MyLine*>(&mli);
   len = pLine->getLength();
   //pLine->deleteMe();
   printf("Length = %d \n",len);

}

void testFunctionArr(std::string* arrList)
{
	cout<<arrList[0] << endl;
	//you cant have more than 3 elements in this array as it was initialised with that many
	//adding more will lead to corruption
	arrList[2] = "Modifying the value of the third string";
	for(int i=0;i<4;i++) printf("%s  ",arrList[i].c_str());
	printf("\n");
	//return;
#define MAX 3
   int  var[MAX] = {10, 100, 200};
	int* pVar = 0;
	pVar = var;

   for (int i = 0; i < MAX; i++) {
       //*(pVar+i) = 800+i;
	   //*var = i; //only the first element is modified
	   //var++;       // This is incorrect. needs l value 
	   *pVar =i; //all the elements are modified	   
	   cout << *pVar++ << endl;	   
      //cout << &var[i] << endl;	 	  
   }
	
}


void testF1(const int& test)
{

	int newtest = test;
	newtest += 100;
	//test = newtest; //not possible to assign a const variable
	cout<<"test:-   "<<test<<"  newtest  "<<newtest<<"  &test  "<<&test<< endl;

}

void menu(std::vector<std::string> menuItems){
    std::cout << "Make selection [1-" << menuItems.size() << "]" << std::endl;
    int idx = 0;
    for (auto item : menuItems){
            ++idx;
            std::cout << "[" << idx <<"] " << item << std::endl; 
    }
}

// Main function for the program
int CCmain( ) {

    // std::vector<std::string> strMenuItems;
    // strMenuItems.insert(strMenuItems.end(), {"Draw Rob Floyd Triangle (RFT)", 
    // "Recursive RFTriangle", "Pattern print X"});

    // menu(strMenuItems);

/*
   Line line1(10);

   Line line2 = line1; // This also calls copy constructor
   cout << line2.getLength() <<endl;
   cout << line1.getLength() <<endl;

   Line line3(200);

   line1 = line3; //this will not invoke the copy ctor
   cout << line1.getLength() <<endl; //length will be changed for line1
   //call to display will invoke the copy ctor again as the input to 
   //that function is Line object.
   display(line1);
   display(line2); //without a copy constructor this will lead to crash.
   return 0;
   */
	//const int* p_alex = NULL; //value of
	int const *p_alex = NULL; //pointer to a constant data. The pointer can be changed no issues
	int alex = 100;
	p_alex = &alex;
	cout <<"p_alex:- "<< p_alex << endl;

	int gem = 400;
	p_alex = &gem;

	testF1(*p_alex);

	int* const p_gem = &gem; //const pointer to any data
	cout<<"p_gem :-"<<p_gem<<endl;

	*p_gem = 600;

	testF1(*p_gem);

	std::string arrLis[] = {"alex", "unda", "paro"};
	testFunctionArr(arrLis);
	cout<<arrLis[10]<<endl;

    //testF1();
   return 0;
}