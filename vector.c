#include "vector.h"
#define CAST OVector * pVector = ( OVector * ) hVector

typedef struct vector
{
  int * data ;
  int size ;
  int capacity ;

  FVector * flags ;
  YVector * copies ;
} OVector ;


VECTOR vector_init_default ( void )
{
  OVector * pVector = NULL ;
  if ( ( pVector = ( OVector * ) malloc ( sizeof ( OVector ) ) ) == NULL ) return NULL ;

  if ( ( pVector -> flags = ( FVector * ) malloc ( sizeof ( FVector ) ) ) == NULL )
  {
    free ( pVector ) ;
    return NULL ;
  }
  if ( ( pVector -> copies = ( YVector * ) malloc ( sizeof ( YVector ) ) ) == NULL )
  {
    free ( pVector -> flags ) ;
    free ( pVector ) ;
    return NULL ;
  }

  if ( ( pVector -> data = ( int * ) malloc ( sizeof ( int ) ) ) == NULL )
  {
    free ( pVector -> flags ) ;
    free ( pVector -> copies ) ;
    free ( pVector ) ;
    return NULL ;
  }
  if ( ( pVector -> copies -> data = ( int * ) malloc ( sizeof ( int ) ) ) == NULL )
  {
    free ( pVector -> data ) ;
    free ( pVector -> flags ) ;
    free ( pVector -> copies ) ;
    free ( pVector ) ;
    return NULL ;
  }


  pVector -> size = 0 ;
  pVector -> capacity = 1 ;

  pVector -> copies -> size = 0 ;
  pVector -> copies -> capacity = 1 ;

  pVector -> flags -> fDestroy = 0 ;
  pVector -> flags -> fGet_size = 0 ;
  pVector -> flags -> fGet_capacity = 0 ;
  pVector -> flags -> fGet_data =  0 ;
  pVector -> flags -> fPush = 0 ;
  pVector -> flags -> fPop = 0 ;

  
  return ( VECTOR ) pVector ;
}

void vector_destroy ( VECTOR * phVector )
{
  OVector * * ppVector = ( OVector * * ) phVector ;
  free ( ( * ppVector ) -> flags ) ;
  if ( ( ( * ppVector ) -> copies ) -> data != NULL )
    free ( ( ( * ppVector ) -> copies ) -> data ) ;
  free ( ( * ppVector ) -> copies) ;
  free ( ( * ppVector ) -> data ) ;
  free ( ( * ppVector ) ) ; * phVector = NULL ;
} 

// Functions return a pointer to a copy of the data

int vector_get_size ( VECTOR hVector )
{
  int * dummy = vector_get_data ( hVector ) ;
  CAST ;

  dummy = NULL ;

  return pVector -> size ;
}

int vector_get_capacity ( VECTOR hVector )
{
  int * dummy = vector_get_data ( hVector ) ;
  CAST ;

  dummy = NULL ;

  return pVector -> capacity ;
}

int * vector_get_data ( VECTOR hVector )
{
  CAST ;

  if ( pVector -> copies -> capacity <= pVector -> size )
  {
    pVector -> copies -> data =
      ( int * ) realloc ( pVector -> copies -> data ,
          sizeof ( int ) * pVector -> capacity ) ;
    pVector -> copies -> capacity = pVector -> capacity ;
  }

  for ( int i = 0 ; i < pVector -> size ; i ++ )
  {
    pVector -> copies -> data [ i ] = pVector -> data [ i ] ;
  }

  pVector -> copies -> size = pVector -> size ;

  return pVector -> copies -> data ;
}

void vector_push ( VECTOR hVector , int d )
{
  CAST ;

  if ( pVector -> size + 1 >= pVector -> capacity )
  {
    pVector -> data =
      ( int * ) realloc ( pVector -> data ,
          sizeof ( int ) * ++ pVector -> capacity ) ;
  }
  pVector -> data [ pVector -> size ++ ] = d ;
}

void  vector_pop ( VECTOR hVector )
{
  CAST ;

  pVector -> size -- ;
}

FVector * vector_get_flags ( VECTOR hVector )
{
  CAST ;

  return pVector -> flags ;
}

YVector * vector_get_copies( VECTOR hVector )
{
  CAST ;

  return pVector -> copies ;
}
