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
 * $Log: build.c,v $
 * Revision 1.11.10.1  1993/12/09  18:56:34  marty
 * 	CR # 840 - Removed local copies of exists(), isdir(), and mmakedir().  They
 * 	are already in libode.a
 * 	[1993/12/09  18:56:19  marty]
 *
 * Revision 1.11.8.3  1993/11/08  22:23:02  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/08  22:22:22  damon]
 * 
 * Revision 1.11.8.2  1993/11/03  17:14:00  damon
 * 	CR 463. More pedantic
 * 	[1993/11/03  17:13:50  damon]
 * 
 * Revision 1.11.8.1  1993/10/28  13:32:12  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:22  damon]
 * 
 * Revision 1.11.6.13  1993/06/02  13:51:43  damon
 * 	CR 517. Cleaned up subprojects wrt sb.conf and sc.conf
 * 	[1993/06/02  13:50:37  damon]
 * 
 * Revision 1.11.6.12  1993/05/28  13:41:51  marty
 * 	CR # 558 - Fix build errors on rios_zix
 * 	[1993/05/28  13:41:39  marty]
 * 
 * Revision 1.11.6.11  1993/05/27  18:25:10  marty
 * 	CR # 554 - build now works outside a sandbox and takes the -set option
 * 	[1993/05/27  18:24:37  marty]
 * 
 * Revision 1.11.6.10  1993/05/17  20:27:26  damon
 * 	CR 419. Replaced calls to rc_file_field with find_field
 * 	[1993/05/17  20:27:19  damon]
 * 
 * Revision 1.11.6.9  1993/05/14  16:50:31  damon
 * 	CR 518. Changed prj_read and prj_write to take full sb path
 * 	[1993/05/14  16:49:29  damon]
 * 
 * Revision 1.11.6.8  1993/05/12  19:51:32  damon
 * 	CR 517. Added subprojects
 * 	[1993/05/12  19:48:38  damon]
 * 
 * Revision 1.11.6.7  1993/04/29  16:45:13  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  16:45:00  marty]
 * 
 * Revision 1.11.6.6  1993/04/20  21:51:42  marty
 * 	Add include file stdio.h
 * 	[1993/04/20  21:51:15  marty]
 * 
 * Revision 1.11.6.5  1993/04/15  17:28:46  marty
 * 	Add include file ode/interface.h
 * 	[1993/04/15  17:28:29  marty]
 * 
 * Revision 1.11.6.4  1993/04/09  14:28:14  damon
 * 	CR 417. Works with new split sandbox setup
 * 	[1993/04/09  14:28:03  damon]
 * 
 * Revision 1.11.6.3  1993/02/01  22:05:50  damon
 * 	CR 417. Now uses Buildconf
 * 	[1993/02/01  22:05:34  damon]
 * 
 * Revision 1.11.6.2  1993/01/28  23:27:18  damon
 * 	CR 419. Replace rc_file_field with get_rc_value
 * 	[1993/01/28  23:25:50  damon]
 * 
 * Revision 1.11.4.7  1992/12/03  19:04:29  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:34:25  damon]
 * 
 * Revision 1.11.4.6  1992/11/09  20:28:41  damon
 * 	CR 329. Added include of stdlib.h
 * 	[1992/11/09  20:25:41  damon]
 * 
 * Revision 1.11.4.5  1992/10/13  18:19:45  damon
 * 	CR 288. Adjusted call to ui_init
 * 	[1992/10/13  18:19:11  damon]
 * 
 * Revision 1.11.4.4  1992/09/24  18:58:31  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:17:07  gm]
 * 
 * Revision 1.11.4.3  1992/06/16  22:11:43  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:01:13  damon]
 * 
 * Revision 1.11.2.2  1992/03/25  22:45:35  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  21:48:45  damon]
 * 
 * Revision 1.11  1991/12/05  20:41:07  devrcs
 * 	Removed runcmdv and endcmd routines so that the libsb versions
 * 	will be used.
 * 	[1991/11/27  19:17:11  mckeen]
 * 
 * 	Updated to not use *_prefix for new make
 * 	[91/04/09  13:11:30  mckeen]
 * 
 * 	Changed sdm to ode; std_defs.h to odedefs.h
 * 	[91/01/11  10:57:18  randyb]
 * 
 * 	Made all Tools II changes.
 * 	[91/01/08  10:14:25  randyb]
 * 
 * 	Changed w.w_status usage to a conditional usage based on
 * 	WAIT_IS_UNION def
 * 	[90/12/20  15:55:35  damon]
 * 
 * 	Fixed non-portable type problem. References to w have been changed
 * 	to w.w_status.
 * 	[90/12/13  10:28:50  damon]
 * 
 * Revision 1.9  90/10/07  21:50:44  devrcs
 * 	Pre-OSF changes.
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
**      This program is a front end for make.  It sets all the necessary
**	environment for working in a sandbox before invoking make.
**
 */

