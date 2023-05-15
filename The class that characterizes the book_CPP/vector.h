#ifndef VECTOR_H
#define VECTOR_H
#include <algorithm>
template <typename T>
class vector
{
private:
    T *vfirst;
    int size_;
    int capacity_;
public:
    typedef T* iterator;
    vector();
    void push_back(const T& t);
    void del(int index);
    T& operator[] (int i) const;
    const T& last ();
    iterator begin ();
    iterator end ();
    int size() const;
    bool empty() const;
    int capacity() const;
    void clear();
};
template <typename T>
vector<T>::vector()
{
  vfirst=new T[3];
  size_=0;
  capacity_=3;
}
template <typename T>
void vector<T>::clear()
{
    delete[] vfirst;
    vfirst=new T[3];
    size_=0;
    capacity_=3;
}
template <typename T>
void vector<T>::push_back(const T& t)
{
    if (capacity_==size_)
    {
        int newcapacity=2*capacity();
        T *newmem=new T[newcapacity];
        std::copy(begin(),end(),newmem);
        delete[] vfirst;
        vfirst=newmem;
        capacity_*=2;
    }
        *(vfirst+size_)=t;
        size_++;
}
template <typename T>
void vector<T>::del(int index)
{
    for (int i=index+1;i<size_;i++)
    {
        vfirst[i-1]=vfirst[i];
    }
    size_--;
}
template <typename T>
int vector<T>::capacity() const
{
    return capacity_;
}
template <typename T>
int vector<T>::size() const
{
    return size_;
}
template <typename T>
bool vector<T>::empty() const
{
    return (size_==0);
}
template <typename T>
T& vector<T>::operator[](int pos) const
{
    return (*(vfirst + pos));
}
template <typename T>
typename vector<T>::iterator vector<T>::begin ()
{
    return vfirst;
}
template <typename T>
typename vector<T>::iterator vector<T>::end ()
{
    return vfirst+size_;
}
template <typename T>
const T& vector<T>::last()
{
    return *(vfirst+size_-1);
}
#endif // VECTOR_H
