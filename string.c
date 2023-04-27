#include "string.h"

#include "memory.h"

#include <stdlib.h>

STR_s_datum_t* STR_f_new( void )
{
	STR_s_datum_t* ps_datum = MEM_f_alloc( sizeof( *ps_datum ) );

	ps_datum->pc_value = NULL;
	ps_datum->n_length = 0;
	ps_datum->n_capacity = 0;
	ps_datum->b_allocated = false;

	return ps_datum;
}


STR_s_datum_t* STR_f_new_with_capacity( int n_capacity )
{
	STR_s_datum_t* ps_datum = MEM_f_alloc( sizeof( *ps_datum ) );
	char* pc_value = MEM_f_alloc( n_capacity );

	ps_datum->pc_value = pc_value;
	ps_datum->n_length = 0;
	ps_datum->n_capacity = n_capacity;
	ps_datum->b_allocated = true;

	return ps_datum;	
}

STR_s_datum_t* STR_f_new_raw( int n_length, const char* pc_value )
{
	if ( n_length < 0 )
		for ( n_length = 0; pc_value[n_length] != '\0'; ++n_length )
		{}

	if ( n_length == 0 )
		return STR_f_new();

	STR_s_datum_t* ps_datum = MEM_f_alloc( sizeof( *ps_datum ) );
	const int n_capacity = n_length + 1;
	char* pc_datum_value = MEM_f_alloc( n_capacity );

	for ( int n = 0; n < n_length; ++n )
		pc_datum_value[n] = pc_value[n];

	pc_datum_value[n_length] = '\0';

	ps_datum->pc_value = pc_datum_value;
	ps_datum->n_length = n_length;
	ps_datum->n_capacity = n_capacity;
	ps_datum->b_allocated = true;

	return ps_datum;
}

STR_s_datum_t* STR_f_new_clone( const STR_s_datum_t* ps_datum )
{
	if ( ps_datum == NULL )
		return STR_f_new();

	return STR_f_new_raw( ps_datum->n_length, ps_datum->pc_value );
}

void STR_f_free( STR_s_datum_t* ps_datum )
{
	if ( ps_datum->b_allocated )
		MEM_f_free( ps_datum->pc_value );
	
	MEM_f_free( ps_datum );
}

void STR_f_increase_capacity( STR_s_datum_t* ps_datum, int n_capacity )
{
	if ( ps_datum == NULL )
		return;

	const int n_capacity_old = ps_datum->n_capacity;

	if ( n_capacity <= n_capacity_old )
		return;

	const int n_capacity_min = n_capacity_old * 2;

	if ( n_capacity < n_capacity_min )
		n_capacity = n_capacity_min;

	const int n_length = ps_datum->n_length;
	char* pc_value_old = ps_datum->pc_value;
	char* pc_value = MEM_f_alloc( n_capacity );

	for ( int n = 0; n < n_length; ++n )
		pc_value[n] = pc_value_old[n];

	if ( ps_datum->b_allocated )
		MEM_f_free( pc_value_old );
	else
		ps_datum->b_allocated = true;

	ps_datum->pc_value = pc_value;
	ps_datum->n_capacity = n_capacity;
}

void STR_f_append_raw( STR_s_datum_t* ps_datum, int n_length, const char* pc_value )
{
	if ( ps_datum == NULL || pc_value == NULL )
		return;

	if ( n_length < 0 )
		for ( n_length = 0; pc_value[n_length] != '\0'; ++n_length )
		{}

	if ( n_length == 0 )
		return;

	const int n_length_old = ps_datum->n_length;
	const int n_length_new = n_length_old + n_length;
	const int n_capacity_new = n_length_new + 1;

	if ( ps_datum->n_capacity < n_capacity_new )
		STR_f_increase_capacity( ps_datum, n_capacity_new );

	char* pc_value_new = ps_datum->pc_value;

	for ( int n = 0; n < n_length; ++n )
		pc_value_new[n_length_old + n] = pc_value[n];

	pc_value_new[n_length_new] = '\0';

	ps_datum->n_length = n_length_new;
}

void STR_f_append( STR_s_datum_t* ps_datum, const STR_s_datum_t* ps_datum_src )
{
	if ( ps_datum_src == NULL )
		return;

	STR_f_append_raw( ps_datum, ps_datum_src->n_length, ps_datum_src->pc_value );
}

void STR_f_append_char_raw( STR_s_datum_t* ps_datum, char c_src )
{
	if ( ps_datum == NULL )
		return;

	const int n_length_old = ps_datum->n_length;
	const int n_length_new = n_length_old + 1;
	const int n_capacity_new = n_length_new + 1;

	if ( ps_datum->n_capacity < n_capacity_new )
		STR_f_increase_capacity( ps_datum, n_capacity_new );

	char* pc_value_new = ps_datum->pc_value;

	pc_value_new[n_length_old] = c_src;
	pc_value_new[n_length_new] = '\0';

	ps_datum->n_length = n_length_new;
}