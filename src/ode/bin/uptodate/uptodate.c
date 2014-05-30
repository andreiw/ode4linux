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
 * $Log: uptodate.c,v $
 * Revision 1.8.10.1  1993/12/09  19:10:02  marty
 * 	CR # 840 - Removed duplicate routine isdir().  It's already in libode.a.
 * 	[1993/12/09  19:09:46  marty]
 *
 * Revision 1.8.8.1  1993/10/28  13:32:38  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:36  damon]
 * 
 * Revision 1.8.6.4  1993/05/28  17:42:47  marty
 * 	CR # 558 - Get it to build on rios_aix
 * 	[1993/05/28  17:42:35  marty]
 * 
 * Revision 1.8.6.3  1993/04/29  17:18:28  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  17:18:14  marty]
 * 
 * Revision 1.8.6.2  1993/04/15  18:33:09  marty
 * 	Add include file stdio.h and ode/interface.h
 * 	[1993/04/15  18:32:47  marty]
 * 
 * Revision 1.8.4.7  1992/12/03  19:08:28  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:37:39  damon]
 * 
 * Revision 1.8.4.6  1992/10/14  20:48:10  damon
 * 	CR 288. Updated call to ui_init
 * 	[1992/10/14  20:45:27  damon]
 * 
 * Revision 1.8.4.5  1992/09/24  19:00:46  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:19:50  gm]
 * 
 * Revision 1.8.4.4  1992/07/26  17:30:17  gm
 * 	Fixed to remove warnings when compiling under OSF/1 R1.1.
 * 	[1992/07/17  20:55:44  gm]
 * 
 * Revision 1.8.4.3  1992/06/16  22:12:13  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:02:16  damon]
 * 
 * Revision 1.8.2.2  1992/03/25  22:47:25  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  22:27:11  damon]
 * 
 * Revision 1.8  1991/12/05  20:54:54  devrcs
 * 	Update to tools II changes and user interface
 * 	[91/01/14  12:38:32  randyb]
 * 
 * 	Minor changes to correspond with changes in std_defs.h
 * 	[90/11/13  17:11:32  randyb]
 * 
 * 	uptodate checks location of latest using rc files
 * 	[90/11/12  09:33:27  randyb]
 * 
 * 	Fixed various compiler warnings.
 * 	[90/11/09  10:22:45  dwm]
 * 
 * 	Style updates; saber c lint
 * 	[90/11/08  08:02:20  randyb]
 * 
 * Revision 1.6  90/10/07  21:52:57  devrcs
 * 	Pre OSF/1 changes.
 * 
 * $EndLog$
 */
/******************************************************************************
**                          Open Software Foundation                         **
**                              Cambridge, MA                                **
**                               April 1990                                  **
*******************************************************************************
**
**  Description:
**	This program updates the links of files in a sandbox compared to
**	the changes in the backing tree.
**
**  Functions:
 */

static char * rcsid =
 "$RCSfile: uptodate.c,v $ $Revision: 1.8.10.1 $ $Date: 1993/12/09 19:10:02 $";

#  include <ode/odedefs.h>
#  include <ode/interface.h>
#  include <stdio.h>
#  include <sys/param.h>
#  include <sys/stat.h>
#  include <ode/parse_rc_file.h>
#  include <errno.h>
#  include <fcntl.h>
#  include <unistd.h>

#  define MAX_ARGS	7
#  define CMP_TO_OP	"-cmp_to"
#  define COPY_FROM_OP	"-copy_from"
#  define NORECURSE_OP	"-norecurse"
#  define OVERWRITE_OP	"-overwrite"
#  define QUERY_OP	"-query"
#  define SNAPDIR	"logs/SNAPSHOT"
#  define UPLOG		"logs/uptodate"


    UIINIT init [] = {                      /* initialize the user interface */
   	{ QUERY_OP, 	1, OVERWRITE, 0, 0, "" },
   	{ OVERWRITE_OP, 1, OVERWRITE, 0, 0, "" },
   	{ NORECURSE_OP, 1, OVERWRITE, 0, 0, "" },
   	{ SB_OP, 	1, OVERWRITE, 1, 1, ARGS_OP },
   	{ CMP_TO_OP, 	1, OVERWRITE, 1, 1, "/*" },
   	{ COPY_FROM_OP, 1, OVERWRITE, 1, 1, "/*" },
   	{ ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" } 
    };

    typedef struct filerev {
      char    * file,                                        /* name of file */
              * rev;                                             /* file rev */
      BOOLEAN   ok,                                  /* status of file's use */
                new;                           /* is file new from last time */
      struct    filerev * nextfr;                    /* create list of these */
    } FILEREV;
 
    char      * itoa (); 
    char      *	progname = "uptodate";


main ( argc, argv ) 

	/* This function checks the command line arguments and makes
           sure they are syntactically correct.  This is done using
           the library function parse_cmd_line.  If this is correct,
           the dependencies are checked.  Errors lead to usage messages.
           If all is okay, the primary procedue is called. */

    int 	  argc;  /* the number of command line arugments */
    char       ** argv;  /* strings with each argument */

{
    FILEREV     * head = NULL;                  /* head of list of file/revs */
    char       ** dirlist,  /* list of directories to use */
                * back,                   /* path to backing tree */
                * latest,                /* path to latest's tree */
                * sandsrc,            /* src directory of sandbox */
                * sbbase;                /* sandbox base and name */
    int		  dirct;  /* to hold number of dirs */

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );
  cmdline_syntax ( &dirlist, &back, &latest, &sandsrc, &sbbase, &dirct );
  list_new_files ( &head, dirlist, back, latest, dirct );
  match_dirs ( dirlist, head, dirct );
  remove_config ( head, sandsrc );
  remove_update ( head, sbbase );

  if ( copy_new_files ( head, latest, sandsrc ))
    update_update ( head, sbbase );

  return ( OK );
}  /* main */



