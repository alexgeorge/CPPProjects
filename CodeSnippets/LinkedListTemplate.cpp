//linkedlist.h header
#include <iostream>

template <class T>
class Node 
{
public:
  Node (const T &value, Node<T> *next = 0);
  ~Node () ;
  Node<T>* next ();
  void next (Node<T> *new_next); 
  const T& value ();
  void value (const T &value);

private:
  Node ();
  T value_;
  Node<T> *next_;
};

template <class T>
class LinkedList 
{
public:
  LinkedList ();
  ~LinkedList (); 

  // returns 0 on success, -1 on failure
  int insert (const T &new_item) ;  
  // returns 0 on success, -1 on failure
  int remove (const T &item_to_remove);
  void print (void);

private:
  void delete_nodes (void);
  Node<T> *head_;
};

// main.cc
// Andrew Gilpin
// agg1@cec.wustl.edu

// This file contains the example program used in the gdb debugging
// tutorial. The tutorial can be found on the web at
// htemplate <class T>p://students.cec.wustl.edu/~agg1/tutorial/

using namespace std;

int number_instantiated = 0;

//node implementation
template <class T> Node<T>::Node(const T &value, Node<T> *next) : 
value_(value), 
next_(next) 
{
    cout << "Creating Node, "
         << ++number_instantiated
         << " are in existence right now" << endl;
}
template <class T>  Node<T>::~Node () 
{
    cout << "Destroying Node, "
         << --number_instantiated
         << " are in existence right now" << endl;
    next_ = 0;
}

template <class T>  Node<T>* Node<T>::next()
{ 
	return next_; 
}
template <class T>  void Node<T>::next (Node<T> *new_next) 
{ 
	next_ = new_next; 
}
template <class T>  const T& Node<T>::value () 
{ 
	return value_; 
}
template <class T>  void Node<T>::value (const T &value) 
{ 	value_ = value; 
}

//LinkedList implemntation
template <class T> LinkedList<T>::LinkedList () : 
head_(0) 
{
}
template <class T> LinkedList<T>::~LinkedList () 
{ 
	delete_nodes (); 
}

// returns 0 on success, -1 on failure
template <class T> int LinkedList<T>::insert (const T &new_item) 
{
    return ((head_ = new Node<T>(new_item, head_)) != 0) ? 0 : -1;
}

// returns 0 on success, -1 on failure
 template <class T> int LinkedList<T>::remove (const T &item_to_remove) 
{
    Node<T> *marker = head_;
    Node<T> *temp = 0;  // temp points to one behind as we iterate

    while (marker != 0) {
      if (marker->value() == item_to_remove) {
        if (temp == 0) { // marker is the first element in the list
          if (marker->next() == 0) {
            head_ = 0;
            delete marker; // marker is the only element in the list
            marker = 0;
          } else {
            head_ = new Node<T>(marker->value(), marker->next());
            delete marker;
            marker = 0;
          }
          return 0;
        } else {
          temp->next (marker->next());
          delete temp;
          temp = 0;
          return 0;
        }
      }
      marker = 0;  // reset the marker
      temp = marker;
      marker = marker->next();
    }

    return -1;	// failure
}

template <class T> void LinkedList<T>::print (void) 
{
    Node<T> *marker = head_;
    while (marker != 0) {
      cout << marker->value() << endl;
      marker = marker->next();
    }
}

template <class T> void LinkedList<T>::delete_nodes (void) 
{
    Node<T> *marker = head_;
    while (marker != 0) {
      Node<T> *temp = marker;
      delete marker;
      marker = temp->next();
    }
}
        

int LLTemplatemain (int argc, char **argv) {
  LinkedList<int> *list = new LinkedList<int> ();

  list->insert (1);
  list->insert (2);
  list->insert (3);
  list->insert (4);

  cout << "The fully created list is:" << endl;
  list->print ();

  cout << endl << "Now removing elements:" << endl;
  list->remove (4);
  list->print ();
  cout << endl;

  list->remove (1);
  list->print ();
  cout << endl;

  list->remove (2);
  list->print ();
  cout << endl;

  list->remove (3);
  list->print ();

  delete list;

  return 0;
}




