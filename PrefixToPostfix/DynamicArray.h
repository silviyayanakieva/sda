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
#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include <assert.h>
#include <exception>

//some of the implementations are taken from the dynamyc array sample in moodle
template <class TypeName>
class DynamicArray
{
    public:

    DynamicArray(int initialCap);
    DynamicArray();
    ~DynamicArray();
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other);
    void clear();

    void append(const TypeName& elem); //adds element at end of array

    TypeName get(size_t index) const;
    size_t getSize() const;
    size_t getCapacity() const;
    bool isEmpty() const;

    private:
        TypeName* arr;
        size_t arrSize, arrCap;
};

template <class TypeName>
inline DynamicArray<TypeName>::DynamicArray(int initialCap):
    arr(nullptr),arrSize(0),arrCap(initialCap)
    {
     if(initialCap <= 0)
     {
         throw std::invalid_argument("Invalid initial size");
     }
     arr = new TypeName[arrCap];
    }

template <class TypeName>
inline DynamicArray<TypeName>::DynamicArray():
    arr(nullptr),arrSize(0),arrCap(1){}

template <class TypeName>
inline DynamicArray<TypeName>::~DynamicArray()
{
   clear();
}

template <class TypeName>
inline DynamicArray<TypeName>::DynamicArray(const DynamicArray& other):
    arr(nullptr), arrSize(other.getSize()), arrCap(other.getCapacity())
{
  arrCap = arrCap ? arrCap : 1;
  arr = new TypeName[arrCap];
  for(size_t i = 0; i < arrSize; ++i)
        arr[i] = other[i];
}

template <class TypeName>
inline DynamicArray<TypeName>& DynamicArray<TypeName>::operator=(const DynamicArray<TypeName>& other)
{
    if (this != &other)
    {
        ensureSize(other.getSize());
        arrSize = other.getSize();

        for(size_t i = 0; i < arrSize; ++i)
            arr[i] = other[i];
    }
    return *this;
}

template <class TypeName>
inline void DynamicArray<TypeName>::append(const TypeName& elem)
{
   if( (arrSize+1) < getCapacity() )
   {
        arr[arrSize]=elem;
        ++arrSize;
   }
   else
   {
       TypeName* temp = new TypeName[arrCap*2];
       arrCap = arrCap*2;
       for(size_t i = 0; i < arrSize; ++i)
            temp[i] = arr[i];
        delete arr;
        arr=temp;
        arr[arrSize]=elem;
        ++arrSize;
   }
}


template <class TypeName>
inline TypeName DynamicArray<TypeName>::get(size_t index) const
{
    if (index <= arrSize)
        return arr[index];

        else throw std::invalid_argument("Invalid index");
}

template <class TypeName>
inline void DynamicArray<TypeName>::clear()
{
   delete[] arr;
    arr = nullptr;
    arrCap = arrSize = 0;
}

template <class TypeName>
inline size_t DynamicArray<TypeName>::getSize() const
{
    return arrSize;
}

template <class TypeName>
inline size_t DynamicArray<TypeName>::getCapacity() const
{
    return arrCap;
}

template <class TypeName>
inline bool DynamicArray<TypeName>::isEmpty() const
  {
    return arrSize == 0;
  }


#endif // DYNAMIC_ARRAY

