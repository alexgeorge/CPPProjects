#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class CSettingsSington
{
    int m_value;
    static CSettingsSington *s_instance;
  public:
    int get_value()
    {
        return m_value;
    }
    void set_value(int v)
    {
        m_value = v;
    }
    static CSettingsSington *instance()
    {
        if (!s_instance){
          s_instance = new CSettingsSington;
		}
		return s_instance;
    }
private:
	CSettingsSington(int v=0) {m_value=v;};						//private ctor, only self create it
	CSettingsSington(const CSettingsSington& gc) = delete;			//prevent copy-construction
	CSettingsSington &operator = (const CSettingsSington& gc);	//prevent assignment
};

// Allocating and initializing CSettingsSington's
// static data member.  The pointer is being
// allocated - not the object inself.
CSettingsSington *CSettingsSington::s_instance = 0;

void foo(void)
{
  CSettingsSington::instance()->set_value(1);
  cout << "foo: global_ptr is " << CSettingsSington::instance()->get_value() << '\n';
}

void bar(void)
{
  CSettingsSington::instance()->set_value(2);
  cout << "bar: global_ptr is " << CSettingsSington::instance()->get_value() << '\n';
}

int main()
{
  cout << "main: global_ptr is " << CSettingsSington::instance()->get_value() << '\n';
  foo();
  bar();
  return 0;
}