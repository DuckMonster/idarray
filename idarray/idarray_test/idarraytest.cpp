#include "stdafx.h"
#include "CppUnitTest.h"
#include <idarray.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace idarray_test {
    TEST_CLASS( ArrayTesting ) {
public:

    TEST_METHOD( Initalizing ) {
        idarray<int> arr;

        Assert::AreEqual<size_t>( 0, arr.count( ) );
        Assert::AreEqual<size_t>( 2, arr.size( ) );
    }

    TEST_METHOD( AddThenRemove ) {
        idarray<int> arr;

        for (int i=0; i <= 0x000000FF; i++)
            Assert::AreEqual<size_t>( i, arr.insert( i ) );

        Assert::AreEqual<size_t>( 0x000000FF + 1, arr.count( ) );
        Assert::AreEqual<size_t>( 0x000000FF + 1, arr.size( ) );

        // Remove first
        arr.remove( 0 );
        
        // Adding should return ID 0
        Assert::AreEqual<size_t>( 0, arr.insert( 0 ) );

        // Remove all elements
        for (int i=0; i < 0x000000FF; i++)
            arr.remove( (size_t)i );

        Assert::AreEqual<size_t>( 0, arr.count( ) );
        Assert::AreEqual<size_t>( 0x000000FF, arr.size( ) );
    }
    };
}