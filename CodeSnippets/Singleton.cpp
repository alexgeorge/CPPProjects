// There are several ways of creating a singleton class. 
//The most simple approach is shown below:
//Here only one instance and the ctor is private

#include <iostream>

using namespace std;

class CMySingleton
{
public:
  static CMySingleton& Instance()
  {
    static CMySingleton singleton;
    return singleton;
  }
  void Write(void)
  {
	cout << "Singleton\n";
  }

// Other non-static member functions
private:
  CMySingleton() {};                                 // Private constructor
  CMySingleton(const CMySingleton&);                 // Prevent copy-construction
  CMySingleton& operator=(const CMySingleton&);      // Prevent assignment
};

//second approach with more than one instances
/*
Here we declare our constructor/s as private, thus denying direct creation of the class.
A static function CreateInstance that creates the class indirectly for us.
Two static members, one holding the current number of instances, another one the maximum allowed.
Note: We have to declare at least one constructor (private - of course), else direct creation will be possible.
*/

class CMyClass
{
private:
  CMyClass() { cout << nCount << "Ctor \n";}                           // Private Constructor

  static int nCount;                      // Current number of instances
  static int nMaxInstance;                // Maximum number of instances

public:
  ~CMyClass();                            // Public Destructor

  static CMyClass* CreateInstance();      // Construct Indirectly

  //Add whatever members you want
};

int CMyClass::nCount = 0;
int CMyClass::nMaxInstance = 1;         // When maxInstance is 1, we have a pure singleton class

CMyClass::~CMyClass()
{
	cout << nCount << "Dtor \n";
  --nCount;                             // Decrement number of instances
}

CMyClass* CMyClass::CreateInstance()
{
  CMyClass* ptr = 0;

  if(nMaxInstance > nCount)
  {
    ptr = new CMyClass;  
    ++nCount;                           // Increment no of instances
  }
  return ptr;
}

int SingleTonmain()
{	
	//only one instance of CMySingleton exists. It can be
	//used only this way. 
	//CMySingleton::Instance().Write();

	CMyClass* pm;	
	pm = CMyClass::CreateInstance();
	delete pm;
	return 0;
}