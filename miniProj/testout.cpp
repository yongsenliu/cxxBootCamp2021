#include <iostream>
#include <iomanip>
#include <numeric>
using namespace std;

const int NUMROWS = 3;
const int NUMCOLS = 3;
const int NUM = NUMROWS * NUMCOLS;

//======================================================================

void toRowCol( int n, int &row, int &col )      // convert from 1d index [n] to 2d index [row][col]
{
   col = n % NUMCOLS;
   row = n / NUMCOLS;
}

//======================================================================

int fromRowCol( int row, int col )              // returns 1d index [n] from 2d index [row][col]
{
   return row * NUMCOLS + col;
}

//======================================================================

int main()
{
   int row, col, n;
   int a[NUM];
   iota( a, a + NUM, 0 );

   #define SP << ' ' << setw( 4 ) <<
   #define NL << '\n'

   cout SP "row" SP "col" SP "a[n]" NL;
   for ( n = 0; n < NUM; n++ ) 
   {
      toRowCol( n, row, col );
      cout SP row SP col SP a[n] NL;
   }

   cout NL NL;

   cout << "2d array:\n";
   for ( row = 0; row < NUMROWS; row++ )
   {
      for ( col = 0; col < NUMCOLS; col++ )
      {
         n = fromRowCol( row, col );
         cout SP a[n];
      }
      cout NL;
   }
}