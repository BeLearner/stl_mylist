/*
 * =====================================================================================
 *
 *       Filename:  test_own_list.cpp
 *
 *    Description:  create my list and my iterator
 *
 *        Version:  1.0
 *        Created:  04/26/2017 07:51:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eden(pengquan.wang@dasudian.com) (), 
 *   Organization:  www.dasudian.com
 *
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>

template <class T>
class list_item{
private:
    T _value;
    list_item *_next;
public:
    typedef T value_type;
    list_item(int value) {_value = value; _next = NULL;}
    T value() const {return _value;}
    list_item * next() {return _next;}
    void set_next(list_item *next) {_next = next;}

    int operator!=(int a) {
        return _value != a;
    }
    int operator==(int a) {
        return _value == a;
    }
};

template <class T>
class mylist
{
private:
    list_item<T> * _front;
    list_item<T> * _end;
    long _size;

public:
    mylist() {
        _size = 0;
        _front = NULL;
        _end = NULL;
    }

    void insert_front(T value) {
        list_item<T> *tmp = new list_item<T>(value);
        tmp->set_next(_front);
        _front = tmp;
        if (0 == _size) {
            _end = _front;
        }
        _size ++;
    }
    void insert_end(T value) {
        list_item<T> *tmp = new list_item<T>(value);
        if (_end != NULL) {
            _end->set_next(tmp);
            _end = tmp;
        } else {
            _front = _end = tmp;
        }
        _size ++;
    }
    void display(std::ostream &os = std::cout) const {
        list_item<T> * tmp;
        os << "element: ";
        for (tmp = _front; tmp != NULL && tmp != _end->next(); tmp = tmp->next()) {
            os << tmp->value() << " ";
        }
        os << std::endl;
    }
    list_item<T>* front() const {
        return _front;
    }
};

//iterator
template <class Item>
struct mylist_iterator {
    Item *ptr;

    typedef Item value_type;
    typedef Item* difference_type;
    typedef Item& reference;
    typedef Item* pointer;
    typedef std::input_iterator_tag iterator_category;

    mylist_iterator(Item *p = NULL)
        : ptr(p) {

        }
    /* return value should be a reference since it should be a lvalue */
    Item& operator*() const {return *ptr;}
    Item* operator->() const {return ptr;}
    /* access item of list */
    mylist_iterator& operator++() {ptr = ptr->next(); return *this;}
    mylist_iterator& operator++(int) {mylist_iterator tmp = *this; ++*this; return tmp;}
    bool operator==(const mylist_iterator &iterator) const { return ptr == iterator.ptr;}
    bool operator!=(const mylist_iterator &iterator) const { return ptr != iterator.ptr;}
    /* access item of list */
    typename Item::value_type value() { return ptr->value();}
};

using namespace std;

int main(int argc, char *argv[])
{
    mylist<int> ilist;
    int i;

    for (i = 0; i< 10; ++i) {
//        ilist.insert_front(i);
        ilist.insert_end(i);
    }
    ilist.display();

    mylist_iterator < list_item<int> > begin(ilist.front());
    mylist_iterator < list_item<int> > end;
    mylist_iterator < list_item<int> > it = find(begin, end, 5);
    if (it == end) {
        cout << "not found " << 5 <<endl;
    } else {
        cout << "found " << it->value() <<endl;
    }

    return 0;
}
