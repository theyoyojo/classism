#include <stdio.h>
#include "class_vector.h"

int main ( int argc , char * argv [] )
{
  CVECTOR _VECTOR = NULL ;
  if ( ( _VECTOR = vector_class_init () ) == NULL ) printf ( "class load failed\n" ) ;

  Vector t = new_vector() ;

  t.push( 3 ) ;

  int * data ;

  t.getData() ;

  data = t.copies -> data ;

  printf ( "Data 0: %d\n" , data [ 0 ] ) ;

  t.destroy() ;


  vector_class_destroy ( & _VECTOR ) ;

  return 0 ;
}
