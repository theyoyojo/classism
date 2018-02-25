#include "class_vector.h"
#include "vector.h"

#define CAST_CLASS CVector * _Vector = ( CVector * ) _VECTOR 

typedef struct class_vector
{
  void ( * init ) ( CVECTOR ) ;
  void ( * destroy ) ( CVECTOR ) ;
  void ( * getSize ) ( CVECTOR ) ;
  void ( * getCapacity ) ( CVECTOR ) ;
  void ( * getData ) ( CVECTOR ) ;
  void ( * push ) ( CVECTOR , int ) ;
  void ( * pop ) ( CVECTOR ) ;

  int nInstances ;
  VECTOR * instances ;

  Vector init_return ;

  int getSize_return ;

  int getCapacity_return ;

  int * getData_return ;
  
} CVector ;

void exec_init ( CVECTOR _VECTOR )
{
  CAST_CLASS ; 

  _Vector -> instances = ( VECTOR * ) realloc (
      _Vector -> instances ,
      sizeof ( VECTOR ) * ++ _Vector -> nInstances  ) ;
  _Vector -> instances [ _Vector -> nInstances - 1 ] = vector_init_default () ;
  
  Vector header ;

  header.flags = vector_get_flags ( _Vector -> instances [ _Vector -> nInstances - 1 ] ) ;
  header.copies = vector_get_copies ( _Vector -> instances [ _Vector -> nInstances - 1 ] ) ;
  
  _Vector -> init_return = header ;
}

Vector return_init ( CVECTOR _VECTOR )
{
  CAST_CLASS ;
  return _Vector -> init_return ;
}

void exec_push ( CVECTOR _VECTOR , int d )
{
  CAST_CLASS ;

  int i ;
  FVector * piFlags ;
  for ( i = 0 ; i < _Vector -> nInstances ; i ++ )
  {
    if ( _Vector -> instances [ i ] == NULL ) continue ;

    piFlags = vector_get_flags ( _Vector -> instances [ i ] ) ;
    if ( piFlags -> fPush == 1 )
    {
      piFlags -> fPush = 0 ;
      vector_push ( _Vector -> instances [ i ] , d ) ;
    }
  }
  
}

void exec_destroy ( CVECTOR _VECTOR )
{
  CAST_CLASS ;

  int i ;
  FVector * piFlags ;

  for ( i = 0 ; i < _Vector -> nInstances ; i ++ )
  {
    if ( _Vector -> instances [ i ] == NULL ) continue ;

    piFlags = vector_get_flags ( _Vector -> instances [ i ] ) ;
    if ( piFlags -> fDestroy == 1 )
    {
      piFlags -> fDestroy = 0 ;
      vector_destroy ( & _Vector -> instances [ i ] ) ;
    }
  }
}

void exec_getData ( CVECTOR _VECTOR )
{
  CAST_CLASS ;

  int i , * data ;
  FVector * piFlags ;

  for ( i = 0 ; i < _Vector -> nInstances ; i ++ )
  {
    if ( _Vector -> instances [ i ] == NULL ) continue ;

    piFlags = vector_get_flags ( _Vector -> instances [ i ] ) ;
    if ( piFlags -> fGet_data == 1 )
    {
      piFlags -> fGet_data = 0 ;
      data = vector_get_data ( _Vector -> instances [ i ] ) ;
    }
  }

  _Vector -> getData_return = data ;
}

int * return_getData ( CVECTOR _VECTOR )
{
  CAST_CLASS ;

  return _Vector -> getData_return ;
}

CVECTOR vector_class_init ( void )
{
  printf ( "in class_init()\n");
  CVector * _Vector = NULL ;
  if ( ( _Vector = ( CVector * ) malloc ( sizeof ( CVector ) ) ) == NULL ) return NULL ;

  _Vector -> instances = NULL ;
  _Vector -> nInstances = 0 ;

  _Vector -> init = exec_init ;
  _Vector -> destroy = exec_destroy ;
  _Vector -> push = exec_push ;
  _Vector -> getData = exec_getData ;

  NONE.flags = NULL ;
  
  return ( CVECTOR ) _Vector ;
}

void vector_class_destroy ( CVECTOR * p_VECTOR )
{
  CVector * * p_Vector = ( CVector * * ) p_VECTOR ;

  int i ;
  for ( i = 0 ; i < ( * p_Vector ) -> nInstances ; i ++ )
  {
    if ( ( * p_Vector ) -> instances [ i ] != NULL )
    {
      free ( ( * p_Vector ) -> instances [ i ] ) ;
    }
  }
  free ( ( * p_Vector ) -> instances ) ;

  free ( * p_Vector ) ;
  * p_Vector = NULL ;
} 