cmdline_syntax ( dirlist, back, latest, sandsrc, sbbase, dirct )

	/* This procedure checks for relationships between the
           command line arguments.  It assumes the syntax is
           already correct.  Most of the functions it calls
           will use uquit to exit if there is an error. */

    char      *** dirlist,  /* list of directories to use */
               ** back,                             /* path to backing tree */
               ** latest,                          /* path to latest's tree */
               ** sandsrc,                      /* src directory of sandbox */
               ** sbbase;                          /* sandbox base and name */
    int		* dirct;  /* number of user directories */

{    
    char      	* sandbox,             /* name of current sandbox */
              	* sbbasedir,          /* current sandbox base dir */
              	* sb_rcfile,        /* current sandbox local file */
              	* usr_rcfile,             /* current user rc file */
		  tmp [ PATH_LEN ],  /* misc string */
	      	* builddir,  		        /* project's build directory */
	      	* build;  		    /* project's build default build */

  sandbox = ui_arg_value ( SB_OP, 1, 1 );
  sbbasedir = NULL;
  sb_rcfile = NULL;
  usr_rcfile = ui_arg_value ( RC_OP, 1, 1 );

  if ( current_sb ( &sandbox, &sbbasedir, &sb_rcfile, &usr_rcfile ) != OK )
    uquit ( ERROR, FALSE, "could not obtain sandbox info.\n" );

  get_src_dir ( sb_rcfile, sandsrc );
  concat ( tmp, PATH_LEN, sbbasedir, "/", sandbox, NULL );
  *sbbase = (char *)strdup ( tmp );

  if (( *back = ui_arg_value ( CMP_TO_OP, 1, 1 )) == NULL ) {
    concat ( tmp, PATH_LEN, *sbbase, "/", LINK_DIR, NULL ); 
    *back = (char *)strdup ( tmp );
  } /* if */

  if (( *latest = ui_arg_value ( COPY_FROM_OP, 1, 1 )) == NULL ) {
    if ( default_build ( &builddir, &build, NULL, sb_rcfile ) == ERROR )
      uquit ( ERROR, FALSE,
		     "no default backing directory; use absolute path.\n" );

    concat ( tmp, PATH_LEN, builddir, "/", build, NULL);
    *latest = (char *)strdup ( tmp );
  } /* if */

  legal_backing ( *back );
  legal_backing ( *latest );

  if ( ! ui_is_set ( ARGS_OP ))
    uquit ( ERROR, TRUE, "No directory(ies) give to update.\n" );

  legal_dirs ( dirlist, *sandsrc, dirct );
  make_logs ( *sbbase );

  if ( ui_ver_level () == VDEBUG )
    print_values ( *back, *latest, *sbbase, *sandsrc, sb_rcfile, usr_rcfile );
}                                            /*  cmdline syntax */



get_src_dir ( sb_rcfile, sandsrc )

	/* This procedure determines the source directory for the user. */

    char      	* sb_rcfile,                 /* file with source information */
               ** sandsrc;                     /* src directory of sandbox */

{
    struct      rcfile  rc_contents;        /* to hold contents of sb rcfile */

  memset ( (char *)&rc_contents, 0, sizeof ( rc_contents ));

  if ( parse_rc_file ( sb_rcfile, &rc_contents ))
    uquit ( ERROR, FALSE, "unable to parse sandbox rcfile %s.\n", sb_rcfile );

  if ( get_rc_value ( SOURCE_BASE, sandsrc, &rc_contents, TRUE ) == ERROR )
    uquit ( ERROR, FALSE, "%s line missing in rc file %s.\n",
	                   SOURCE_BASE, sb_rcfile );

  if ( **sandsrc != SLASH )
    uquit ( ERROR, FALSE, "value of %s field does not begin with a %c.\n",
			   SOURCE_BASE, SLASH );

  if (( isdir ( *sandsrc ) == ERROR ))
    uquit ( ERROR, FALSE, "no source directory, %s, in sandbox.\n", sandsrc );
}                                                             /* get src dir */




legal_backing ( directory )

	/* This procedure makes sure there is a file to use as
	   as a snapshot file. */

    char      * directory;                    /* holds path to snapshot file */
	
{
  if ( isdir ( directory ) != OK )
    uquit ( ERROR, FALSE, "\tno backing tree at: %s.\n", directory );
}                                                      /* legal backing tree */



