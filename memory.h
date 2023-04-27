#ifndef __MEMORY_H__
#define __MEMORY_H__

	#include <stddef.h>

	void* MEM_f_alloc( size_t );
	void* MEM_f_realloc( size_t, void* );
	void  MEM_f_free( void* );

#endif