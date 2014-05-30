/*
 * @OSF_FREE_COPYRIGHT@
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
 * $Log: copyscan.c,v $
 * Revision 1.1.4.1  1993/10/05  20:01:14  damon
 * 	Handles whitespace and duplicate copyrights better
 * 	[1993/10/05  20:00:11  damon]
 *
 * Revision 1.1.2.6  1992/12/03  19:08:44  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:37:54  damon]
 * 
 * Revision 1.1.2.5  1992/07/22  14:13:07  damon
 * 	Fixed quoted comment problem
 * 	[1992/07/22  14:12:21  damon]
 * 
 * 	Fixed continguous c comment problem
 * 	[1992/07/20  23:00:34  damon]
 * 
 * Revision 1.1.2.4  1992/07/20  18:37:55  damon
 * 	Changed to work with list of files/comment leaders
 * 	[1992/07/20  18:37:32  damon]
 * 
 * Revision 1.1.2.3  1992/04/14  22:49:52  damon
 * 	Added call to free()
 * 	[1992/04/14  22:46:21  damon]
 * 
 * Revision 1.1.2.2  1992/04/13  15:45:49  damon
 * 	Initial Version
 * 	[1992/04/13  15:45:03  damon]
 * 
 * $EndLog$
 */
#  include <ode/odedefs.h>
#  include <stdio.h>
#  include <string.h>

#define MAX_LEN 100000
#define MAXPATHLEN 1000
/*
 * in_comment means that we are in a comment section. This is
 * easy for a comment convention that doesn't have a begin and end
 * comment convention. It means we haven't hit a line that isn't a comment.
 * In cases where there is a begin/end comment it means that we haven't
 * hit a line that isn't the beginning, the end, or part of a comment.
 *
 * in_se_comment means that we haven't hit the 'end of comment' indicator
 * of a comment yet. You may hit 'end of comment' and then on the next
 * line start up a new comment. You are still in a comment section.
 */
int in_comment = FALSE;
int in_se_comment = FALSE;
int buf_empty = TRUE;
char buf [MAX_LEN];
int num_copyrights = 0;
char copyrights [500][2000];
int copy_len [500];

int num_candidates = 0;
char candidates [200][100];

char file_name [ MAXPATHLEN ];

BOOLEAN emitted_string = FALSE;

main (argc, argv)
int argc;
char * argv [ ];
{
  char s [MAX_LEN];
  char * sptr;
  FILE * in;
  FILE * copy_f;
  FILE * cand_f;
  FILE * files_f;
  int len;
  char comment [ 10 ];

  char * res;
  if ( argc < 4 ) {
    printf ( "usage: copyscan seed-list candidate-list file-list\n" );
    exit ( 1 );
  } /* if */ 

  buf [0] = '\0';

  copy_f = fopen ( argv[ 1 ], "r" );
  while ( ( res = ( fgets ( s, MAX_LEN, copy_f ) ) != NULL ) ) {
    rm_newline ( s );
    normalize ( s );
    strcpy ( copyrights [ num_copyrights ], s );
    copy_len [ num_copyrights ] = strlen ( s );
    num_copyrights ++;
  } /* while */
  fclose ( copy_f );
  
  cand_f = fopen ( argv[ 2 ], "r" );
  while ( ( res = ( fgets ( s, MAX_LEN, cand_f ) ) != NULL ) ) {
    rm_newline ( s );
    strcpy ( candidates [ num_candidates ], s );
    num_candidates++;
  } /* while */
  fclose ( cand_f );

  files_f = fopen ( argv [ 3 ], "r" );
  while ( ( res = ( fgets ( s, MAXPATHLEN, files_f ) ) != NULL ) ) {
    emitted_string = FALSE;
    in_comment = FALSE;
    in_se_comment = FALSE;
    rm_newline ( s );
/*
 * Parse the line into file name and comment leader. They are
 * separated by a tab character.
 */
    sptr = s;
    while ( TRUE ) {
      if ( *sptr == '\0' ) {
         printf ( "Missing tab in file list.\n" );
         exit ( 1 );
      } /* if */
      if ( *sptr == '\t' )
        break;
      /* if */
      sptr++;
    } /* while */
    *sptr = '\0';
    sptr++;
    strcpy ( file_name, s );
    strcpy ( comment, sptr );

    len = strlen ( comment );
    in = fopen ( file_name, "r" );
    if ( in == NULL ) {
      fputs ( file_name, stdout);
      fputs ( "\tERROR\t", stdout);
      fputs ( "Missing file\n", stdout );
      continue;
    } /* if */
    if ( strcmp ( " * ", comment ) == 0 ) {
      while ( ( res = ( fgets ( s, MAX_LEN, in ) ) != NULL ) ) {
        cmt ( s );
      } /* while */
      if ( in_comment ) {
        emit ( buf );
        buf [0] = '\0';
        buf_empty = TRUE;
      } /* if */
    } else if ( strcmp ( "NONE", comment ) == 0 ) {
      fputs ( file_name, stdout);
      fputs ( "\tNONE\n", stdout);
    } else {
      while ( ( res = ( fgets ( s, MAX_LEN, in )) != NULL ) ) {
        cmt2 ( s, comment, len );
      } /* while */
      if ( in_comment ) {
        emit ( buf );
        buf [0] = '\0';
        buf_empty = TRUE;
      } /* if */
    } /* if */
    fclose ( in );
    if ( ! emitted_string ) {
      fputs ( file_name, stdout);
      fputs ( "\tNOTHING\n", stdout);
    } /* if */
  } /* while */
  fclose ( files_f );
  exit ( 0 );
}  