legal_dirs ( dirlist, srcbase, dirct )

	/* This procedure checks to see if the dirs are absolute.
	   If they are not, it checks to see if the user is in the
	   sandbox.  If he is, then the current directory is added
	   to the names of the dirs. */

    char      *** dirlist,  /* list of directories to use */
		* srcbase;                     /* src directory of sandbox */
    int		* dirct;  /* number of user directories */

{
    char          curdir [ PATH_LEN ],                        /* misc string */
                  tmpfile [ PATH_LEN ],                       /* misc string */
	       ** travel,  /* track each directory */
              	* belowsrc;                       /* pts to dir below source */
    int		  ct;  /* misc integer */
    BOOLEAN       first = TRUE;                              /* misc boolean */

  if (( *dirct = ui_entries_to_argv ( ARGS_OP, dirlist )) <= 0 )
    uquit ( ERROR, FALSE, "\tno directories given.\n" );
   
  for ( ct = 0; ct < *dirct; ct++ ) {
    travel = (*dirlist) + ct;

    if ( **travel != SLASH ) {
      if ( first ) {
	first = FALSE;

	if ( getcwd ( curdir, sizeof(curdir) ) == NULL )
	  uquit ( ERROR, FALSE, "\tgetcwd: %s.\n", strerror(errno) );

	if ( strncmp( srcbase, curdir, strlen ( srcbase )) != OK )
          uquit ( ERROR, FALSE, "current directory, not in source base: %s.\n",
				 curdir, srcbase );
	
	belowsrc = curdir + strlen ( srcbase );

	if ( *belowsrc != SLASH ) {
	  if ( *belowsrc != NUL )
	    uquit ( ERROR, FALSE, "current directory not in source base: %s.\n",
				   srcbase );
          else
	    belowsrc = "";  /* exactly at src base */
	} /* if */
      } /* if */

      concat ( tmpfile, PATH_LEN, ".", belowsrc, "/", *travel, NULL );
    } /* if */

    else
      concat ( tmpfile, PATH_LEN, ".", *travel, NULL );

    *travel = (char *)strdup ( tmpfile );
    canonicalize_file ( *travel );
    ui_print ( VDEBUG, "dir: %s.\n", *travel );
  } /* for */
}                                                              /* legal dirs */



canonicalize_file ( outbuf )

	/* This procedure checks a line to make sure it does not
           not have any "./." or "/../" in it. */

    char      * outbuf;                                            /* result */

{
    char      * from,                         /* pointer for looking at line */
              * to,                           /* pointer for looking at line */
              * slash,                        /* pointer for looking at line */
              * peek;                         /* pointer for looking at line */

  slash = outbuf + 1;
  from = to = slash + 1;

  while ( *from != NUL ) {              /* extract problems from each string */
    if (( *to++ = *from++ ) != SLASH )
      continue;

    peek = to - 2;

    if (*peek == SLASH ) {                        /* found "//", back up one */
      to--;
      continue;
    } /* if */

    if ( *peek != PERIOD )
      continue;

    peek--;

    if ( *peek == SLASH ) {                      /* found "/./", back up two */
      to -= 2;
      continue;
    } /* if */

    if ( *peek != PERIOD )
      continue;

    peek--;

    if ( *peek != SLASH )
      continue;
			       /* found "/../", try to remove preceding token */
    if ( peek == slash ) {
       to = slash + 1;
       continue;             /* "first" slash, do not remove any more tokens */
    } /* if */

    while ( *--peek != SLASH )                           /* backup one token */
      ;

    to = peek + 1;
  } /* while */

  *to-- = NUL;

  if ( *to == PERIOD ) {                               /* trailing /. or /.. */
    peek = to - 1;

    if ( *peek == SLASH ) {                             /* found trailing /. */
      to = peek + 1;
      *to-- = NUL;
    } /* if */

    else if ( *peek-- == PERIOD ) {
      if ( *peek == SLASH ) {                          /* found trailing /.. */
        if ( peek != slash ) {
          while ( *--peek != SLASH )                     /* backup one token */
            ;
	} /* if */

        to = peek + 1;
	*to-- = NUL;
      } /* if */
    } /* else if */
  } /* if */

  if ( to > outbuf && *to == SLASH )
    *to = NUL;
}                                                       /* canonicalize file */



make_logs ( sbbase )

	/* This procedure creates the logs directory if it is not
	   already in place. */

    char        * sbbase;                         /* sandbox base directory */

{
    char          curpath [ PATH_LEN ];                       /* misc string */

  concat ( curpath, PATH_LEN, sbbase, "/logs", NULL );

  if ( access ( curpath, F_OK ) != OK ) {
    ui_print ( VDETAIL, "mkdir: %s.\n", curpath );

    if ( mkdir ( curpath, 0777 )) 
      uquit ( ERROR, FALSE, "\tCan't create directory: %s.\n", curpath );
  } /* if */
}                                                               /* make logs */



print_values ( back, latest, sbbase, src, sb_rcfile, usr_rcfile )

	/* This procedure prints out the fields it will use. */

    char        * back,                         /* path to backing SNAPSHOT */
                * latest,                      /* path to latest's SNAPSHOT */
                * sbbase,                        /* name and dir of sandbox */
                * src,                          /* src directory of sandbox */
                * sb_rcfile,                  /* current sandbox local file */
                * usr_rcfile;                       /* current user rc file */


