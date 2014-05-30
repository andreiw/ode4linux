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
 * $Log: resb.c,v $
 * Revision 1.12.12.4  1994/02/03  16:00:14  damon
 * 	CR 888. Check for backing argument even if not in ode bld env
 * 	[1994/02/03  16:00:03  damon]
 *
 * Revision 1.12.12.3  1994/01/19  14:01:28  marty
 * 	CR # 971 - Remove debugging statements.
 * 	[1994/01/19  14:01:13  marty]
 * 
 * Revision 1.12.12.2  1994/01/12  19:30:00  marty
 * 	CR # 971 - Put in more checks that the tree we are resb'ing to is
 * 	a valid backing tree.
 * 	[1994/01/12  19:29:30  marty]
 * 
 * Revision 1.12.12.1  1993/12/29  17:59:19  damon
 * 	CR 952. Added VERROR, check for no sb
 * 	[1993/12/29  17:58:55  damon]
 * 
 * Revision 1.12.10.3  1993/11/12  18:31:51  damon
 * 	CR 780. resb now handles subproject sb.conf files
 * 	[1993/11/12  18:31:40  damon]
 * 
 * Revision 1.12.10.2  1993/11/04  20:39:04  damon
 * 	CR 463. More pedantic
 * 	[1993/11/04  20:38:52  damon]
 * 
 * Revision 1.12.10.1  1993/10/28  13:32:24  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:29  damon]
 * 
 * Revision 1.12.8.1  1993/09/21  16:48:34  damon
 * 	CR 673. Read all sb.conf files in backing chain
 * 	[1993/09/21  16:48:01  damon]
 * 
 * Revision 1.12.6.10  1993/06/07  15:11:51  marty
 * 	CR # 561 - Fix for 'resb' core dumping  when running
 * 	outside a sandbox.
 * 	[1993/06/07  15:11:36  marty]
 * 
 * Revision 1.12.6.9  1993/06/02  17:55:54  damon
 * 	CR 517. Cleaned up subprojects wrt sb.conf and sc.conf
 * 	[1993/06/02  17:55:42  damon]
 * 
 * Revision 1.12.6.8  1993/05/28  15:42:37  marty
 * 	CR # 558 - Get it running on rios_aix.
 * 	[1993/05/28  15:42:21  marty]
 * 
 * Revision 1.12.6.7  1993/05/27  15:20:20  damon
 * 	CR 548. Change sb_conf_read to use sb_path instead of basedir+sb
 * 	[1993/05/27  15:19:57  damon]
 * 
 * Revision 1.12.6.6  1993/05/14  16:50:36  damon
 * 	CR 518. Changed prj_read and prj_write to take full sb path
 * 	[1993/05/14  16:49:33  damon]
 * 
 * Revision 1.12.6.5  1993/05/13  14:53:00  damon
 * 	CR 521. Now calls sb_conf_resb to adjust sb.conf file
 * 	[1993/05/13  14:52:37  damon]
 * 
 * Revision 1.12.6.4  1993/04/29  16:52:00  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  16:51:47  marty]
 * 
 * Revision 1.12.6.3  1993/04/15  18:26:46  marty
 * 	Added include file ode/interface.h
 * 	[1993/04/15  18:26:28  marty]
 * 
 * Revision 1.12.6.2  1993/02/01  23:19:39  damon
 * 	CR 417. Separated source control and build. Use sb.conf
 * 	[1993/02/01  23:18:47  damon]
 * 
 * Revision 1.12.4.7  1992/12/03  19:08:16  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:37:26  damon]
 * 
 * Revision 1.12.4.6  1992/10/14  20:48:01  damon
 * 	CR 288. Updated call to ui_init
 * 	[1992/10/14  20:45:20  damon]
 * 
 * Revision 1.12.4.5  1992/09/24  18:59:39  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:18:10  gm]
 * 
 * Revision 1.12.4.4  1992/07/26  17:30:12  gm
 * 	Fixed to remove warnings when compiling under OSF/1 R1.1.
 * 	[1992/07/17  20:53:19  gm]
 * 
 * Revision 1.12.4.3  1992/06/16  22:12:02  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:01:43  damon]
 * 
 * Revision 1.12.2.2  1992/03/25  22:47:06  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  22:24:21  damon]
 * 
 * Revision 1.12  1991/12/05  20:53:36  devrcs
 * 	Changed sdm to ode; std_defs.h to odedefs.h
 * 	[91/01/11  11:03:15  randyb]
 * 
 * 	Upgraded to Tools II interface
 * 	[90/12/28  15:32:41  randyb]
 * 
 * 	Corrected arguments for buid_base_dir
 * 	[90/12/10  16:07:04  randyb]
 * 
 * 	Added use of build_list to determine location of new build.
 * 	[90/12/06  16:05:59  randyb]
 * 
 * 	Now uses rc file variables to determine the directory to the builds.
 * 	Added significant recovery code so if the retargeting fails, the
 * 	original rc files and link are put back in place.
 * 	[90/11/09  16:50:59  randyb]
 * 
 * 	Style fixes; linted
 * 	[90/11/07  13:25:25  randyb]
 * 
 * Revision 1.10  90/10/07  21:52:39  devrcs
 * 	Pre-OSF/1 changes.
 * 
 * $EndLog$
 */
