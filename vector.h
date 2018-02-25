#ifndef VECTOR_H
#define VECTOR_H "vector.h"
#include <stdio.h>
#include <stdlib.h>

typedef void * VECTOR ;

typedef struct flags_vector {
  int fDestroy ;
  int fGet_size ;
  int fGet_capacity ;
  int fGet_data ;
  int fPush ;
  int fPop ;
} FVector ;

typedef struct copies_vector
{
  int * data ;
  int size ;
  int capacity ;
} YVector ;

VECTOR vector_init_default ( void ) ;

void vector_destroy ( VECTOR * phVector ) ;

// Functions return a value from copy 

int vector_get_size ( VECTOR hVector ) ;

int vector_get_capacity ( VECTOR hVector ) ;

int * vector_get_data ( VECTOR hVector ) ;

void vector_push ( VECTOR hVector , int d ) ;

void  vector_pop ( VECTOR hVector ) ;

FVector * vector_get_flags ( VECTOR hVector ) ;

YVector * vector_get_copies( VECTOR hVector ) ;

#endif