cmt2 ( str, comment, len )
char * str;
char * comment;
int len;
{
  char buf2 [MAX_LEN];
  char * p;

  if ( ( p = strstr ( str, comment ) ) != NULL ) {
    p = p + len;
    in_comment = TRUE;
    rm_newline ( str );
    concat ( buf2, MAX_LEN, buf, " ", p, NULL );
    strcpy ( buf, buf2 );
  } else {
    if ( in_comment ) {
      emit ( buf );
      buf [0] = '\0';
      buf_empty = TRUE;
    } /* if */
    in_comment = FALSE;
  } /* if */
} /* end cmt2 */

cmt ( str )
char * str;
{
  char buf2 [MAX_LEN];
  char * p;

  if ( (p = strstr ( str, "/*" ))  != NULL
       && strstr ( str, "\"/*\"") == NULL ) {
    in_comment = TRUE;
    in_se_comment = TRUE;
  } else
    p = str;
  /* if */
  rm_newline ( p );
  if ( in_se_comment ) {
    concat ( buf2, MAX_LEN, buf, " ", p, NULL );
    strcpy ( buf, buf2 );
    if ( strstr ( p, "*/" )  != NULL && strstr ( p, "\"*/\"") == NULL ) {
      in_se_comment = FALSE;
    } /* if */
  } else {
    if ( in_comment ) {
      emit ( buf );
      buf [0] = '\0';
      buf_empty = TRUE;
    } /* if */
    in_comment = FALSE;
  } /* if */
}

emit ( str )
char * str;
{
  BOOLEAN further_reducible;

  char * orig;
  char * str2;

  str2 = strdup ( str );
  orig = strdup ( str );
  normalize ( str2 );
  reduce ( &str2, &further_reducible );
  if ( further_reducible ) {
    emitted_string = TRUE;
    fputs ( file_name, stdout );
    fputs ( "\tORIGINAL\t", stdout );
    fputs ( orig, stdout );
    fputs ( "\n", stdout );
    fputs ( file_name, stdout );
    fputs ( "\tREMAINDER\t", stdout );
    fputs ( str2, stdout );
    fputs ( "\n", stdout );
  }  /* if */
  free ( str2 );
  free ( orig );
} /* end emit */

reduce ( str, further_reducible )
char ** str;
BOOLEAN * further_reducible;
{
  char buf [ MAX_LEN ];
  char * b;
  int len;
  int i;
  char * p;

  for ( i = 0; i < num_copyrights; i++ ) {
    for (;;) {
      p = strstr ( *str, copyrights [ i ] );
      if ( p != NULL) {
        strcpy ( p, p + copy_len [i ] );
        emitted_string = TRUE;
        fputs ( file_name, stdout );
        fputs ( "\tFOUND\t", stdout );
        fputs ( copyrights [ i ], stdout );
        fputs ( "\n", stdout );
      } else {
        break;
      } /* if */
    } /* for */
  } /* for */
  *further_reducible = copyrighted ( *str );
} /* end reduce */

BOOLEAN copyrighted ( str )
char * str;
{
  int i;

  for ( i = 0; i < num_candidates; i++ ) {
    if ( strstr ( str, candidates [ i ] ) != NULL ) {
      return ( TRUE );
    } /* if */
  } /* for */
  return ( FALSE );
} /* end copyrighted */

normalize ( text )
char * text;
{
  int i;
  int n;
  char c;
  BOOLEAN in_junk;
  int first_junk;

  n = 0;
  first_junk=0;
  in_junk = strchr ( "* \t/#", *text ) != NULL;

  for ( i = 0; i < strlen(text); i++ ) {
    c = *(text+i);
    if ( strchr ( "* \t/#", c ) != NULL ) {
      if ( !in_junk ) {
        in_junk = TRUE;
        *(text+n) = ' ';
        first_junk = n;
        n++;
      } /* if */
    } else {
      in_junk = FALSE;
      *(text+n) = c;
      n++;
    } /* if */
  } /* for */
  if ( strchr ( "* \t/#", c ) != NULL ) {
    n = first_junk;
  } /* if */
  *(text+n) = '\0';
} /* end normalize */
