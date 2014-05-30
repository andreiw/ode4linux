/*
 * COPYRIGHT NOTICE
 * Copyright (c) 1992, 1991, 1990  
 * Open Software Foundation, Inc. 
 *  
 * Permission is hereby granted to use, copy, modify and freely distribute 
 * the software in this file and its documentation for any purpose without 
 * fee, provided that the above copyright notice appears in all copies and 
 * that both the copyright notice and this permission notice appear in 
 * supporting documentation.  Further, provided that the name of Open 
 * Software Foundation, Inc. ("OSF") not be used in advertising or 
 * publicity pertaining to distribution of the software without prior 
 * written permission from OSF.  OSF makes no representations about the 
 * suitability of this software for any purpose.  It is provided "as is" 
 * without express or implied warranty. 
 */
/*
 * HISTORY
 * $Log: datestrip.c,v $
 * Revision 1.1.2.1  1993/12/14  16:29:24  damon
 * 	CR 857. Creating new test suite
 * 	[1993/12/14  16:29:04  damon]
 *
 * $EndLog$
 */

#include <ode/odedefs.h>
#include <ode/util.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>

BOOLEAN history_rev_line ( char * buf, char ** pos )
{
  char * bptr;
  char buf2 [MAXPATHLEN];
  char * token;

  if ( ( *pos = strstr ( buf, "Revision" ) ) == NULL ) {
    return ( FALSE );
  } /* if */
  strcpy ( buf2, buf );
  bptr = buf2;
  token = nxtarg ( &bptr, WHITESPACE );
  token = nxtarg ( &bptr, WHITESPACE );
  return ( strcmp ( token, "Revision" ) == 0 );
} /* end history_rev_line */

BOOLEAN history_stamp_line ( char * buf, char ** pos, BOOLEAN * has_leader )
{
  char * bptr;
  char buf2 [MAXPATHLEN];
  char * token;

  if ( ( *pos = strchr ( buf, '[' ) ) == NULL ) {
    return ( FALSE );
  } /* if */
  strcpy ( buf2, buf );
  bptr = buf2;
  token = nxtarg ( &bptr, WHITESPACE );
  *has_leader = FALSE;
  if ( *token != '[' ) {
    token = nxtarg ( &bptr, WHITESPACE );
    if ( *token != '[' ) {
      return ( FALSE );
    } /* if */
    *has_leader = TRUE;
  } /* if */
  token = nxtarg ( &bptr, WHITESPACE );
  token = nxtarg ( &bptr, WHITESPACE );
  if ( token == NULL || *token == '\0' ) {
     return ( FALSE );
  } /* if */
  return ( *(token+strlen(token)-1) == ']' );
} /* end history_stamp_line */

void
main(int argc, char ** argv)
{
  char buf [MAXPATHLEN];
  char * bptr;
  char * token;
  char * pos;
  char * revision;
  char leader[30];
  FILE * in;
  BOOLEAN has_leader;

  in = fopen ( *(argv+1), "r" );
  if ( in == NULL ) {
    fprintf ( stderr, "Unable to open file '%s'\n", *(argv+1) );
  } /* if */
  while ( fgets ( buf, sizeof(buf), in ) != NULL ) {
    if ( strncmp ( "date\t", buf, 5 ) == 0 ) {
      bptr = buf;
      token = nxtarg ( &bptr, WHITESPACE );
      token = nxtarg ( &bptr, WHITESPACE );
      printf (  "date\t DATE %s", bptr );
    } else if ( strncmp ( "  Date: ", buf, 8 ) == 0 ) {
      bptr = buf;
      printf (  " Date: DATE; Time: TIME" );
    } else if ( history_rev_line ( buf, &pos ) ) {
      strncpy ( leader, buf, pos-buf );
      bptr = buf;
      token = nxtarg ( &bptr, WHITESPACE );
      token = nxtarg ( &bptr, WHITESPACE );
      revision = nxtarg ( &bptr, WHITESPACE );
      token = nxtarg ( &bptr, WHITESPACE );
      token = nxtarg ( &bptr, WHITESPACE );
      printf ( "%sRevision %s DATE TIME %s", leader, revision, bptr );
    } else if ( history_stamp_line ( buf, &pos, &has_leader ) ) {
      strncpy ( leader, buf, pos-buf );
      bptr = buf;
      if ( has_leader ) {
        token = nxtarg ( &bptr, WHITESPACE );
      } /* if */
      token = nxtarg ( &bptr, WHITESPACE );
      token = nxtarg ( &bptr, WHITESPACE );
      printf ( "%s[DATE  TIME  %s", leader, bptr );
    } else if ( strncmp ( "Locked on: ", buf, 11 ) == 0 ) {
      printf ( "Locked on: DATE\n" );
    } else if ( ( pos = strstr ( buf, ".Tlog" ) ) != NULL ) {
      if ( *(pos-5) == '/' ) {
        strcpy ( pos-4, "HH:MM" );
      } else {
        strcpy ( pos-5, "HH:MM" );
      } /* if */
      printf ( "%s", buf );
    } else {
      printf ( "%s", buf );
    } /* if */
  } /* while */
  fclose ( in );
} /* end main */
