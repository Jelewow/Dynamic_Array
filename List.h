#pragma once

#include <malloc.h>
#include <xutility>
#include <type_traits>

template<typename T>
class List
{
private:
    const size_t kBaseCapacity = 8;

    T* list;
    size_t current_size = 0;
    size_t current_capacity = 0;

    void Reset()
    {
        current_capacity *= 2;
        T* temp = (T*)malloc(current_capacity * sizeof(T));

        for (int i = 0; i < current_size; ++i) {
            if (std::is_move_constructible<T>::value) {
                new(temp + i) T(std::move(list[i]));
            }
            else {
                new(temp + i) T(std::ref(list[i]));
            }
        }
          
        Erase();
        list = temp;
    }

    void Erase()
    {
        for (int i = 0; i < current_size; ++i)
            list[i].~T();

        free(list);
    }

public:
    class Iterator
    {
    private:
        const List* ptrList;
        bool isReverse;
        size_t index;
        size_t end;

    public:
        Iterator(const List* list, int index, int end, bool is_reverse)
        {
            isReverse = is_reverse;
            ptrList = list;
            this->index = index;
            this->end = end;
        }

        const T& get() const
        {
            return ptrList->list[index];
        }

        void set(const T& value)
        {
            ptrList->list[index] = value;
        }

        void next()
        {
            isReverse ? index-- : index++;
        }

        bool hasNext() const
        {
            return index != end;
        }
    };

    List()
    {
        list = (T*)malloc(kBaseCapacity * sizeof(T));
        current_capacity = kBaseCapacity;
        current_size = 0;
    }

    List(int capacity)
    {
        list = (T*)malloc(capacity * sizeof(T));
        current_capacity = capacity;
        current_size = 0;
    }

    ~List()
    {
        Erase();
    }

    int insert(const T& value)
    {
        if (current_size == current_capacity)
        {
            Reset();
        }
        
        if (std::is_move_constructible<T>::value) {
            new(list + current_size) T(std::move(value));
        }
        else 
        {
            new(list + current_size) T(std::ref(value));
        }
        current_size++;
        return current_size - 1;
    }

    int insert(int index, const T& value)
    {
        if (current_size == current_capacity)
        {
            Reset();
        }
            
        if (std::is_move_constructible<T>::value)
        {
            for (int i = current_size; i > index; i--)
            {
                new(list + i) T(std::move(list[i - 1]));
                list[i - 1].~T();
            }
        }
        else
        {
            for (int i = current_size; i > index; i--)
            {
                new(list + i) T(list[i - 1]);
                list[i - 1].~T();
            }
        }

        current_size++;
        if (std::is_move_constructible<T>::value) {
             new(list + index) T(std::move(value));
        }
        else 
        {
            new(list + index) T(std::ref(value));
        }
        return index;
    }

    void remove(int index)
    {
        list[index].~T();

        if (std::is_move_constructible<T>::value)
        {
            for (int i = index; i < current_size - 1; i++)
            {
                new(list + i) T(std::move(list[i + 1]));
                list[i + 1].~T();
            }
        }
        else
        {
            for (int i = index; i < current_size - 1; i++)
            {
                new(list + i) T(list[i + 1]);
                list[i + 1].~T();
            }
        }
        
        current_size--;
    }

    int size() const
    {
        return current_size;
    }

    int capacity() const
    {
        return current_capacity;
    }

    const T& operator[](int index) const
    {
        return list[index];
    }

    T& operator[](int index)
    {
        return list[index];
    }

    Iterator iterator()
    {
        return Iterator(this, 0, this->current_size, false);
    }

    const Iterator iterator() const
    {
        return Iterator(this, 0, this->current_size, false);
    }

    Iterator reverseIterator()
    {
        return Iterator(this, this->current_size - 1, -1, true);
    }

    const Iterator reverseIterator() const
    {
        return Iterator(this, this->current_size - 1, -1, true);
    }
};