{
  ui_print ( VDEBUG, "comparing from: %s.\n", back );
  ui_print ( VCONT, "copying from: %s.\n", latest );
  ui_print ( VCONT, "sandbox: %s.\n", sbbase );
  ui_print ( VCONT, "source dir: %s.\n", src );
  ui_print ( VCONT, "sb rc file: %s.\n", sb_rcfile );
  ui_print ( VCONT, "usr rc file: %s.\n", usr_rcfile );
}                                                            /* print values */



list_new_files ( head, dirlist, back, latest, dirct )

	/* This procedure reads in the snapshot files, comparing
	   them, and making a list of those which have been changed. */

    FILEREV    ** head;                         /* head of list of file/revs */
    char       ** dirlist,  /* list of directories to use */
                * back,                           /* path to backing tree */
                * latest;                        /* path to latest's tree */
    int		  dirct;  /* to hold number of dirs */

{
    FILE        * bss,                            /* pts to backing snapshot */
                * lss;                             /* pts to latest snapshot */
    FILEREV     * current = NULL;                 /* pts to current file/rev */
    char          backss [ PATH_LEN ],           /* path to backing SNAPSHOT */
                  bfile [ NAME_LEN ],            /* file from build SNAPSHOT */
                  brev [ NAME_LEN ],              /* rev from build SNAPSHOT */
                * bmore,              /* results from getting build SNAPSHOT */
                  latestss [ PATH_LEN ],          /* path to latest SNAPSHOT */
                  lfile [ NAME_LEN ],           /* file from latest SNAPSHOT */
                  lrev [ NAME_LEN ],             /* rev from latest SNAPSHOT */
                * lmore;             /* results from getting latest SNAPSHOT */
    int           cmp,                                       /* misc integer */
                  ctc = 0,                         /* count of changed files */
                  ctn = 0,                      /* count of new latest files */
                  ctl = 0;                       /* count of lost back files */

  concat ( backss, PATH_LEN, back, "/", SNAPDIR, NULL );
  concat ( latestss, PATH_LEN, latest, "/", SNAPDIR, NULL );
  ui_print ( VDETAIL, "Comparing file: %s\n\t       to: %s.\n",
		       backss, latestss );

  if (( bss = fopen ( backss, READ )) == NULL )
    uquit ( ERROR, FALSE, "\tCan't open snapshot file: %s.\n", backss );

  if (( lss = fopen ( latestss, READ )) == NULL )
    uquit ( ERROR, FALSE, "\tCan't open snapshot file: %s.\n", latest );

  bmore = backss;                           /* initialize to other than NULL */
  lmore = latestss;
  nextline ( lfile, lrev, &lmore, lss );
  nextline ( bfile, brev, &bmore, bss );

  while ( lmore != NULL || bmore != NULL ) {
    if (( cmp = strcmp ( lfile, bfile )) == 0 ) {
      if ( strcmp ( lrev, brev ) > 0 ) {
	add_file ( head, &current, lfile, lrev, FALSE );
	ctc++;
      } /* if */

      nextline ( lfile, lrev, &lmore, lss );
      nextline ( bfile, brev, &bmore, bss );
    } /* if */

    else if (( lmore != NULL ) &&             /* latest has line not in back */
	     (( cmp < 0 ) || ( bmore == NULL ))) {
      add_file ( head, &current, lfile, lrev, TRUE );
      nextline ( lfile, lrev, &lmore, lss );
      ctn++;
    } /* else if */

    else {                                    /* back has line not in latest */
      if ( is_in_dirs ( dirlist, bfile, dirct ))
        ui_print ( VDETAIL, "backing file: %s, not in default build.\n", bfile);

      nextline ( bfile, brev, &bmore, bss );
      ctl++;
    } /* else */
  } /* while */

  ui_print ( VDETAIL, "\nFound %d changed files between two SNAPSHOTS;\n", ctc);
  ui_print ( VCONT, "%d files in default build not in backing SNAPSHOT;\n",
		     ctn );
  ui_print ( VCONT,
	"%d files in backing SNAPSHOT but no longer in default build.\n", ctl );
  fclose ( lss );
  fclose ( bss );
}                                                          /* list new files */



nextline ( name, rev, more, file )

	/* This procedure reads the next line from the file and
	   divides it into the file name and rev. */

    char      	* name,                             /* name portion of line */
              	* rev,                               /* rev portion of line */
               ** more;                                  /* results of fgets */
    FILE      	* file;                                 /* file to read from */

{
    char          line [ PATH_LEN ],                          /* misc string */
              	* nm,                                     /* misc string ptr */
              	* rv;                                     /* misc string ptr */

  if ( *more != NULL ) {
    if (( *more = fgets ( line, PATH_LEN, file )) != NULL ) {
      nm = (char *)nxtarg ( more, WHITESPACE );
      rv = (char *)nxtarg ( more, WHITESPACE );
      strcpy ( name, nm );
      strcpy ( rev, rv );
    } /* if */
  } /* if */
}                                                                /* nextline */
  