static const char * rcsid =
 "$RCSfile: build.c,v $ $Revision: 1.11.10.1 $ $Date: 1993/12/09 18:56:34 $";

#include <ode/builddata.h>
#include <ode/odedefs.h>
#include <ode/interface.h>
#include <ode/project.h>
#include <ode/run.h>
#include <ode/sandboxes.h>
#include <ode/sets.h>
#include <ode/util.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>
#include <varargs.h>
#include <a.out.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ode/parse_rc_file.h>
#include <stdio.h>

/*
 * PROTOTYPES
 */
char * path_relative_to ( char * );
void cmdline_syntax ( char **, char ** );
void check_sandbox (struct rcfile *);
void print_envvar (struct arg_list *);
void set_paths (void);
void build_targets (void);
void resize_makeargs  ( int * );
void check_targets (void);
int exists ( const char * );
BOOLEAN srcdir ( int , char * );
int makedir ( char * dir );

#  define  MAX_ARGS     8
#  define  CLEAN_OP	"-clean"
#  define  SET_OP	"-set"
#  define  HERE_OP	"-here"
#  define  LINT_OP	"-lint"
#  define  DASH_OP	"-*"
#  define  EQUAL_OP	"*=*"
#  define  ECHO         "/bin/echo"                          /* echo command */

    UIINIT init [] = {                      /* initialize the user interface */
      { CLEAN_OP, 1, OVERWRITE, 0, 0, "" },
      { HERE_OP,  1, OVERWRITE, 0, 0, "" },
      { LINT_OP,  1, OVERWRITE, 0, 0, "" },
      { SB_OP,    1, OVERWRITE, 1, 1, ARGS_OP }, 
      { SET_OP,    1, OVERWRITE, 1, 1, ARGS_OP }, 
      { DASH_OP,  UNLIMITED, OVERWRITE, 0, 0, "" }, 
      { EQUAL_OP, UNLIMITED, OVERWRITE, 0, 0, "" }, 
      { ARGS_OP,  UNLIMITED, OVERWRITE, 0, 0, "" }
    };

    char 	* sandbox = NULL,
		* set = NULL;

    char 	* rcfile_source_base,
         	* rcfile_object_base,
         	* rcfile_object_owner,
         	* rcfile_object_cover,
         	* rcfile_build_makeflags,
         	* user,
         	  makecmd [ MAXPATHLEN ],
         	* relative_path,
         	* sourcedirpath,
         	* deftargetdirs [ 2 ],
               ** makeargs,
               ** targets,
               ** targetdirs;
    const char  * progname = "build";
    
    int 	  needabsolute,
        	  ntargets,
        	  nmakeargs;
    BOOLEAN isdir ( const char * );

    const char * deftargets [] = {
      		    "build_all",
      		    NULL
    		  };
    
    struct 	rcfile rcfile;
    