/******************************************************************************
**                          Open Software Foundation                         **
**                              Cambridge, MA                                **
**                                May 1990                                   **
*******************************************************************************
**
** Description:
**	This program re-targets a sandbox from one backing tree to another.
**	It also updates the rc files.
**
**  Functions:
**    main (int, ** char) int
**      cmdline_syntax (** char, ** char, ** char, ** char, ** char) int
**        legal_backing_tree (** char, * char, * char) int
**      move_rc_files (* char, * char, * char) int
**      check_makeconf (* char, * char) int
**      change_backing_link (* char, * char, * char, * char, * char) int
**        unmove_rc_files (* char, * char, * char) int
**        complete_recovery (* char, * char, * char, * char) int
**          unmove_rc_files
**      make_rc_files (* char, * char, * char, * char) int
**        create_sb_rc_files (* char, * char, * char, * char, * char,
**			      * char, * char, * char) int
**          complete_recovery
**    print_usage () int
 */

static const char * rcsid =
 "$RCSfile: resb.c,v $ $Revision: 1.12.12.4 $ $Date: 1994/02/03 16:00:14 $";

#include <ode/odedefs.h>
#include <ode/interface.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <ode/builddata.h>
#include <ode/parse_rc_file.h>
#include <ode/project.h>
#include <ode/sandboxes.h>
#include <ode/util.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define  MAX_ARGS	2
#define  BACKUP_TYPE 	".BAK"


    UIINIT init [] = {                      /* initialize the user interface */
      { SB_OP,     1, OVERWRITE, 1, 1, ARGS_OP },
      { ARGS_OP,   1, OVERWRITE, 0, 0, "" }
    };

    const char        * progname = "resb";                /* name of program */
    char * backing_build;
    BOOLEAN ode_sc;
    BOOLEAN ode_build_env;

/*
 * PROTOTYPES
 */
BOOLEAN
validate_rc_files( char *, char *, char *);
void
cmdline_syntax ( char ** sb, char ** sbbase, char ** sb_rcfile, char ** rc_file, char * , char * , char ** );
void
check_makeconf ( char * sb, char * sbbase );
void
legal_backing_tree ( char ** dir, char * default_base,
                             char * sb_rcfile );
void
change_backing_link ( char * , char * , char * , char * , char * );
void
complete_recovery ( char * , char * , char * , char * );

