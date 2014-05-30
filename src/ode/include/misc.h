/*
 * COPYRIGHT NOTICE 
 */
/*
 * HISTORY
 * $Log: misc.h,v $
 * Revision 1.1.4.1  1993/12/09  16:18:51  marty
 * 	CR # 840 - Wrapper around misc.h
 * 	[1993/12/09  16:18:38  marty]
 *
 * Revision 1.1.2.3  1993/04/27  15:23:56  damon
 * 	CR 463. First round of -pedantic changes
 * 	[1993/04/27  15:19:23  damon]
 * 
 * Revision 1.1.2.2  1993/04/26  21:59:22  damon
 * 	CR 446. New declarations for misc.c
 * 	[1993/04/26  21:59:12  damon]
 * 
 * 	CR 446. New declarations for misc.c
 * 
 * $EndLog$
 */

#ifndef _MISC_H
#define _MISC_H
#include <stdarg.h>
#include <ode/odedefs.h>

char * alloc_switch ( char, const char *);
void enter ( const char * );
void leave ( void );
void report_current_function ( void );
void atomic_init ( void );
void begin_atomic ( void );
void end_atomic ( void );
int exists ( const char * );
BOOLEAN isdir ( const char * );
void get_date ( char *, char * );
int insert_line_in_sorted_file ( char *, char *, int (*cmp_func)(char *, ...),
                                 int );
int canonicalize ( const char *, const char *, char *, int );
BOOLEAN str_to_BOOLEAN ( const char * );
#endif
