
#include "option.h"

#include "memory.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

OPT_s_datum_t* OPT_f_new( FLA_s_data_t* ps_flag_data )
{
	OPT_s_datum_t* ps_datum = MEM_f_alloc( sizeof( *ps_datum ) );

	const FLA_s_datum_t* ps_flag_datum_args = FLA_f_find_by_key_raw( ps_flag_data, -1, "args" );
	const FLA_s_datum_t* ps_flag_datum_command = FLA_f_find_by_key_raw( ps_flag_data, -1, "command" );

	const bool b_args = ( ps_flag_datum_args != NULL && ps_flag_datum_args->ps_value != NULL );
	STR_s_datum_t* ps_args = ( ( b_args ) ? STR_f_new_clone( ps_flag_datum_args->ps_value ) : NULL );
	const bool b_command = ( ps_flag_datum_command != NULL && ps_flag_datum_command->ps_value != NULL );
	STR_s_datum_t* ps_command = ( ( b_command ) ? STR_f_new_clone( ps_flag_datum_command->ps_value ) : NULL );
	STR_s_datum_t* ps_command_with_args = ( ( b_command ) ? STR_f_new_with_capacity( 128 + ps_command->n_length + ( ( b_args ) ? ps_args->n_length + 1 : 0 ) + 1 ) : NULL );
	const bool b_daemon = ( FLA_f_contains_by_key_raw( ps_flag_data, 1, "d" ) || FLA_f_contains_by_key_raw( ps_flag_data, -1, "daemon" ) );

	if ( b_command )
	{
		STR_f_append( ps_command_with_args, ps_command );

		if ( b_args )
		{
			STR_f_append_char_raw( ps_command_with_args, ' ' );
			STR_f_append( ps_command_with_args, ps_args );
		}

		if ( b_daemon )
			STR_f_append_raw( ps_command_with_args, -1, " > /dev/null" );
	}

	ps_datum->ps_args = ps_args;
	ps_datum->ps_command = ps_command;
	ps_datum->ps_command_with_args = ps_command_with_args;
	ps_datum->b_daemon = b_daemon;

	return ps_datum;
}

void OPT_f_free( OPT_s_datum_t* ps_datum )
{
	MEM_f_free( ps_datum->ps_args );
	MEM_f_free( ps_datum->ps_command );
	MEM_f_free( ps_datum->ps_command_with_args );

	MEM_f_free( ps_datum );
}

static void f_handle_daemon()
{
	int n_pid = fork();

	printf( "PID: %d\n", n_pid );

	if ( n_pid < 0 )
		exit( EXIT_FAILURE );

	if ( n_pid > 0 )
		exit( EXIT_SUCCESS );

	n_pid = setsid();

	if ( n_pid < 0 )
		exit( EXIT_FAILURE );

	freopen( "/dev/null", "a", stdout );
}

static void f_handle_command( const OPT_s_datum_t* ps_option_datum )
{
	if (ps_option_datum->ps_args != NULL)
	printf( "ARGS: %s\n", ps_option_datum->ps_args->pc_value);

	if ( ps_option_datum->ps_command != NULL )
		for ( ;; )
			system( ps_option_datum->ps_command_with_args->pc_value );
}

void OPT_f_handle( const OPT_s_datum_t* ps_option_datum )
{
	if ( ps_option_datum->b_daemon )
		f_handle_daemon();

	if ( ps_option_datum->ps_command != NULL )
		f_handle_command( ps_option_datum );

	printf( "END\n" );
}