void
main ( int argc, char ** argv )

	/* This function checks the command line arguments and makes
	   sure they are syntactically correct.  This is done using
           the library function ui_init.  If this is correct, the
	   dependencies are checked.  Errors lead to usage messages.
	   If all is okay, the primary procedure is called. */
{
    char        * sb,                                        /* sandbox name */
                * sbbase = NULL,                          /* path to sandbox */
                * sb_rcfile,                         /* sandbox rc file name */
                * rc_file,                                   /* user rc file */
                linkdir [ PATH_LEN ],                 /* sandbox link file */
                link_path [ PATH_LEN ],            /* holds old path of link */
                * targdir;                       /* directory to retarget to */

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );
  cmdline_syntax ( &sb, &sbbase, &sb_rcfile, &rc_file, linkdir, link_path,
                   &targdir );
  if ( ode_build_env ) {
    check_makeconf ( sb, sbbase );
  } /* if */
  exit ( OK );
}                                                                    /* main */


void
cmdline_syntax ( char ** sb, char ** sbbase, char ** sb_rcfile, char ** rc_file, char * linkdir, char * link_path, char ** targdir )

	/* This procedure makes sure the options which are chosen
	   work together legally. */
{
    char      * default_base=NULL;      /* base of default build directory */
    struct rcfile sbconf_rc;
    char * project;
    char * sub_project;
    char * current_dir;

  if ( ! ui_is_set ( ARGS_OP ))
     uquit (  ERROR, TRUE,
           "\tMust include name of backing tree to retarget to.\n" );

  *sb = ui_arg_value ( SB_OP, 1, 1 );
  *sb_rcfile = NULL;
  *rc_file = ui_arg_value ( RC_OP, 1, 1 );
  *targdir = ui_entry_value ( ARGS_OP, 1 );

  if ( current_sb ( sb, sbbase, sb_rcfile, rc_file ) != OK ) {
    if ( *sb != NULL ) {
      ui_print ( VERROR, "Could not find sandbox '%s'.\n", *sb );
    } else {
      ui_print ( VERROR, "Could not find default sandbox.\n" );
    } /* if */
    exit(1);
  } /* if */
  sb_current_dir ( *sb, *sbbase, &current_dir );

  if (current_dir == NULL)
	current_dir = (char *)".";
  prj_read ( sb_full_path ( *sbbase, *sb ), current_dir, &project,
             &sub_project );
  sb_conf_read_chain ( &sbconf_rc, sb_full_path ( *sbbase, *sb ), project,
                       sub_project );
  sb_conf_std ( &sbconf_rc, &project, &backing_build, &ode_sc, &ode_build_env );
  if ( ode_build_env ) {
#ifdef notdef
    if ( default_build ( &default_base, NULL, *sb_rcfile ) == ERROR )
      uquit ( ERROR, FALSE,
  	    "\tcannot continue without default directory info.\n" );
#endif
    ui_print ( VDETAIL, "Project's base directory is: %s.\n", default_base );

    legal_backing_tree ( targdir, default_base, *sb_rcfile );
  } /* if */
  if (validate_rc_files(*targdir, project, sub_project) == TRUE) {
  	change_backing_link ( *sb, *sbbase, *targdir, linkdir, link_path );
  	sb_conf_resb ( *sbbase, *sb, project, sub_project, *targdir );
  } else {
	exit (1);

  }
}                                                          /* cmdline syntax */


void
legal_backing_tree ( char ** dir, char * default_base,
                             char * sb_rcfile )

	/* This function verifies the presence of a legal backing
	   tree.  If it finds one, after looking in both the default
	   base and in the build_list, it creates the space for the
	   name and points dir to it. */

