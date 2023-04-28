#include "flag.h"

#include "memory.h"

#include <stddef.h>
#include <stdlib.h>

FLA_s_data_t* FLA_f_new( int n_argc, const char** ppc_argv )
{
	FLA_s_data_t* ps_data = MEM_f_alloc( sizeof( *ps_data ) );

	ps_data->n_size = 0;

	for ( int n = FLA_gn_data_max - 1; n >= 0; --n )
		ps_data->as_data[n].ps_value = NULL;

	for ( int n = 1; n < n_argc; ++n )
	{
		const char* pc_arg = *( ppc_argv + n );
		int n_arg_equals_index = -1;
		int n_arg_len = 0;
		char c;

		for ( int n_2 = 0; ( c = pc_arg[n_2] ) != '\0'; ++n_2 )
		{            
			++n_arg_len;

			if ( n_arg_equals_index == -1 && c == '=' )
				n_arg_equals_index = n_2;
		}

		if ( n_arg_len < 2 || pc_arg[0] != '-' )
			continue;

		const char* pc_key = NULL;
		int n_key_len = 0;

		const char* pc_value = NULL;
		int n_value_len = 0;

		if ( n_arg_len == 2 )
		{
			if ( pc_arg[1] != '-' )
			{
				pc_key = pc_arg + 1;
				n_key_len = 1;
			}
		}
		else if ( n_arg_len > 3 && pc_arg[1] == '-' )
		{
			if ( n_arg_equals_index == -1 )
				n_key_len = n_arg_len - 2;
			else
			{
				n_key_len = n_arg_equals_index - 2;
				n_value_len = n_arg_len - ( n_arg_equals_index + 1 );
				pc_value = pc_arg + n_arg_equals_index + 1;
			}

			if ( n_key_len < 2 )
				n_key_len = 0;
			else
				pc_key = pc_arg + 2;
		}

		if ( n_key_len > 0 )
		{
			STR_s_datum_t* ps_key = STR_f_new_raw( n_key_len, pc_key );
			FLA_s_datum_t* ps_datum = &( ps_data->as_data[ps_data->n_size++] );

			ps_datum->ps_key = ps_key;

			if ( n_value_len > 0 )
			{
				STR_s_datum_t* ps_value = STR_f_new_raw( n_value_len, pc_value );

				ps_datum->ps_value = ps_value;
			}

			if ( ps_data->n_size == FLA_gn_data_max )
				break;
		}
	}

	return ps_data;
}

void FLA_f_free( FLA_s_data_t* ps_data )
{
	for ( int n = ps_data->n_size - 1; n >= 0; --n )
	{
		STR_f_free( ps_data->as_data[n].ps_key );

		if ( ps_data->as_data[n].ps_value != NULL )
			STR_f_free( ps_data->as_data[n].ps_value );
	}

	MEM_f_free( ps_data );
}

static int f_find_index_by_key_raw( FLA_s_data_t* ps_data, int n_key_len, const char* pc_key )
{
	if ( ps_data == NULL || pc_key == NULL )
		return NULL;

	if ( n_key_len < 0 )
		for ( n_key_len = 0; pc_key[n_key_len] != '\0'; ++n_key_len )
		{}

	if ( n_key_len == 0 )
		return NULL;

	for ( int n_index = ps_data->n_size - 1; n_index >= 0; --n_index )
	{
		const FLA_s_datum_t* ps_datum = &( ps_data->as_data[n] );
		const STR_s_datum_t* ps_datum_key = ps_datum->ps_key;
		
		if ( ps_datum_key->n_length != n_key_len )
			continue;

		bool b_match = true;

		for ( int n_2 = 0; n_2 < n_key_len; ++n_2 )
		{
			if ( ps_datum_key->pc_value[n] != pc_key[n] )
			{
				b_match = false;
				break;
			}
		}

		if ( b_match )
			return n_index;
	}

	return -1;
}

const FLA_s_datum_t* FLA_f_find_by_key_raw( FLA_s_data_t* ps_data, int n_key_len, const char* pc_key )
{
	int n_index = f_find_index_by_key_raw( ps_data, n_key_len, pc_key );

	return (
		( n_index >= 0 )
			? &( ps_data->as_data[n_index] )
			: NULL
	);
}

bool FLA_f_contains_by_key_raw( FLA_s_data_t* ps_data, int n_key_len, const char* pc_key )
{
	int n_index = f_find_index_by_key_raw( ps_data, n_key_len, pc_key );

	return ( n_index >= 0 );
}