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

        for (int i=0; i < 0x000000FF; i++)
            arr.insert( i * 2 );

        while (true) {
            clock_t startTime = clock( );

            arr.find( 0x000000FF - 1 );
            cout << double( clock( ) - startTime ) / (double)CLOCKS_PER_SEC << " seconds.\n";

            this_thread::sleep_for( chrono::seconds( 1 ) );
        }
    }

    cin.get( );

    return 0;
}