add_file ( head, current, file, rev, new )

	/* This procedure adds a new entry to the list of file/revs. */

    FILEREV  ** head,                           /* head of list of file/revs */
             ** current;                          /* pts to current file/rev */
    char      * file,                                        /* name of file */
              * rev;                                          /* rev of file */
    BOOLEAN     new;                                          /* is file new */

{
  if ( *head == NULL ) {
    *head = ( FILEREV * ) malloc ( sizeof ( FILEREV ));
    *current = *head;
  } /* if */

  else {
    (*current)->nextfr = ( FILEREV * ) malloc ( sizeof ( FILEREV ));
    *current = (*current)->nextfr;
  } /* else */

  if (((*current)->file = (char *)strdup ( file )) == NULL )
    uquit ( ERROR, FALSE, "\tno strdup space for string: %s.\n", file );

  if (((*current)->rev = (char *)strdup ( rev )) == NULL )
    uquit ( ERROR, FALSE, "\tno strdup space for string: %s.\n", rev );

  (*current)->ok = FALSE;
  (*current)->new = new;
  (*current)->nextfr = NULL;

  if ( ui_ver_level () >= VDEBUG ) {
    if ( new )
      ui_print ( VALWAYS, "new file: %s; rev: %s.\n",
			  (*current)->file, (*current)->rev);
    else
      ui_print ( VALWAYS, "file: %s; rev: %s.\n",
			  (*current)->file, (*current)->rev);
  } /* if */
}                                                                /* add file */



BOOLEAN	is_in_dirs ( dirlist, file, dirct )

	/* This procedure checks to see if the file is in the list of
	   directories.  If it is, it returns TRUE, else FALSE. */

    char       ** dirlist,  /* list of directories to use */
              	* file;                          /* file to compare to list */
    int		  dirct;  /* total dir count */

{
    char       ** vptr,  /* points to value */
		* chptr;                                 /* misc string ptr */
    int 	  ct;  /* misc counter */

  for ( ct = 0; ct < dirct; ct++ ) {
    vptr = dirlist + ct;
  
    if (( strncmp ( *vptr, file, strlen ( *vptr )) == 0 ) &&
	( file[strlen ( *vptr)] == SLASH )) {
      if ( ui_is_set ( NORECURSE_OP )) {
	chptr = &file[strlen ( *vptr ) + 1];

	while ( *chptr != SLASH && *chptr != NUL )
	  chptr++;

	if ( *chptr == NUL )
	  return ( TRUE );
      } /* if */

      else
	return ( TRUE );
    } /* if */
  } /* while */

  return ( FALSE );
}                                                              /* is in dirs */



match_dirs ( dirlist, head, dirct )

	/* This procedure goes through the list of changed files and
	   the list of directories and matches them.  It sets the ok
	   field to true if they match. */

    char       ** dirlist;  /* list of directories to use */
    FILEREV     * head;                         /* head of list of file/revs */
    int		  dirct;  /* total dir count */

{
    FILEREV   	* lentry = head;               /* travels down list of files */
    char       ** uentry,  /* travels list of dirs */
		* chptr;                                 /* misc string ptr */
    int		  ct = 0,  /* misc counter */
		  isct = 0,  /* counter of dirs */
                  cmp;                                       /* misc integer */

  ui_print ( VDETAIL, "\nMatching changed and new files to directories.\n" );
  sort_dirs ( dirlist, dirct );
  uentry = dirlist;

  while ( lentry != NULL && isct < dirct ) {
    if (( cmp = strncmp ( lentry->file, *uentry, strlen ( *uentry))) < 0 )
      lentry = lentry->nextfr;

    else if (( cmp > 0 ) ||
	     ( lentry->file [ strlen (*uentry)] != SLASH ))
      uentry = dirlist + ++isct;

    else {
      if ( ui_is_set ( NORECURSE_OP )) {
	chptr = &lentry->file[strlen (*uentry) + 1];

	while ( *chptr != SLASH && *chptr != NUL )
	  chptr++;

	if ( *chptr == NUL ) {
	  lentry->ok = TRUE;
	  ct++;
	} /* if */
      } /* if */

      else {
	lentry->ok = TRUE;
	ct++;
      } /* else */

      if ( lentry->ok )
	ui_print ( VDEBUG, "match dir and file: %s.\n", lentry->file );

      lentry = lentry->nextfr;
    } /* else */
  } /* while */

  ui_print ( VDETAIL, "Total number of matches is: %d.\n", ct );
}                                                              /* match dirs */



sort_dirs ( values, dirct )

	/* This procedure sorts the fields in the directory list so
	   they are in the same order as the files in the file/rev list. */

    char       ** values;                             /* head of values list */
    int		  dirct;  /* total dir count */

{
    char       ** next = values,                         /* holds value list */
               ** traveler,                            /* travels value list */
                * tmp;                                      /* misc char ptr */
    int		  ct = 0,  /* misc counter */
		  sct;  /* misc counter */

  while ( ct++ < dirct ) {
    traveler = next + 1;
    sct = ct;

    while ( sct++ < dirct ) {
      if ( strcmp ( *traveler, *next ) < 0 ) {
	tmp = *next;
	*next = *traveler;
	*traveler = tmp;
      } /* if */

      traveler++;
    } /* while */

    next++;
  } /* while */
}                                                               /* sort dirs */