{
    char        newtree [ PATH_LEN ],            /* path to new backing tree */
              * newbase;                      /* points to base of new build */
    struct      stat statbuf;                         /* buffer used by stat */
    struct      rcfile  rc_contents;           /* holds contents of rc files */
    BOOLEAN     justname = FALSE;                            /* misc boolean */

  if ( (char *)strchr ( *dir, SLASH ) == NULL ) {                /* no slash in name */
    concat ( newtree, PATH_LEN, default_base, "/", *dir, NULL );
    justname = TRUE;
  } /* if */
  
  else
    strcpy ( newtree, *dir );

  if (( stat ( newtree, &statbuf ) == ERROR ) ||
      (( statbuf.st_mode & S_IFDIR ) == 0 )) {
    if ( justname ) {
      memset ( (char *)&rc_contents, 0, sizeof ( rc_contents ));
#ifdef notdef
      if ( parse_rc_file ( sb_rcfile, &rc_contents ))
        uquit (  ERROR, FALSE,
	 "\tno build %s in default base; no alternative base.\n", *dir );
#endif
      if (( newbase = build_base_dir ( *dir, &rc_contents,
			 ui_ver_level () >= VDIAG, FALSE )) == NULL )
        uquit (  ERROR, FALSE,
	 	 "\tno backing tree %s in known build locations.\n", *dir );
      else {
	concat ( newtree, PATH_LEN, newbase, "/", *dir, NULL );

	if (( stat ( newtree, &statbuf ) == ERROR ) ||
            (( statbuf.st_mode & S_IFDIR ) == 0 ))
        uquit ( ERROR, FALSE, "\t%s is not a directory.\n", newtree );
      } /* else */
    } /* if */

    else
      uquit ( ERROR, FALSE, "The path %s is not a directory.\n", newtree );
  } /* if */
 
  if (( *dir = (char *) strdup ( newtree )) == NULL )
    uquit ( ERROR, FALSE, "\tunable to strdup space for %s.\n", *dir );
}                                                      /* legal backing tree */

void
check_makeconf ( char * sb, char * sbbase )

	/* This procedure checks to see if the file Makeconf exists.
	   If it does not, it links it through the "link" directory. */
{
    char        mkconf [ PATH_LEN ],                          /* misc string */
                sb_path [ PATH_LEN ];                 /* path and name to sb */

  concat ( sb_path, PATH_LEN, sbbase, "/", sb, "/", MKCONF_LINK, NULL );

  if ( access ( sb_path, F_OK ) == ERROR ) {
    concat ( mkconf, PATH_LEN, "../", LINK_DIR, "/", MKCONF_LINK, NULL );

    if ( ! ui_is_info ()) {
      if ( symlink ( mkconf, sb_path ) == ERROR )
	ui_print ( VFATAL,
		"could not create link, %s, to: %s.\n", sb_path, mkconf);
    } /* if */

    else
      ui_print ( VALWAYS, "Would link %s to backing tree.\n", MKCONF_LINK );

    ui_print ( VDETAIL, "Successfully linked %s to backing tree.\n",
			 MKCONF_LINK );
  } /* if */
}                                                          /* check makeconf */



void
change_backing_link ( char * sb, char * sbbase, char * targdir, char * linkdir, char * link_path )

	/* This procedure changes the backing link. */
{
    int         ln_ct;             /* number of chars returned from readlink */

  concat ( linkdir, PATH_LEN, sbbase, "/", sb, "/", LINK_DIR, NULL );

  if (( ln_ct = readlink ( linkdir, link_path, PATH_LEN )) == ERROR ) {
    *link_path = NUL;
    ui_print ( VWARN, "old link, %s, could not be read.\n", linkdir );
  } /* if */

  else
    link_path [ ln_ct ] = NUL;

  ui_print ( VDEBUG, "Removing %s-> %s.\n", linkdir, link_path );

  if ( ! ui_is_info ()) {
    if ( unlink ( linkdir )) {
      uquit (  ERROR, FALSE,
		   "\tunlink failed on current backing link: %s.\n", linkdir );
    } /* if */

    ui_print ( VDEBUG, "arg is %s\n  symlinking %s to %s.", targdir, targdir,
		  	linkdir );
  							    /* Make new link */
    if ( symlink ( targdir, linkdir ) == ERROR ) {
      complete_recovery ( sb, sbbase, link_path, linkdir );
      uquit (  ERROR, FALSE,
              "\tfailed to link to backing tree\n  %s->%s.\n%s\n",
	       targdir, linkdir,
	      "WARNING: you must create this link manually to continue." );
    } /* if */
  } /* if */

  else
    ui_print ( VALWAYS, "Would link %s to %s.\n", linkdir, targdir );

  ui_print ( VDETAIL, "Linked %s to %s.\n", linkdir, targdir );
}                                                     /* change backing link */


