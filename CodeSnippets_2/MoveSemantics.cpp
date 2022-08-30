#include <iostream>
#include <cstring>

//Move semantics
//Rvalue references and the related concept of move semantics 
//is one of the most powerful new features the C++11

class AString {

public:
    AString() {}
    //regulat ctor
    AString(const char* str)
    {
        printf("Created Astring \n");
        m_size = strlen(str);
        m_data = new char[m_size];
        memcpy(m_data, str, m_size);
    }

    //copy ctor(). Since the opy has to
    //hold the m_data we have to do a memcpy
    //to preserve the copy. If we call the 
    //entity.PrintName(), if will fail without
    //the copy ctor. 
    AString(const AString& other) noexcept
    {
        printf("Copied Astring \n");
        m_size = other.m_size;
        m_data = new char[m_size];
        memcpy(m_data, other.m_data, m_size);       
    }

    virtual ~AString()
    {
        std::cout << "Deleting Astring!\n";
        delete [] m_data;
    }

    void PrintName()
    {
        for (uint32_t i=0; i<m_size; ++i)
        {
            printf("%c", m_data[i]);
        }
        printf("\n");
    }

private:
    char* m_data;
    uint32_t m_size;    
};

class Entity {
public:
    Entity() {}
    //The ASting object will be deleted immediately
    //after executing the ctor of Entity. Further
    //the AString print name will not work as the m_data is deleted, 
    //if we haven't implemented the copy ctor in AString    
    Entity(const AString& strIn): 
        m_name(strIn)
    {

    }
    virtual ~Entity()
    {
        std::cout << "Deleting Entity!\n";
    } 

    void PrintName()
    {
        m_name.PrintName();
    }    

private:
    AString m_name;
};


int main()
{
    Entity entity(AString("AlexG"));
    std::cout << "Completed operation!\n";
    //without copy ctor in AString the 
    //print will not be valid         
    entity.PrintName();

    return 0;
}