remove_config ( head, sbsrc )

	/* This procedure reads through the BCSconfig file and
	   marks any file in file/rev list which is also in the
	   config file to FALSE. */

    FILEREV   	* head;                         /* head of list of file/revs */
    char        * sbsrc;                          /* holds dir to sb source */

{
    FILEREV   	* traveler;                      /* walks lists of new files */
    FILE      	* confptr;                             /* ptr to config file */
    char          config [ PATH_LEN ],                /* name of config file */
                  line [ PATH_LEN ],                          /* misc string */
              	* newline,                             /* misc ptr to string */
              	* name;                                /* misc ptr to string */
    int           ct = 0;                                    /* misc integer */
    BOOLEAN       nomatch;                                   /* misc boolean */

  concat ( config, PATH_LEN, sbsrc, "/", BCSCONFIG, NULL );
  ui_print ( VDETAIL, "\nRemoving from list, files already in: %s.\n", config );

  if (( confptr = fopen ( config, READ )) != NULL ) {
    while (( newline = fgets ( line, PATH_LEN, confptr )) != NULL ) {
      name = (char *)nxtarg ( &newline, WHITESPACE );
      traveler = head;
      nomatch = TRUE; 
      
      while ( traveler != NULL && nomatch ) {
	if ( streq ( traveler->file, name )) {
	  nomatch = FALSE;

	  if ( traveler->ok ) {
	    traveler->ok = FALSE;
	    ct++;

	    ui_print ( VDEBUG, "removed config file: %s.\n", traveler->file );
	  } /* if */
	} /* if */

	else
	  traveler = traveler->nextfr;
      } /* while */
    } /* while */
  } /* if */

  ui_print ( VDETAIL, "Number of files already in %s is: %d.\n", BCSCONFIG, ct);
}                                                           /* remove config */



remove_update ( head, sbbase )

	/* This procedure reads through the uptodate file and
	   marks any file in file/rev list which is also in the
	   uptodate file and which has the same rev to FALSE. */

    FILEREV   	* head;                         /* head of list of file/revs */
    char        * sbbase;                           /* holds dir to sb base */

{
    FILEREV   	* traveler;                      /* walks lists of new files */
    FILE      	* upptr;                               /* ptr to config file */
    char          update [ PATH_LEN ],                /* name of update file */
                  line [ PATH_LEN ],                          /* misc string */
              	* newline,                             /* misc ptr to string */
              	* name,                                  /* ptr to file name */
              	* rev;                                 /* pts to rev of file */
    int           ct = 0;                                    /* misc integer */
    BOOLEAN       nomatch;                                   /* misc boolean */

  concat ( update, PATH_LEN, sbbase, "/", UPLOG, NULL );
  ui_print ( VDETAIL, "\nRemoving from list, files already in: %s.\n", update );

  if (( upptr = fopen ( update, READ )) != NULL ) {
    while (( newline = fgets ( line, PATH_LEN, upptr )) != NULL ) {
      name = (char *)nxtarg ( &newline, WHITESPACE );
      rev = (char *)nxtarg ( &newline, WHITESPACE );
      traveler = head;
      nomatch = TRUE; 
      
      while ( traveler != NULL && nomatch ) {
	if ( streq ( traveler->file, name )) {
	  nomatch = FALSE;
	  
	  if ( traveler->ok ) {
	    if ( streq ( traveler->rev, rev )) {
	      traveler->ok = FALSE;
	      ct++;
	      ui_print ( VDEBUG, "removed uptodate file: %s.\n",
				  traveler->file );
	    } /* if */
	  } /* if */
	} /* if */

	else
	  traveler = traveler->nextfr;
      } /* while */
    } /* while */
  } /* if */

  ui_print ( VDETAIL, "Number of files already in %s is: %d.\n", UPLOG, ct );
}                                                           /* remove update */



BOOLEAN	copy_new_files ( head, latest, sandsrc )

	/* This function actually does the copying from the latest
	   directory to the sandbox directory.  It returns TRUE if
	   any files were copied. */

    FILEREV   	* head;                         /* head of list of file/revs */
    char        * latest,                         /* directory to copy from */
                * sandsrc;                          /* holds dir to sb base */

