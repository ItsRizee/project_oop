#ifndef VECTOR_H
#define VECTOR_H

template<typename T>
class Vector {
private:
    T* data;
    int count;
    int capacity;

    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < count; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
    }

public:
    Vector() {
        capacity = 2;
        count = 0;
        data = new T[capacity];
    }

    ~Vector() {
        delete[] data;
    }

    void push_back(T item) {
        if (count == capacity)
            resize();
        data[count++] = item;
    }

    void remove(int index) {
        if (index < 0 || index >= count) return;
        for (int i = index; i < count - 1; ++i)
            data[i] = data[i + 1];
        --count;
    }

    bool contains(const T& item) const {
        for (int i = 0; i < count; ++i) {
            if (data[i] == item)
                return true;
        }
        return false;
    }


    T get(int index) const {
        if (index < 0 || index >= count)
            return nullptr;
        return data[index];
    }

    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    int size() const {
        return count;
    }
};

#endif