void
complete_recovery ( char * sb, char * sbbase, char * link_path, char * linkdir )

	/* This procedure attempts to completely restore the sandbox
	   to its beginning state.  It is used when the resb has
	   failed. */
{
  ui_print ( VFATAL, "returning sandbox to its original state.\n" );

  if ( *link_path != NUL ) {
    if ( unlink ( linkdir ) == ERROR || symlink ( link_path, linkdir ) == ERROR )
      ui_print ( VWARN, "could not restore %s to %s.\n", linkdir, link_path );
  } /* if */

}                                                       /* complete recovery */

void print_usage (void)

{
  printf ( "USAGE:\n" );
  printf ( "%s new-backing-tree [sb_opts]\n", progname );
  printf ( "     new-backing-tree: the sandbox or build to be backed by.\n" );
  printf ( "     sb_opts:\n" );
  printf ( "       [-sb <sandbox>, -rc <rc_file>, -sb_rc <sb_rcfile>]\n" );
}                                                             /* print usage */

BOOLEAN 
validate_rc_files( 
char * backingtree, 
char * project, 
char * sub_project)
{
char srcdir[MAXPATHLEN];
char rc_filesdir[MAXPATHLEN];
char sbconf[MAXPATHLEN];
int  status, rcstatus, srcstatus;
struct stat statbuf;
struct stat rc_filesbuf;
struct stat srcbuf;

status = stat (backingtree, &statbuf);
if (status != 0) {
	ui_print (VFATAL, "Cannot access %s.\n", backingtree);
	ui_print (VCONT, 
		"Please check to see that this path exists.\n");
	return (FALSE);
}

if (((statbuf.st_mode & S_IFMT) == S_IFDIR) ||
    ((statbuf.st_mode & S_IFMT) == S_IFLNK)) {

	/* Check for rc_files and src directories. */
	concat (srcdir, sizeof(srcdir), backingtree, "/src", NULL);
	concat (rc_filesdir, sizeof(rc_filesdir), backingtree, 
		"/rc_files", NULL);
	rcstatus = stat (rc_filesdir, &rc_filesbuf);
	srcstatus = stat (srcdir, &srcbuf);

	if ((rcstatus != 0) && (srcstatus != 0)) {
		/* Both are missing ... error */
		ui_print (VFATAL, 
			"The backing tree %s is invalid.\n", backingtree);
		ui_print (VCONT, 
			"The subdirectories 'rc_files' and 'src' are missing from this tree.\n");
		return (FALSE);
	}
	if (rcstatus != 0) {
		ui_print (VFATAL, 
			"The backing tree %s is invalid.\n", backingtree);
		ui_print (VCONT, 
			"The subdirectory 'rc_files' is missing from this tree.\n");
		return (FALSE);
	}
	if (srcstatus != 0) {
		ui_print (VFATAL, 
			"The backing tree %s is invalid.\n", backingtree);
		ui_print (VCONT, 
			"The subdirectory 'src' is missing from this tree.\n");
		return (FALSE);
	}
	
	/* Check for sb.conf file */
	concat (sbconf, sizeof (sbconf), rc_filesdir, "/", project, "/sb.conf",
		NULL);
	status = stat (sbconf, &statbuf);
	if (status != 0) {
		concat (sbconf, sizeof (sbconf), rc_filesdir, 
			"/", project, "/", sub_project, "/sb.conf", NULL);
		status = stat (sbconf, &statbuf);
		if (status != 0) {
			ui_print (VFATAL, 
				"Invalid backing tree configuration.\n");
			ui_print (VCONT,
				"Cannot access the file 'sb.conf' in the backing tree %s.\n", backingtree);
			return (FALSE);
		} 

	} 
	return (TRUE);
} else {
	/* Backing tree path given is wrong type of file. */
	ui_print (VFATAL, 
		"The path %s must be a directory or a link to a directory.\n", 
		backingtree);
	ui_print (VCONT, "This does not appear to be a valid backing tree.\n");
	return (FALSE);
}
return (TRUE);
}