void
main ( int argc, char ** argv )
{
  char * sb_rcfile = NULL;
  char   sandbox_base [MAXPATHLEN];
  char * project = NULL;
  char * sub_project = NULL;
  char * dir = (char *)".";
  char * usr_rcfile = NULL;
  char * basepath = NULL;

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  cmdline_syntax ( &sb_rcfile, &basepath );
  concat ( sandbox_base, sizeof(sandbox_base), basepath, "/", sandbox, NULL );
  memset ( (char *)&rcfile, 0, sizeof( struct rcfile) );

  if (ui_is_set ( SET_OP )) {
        current_set(&set, &dir, &sandbox, &usr_rcfile);
  } else {
  	if(sb_current_dir ( sandbox, basepath, &dir ) != TRUE)
		current_set(&set, &dir, &sandbox, &usr_rcfile);
  }

  prj_read ( sb_full_path ( basepath, sandbox ), dir, &project, &sub_project );
  bld_conf_read ( sandbox_base, project, &rcfile );
  check_sandbox(&rcfile);
  set_paths ();
  check_targets ();
  build_targets ();
  exit(0);
}


void
cmdline_syntax ( char ** sb_rcfile, char ** basepath )

	/* This procedure checks for relationships between the
           command line arguments.  It assumes the syntax is
           already correct.  Most of the functions it calls
           will use uquit to exit if there is an error. */

{
    char 	* usr_rcfile;
    int   	  maxmakeargs = 0,
                  ct;                                        /* misc integer */

  sandbox = ui_arg_value ( SB_OP, 1, 1 );
  *sb_rcfile = NULL;
  usr_rcfile = ui_arg_value ( RC_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );

  if ( current_sb ( &sandbox, basepath, sb_rcfile, &usr_rcfile) == ERROR )
    uquit ( ERROR, FALSE, "unable to parse home sandbox rc: %s.\n", usr_rcfile);

  if (( user = getenv ( "USER" )) == NULL )
    uquit ( ERROR, FALSE, "USER not found in environment");
  
  ui_print ( VDETAIL, "environment variable USER: %s.\n", user );
  nmakeargs = 0;
  ui_print ( VDEBUG, "checking command line arguments\n" );

  for ( ct = 1; ct <= ui_entry_cnt ( DASH_OP ); ct++ ) {
    if ( nmakeargs == maxmakeargs )
      resize_makeargs ( &maxmakeargs );

    makeargs[nmakeargs++] = ui_entry_value ( DASH_OP, ct );
  } /* for */

  for ( ct = 1; ct <= ui_entry_cnt ( EQUAL_OP ); ct++ ) {
    if ( nmakeargs == maxmakeargs )
      resize_makeargs ( &maxmakeargs );

    makeargs[nmakeargs++] = ui_entry_value ( EQUAL_OP, ct );
  } /* for */

    /*
     * "no targets" implies "build_all" in the current directory when
     * not running as root.
     */

  if (( ntargets = ui_entry_cnt ( ARGS_OP )) == 0 ) {
    ntargets = 1;
    targets = (char **)deftargets;
    targetdirs = deftargetdirs;
  } /* if */

  else {
    if (( ntargets = ui_entries_to_argv ( ARGS_OP, &targets )) <= 0 )
      uquit ( ERROR, FALSE, "ui_entries_to_argv failed\n" );

    if (( targetdirs = (char **) malloc((unsigned) ntargets * sizeof(char *)))
		     == (char **) NULL )
      uquit ( ERROR, FALSE, "targetdirs malloc failed\n" );
  } /* else */
}                                                          /* cmdline syntax */


void
resize_makeargs  ( int * maxmakeargs )
{
  if ( *maxmakeargs == 0 ) {
    *maxmakeargs = 16;
    makeargs = (char **) malloc((unsigned) *maxmakeargs * sizeof(char *));
  }

  else {
    *maxmakeargs <<= 1;
    makeargs = (char **) realloc((char *) makeargs,
	                 (unsigned) *maxmakeargs * sizeof(char *));
  }

  if (makeargs == NULL)
    uquit ( ERROR, FALSE, "makeargs malloc failed");
}