{
    char          copyfrom [ PATH_LEN ],         /* holds paths to copy from */
                  copyto [ PATH_LEN ];              /* holds path to copy to */
    FILEREV   	* traveler = head;               /* walks lists of new files */
    int           ctc = 0,                    /* count files that get copied */
                  cte = 0;                         /* count files that exist */

  if ( chdir ( sandsrc ) == ERROR )
    uquit ( ERROR, FALSE, "\tcould not change directory to: %s.\n", sandsrc );

  if ( ui_is_info ())
    ui_print ( VALWAYS, "\nCopying files: (* is new file)\n" );
  else
    ui_print ( VDETAIL, "\nCopying files: (* is new file)\n" );

  while ( traveler != NULL ) {
    if ( traveler->ok ) {
      strcpy ( copyto, traveler->file );
      rm_comma_v ( copyto );
      concat ( copyfrom, PATH_LEN, latest, "/src/", copyto, NULL );

      if (( ! ui_is_set ( OVERWRITE_OP )) &&
	  ( access ( copyto, F_OK ) == OK )) {
	traveler->ok = FALSE;
	cte++;
	ui_print ( VDEBUG, "file: %s, exists.\n", copyto );
      } /* if */
      
      else if (( ui_is_set ( QUERY_OP )) &&
	       ( skip_copy ( copyfrom, sandsrc, copyto )))
	traveler->ok = FALSE;
      
      else {
	ctc++;

	if ( ui_is_info ())
	  ui_print ( VALWAYS, "%s%s\n", traveler->new ? "*" : "", copyto );
	else
	  ui_print ( VDETAIL, "%s%s\n", traveler->new ? "*" : "", copyto );

	if ( ! ui_is_info ()) {
	  if ( makepath ( copyto, NULL, TRUE, TRUE ) != OK )
            ui_print ( VWARN, "could not make path: %s.\n", copyto );
	  else
	    do_copy ( copyfrom, copyto );
	} /* if */
      } /* else */
    } /* if */

    traveler = traveler->nextfr;
  } /* while */

  if ( ctc == 0 ) {
    ui_print ( VNORMAL, "No files to copy!\n" );
    return ( FALSE );
  } /* if */
    
  ui_print ( VDETAIL, "Number of files copied is: %d.\n", ctc );

  if ( ! ui_is_set ( OVERWRITE_OP ))
    ui_print ( VCONT, "Number of files which already existed is: %d.\n", cte );

  return ( TRUE );
}                                                          /* copy new files */



rm_comma_v ( filename )

	/* This procedure removes the trailing ,v if there is one
	   from the file name. */

    char        filename [];                           /* file to rm ,v from */

{
  if (( filename [ strlen ( filename ) - 2 ] == COMMA ) &&
      ( filename [ strlen ( filename ) - 1 ] == 'v' ))
    filename [ strlen ( filename ) - 2 ] = NUL;
}                                                              /* rm comma v */



BOOLEAN	skip_copy ( copyfrom, cdir, copyto )

	/* This function prompts the user, asking if the files
	   should be copied.  It returns the user's answer. */

    char        copyfrom [],                                 /* file to copy */
                cdir [],                                      /* current dir */
                copyto [];                                 /* file to create */

{
    char        ans [ STRING_LEN ];                         /* anwser string */

  ui_print ( VALWAYS, "copy %s \n  to %s/%s? [<y>|n]: ",
		       copyfrom, cdir, copyto );
  gets ( ans );
  return ( *ans == 'n' );
}                                                               /* skip copy */



do_copy ( src, dest ) 

	/* Copy the file from source to destination */

    char      * src,                   /* where the file will be copied from */
              * dest;                    /* where the file will be copied to */

{
    int 	fd_src, fd_dest;

  if (( fd_src = open ( src, O_RDONLY, 0 )) < OK ) {
    ui_print ( VFATAL, "failed to open file: %s.\n", src );
    return;
  } /* if */

  if (( fd_dest = open ( dest, O_WRONLY|O_TRUNC|O_CREAT, 0666 )) < OK ) {
    ui_print ( VFATAL, "failed to open file: %s.\n", dest );
    ( void ) close ( fd_src );
    return;
  } /* if */

  if ( filecopy ( fd_src, fd_dest ) < OK )
    ui_print ( VFATAL, "filecopy of %s\n\tto %s failed.\n", dest, src );

  if ( close ( fd_src ) < OK )
    ui_print ( VFATAL, "could not close file %s\n", src );

  if ( close ( fd_dest ) < OK )
    ui_print ( VFATAL, "could not close file %s\n", dest );
}                                                                 /* do copy */



update_update ( head, sbbase )

	/* This procedure updates the uptodate files by creating a
	   new one in the form of uptodate.N and by putting in the
	   copied files into the uptodate file. */

    FILEREV   	* head;                         /* head of list of file/revs */
    char        * sbbase;                           /* holds dir to sb base */

{
    FILEREV   	* traveler = head;              /* travels list of file/revs */
    FILE      	* upptr,                             /* pts to uptodate file */
              	* tmpptr;                                 /* pts to tmp file */
    char          uptofile [ PATH_LEN ],                    /* uptodate file */
                  nuptofile [ PATH_LEN ],               /* new uptodate file */
                  tmpfile [ PATH_LEN ];                          /* tmp file */

  name_update_file ( sbbase, nuptofile );         /* update uptodate.N */

  if ( ui_is_info ())
    return;

  if (( upptr = fopen ( nuptofile, WRITE )) == NULL )
    uquit ( ERROR, FALSE, "\tcould not open log file: %s.\n", nuptofile );
 
  while ( traveler != NULL ) {
    if ( traveler->ok )
      fprintf ( upptr, "%s\t%s\n", traveler->file, traveler->rev );

    traveler = traveler->nextfr;
  } /* while */

  fclose ( upptr );
  concat ( uptofile, PATH_LEN, sbbase, "/", UPLOG, NULL );
  concat ( tmpfile, PATH_LEN, uptofile, "0", NULL );
  ui_print ( VDETAIL, "Merging copied files into %s.\n", uptofile );

  if (( upptr = fopen ( uptofile, READ )) == NULL )
    do_copy ( nuptofile, uptofile );

  else {
    if (( tmpptr = fopen ( tmpfile, WRITE )) == NULL )
      uquit ( ERROR, FALSE, "\tcould open tmp log: %s.\n", tmpfile );

    merge_updates ( head, upptr, tmpptr );
    fclose ( upptr );
    fclose ( tmpptr );

    if ( rename ( tmpfile, uptofile ) == ERROR )
      uquit ( ERROR, FALSE, "\tcould not rename %s to %s.\n",
				   tmpfile, uptofile );
  } /* else */
}                                                           /* update update */



