#ifndef __OPTION_H__
#define __OPTION_H__

	#include "flag.h"
	#include "string.h"

	typedef struct {
		STR_s_datum_t* ps_args;
		STR_s_datum_t* ps_command;
		STR_s_datum_t* ps_command_with_args;
		bool b_daemon;
	} OPT_s_datum_t;

	OPT_s_datum_t* OPT_f_new( FLA_s_data_t* );
	void           OPT_f_free( OPT_s_datum_t* );

	void OPT_f_handle( const OPT_s_datum_t* );

#endif