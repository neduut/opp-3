#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* buffer;
    size_t _size;
    size_t _capacity;

    // 1. reallocate
    void reallocate(size_t new_cap) {
        if (new_cap == _capacity) return;
        T* new_buffer = new T[new_cap];
        size_t new_size = std::min(_size, new_cap);
        for (size_t i = 0; i < new_size; ++i) {
            new_buffer[i] = std::move(buffer[i]);
        }
        delete[] buffer;
        buffer = new_buffer;
        _capacity = new_cap;
        _size = new_size;
    }

public:
    // CONSTRUCTORS

    // 2. vector (default constructor)
    Vector() : buffer(nullptr), _size(0), _capacity(0) {}

    // 3. vector (size constructor)
    explicit Vector(size_t n) : buffer(new T[n]), _size(n), _capacity(n) {}

    // 4. vector (size, value constructor)
    Vector(size_t n, const T& value) : buffer(new T[n]), _size(n), _capacity(n) {
        for (size_t i = 0; i < n; ++i) buffer[i] = value;
    }

    // 5. vector (initializer_list constructor)
    Vector(std::initializer_list<T> init)
        : buffer(new T[init.size()]), _size(init.size()), _capacity(init.size()) {
        size_t i = 0;
        for (const T& val : init) {
            buffer[i++] = val;
        }
    }

    // RULE OF FIVE

    // 6. vector (copy constructor)
    Vector(const Vector<T>& other) : buffer(new T[other._capacity]), _size(other._size), _capacity(other._capacity) {
        for (size_t i = 0; i < _size; ++i) buffer[i] = other.buffer[i];
    }

    // 7. vector (move constructor)
    Vector(Vector<T>&& other) noexcept : buffer(other.buffer), _size(other._size), _capacity(other._capacity) {
        other.buffer = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    // 8. ~vector (destructor)
    ~Vector() { delete[] buffer; }

    // 9. operator= (copy assignment)
    Vector<T>& operator=(const Vector<T>& other) {
        if (this != &other) {
            delete[] buffer;
            _capacity = other._capacity;
            _size = other._size;
            buffer = new T[_capacity];
            for (size_t i = 0; i < _size; ++i) buffer[i] = other.buffer[i];
        }
        return *this;
    }

    // 10. operator= (move assignment)
    Vector<T>& operator=(Vector<T>&& other) noexcept {
        if (this != &other) {
            delete[] buffer;
            buffer = other.buffer;
            _size = other._size;
            _capacity = other._capacity;
            other.buffer = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    // ELEMENT ACCESS

    // 11. operator[]
    T& operator[](size_t index) { return buffer[index]; }
    
    // 12. operator[] const
    const T& operator[](size_t index) const { return buffer[index]; }
    
    // 13. back
    T& back() { return buffer[_size - 1]; }
    const T& back() const { return buffer[_size - 1]; }

    // 14. front
    T& front() { return buffer[0]; }
    const T& front() const { return buffer[0]; }

    // 15. data
    T* data() { return buffer; }
    const T* data() const { return buffer; }

    // 16. at
    T& at(size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return buffer[index];
    }
    const T& at(size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return buffer[index];
    }

    // ITERATORS

    // 17. begin
    T* begin() { return buffer; }
    const T* begin() const { return buffer; }

    // 18. end
    T* end() { return buffer + _size; }
    const T* end() const { return buffer + _size; }

    // SIZE AND CAPACITY

    // 19. size
    size_t size() const { return _size; }

    // 20. capacity
    size_t capacity() const { return _capacity; }

    // 21. empty
    bool empty() const { return _size == 0; }

    // MEMORY MANAGEMENT

    // 22. reserve
    void reserve(size_t new_cap) {
        if (new_cap > _capacity) reallocate(new_cap);
    }
    
    // 23. shrink_to_fit
    void shrink_to_fit() {
        if (_capacity > _size) reallocate(_size);
    }

    // MODIFIERS

    // 24. push_back (copy)
    void push_back(const T& value) {
        if (_size >= _capacity) reserve(_capacity ? _capacity * 2 : 1);
        buffer[_size++] = value;
    }

    // 25. push_back (move)
    void push_back(T&& value) {
        if (_size >= _capacity) reserve(_capacity ? _capacity * 2 : 1);
        buffer[_size++] = std::move(value);
    }

    // 26. pop_back
    void pop_back() { if (_size > 0) --_size; }

    // 27. clear
    void clear() { _size = 0; }

    // 28. resize (without value)
    void resize(size_t new_size) {
        if (new_size > _capacity) reserve(new_size);
        _size = new_size;
    }

    // 29. resize (with value)
    void resize(size_t new_size, const T& value) {
        if (new_size > _size) {
            if (new_size > _capacity) reserve(new_size);
            for (size_t i = _size; i < new_size; ++i) buffer[i] = value;
        }
        _size = new_size;
    }

    // 30. insert
    void insert(size_t index, const T& value) {
        if (index > _size) throw std::out_of_range("Index out of range");
        if (_size >= _capacity) reserve(_capacity ? _capacity * 2 : 1);
        for (size_t i = _size; i > index; --i) buffer[i] = std::move(buffer[i - 1]);
        buffer[index] = value;
        ++_size;
    }

    // 31. erase
    void erase(size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < _size - 1; ++i) buffer[i] = std::move(buffer[i + 1]);
        --_size;
    }

    // 32. swap
    void swap(Vector<T>& other) {
        std::swap(buffer, other.buffer);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    // 33. assign
    void assign(size_t count, const T& value) {
        clear();
        if (count > _capacity) reserve(count);
        _size = count;
        for (size_t i = 0; i < count; ++i) buffer[i] = value;
    }

    // 34. reverse
    void reverse() {
        for (size_t i = 0; i < _size / 2; ++i) {
            std::swap(buffer[i], buffer[_size - i - 1]);
        }
    }

    // 35. remove
    void remove(const T& value) {
        int idx = index_of(value);
        if (idx != -1) erase(static_cast<size_t>(idx));
    }

    // COMPARISON OPERATORS

    // 36. operator==
    bool operator==(const Vector<T>& other) const {
        if (_size != other._size) return false;
        for (size_t i = 0; i < _size; ++i) {
            if (buffer[i] != other.buffer[i]) return false;
        }
        return true;
    }

    // 37. operator!=
    bool operator!=(const Vector<T>& other) const { return !(*this == other); }

    // 38. operator<
    bool operator<(const Vector<T>& other) const {
        size_t min_size = std::min(_size, other._size);
        for (size_t i = 0; i < min_size; ++i) {
            if (buffer[i] < other.buffer[i]) return true;
            else if (buffer[i] > other.buffer[i]) return false;
        }
        return _size < other._size;
    }

    // 39. operator>
    bool operator>(const Vector<T>& other) const { return other < *this; }

    // SEARCH

    // 40. contains
    bool contains(const T& value) const {
        for (size_t i = 0; i < _size; ++i) {
            if (buffer[i] == value) return true;
        }
        return false;
    }

    // 41. index_of
    int index_of(const T& value) const {
        for (size_t i = 0; i < _size; ++i) {
            if (buffer[i] == value) return static_cast<int>(i);
        }
        return -1;
    }

    // OTHER UTILITIES

    // 42. slice
    Vector<T> slice(size_t start, size_t end) const {
        if (start > end || end > _size) throw std::out_of_range("Invalid slice range");
        Vector<T> result;
        result.reserve(end - start);
        for (size_t i = start; i < end; ++i) result.push_back(buffer[i]);
        return result;
    }

    // 43. sort
    void sort() { std::sort(begin(), end()); }

    // 44. unique
    void unique() {
        if (_size <= 1) return;
        sort();
        size_t j = 0;
        for (size_t i = 1; i < _size; ++i) {
            if (buffer[j] != buffer[i]) buffer[++j] = std::move(buffer[i]);
        }
        _size = j + 1;
    }
    // 45. map
    Vector<T> map(std::function<T(const T&)> func) const {
        Vector<T> result;
        result.reserve(_size);
        for (size_t i = 0; i < _size; ++i) result.push_back(func(buffer[i]));
        return result;
    }
};