name_update_file ( sbbase, newfile )

	/* This procedure renames the update path to uptodate.N
	   where N is the next numbered update file. */

    char        * sbbase,                       /* path and name of sandbox */
                * newfile;                   /* will hold new uptodate file */

{
    int         count = 1;                                   /* misc counter */

  concat ( newfile, PATH_LEN, sbbase, "/", UPLOG, ".", itoa ( count ), NULL );

  while ( access ( newfile, F_OK ) == OK ) {
    count++;
    concat ( newfile, PATH_LEN, sbbase, "/", UPLOG, ".", itoa ( count ), NULL );
  } /* while */

  ui_print ( VDETAIL, "New uptodate file is: %s.\n", newfile );
}                                                      /* rename update file */



char * itoa ( num ) 

	/* This function converts an integer to a char. */

    int num;                                           /* integer to convert */

{
    static char buf [ 20 ];

  sprintf ( buf, "%d", num );
  return ( buf );
}                                                                    /* itoa */



merge_updates ( head, from, to )

	/* This procedure merges the list of files copied and the
	   current uptodate file into a tmp file. */

    FILEREV   * head;                           /* head of list of file/revs */
    FILE      * from,                                /* pts to uptodate file */
              * to;                                       /* pts to tmp file */
{
    FILEREV   * traveler = head;                /* travels list of file/revs */
    char        line [ PATH_LEN ],                            /* misc string */
              * newline,                               /* misc ptr to string */
              * name,                                    /* ptr to file name */
              * rev;                                   /* pts to rev of file */
    int         cmp;                                         /* misc integer */

  if (( newline = fgets ( line, PATH_LEN, from )) != NULL ) {
    name = (char *)nxtarg ( &newline, WHITESPACE );
    rev = (char *)nxtarg ( &newline, WHITESPACE );
  } /* if */

  while ( traveler != NULL && ! traveler->ok )
    traveler = traveler->nextfr;

  while ( traveler != NULL && newline != NULL ) {

    if (( cmp = strcmp ( traveler->file, name )) <= 0 ) {
      fprintf ( to, "%s\t%s\n", traveler->file, traveler->rev );
      traveler = traveler->nextfr;

      while ( traveler != NULL && ! traveler->ok )
        traveler = traveler->nextfr;

      if ( cmp == 0 )
        newline = fgets ( line, PATH_LEN, from );
    } /* if */

    else {
      fprintf ( to, "%s\t%s\n", name, rev );

      if (( newline = fgets ( line, PATH_LEN, from )) != NULL ) {
        name = (char *)nxtarg ( &newline, WHITESPACE );
        rev = (char *)nxtarg ( &newline, WHITESPACE );
      } /* if */
    } /* else */
  } /* while */

  while ( traveler != NULL ) {
    fprintf ( to, "%s\t%s\n", traveler->file, traveler->rev );
    traveler = traveler->nextfr;

    while ( traveler != NULL && ! traveler->ok )
      traveler = traveler->nextfr;
  } /* if */

  if ( newline != NULL ) {
    fprintf ( to, "%s\t%s\n", name, rev );

    while ( fgets ( line, PATH_LEN, from ) != NULL )
      fprintf ( to, "%s", line );
  } /* if */
}                                                           /* merge updates */



void print_usage (void) 

	/* This procedure prints the usages for uptodate. */

{
  printf ( "USAGE:\n" );
  printf ( "%s [-query -overwrite -norecurse] [sb_opts] [gen_opts]\n",
		progname );
  printf ( "\t   directory(ies)...\n" );
  printf ( "\t -query: ask before making each copy\n" );
  printf ( "\t -overwrite: overwrite a file if it exists\n" );
  printf ( "\t -norecurse: check only directories listed, do not descend\n" );
  printf ( "\t sb_opts:\n" );
  printf ( "\t   -sb <sandbox>, -rc <user rc file>, -sb_rc <sb rc file>\n" );
  printf ( "\t gen_opts:\n" );
  printf ( "\t   -copy_from <src>: use <src> instead of default build\n");
  printf ( "\t   -cmp_to <base>: use <base> instead of backing SNAPSHOT\n" );
  printf ( "\t directory(ies): list of directories to update\n" );
  printf ( "%s -usage | rev\n", progname );
}  /* print usage */
