#include <iostream>
#include <stdlib.h>

class Base
{
  public:
    char* buff;

    Base()
    {
        buff = new char[10];
		printf("Base ctor is called \n");
    }

    virtual ~Base()
    {
		printf("Base dtor is called - Invokded delete from base \n");
        //this will lead to memory leak
		//delete buff;
		delete[] buff;
		buff = 0;
    }

    virtual void reset() = 0;

};

class Derived : public Base
{
  public:
    Derived(){
		printf("Derived ctor is called \n");
	}

    void reset()
    {
		//reset is modified to do the deletion of entire buffer
       //free( buff );
		delete[] buff;
		buff = 0;
    }
	virtual ~Derived() {
		printf("Derived class dstor is called \n");
	}
};

int Honeywellmain()
{
  Base* b = new Derived;
  //here the memory is emncroached as the limit is set to <=10
  //for( int i = 0; i <= 10; i++ )
  for (int i = 0; i < 10; i++)
  {
    b->buff[i] = i;
  }

  //the code is fixed to print the buffer
  for (int i = 0; i<10;i++) printf("%d", b->buff[i]);
  printf("\n");
  //this line is not printing anything
  std::cout << b->buff << std::endl;

  b->reset();
  //the object is to deleted
  //delete b;
  Base* b2;

  if( b->buff == 0 )
  {
    b2 = new Derived;
  }

  //here the delete will not call the derived class destr as it is not virtual
  //delete b2;
  return 0;
}