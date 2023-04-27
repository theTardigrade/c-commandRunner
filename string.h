#ifndef __STRING_H__
#define __STRING_H__

    #include <stdbool.h>

    typedef struct {
        char* pc_value;
        int   n_length;
        int   n_capacity;
        bool  b_allocated;
    } STR_s_datum_t;

    STR_s_datum_t* STR_f_new( void );
    STR_s_datum_t* STR_f_new_with_capacity( int );
    STR_s_datum_t* STR_f_new_raw( int, const char* );
    STR_s_datum_t* STR_f_new_clone( const STR_s_datum_t* );
    void           STR_f_free( STR_s_datum_t* );

    void STR_f_increase_capacity( STR_s_datum_t*, int );
    void STR_f_append( STR_s_datum_t*, const STR_s_datum_t* );
    void STR_f_append_raw( STR_s_datum_t*, int, const char* );
    void STR_f_append_char_raw( STR_s_datum_t*, char );

#endif