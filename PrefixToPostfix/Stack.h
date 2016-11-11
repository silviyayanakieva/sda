/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Silviya Yanakieva
 * @idnumber 61881
 * @task 1
 * @compiler GCC
 *
 */
#ifndef MY_STACK
#define MY_STACK

#include<iostream>
#include<cstdlib>
#include <assert.h>
#include<stdexcept>

//fixed size template stack
template <typename Type>
class Stack
{
public:
    Stack(int maxsize);
    ~Stack();

    void Push(const Type & element);
    void Pop();
    Type Top();
    void Clear();

    bool isEmpty();
    size_t getSize();
    size_t getMaxSize();

private:
    Type* data;
    size_t st_capacity, st_size;

};

template <typename Type>
inline Stack<Type>::Stack(int maxsize) : st_size(0) , st_capacity(maxsize)
{
     if (maxsize <= 0)
    {
        throw std::invalid_argument("Invalid size");
    }
    data = new Type[maxsize];
}

template <typename Type>
inline void Stack<Type>::Push(const Type & element)
{
   assert(st_size < st_capacity);
    data[st_size] = element;
    st_size++;
}

template <typename Type>
inline void Stack<Type>::Pop()
{
    assert(st_size > 0);
    --st_size;
}

template <typename Type>
inline Type Stack<Type>::Top()
{
    assert(st_size > 0);
    return data[st_size-1];
}

template <typename Type>
inline void Stack<Type>::Clear()
{
    st_size = 0;
}

template <typename Type>
 inline bool Stack<Type>::isEmpty()
 {
     if (st_size)
        return false;
     else return true;
 }

template <typename Type>
inline size_t Stack<Type>::getSize()
{
    return st_size;
}

template <typename Type>
inline size_t Stack<Type>::getMaxSize()
{
    return st_capacity;
}

 template <typename Type>
inline Stack<Type>::~Stack()
 {
    delete[] data;
 }
#endif // MY_STACK


