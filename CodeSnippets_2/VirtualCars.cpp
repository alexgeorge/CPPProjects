#include <iostream>
#include <string>

class CVehicle {
public:
    CVehicle() {std::cout << "Base ctor()!\n";}
    virtual ~CVehicle() {std::cout << "Base dtor()!\n";}

    //1. If it is not virutal a call to ccar drive will
    //call the base class drive
    //2. If it is virtual then the derived ccar drive will
    //be called
    //3. For pure virtual we have to override
    void virtual Drive() = 0;
};

//virtual inheritance will ensure that only one copy of the
//base class member variables are inherited by the derived ones 
class CCar : public virtual CVehicle {
public:
    CCar() {std::cout << "CCar ctor()!\n";}
    virtual ~CCar() {std::cout << "CCar dtor()!\n";}

    void Drive() override {
        std::cout << "CCar Drive()!\n";
    }
};

//dynamic, static, reinterpret casts 
void TestCastings(CVehicle *pVeh){
    //static when you are sure about the type
    float flo = 5.67;
    auto conv = static_cast<int>(flo);
    std::cout << "Static cast conversion [" << conv << "]" << std::endl;
    
    {
        int* a = new int();
        *a =100;
        void* b = static_cast<void*>(a);
        int* c = static_cast<int*>(b);
        //both contain the same address
        std::cout << "void *[" << b << "] int* [" << c << "]" << std::endl;        
    }

    {
        //For casting to and from void*, static_cast should be preferred.
        int* a = new int();
        *a = 200;
        void* b = reinterpret_cast<void*>(a);
        int* c = reinterpret_cast<int*>(b);
        //both contain the same address, but b is undefined 
        std::cout << "void *[" << b << "] int* [" << c << "]" << std::endl;
    }

    //Dynamic cast to make sure that the polymorphic instance
    //is actually the right object. If it is not then the object
    //will be undefined and we can avoid calling the specific calls
    CCar *pCar = dynamic_cast<CCar*>(pVeh);
    if (pCar){
        //This can be used to make a call to the
        //derived class exclusive functions
        pCar->Drive();
    }
}

int main(){
    CVehicle *pCar = NULL;   
    pCar = new CCar();
    TestCastings(pCar);
    pCar->Drive();
    delete pCar;

    std::cout << "Complete drive!\n";
    return 1;
}
