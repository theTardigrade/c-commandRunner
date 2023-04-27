#ifndef __FLAG_H__
#define __FLAG_H__

	#include "string.h"

	#define FLA_gn_data_max ( 2048 )

	typedef struct {
		STR_s_datum_t* ps_key;
		STR_s_datum_t* ps_value;
	} FLA_s_datum_t;

	typedef struct {
		FLA_s_datum_t as_data[FLA_gn_data_max];
		int n_size;
	} FLA_s_data_t;

	FLA_s_data_t* FLA_f_new( int, const char** );
	void          FLA_f_free( FLA_s_data_t* );

	const FLA_s_datum_t* FLA_f_find_by_key_raw( FLA_s_data_t*, int, const char* );
	bool                 FLA_f_contains_by_key_raw( FLA_s_data_t*, int, const char* );

#endif