void
check_sandbox (struct rcfile * rcfile_p)
{
    char 	* rcfile_source_cover;
    char 	* rcfile_source_owner;
    struct 	field    * field_p;
    struct 	arg_list * args_p;

  ui_print ( VDEBUG, "checking sandbox\n" );

  if (get_rc_value ( "source_base", &rcfile_source_base, rcfile_p, TRUE) != OK)
    uquit ( ERROR, FALSE, "source_base not defined.\n" );

  if ( *rcfile_source_base != '/' )
    uquit ( ERROR, FALSE, "source_base is not an absolute path.\n" );

  if ( exists(rcfile_source_base) < 0 )
    uquit ( ERROR, FALSE, "source_base %s not found.\n", rcfile_source_base );

  if ( get_rc_value ( "source_owner", &rcfile_source_owner, rcfile_p, FALSE )
       != OK )
    rcfile_source_cover = NULL;
  
  else {

    if ( get_rc_value ( "source_cover", &rcfile_source_cover, rcfile_p, TRUE )
         != OK )
      uquit ( ERROR, FALSE, "source_cover not defined.\n" );

    if ( *rcfile_source_cover != '/' )
      uquit ( ERROR, FALSE, "source_cover is not an absolute path.\n" );

    if ( access ( rcfile_source_cover, X_OK ) < 0 )
      uquit ( ERROR, FALSE, "source_cover %s not executable.\n",
			     rcfile_source_cover );
  } /* else */

  if ( get_rc_value ( "object_base", &rcfile_object_base, rcfile_p, TRUE )
       != OK )
    uquit ( ERROR, FALSE, "object_base not defined.\n" );

  if (*rcfile_object_base != '/')
    uquit ( ERROR, FALSE, "object_base is not an absolute path.\n" );

  if (exists(rcfile_object_base) < 0)
    uquit ( ERROR, FALSE, "object_base %s not found.\n", rcfile_object_base );

  if ( get_rc_value ( "object_owner", &rcfile_object_owner, rcfile_p, FALSE )
                    != OK ) {
    rcfile_object_owner = NULL;
    rcfile_object_cover = NULL;
  } else {

    if ( get_rc_value ( "object_cover", &rcfile_object_cover, rcfile_p, TRUE )
         != OK )
      uquit ( ERROR, FALSE, "object_cover not defined.\n" );

    if (*rcfile_object_cover != '/')
      uquit ( ERROR, FALSE, "object_cover is not an absolute path.\n" );

    if (access(rcfile_object_cover, X_OK) < 0)
      uquit ( ERROR, FALSE, "object_cover %s not executable.\n",
	rcfile_object_cover);
  } /* if */

  if ( get_rc_value ( "build_makeflags", &rcfile_build_makeflags, rcfile_p,
                       FALSE ) != OK )
    rcfile_build_makeflags = NULL;
  /* if */

  if ( ui_ver_level () >= VDETAIL ) {
    if ( find_field(rcfile_p, "setenv", &field_p, 0 ) == 0 ) {
      ui_print ( VDETAIL, "The following environment variables were set:\n" );

      for (args_p = field_p->args; args_p != NULL; args_p = args_p->next)
	print_envvar (args_p);
    } /* if */
  } /* if */
}                                                           /* check sandbox */



void
print_envvar (struct arg_list *var)
{
    char 	* val;

  if (var->ntokens != 1)
    return;

  if ((val = getenv(var->tokens[0])) == NULL)
    return;

  ui_print ( VCONT, "  %s=%s\n", var->tokens[0], val);
}


