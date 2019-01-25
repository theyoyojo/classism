#include <stdio.h>
#include "class_vector.h"

int main ( int argc , char * argv [] )
{
  Vector t = new_vector() ;

  t.push( 3 ) ;

  int * data ;

  int x = t.getData() ;

  data = t.copies -> data ;

  printf ( "Data 0: %d\n" , data [ 0 ] ) ;

  t.destroy() ;

  return 0 ;
}
