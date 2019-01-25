#ifndef CLASS_VECTOR_H
#define CLASS_VECTOR_H "class_vector.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

// Note from 25 January 2019: I should have documented this program

typedef struct Cvector_public CVector_public ;
typedef CVector_public * CVECTOR ;

typedef struct Cvector_public
{
  void ( * init ) ( CVECTOR ) ;
  void ( * destroy ) ( CVECTOR ) ;
  void ( * getSize ) ( CVECTOR ) ;
  void ( * getCapacity ) ( CVECTOR ) ;
  void ( * getData ) ( CVECTOR ) ;
  void ( * push ) ( CVECTOR , int ) ;
  void ( * pop ) ( CVECTOR ) ;
} CVector_public ;

typedef struct header
{
  FVector * flags ;
  YVector * copies ;
} Vector ;

Vector NONE ;

#define destroy() flags -> fDestroy = 1 ; \
                  _VECTOR -> destroy(_VECTOR) ;

#define new_vector() ( _VECTOR -> init (_VECTOR) , 1 ) ? return_init ( _VECTOR ) : NONE ;

#define push(d) flags -> fPush = 1 ; \
               _VECTOR -> push ( _VECTOR , d )

#define getData() flags -> fGet_data -> enable()  ,\
                 _VECTOR -> getData ( _VECTOR ) , return_getData ( _VECTOR )


CVECTOR _VECTOR ;
void class_vector_premain() __attribute__ ((constructor)) ;
void class_vector_postmain() __attribute__ ((destructor)) ;

CVECTOR vector_class_init ( void ) ;

void vector_class_destroy ( CVECTOR * p_Vector ) ;

Vector return_init ( CVECTOR _VECTOR ) ;

int * return_getData ( CVECTOR _VECTOR ) ;

/*

   Why does this cause multiple definition error at linking?

#ifndef main
#define main xmain( int argc , char * argv [] ) ; \
CVECTOR _VECTOR = NULL ; \
int main( int argc , char * argv [] ) 
{ \
  int main_return ; \
  if ( ( _VECTOR = vector_class_init () ) == NULL ) \
  { \
    printf ( "Error intitalizing vector class. Killing self...\n" ) ; \
    exit ( 1 ) ; \
  } \
  main_return = xmain ( argc , argv ) ; \
  vector_class_destroy ( & _VECTOR ) ; \
  return main_return ; \
} ; \
int xmain
#endif

*/

#endif