void
set_paths (void)
{
    char 	  buf [MAXPATHLEN];
    char 	  file_path [MAXPATHLEN];
    char 	* ptr;

  ui_print ( VDEBUG, "setting paths\n" );

  if (( ptr = getenv( "MAKE" )) != NULL ) {
    (void) strcpy ( makecmd, ptr );
    ui_print ( VDETAIL, "reading MAKE from environment as: %s.\n", makecmd );
  } /* if */
 
  else {
    if (( ptr = getenv ("PATH")) == NULL )
      uquit ( ERROR, FALSE, "PATH not defined in environment.\n" );
    else
      ui_print ( VDETAIL, "reading PATH from environment as:\n   %s.\n", ptr );

    if ( searchp ( ptr, "make", file_path, exists ) == 0 )
      (void) strcpy ( makecmd, file_path );
    else
      (void) strcpy ( makecmd, "make" );
  } /* else */

  if (( sourcedirpath = getenv ( "SOURCEDIR" )) == NULL )
    uquit ( ERROR, FALSE, "SOURCEDIR not defined in environment.\n" );

  if ( *sourcedirpath == NUL )
    sourcedirpath = rcfile_source_base;
  else {
    ui_print ( VDEBUG, "backing source: %s\n", sourcedirpath );
    concat( buf, MAXPATHLEN, rcfile_source_base, ":", sourcedirpath, NULL );
    
    if (( sourcedirpath = strdup (buf)) == NULL )
      uquit ( ERROR, FALSE, "strdup sourcedirpath failed.\n" );
  } /* else */

  ui_print ( VDEBUG, "usr source: %s\n", rcfile_source_base );
  relative_path = path_relative_to (rcfile_source_base);

  if ( relative_path != NULL )
    ui_print ( VNORMAL, "relative path: .%s\n", relative_path );
}                                                               /* set paths */



char *
path_relative_to ( char * base_dir )

	/*
 	 * If we are within the directory subtree of base_dir, return the path
 	 * from there to the current directory.  Otherwise, return NULL.
 	 */

{
    static char   curdir [MAXPATHLEN];
    static int    curdir_len = 0;
    char 	  basepath [MAXPATHLEN],
         	* file_path;
    int 	  len;

  if (curdir_len == 0) {
    if ( getcwd ( curdir, sizeof(curdir) ) == NULL )
      uquit ( ERROR, FALSE, "getcwd: %s.\n", strerror(errno) );

    curdir_len = strlen ( curdir );

    if ( curdir_len == 0 || curdir[0] != '/' )
      uquit ( ERROR, FALSE, "getcwd returned bad current directory: %s.",
			     curdir );
  }  /* if */

  if ( chdir ( base_dir ) < 0 )
    uquit ( ERROR, FALSE, "chdir %s.\n", base_dir);

  if ( getcwd ( basepath, sizeof(basepath) ) == NULL )
    uquit ( ERROR, FALSE, "getcwd %s: %s.\n", base_dir, strerror(errno));

  if ( chdir ( curdir ) < 0 )
    uquit ( ERROR, FALSE, "chdir %s.\n", curdir);

  len = strlen ( basepath );

  if ( len == 0 || basepath[0] != '/' )
    uquit ( ERROR, FALSE, "getcwd returned bad base directory: %s.", basepath );

  if ( curdir_len < len )
    return( NULL );

  if ( memcmp ( basepath, curdir, len ) != 0 )
    return( NULL );

  if ( curdir[len] != NUL && curdir[len] != '/' )
    return( NULL );

  if (( file_path = strdup ( curdir + len )) == NULL )
    uquit ( ERROR, FALSE, "strdup relative path.\n" );

  return ( file_path );
}                                                        /* path relative to */


void
check_targets (void)

