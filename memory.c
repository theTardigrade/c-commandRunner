
#include "memory.h"

#include <stdlib.h>

void* MEM_f_alloc( size_t n_size )
{
	void* pv_result = malloc( n_size );

    if ( pv_result == NULL )
        exit( EXIT_FAILURE );

    return pv_result;
}

void* MEM_f_realloc( size_t n_size, void* pv_block )
{
	void* pv_result = realloc( pv_block, n_size );

    if ( pv_result == NULL )
        exit( EXIT_FAILURE );

    return pv_result;
}

void MEM_f_free( void* pv )
{
    if ( pv != NULL )
    {
        free( pv );
        pv = NULL;
    }
}