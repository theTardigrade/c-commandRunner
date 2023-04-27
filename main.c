
#include "flag.h"
#include "option.h"

#include <stdlib.h>

int main( int n_argc, const char** ppc_argv )
{
	FLA_s_data_t* ps_flag_data = FLA_f_new( n_argc, ppc_argv );
	OPT_s_datum_t* ps_option_datum = OPT_f_new( ps_flag_data );

	OPT_f_handle( ps_option_datum );

	OPT_f_free( ps_option_datum );
	FLA_f_free( ps_flag_data );

	return EXIT_SUCCESS;
}