{
    char 	  dirbuf [MAXPATHLEN],
		  filbuf [MAXPATHLEN],
         	  testtarget [MAXPATHLEN],
         	  targetdir [MAXPATHLEN],
         	* fulltarget,
         	* ptr,
		* p;
    int 	  absolute,
        	  i;

  for ( i = 0; i < ntargets; i++ ) {
    fulltarget = targets[i];
    ui_print ( VDETAIL, "target: %s\n", fulltarget );

	/*
	 * remember whether or not the target is absolute
	 */
    absolute = (*fulltarget == '/');

    if ( ! absolute ) {
      if (relative_path == NULL)
	uquit ( ERROR, FALSE, "not in sandbox and target %s is not absolute.\n",
		  	       fulltarget );
    }  /* if */

    if ( ui_is_set ( HERE_OP ) || strcmp(fulltarget, "build_all") == 0) {
      if ( streq ( fulltarget, "build_all" ))
	  targetdir[0] = NUL;
      
      else {
	(void) strcpy ( targetdir, fulltarget );
	if ( targetdir[0] == NUL ) {
	  targetdir[0] = '/';
	  targetdir[1] = NUL;
	}  /* if */
      }  /* else */

      filbuf[0] = NUL;
    }  /* if  */
    
    else {
      path ( fulltarget, dirbuf, filbuf );

      if ( filbuf[0] == NUL || ( filbuf[0] == '.' && filbuf[1] == NUL ))
	uquit ( ERROR, FALSE, "invalid null target.\n" );

      if ( srcdir ( absolute, fulltarget ))
	(void) strcpy ( targetdir, fulltarget );

      else {
	ptr = fulltarget;
	p = testtarget;

	while ( (*p = *ptr++) )
	    p++;

	ptr = NULL;

	while ( p >= testtarget && *p != '/' ) {
	    if ( *p == '.' )
	      ptr = p;

	    p--;
	}  /* while */

	if (ptr != NULL && ptr != p + 1)
	  *ptr = NUL;
	else
	  ptr = NULL;

	if ( ptr != NULL && srcdir ( absolute, testtarget ))
	  (void) strcpy ( targetdir, testtarget );
	else
	  (void) strcpy ( targetdir, dirbuf );
      }  /* else */
    }  /* else */

    if (targetdir[0] == '.' && targetdir[1] == NUL)
      targetdir[0] = NUL;

    if ( ! srcdir ( absolute, targetdir ))
      uquit ( ERROR, FALSE, "targetdir %s is not a directory", targetdir);

    targets[i] = strdup(filbuf);

      	/*
       	 * If we are changing to some directory for the build (e.g. the
         * original target contained a slash), figure out how to
         * indicate this to the user.  If the target is relative to the
         * current directory, just use the relative directory name.  If
         * the target is absolute preceed this with the string "... ."
         * to suggest that the directory is relative to the absolute
         * base of the source tree.
         */
    if ( absolute || *targetdir != NUL )
      targetdirs[i] = strdup (targetdir);
    else
      targetdirs[i] = NULL;
  }  /* for */
}                                                           /* check targets */




BOOLEAN
srcdir ( int absolute, char * testtarget )
{
    char 	  buf [MAXPATHLEN];

  if ( *testtarget == NUL )
    return ( TRUE );

  if ( absolute ) {
    if ( searchp ( sourcedirpath, testtarget + 1, buf, isdir ) == 0 )
      return ( TRUE );
  }  /* if */

  else if ( isdir ( testtarget ) == 0 )
    return ( TRUE );

  return ( FALSE );
}                                                                  /* srcdir */

