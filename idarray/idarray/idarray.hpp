#pragma once
#include <memory>

template<typename T>
class idarray {
public:
    idarray( );
    ~idarray( );

    // Insert an item into the array
    size_t                      insert( const T& value );

    // Remove item by reference
    bool                        remove( const T& value );
    // Remove item by ID
    bool                        remove( const size_t& id );

    // Find the ID of an item in the array
    size_t                      find( const T& value );

    T&                          operator[]( const size_t& id );

private:
    struct entry {
    public:
        T       value;
        bool    valid = false;

        entry( ) :
            value( ),
            valid( false ) {
        }
        entry( const T& value ) :
            value( value ),
            valid( true ) {
        }
    };

    size_t                      _arraySize  = 2;
    size_t                      _arrayCount = 0;
    size_t                      _cursor     = 0;
    entry*                      _array      = nullptr;

    //-----------------------

    // Will allocate new memory (and copy existing memory if it's valid) of set size, and set _arraySize properly
    void                        allocate( int newSize );
    // Will double the size of the array, and allocate it
    void                        expand( );

    // Find an empty ID in the array
    size_t                      findEmpty( );
};

template<typename T>
inline idarray<T>::idarray( ) {
    allocate( _arraySize );
}

template<typename T>
inline idarray<T>::~idarray( ) {
    delete[] _array;
}

template<typename T>
inline size_t idarray<T>::insert( const T & value ) {
    // Expand if necessary
    if (_arrayCount == _arraySize)
        expand( );

    size_t id = findEmpty( );

    // Insert into array
    _array[id] = entry( value );

    // Increase count
    _arrayCount++;

    return id;
}

template<typename T>
inline bool idarray<T>::remove( const T & value ) {
    // Find ID and remove it
    size_t id = find( value );
    remove( id );
}

template<typename T>
inline bool idarray<T>::remove( const size_t & id ) {
    if (id > _arraySize)

    // Reset memory at location
    memset( &_array[id], 0, sizeof( entry ) )
}

template<typename T>
inline size_t idarray<T>::find( const T & value ) {
    entry target( value );

    for (int i=0; i < _arraySize; i++) {
        if (memcmp( &_array[i], &target, sizeof( entry ) ) == 0)
            return i;
    }

    return -1;
}

template<typename T>
inline T & idarray<T>::operator[]( const size_t & id ) {
    return _array[id].value;
}

template<typename T>
inline void idarray<T>::allocate( int newSize ) {
    entry* oldArray     = _array;
    _array              = new entry[newSize];

    // Clear out memory
    memset( _array, 0, sizeof( entry ) * newSize );

    // Copy contents and clean up
    if (oldArray != nullptr) {
        memcpy( _array, oldArray, sizeof( entry ) * _arraySize );
        delete[] oldArray;
    }

    _arraySize = newSize;
}

template<typename T>
inline void idarray<T>::expand( ) {
    // Allocate new memory of double the size
    allocate( _arraySize * 2 );
}

template<typename T>
inline size_t idarray<T>::findEmpty( ) {
    size_t c = _cursor;

    // Loop until c does not point to a valid pointer in the array
    while (_array[c].valid) {

        // Next item (looping around)
        c = (c + 1) % _arraySize;
    }

    // Save cursor, for quicker empty finding
    _cursor = (c + 1) % _arraySize;

    return c;
}
