#include <iostream>
#include <thread>
#include "idarray.hpp"

using namespace std;

struct foo {
    int arr[100];
};

struct f {
    char a[5];
    bool b;
};

int main( ) {
    {
        idarray<int> arr;

        for (int i=0; i < 0x0000FFFF; i++)
            arr.insert( int() );

        this_thread::sleep_for( chrono::seconds( 10 ) );
    }

    this_thread::sleep_for( chrono::seconds( 5 ) );

    return 0;
}