void
build_targets (void)
{
    char 	  prompt [MAXPATHLEN],
         	  dirbuf [MAXPATHLEN],
         	  build_target [MAXPATHLEN],
         	  clean_target [MAXPATHLEN],
         	  lint_target [MAXPATHLEN],
         	* cd,
		* target,
    		* dirptr,
    		* ptr,
    		* cmd;
    char  * av[64];
    int 	  status,
    		  pid,
    		  i = 0,
		  vi, j,
    		  firsti;

  concat ( dirbuf, sizeof ( dirbuf ), rcfile_source_base, NULL );
  dirptr = dirbuf;

  if ( rcfile_object_owner == NULL ) {
    if (( ptr = strrchr ( makecmd, '/' )) != NULL )
      ptr++;
    else
      ptr = makecmd;

    av[i++] = ptr;
    cmd = makecmd;
  }  /* if */
  
  else {
    ui_print ( VDETAIL, "setenv AUTHCOVER_USER %s.\n", rcfile_object_owner );

    if ( ! ui_is_info ()) {
      if (setenv( "AUTHCOVER_USER", rcfile_object_owner, 1) < 0)
	uquit ( ERROR, FALSE, "AUTHCOVER_USER setenv failed");
    }  /* if */

    ui_print ( VDETAIL, "setenv AUTHCOVER_TESTDIR %s.\n", rcfile_object_base );

    if ( ! ui_is_info ()) {
      if ( setenv ( "AUTHCOVER_TESTDIR", rcfile_object_base, 1 ) < 0 )
	uquit ( ERROR, FALSE, "AUTHCOVER_TESTDIR setenv failed.\n" );
    }  /* if */

    av[i++] = (char *)"authcover";
    av[i++] = makecmd;
    cmd = rcfile_object_cover;
  }  /* else */

  if ( rcfile_build_makeflags != NULL )
    av[i++] = rcfile_build_makeflags;

  for ( j = 0; j < nmakeargs; j++ )
    av[i++] = makeargs[j];

  firsti = i;

    /*
     * For each target:
     *   Run a "clean" operation first, if requested
     *   Run a "build" operation
     *   Run a "lint" operation, if requested.
     */

  for ( j = 0; j < ntargets; j++ ) {
    i = firsti;
    cd = targetdirs[j];
    target = targets[j];

    if ( target == NULL )
      continue;

    ui_print ( VDETAIL, "building: %s.\n",
			 (*target != NUL) ? target : "build_all" );

    if (cd != NULL) {
      if (*cd != NUL && *cd != '/')
	ui_print ( VNORMAL, "cd %s\n", cd );

      else {
	ui_print ( VNORMAL, "cd ... .%s.\n", cd );
	(void) concat( dirptr, dirbuf + sizeof(dirbuf) - dirptr, cd, NULL );
	cd = dirbuf;
      }  /* else */

      if ( exists (cd) < 0 ) {
	(void) concat(prompt, sizeof(prompt),
		      "Directory ", cd, " not found - create", NULL );
	if ( ! getbool ( prompt, TRUE )) {
	  targets[j] = NULL;
	  continue;
	}  /* if */

	if ( ! ui_is_info ())
	  makedir(cd);
      }  /* if */
    }  /* if */

    if ( *target == NUL ) {
      if ( ui_is_set ( CLEAN_OP ))
	av[i++] = (char *)"clean_all";

      av[i++] = (char *)"build_all";

      if ( ui_is_set ( LINT_OP ))
	av[i++] = (char *)"lint_all";
    }   /* if */
    
    else {
      if ( ui_is_set ( CLEAN_OP )) {
	(void) concat ( clean_target, sizeof(clean_target),
		        target, NULL );
	av[i++] = clean_target;
      }  /* if */

      (void) concat ( build_target, sizeof(build_target),
		      target, NULL);
      av[i++] = build_target;

      if ( ui_is_set ( LINT_OP )) {
	(void) concat ( lint_target, sizeof(lint_target),
			target, NULL);
	av[i++] = lint_target;
      }  /* if */
    }  /* else */

    av[i++] = NULL;
    (void) fflush(stdout);
    (void) fflush(stderr);
		    
    if ( ui_ver_level () == VDEBUG ) {
      (void) runv( ECHO, av );
      continue;
    }  /* if */

    if ( ui_ver_level () >= VDETAIL ) {
      ui_print ( VDETAIL, "string passed to %s:\n   ", cmd );

      for ( vi = 0; vi < (i-1); vi++ )
	ui_print ( VALWAYS, "%s ", av[vi] );	
      
      ui_print ( VALWAYS, "\n" );
    }  /* if */

    if ( ! ui_is_info ()) {              /* make runcmd conditional on -info */
      if (( pid = runcmdv ( cmd, cd, av )) == ERROR )
	exit ( ERROR );
      if (( status = endcmd ( pid )) != 0 )
	exit ( status );
    }  /* ifi */
  }  /* for */
}                                                           /* build targets */



void print_usage (void)

        /* This procedure prints the usages for build. */

{
  printf ( "USAGE:\n" );
  printf ( "%s [-here -clean -lint] [-*] [*=*] [sb_opts] target(s)\n",
		    progname );
  printf ( "      -here : targets are directories to work from\n" );
  printf ( "      -clean : old format to remove and rebuild target\n" );
  printf ( "      -lint : old format to run lint\n" );
  printf ( "      -* : any additional dash arg is passed to make\n" );
  printf ( "      *=* : any equation of this form is passed to make\n" );
  printf ( "      sb_opts:\n" );
  printf ( "        -sb <sandbox>, -rc <user rc file>, -sb_rc <sb rc file>\n" );
  printf ( "      target(s) : list of items to build\n" );
  printf ( "%s -usage | -rev\n", progname );
}                                                             /* print usage */
