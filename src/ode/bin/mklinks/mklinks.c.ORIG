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
 * $Log: mklinks.c,v $
 * Revision 1.12.14.11  1994/03/22  21:35:00  marty
 * 	CR # 1097 - When creating subdirectories, only call mkdir() when
 * 	path components need to be created.
 * 	[1994/03/22  21:34:34  marty]
 *
 * Revision 1.12.14.10  1994/01/25  17:39:07  marty
 * 	CR # 1004 - mklinks -sb sbox now works if sbox is not your
 * 	default sandbox.
 * 	[1994/01/25  17:38:53  marty]
 * 
 * Revision 1.12.14.9  1994/01/11  20:31:26  root
 * 	CR # 540 - Fix compilation problems on hp700_hpux.
 * 	[1994/01/11  20:30:56  root]
 * 
 * Revision 1.12.14.8  1993/12/31  17:47:06  marty
 * 	CR # 962 - When using -link_from option with a relative pathname, mklinks
 * 	now expands to a full pathname.
 * 	[1993/12/31  17:46:39  marty]
 * 
 * Revision 1.12.14.7  1993/12/17  20:53:10  marty
 * 	CR # 929 - mklinks shouldn't chop characters out of pathname.
 * 	[1993/12/17  20:52:56  marty]
 * 
 * Revision 1.12.14.6  1993/12/15  01:39:30  marty
 * 	CR # 70 - mklinks -copy now preseves the execution bits of files copied.
 * 	[1993/12/15  01:39:06  marty]
 * 
 * Revision 1.12.14.5  1993/12/15  01:27:16  marty
 * 	CR # 108 - "-query" should be done on a per file basis.
 * 	[1993/12/15  01:26:58  marty]
 * 
 * Revision 1.12.14.4  1993/12/14  23:56:49  marty
 * 	CR # 904 - mklinks now uses 'mkdir -p' to create directories up to the target
 * 	directory.
 * 	[1993/12/14  23:56:31  marty]
 * 
 * Revision 1.12.14.3  1993/12/14  22:18:11  marty
 * 	CR # 876 - mklinks now canonicalizes pathnames of files it creates.
 * 	[1993/12/14  22:17:56  marty]
 * 
 * Revision 1.12.14.2  1993/12/08  22:14:52  marty
 * 	CR # 840 - Change name of exists to f_exists.
 * 	[1993/12/08  22:14:37  marty]
 * 
 * Revision 1.12.14.1  1993/11/29  22:10:59  marty
 * 	CR # 736 - mklinks no longer gets confused when sandboxes are referenced through
 * 	symbolic links.
 * 	[1993/11/29  22:01:01  marty]
 * 
 * Revision 1.12.11.5  1993/11/15  22:05:20  marty
 * 	CR # 811 - mklinks now differentiates between files that are
 * 	checked out in a sandbox and those that do not exista t all in the
 * 	backing chain.
 * 	[1993/11/15  22:04:42  marty]
 * 
 * Revision 1.12.11.4  1993/11/10  18:46:19  root
 * 	CR 463. Pedantic changes
 * 	[1993/11/10  18:45:40  root]
 * 
 * Revision 1.12.11.3  1993/11/04  16:42:46  damon
 * 	CR 463. More pedantic
 * 	[1993/11/04  16:42:37  damon]
 * 
 * Revision 1.12.11.2  1993/11/03  16:04:41  marty
 * 	CR # 684 - mklinks now asks verification before processing
 * 	the list of files in the backing chain.
 * 	[1993/11/03  16:04:25  marty]
 * 
 * Revision 1.12.11.1  1993/11/03  15:35:25  marty
 * 	CR # 737 - mklinks now complains if it can't find the specified files
 * 	in the backing chain.
 * 	[1993/11/03  15:34:44  marty]
 * 
 * Revision 1.12.9.6  1993/09/22  16:39:27  marty
 * 	CR # 677 - The -linkfrom and -linkto options now  generate files in correct path.
 * 	[1993/09/22  16:39:06  marty]
 * 
 * Revision 1.12.9.5  1993/09/08  13:21:28  root
 * 	cr # 652 - Get it to build on rios_aix
 * 	[1993/09/08  13:21:09  root]
 * 
 * Revision 1.12.9.4  1993/09/07  19:40:26  marty
 * 	CR # 652 - fix to memory overwrite bug that prohibits linking from the
 * 	second level directory.
 * 	[1993/09/07  19:40:04  marty]
 * 
 * Revision 1.12.9.3  1993/09/03  16:22:51  marty
 * 	CR # 651 - Null terminate string returned by readlink();
 * 	[1993/09/03  16:22:32  marty]
 * 
 * Revision 1.12.9.2  1993/09/02  16:26:12  root
 * 	CR # 642 - Type cast for rios_aix
 * 	[1993/09/02  16:25:53  root]
 * 
 * Revision 1.12.9.1  1993/08/31  20:49:18  marty
 * 	CR # 642 - Fix -link_from and -link_to options.
 * 	[1993/08/31  20:48:59  marty]
 * 
 * Revision 1.12.7.14  1993/06/08  21:46:27  root
 * 	CR # 581 - Initialize 'next' field on backing chain list.
 * 	[1993/06/08  21:46:10  root]
 * 
 * Revision 1.12.7.13  1993/06/08  19:44:54  marty
 * 	CR # 283 - mklinks -copy -over now overwrites links AND sets permissions to 444.
 * 	[1993/06/08  19:44:37  marty]
 * 
 * Revision 1.12.7.12  1993/05/28  14:20:08  marty
 * 	CR # 558 - Get it building on rios_aix.
 * 	[1993/05/28  14:19:56  marty]
 * 
 * Revision 1.12.7.11  1993/05/27  17:31:27  marty
 * 	CR # 544 - core dumps on pmax_osf1 were due to variables not being
 * 	initialized before calling current_sb().
 * 	[1993/05/27  17:30:53  marty]
 * 
 * Revision 1.12.7.10  1993/05/25  15:18:57  marty
 * 	CR # 540 - mklinks now sets correct permissions with "-copy" AND
 * 	it now works with first level directory.
 * 	[1993/05/25  15:18:39  marty]
 * 
 * Revision 1.12.7.9  1993/05/20  13:52:45  marty
 * 	CR # 520
 * 	[1993/05/20  13:52:26  marty]
 * 
 * 	CR # 520 - mklinks now goes through "link" file in sandbox.
 * 	[1993/05/20  13:18:34  marty]
 * 
 * Revision 1.12.7.8  1993/05/17  17:35:35  marty
 * 	CR # 510 - Fix typo.
 * 	[1993/05/17  17:34:59  marty]
 * 
 * Revision 1.12.7.7  1993/05/07  20:48:55  marty
 * 	CR # 510 - Change -refresh option to -norefresh.  Links will
 * 	be refreshed by default.
 * 	[1993/05/07  20:48:39  marty]
 * 
 * Revision 1.12.7.6  1993/04/29  17:25:17  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  17:25:01  marty]
 * 
 * Revision 1.12.7.5  1993/04/15  17:37:17  marty
 * 	Add include files ode/interface.h and dirent.h
 * 	[1993/04/15  17:36:59  marty]
 * 
 * Revision 1.12.7.4  1993/03/31  16:18:45  marty
 * 	Query the user before creating any links.
 * 	[1993/03/31  16:17:07  marty]
 * 
 * Revision 1.12.7.3  1993/02/03  19:16:11  marty
 * 	Cleanup
 * 	[1993/02/03  15:43:42  marty]
 * 
 * 	more code.
 * 	[1993/02/02  22:29:29  marty]
 * 
 * 	Reorganized a little.
 * 	[1993/02/02  20:19:12  marty]
 * 
 * 	Added -refresh option.
 * 	[1993/02/02  17:17:14  marty]
 * 
 * 	more code
 * 	[1993/02/01  19:06:45  marty]
 * 
 * 	more code
 * 	[1993/01/28  23:23:00  marty]
 * 
 * 	More code.
 * 	[1993/01/28  22:37:04  marty]
 * 
 * 	Fixing mklinks to work for backing chains.
 * 	[1993/01/28  15:35:46  marty]
 * 
 * Revision 1.12.7.2  1993/01/13  16:43:20  damon
 * 	CR 382. Removed NO_DIRENT and MAXBSIZE
 * 	[1993/01/05  20:47:34  damon]
 * 
 * Revision 1.12.4.7  1992/12/03  19:07:45  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:36:58  damon]
 * 
 * Revision 1.12.4.6  1992/11/13  15:19:58  root
 * 	Removed malloc declaration
 * 	[1992/11/13  14:58:24  root]
 * 
 * Revision 1.12.4.5  1992/10/14  20:47:45  damon
 * 	CR 288. Updated call to ui_init
 * 	[1992/10/14  20:45:09  damon]
 * 
 * Revision 1.12.4.4  1992/09/24  18:58:49  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:17:36  gm]
 * 
 * Revision 1.12.4.3  1992/07/26  17:29:48  gm
 * 	Fixed to remove warnings when compiling under OSF/1 R1.1.
 * 	[1992/07/17  20:48:23  gm]
 * 
 * Revision 1.12.4.2  1992/06/12  20:00:37  damon
 * 	Synched with 2.1.1
 * 	[1992/06/12  15:21:04  damon]
 * 
 * Revision 1.12.2.2  1992/03/25  22:46:24  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  22:10:41  damon]
 * 
 * Revision 1.12  1991/12/05  20:45:48  devrcs
 * 	Changed printf from utimes to utime for NO_UTIMES.
 * 	[91/09/04  12:54:17  damon]
 * 
 * 	Added code to deal with the absence of the utimes call.
 * 	[91/02/14  17:09:40  damon]
 * 
 * 	Fixed string allocation problem caused by improper use of salloc().
 * 	[91/01/30  13:49:45  damon]
 * 
 * 	Changed sdm to ode; std_defs.h to odedefs.h
 * 	[91/01/11  10:59:36  randyb]
 * 
 * 	Upgraded to Tools II interface
 * 	[91/01/07  09:28:33  randyb]
 * 
 * 	Put in the -open option so -copy can be forced to overwrite
 * 	existing files.
 * 	Added support for the -debug option.
 * 	[90/11/07  16:54:05  randyb]
 * 
 * Revision 1.10  90/10/07  21:51:41  devrcs
 * 	Added -debug option to reduce the amount of verbage when the -v is used.
 * 	This does not solve the entire problem, however, as this option needs
 * 	to be passed to the library routine that makes links.
 * 	[90/10/03  13:01:59  randyb]
 * 
 * Revision 1.9  90/09/23  16:55:49  devrcs
 * 	Pre-OSF/1 changes.
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
**	This program makes the links or copies of files in the backing
**	build to sandboxes.
**
 */

static const char * rcsid =
 "$RCSfile: mklinks.c,v $ $Revision: 1.12.14.11 $ $Date: 1994/03/22 21:35:00 $";

#include <ode/interface.h>
#include <ode/odedefs.h>
#include <ode/sandboxes.h>
#include <ode/util.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/time.h>
#include <fcntl.h>
#include <utime.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ode/misc.h>

/*  Defines for getmode() */
#define USER    05700
#define GROUP   02070
#define OTHER   00007
#define ALL     07777
#define READ_MASK 00444
#define WRITE_MASK 00222
#define EXECUTE 00111
#define SETID   06000
#define SETUID  04000
#define SETGID  02000
#define STICKY  01000
/* end of defines for getmode() */
int    usflag;
mode_t defmode = S_IRWXU | S_IRWXG | S_IRWXO;
mode_t mask;
mode_t mode;
char *modestr;
char *msptr;
int
Mkdir (char *, mode_t);
int 
mkdirp (char *);
void
report (char *);
int
intmode(char *);
int 
who (void);
char
m_op(void);
int
perm(void);
int
getmode(void);

#  define  CMP_OP   	"-cmp"
#  define  LINK_FR_OP  	"-link_from"
#  define  LINK_TO_OP  	"-link_to"
#  define  NORECURSE_OP "-norecurse"
#  define  NOREFRESH_OP   "-norefresh"
#  define  OVER_OP   	"-over"
#  define  QUERY_OP   	"-query"
#  define  MAX_ARGS	10
#  define  TRUE		1
#  define  FALSE	0

    UIINIT init [] = {
      { COPY_OP,      1, OVERWRITE, 0, 0, "" },
      { OVER_OP,      1, OVERWRITE, 0, 0, "" },
      { NORECURSE_OP, 1, OVERWRITE, 0, 0, "" },
      { NOREFRESH_OP,   1, OVERWRITE, 0, 0, "" }, 
      { CMP_OP,       1, OVERWRITE, 0, 0, "" },
      { QUERY_OP,     1, OVERWRITE, 0, 0, "" },
      { LINK_FR_OP,   1, OVERWRITE, 1, 1, ARGS_OP },
      { LINK_TO_OP,   1, OVERWRITE, 1, 1, ARGS_OP },
      { SB_OP,        1, OVERWRITE, 1, 1, ARGS_OP },
      { ARGS_OP,      1, OVERWRITE, 0, 0, "" } 
    };

    /* Global variables used to cut down calls to user
       interface routines. */
    int		norefresh_op,		/* -norefresh option 	*/
		copy_op,		/* -copy option		*/
		norecurse_op,		/* -norecurse option	*/
		link_fr_op,		/* -link_from option	*/
		overwrite_op;		/* -over option		*/
    char      * link_to_entry;		/* Value given with
					   -link_to option	*/
    char      * link_from_entry;	/* Value given with
					   -link_from option	*/
    struct chainlist *chain;		/* The backing chain.   */
    char *sandbox_base;			/* The users sandbox    */
    int  query;

    BOOLEAN files_exists_in_bt = FALSE;

   /* This structure represents a list of each directory
      in the backing chain. */
   struct chainlist {
	char *path;			
	char *link_levels;
	struct chainlist *next;
   };

   /* This structure is used to represent all files and directories in
      the backing chain. */ 
   struct dir_entry {
	char *name;			/* Name of this file/directory in the 
					  tree.                               */
	struct chainlist *chain_entry;	/* If it's a file,  this is a pointer  
					   to the backing chain structure     
					   it should be linked to.  
						                       */
	int file_type;			/* File type (i.e. S_IFLNK, 
					   S_IFREG, ...)                      */
	struct dir_entry *sub_dir_entries; /* If it's a directory, this is a 
					      list of its sub-directories.    */
	struct dir_entry *files;	/* If it's a directory, this is a list 
					   of its files.		      */
	struct dir_entry *next;		
   };

    struct sandbox_env {
            const char * sandboxdir;	/* string with sandbox and basedir    */
            const char * reldir;        /* holds relative directory           */
		 const char * file;		/* The file/directory to link.        */
    };

/*
 * PROTOTYPES
 */
void
cmdline_syntax (void);
struct sandbox_env *get_sb_loc(void); /* Get sandbox and file pathnames.    */
void
verify (char * link_from, char * link_to);
void
create_files (struct dir_entry * node, const char * reldir);
void
update_tree (struct dir_entry * node, const char * base, const char * reldir);
void
get_lists(struct dir_entry * node, const char * base, const char * rel_path);
    struct dir_entry *talloc(void);	/* Space allocation  	              */
    char *head(const char * );         	/* returns directory component of 
					   pathname                           */
    char *tail(const char * );		/* returns file component of pathname */
    struct chainlist *backing_chain(const char * );  /* returns backing chain              */
    struct dir_entry *newnode(const char *);	/* Creats nodes for file/directories 
					   in list                            */
struct dir_entry *
populate_tree (struct dir_entry * tree, const char * base, const char * reldir,
               const char * file);
/* Builds up list of all files in 
					   backing chain.                     */
int
symlink_file ( char * , char * );       /* Create symbolic link.              */
    int    copy_file (char *, char *);	/* Copy file to sandbox.              */
    int    cmp_files (char *, char *);	/* Compare files 	              */
void 
get_current_directory (char *, char []);


    const char 	* progname = "mklinks";

void
main ( int argc, char ** argv )
{
    char	sandbox_to_link[ PATH_LEN ],
		current_dir [ MAXPATHLEN ],
		backing_build[ PATH_LEN ];

    struct dir_entry *tree;  /* Represents the top of the generated tree. */
    struct sandbox_env *sb;

   /* Initialize user interface and parse the command line. */
   ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

   /* Check for correct combination of command line arguments. */
   cmdline_syntax ();  

   /* Set commandline options to global variables (for faster access). */
   norefresh_op 	= ui_is_set(NOREFRESH_OP);
   norecurse_op = ui_is_set(NORECURSE_OP);
   copy_op	= ui_is_set(COPY_OP);
   overwrite_op = ui_is_set(OVER_OP);
   link_fr_op   = ui_is_set(LINK_FR_OP);
   link_to_entry = ui_arg_value (LINK_TO_OP, 1, 1);
   link_from_entry = ui_arg_value (LINK_FR_OP, 1, 1);
   query = ui_is_set ( QUERY_OP );

   /* Get sandbox info (i.e. sandbox location, relative directory in sandbox, 
      and the file to link */
   sb = get_sb_loc();

   if (link_fr_op) {
	if ( (link_from_entry != NULL) && (*link_from_entry != '/') ) {
		getcwd (current_dir, sizeof(current_dir));
		strcat (current_dir, "/");
		strcat (current_dir, link_from_entry);
		sandbox_base = strdup (current_dir);
	} else
		sandbox_base = strdup (link_from_entry);
   } else
   	sandbox_base = strdup((char *)sb->sandboxdir);

   /* Get the backing chain. */
   chain = backing_chain(sb->sandboxdir);

   concat (backing_build, sizeof(backing_build), strdup (chain->path), "/",
	sb->reldir,  "/", sb->file, NULL);
   concat (sandbox_to_link, sizeof(sandbox_to_link), sb->sandboxdir, "/src/",
	sb->reldir, "/", sb->file, NULL);
   
   if (link_fr_op)
	verify (link_from_entry, link_to_entry);
   else
	verify (backing_build, sandbox_to_link);

   tree = NULL; 

   /* Build up the list of files in the backing chain to link to. */
   while ((chain != NULL) && (chain->path != NULL)) {
	tree = populate_tree(tree, chain->path, sb->reldir, sb->file); 
	chain = chain->next; 
   }

   /* Copy/link all files built up from the backing chain. */
   if (tree != NULL) {
	create_files (tree, sb->reldir);
   } else {
	if (files_exists_in_bt == FALSE)
		ui_print (VWARN, 
			"Cannot find file '%s' in the backing chain.\n",
			ui_entry_value ( ARGS_OP, 1 ));
   }

   exit( OK );
}                                                                    /* main */

struct sandbox_env *
get_sb_loc(void)
{
   struct sandbox_env *sb_files;
   char curdir [ PATH_LEN ];
   char * sb = NULL, 
	* basedir = NULL,
	* sb_rcfile = NULL,
	* rc_file = NULL,
	  sandboxdir [ PATH_LEN ],
	* directory = NULL,
	* curpath = NULL;

   sb_files = (struct sandbox_env *)malloc(sizeof (struct sandbox_env));
   sb_files->sandboxdir = NULL;
   sb_files->reldir = NULL;
   sb_files->file = NULL;

   if (ui_is_set ( LINK_FR_OP )) {
	/*  Linking directories outside of sandbox.  */
	sb_files->file = ".";
	sb_files->reldir = "."; 
	sb_files->sandboxdir = link_to_entry;
   } else {

	if (ui_is_set ( SB_OP ))
		sb = ui_arg_value ( SB_OP, 1, 1 );

	/* linking files in this sandbox to the backing chain. */
  	if ( current_sb ( &sb, &basedir, &sb_rcfile, &rc_file ) != OK )
    		uquit ( ERROR, FALSE, "could not get current sandbox information.\n" );
  	concat ( sandboxdir, PATH_LEN, basedir, "/", sb, NULL );

	get_current_directory ((char *)&curdir, sandboxdir);

    	if ( strncmp ( sandboxdir, curdir, strlen ( sandboxdir )) != OK )
      		uquit ( ERROR, TRUE,
	 	   "directory given is relative; current directory not in sandbox.\n" );
        if (strcmp (&curdir [ strlen ( sandboxdir )  ], "/src") == 0) 
		curpath = "";
	else
   		curpath = &curdir [ strlen ( sandboxdir ) + 5 ];

  	if ( *(directory = ui_entry_value ( ARGS_OP, 1 )) == '/' ) {
		/* Absolute pathnames cause all processing to be
		   done from the base of the sandbox. */
    		sb_files->file = strdup(directory);
    		sb_files->reldir = "";
  	} else {
		/* Relative pathnames cause all processing to be done from the
		   current directory. */
		if (strcmp(directory, ".") == 0) {
			sb_files->file =  strdup(tail(curpath));
			sb_files->reldir = head(curpath);
		} else {
    			sb_files->file = strdup(directory);
    			sb_files->reldir= strdup(curpath);
		}
  	} 
  	sb_files->sandboxdir = strdup(sandboxdir);
   }
   return (sb_files);
}


int 
file_type (const char * base, const char * reldir, const char * file)
{
   char file_path[PATH_LEN];
   struct stat statbuf;
	
   concat (file_path, sizeof(file_path), base, "/", reldir, "/", file, NULL);

   lstat(file_path, &statbuf);
   return (statbuf.st_mode & S_IFMT);
}

int
f_exists(char * file_path)
{
   struct stat statbuf;
   int status;
   status = lstat(file_path, &statbuf) ;

   if ((status == -1) || ( (statbuf.st_mode & S_IFMT) == S_IFLNK) ) 
	return (FALSE);
   else
	return (TRUE);
}


int
search_sandbox (const char * reldir, const char * file)
{
   char file_path[PATH_LEN];
   char to_dir[PATH_LEN];

   if (link_fr_op) {
        concat(to_dir, sizeof(to_dir), link_to_entry, "/", NULL);
   } else {
        concat(to_dir, sizeof(to_dir), sandbox_base, "/src/", NULL);
   }

   concat (file_path, sizeof(file_path), to_dir, reldir, "/", file, NULL);
   if (f_exists(file_path) == TRUE) {
	if ((copy_op) && (overwrite_op)) 
		/* Force file to be overwritten in sandbox. */
		return (FALSE);
	else
		return (TRUE);
   } else
   	return (FALSE);
}

struct dir_entry *
populate_tree (struct dir_entry * tree, const char * base, const char * reldir,
               const char * file)
{
	char file_path[PATH_LEN];
	int  ft;
	concat (file_path, sizeof(file_path), base, "/", reldir, "/", file, NULL);
	if (f_exists (file_path) == FALSE)
		return(tree);

	if (tree == NULL) {

		if ( (ft = file_type(base, reldir, file)) == S_IFREG) {
			files_exists_in_bt = TRUE;
			if (search_sandbox(reldir, file) == FALSE) {
				tree = newnode(file); 
				tree->chain_entry = chain; 
				tree->file_type = ft;
			} else
				return(tree);
		} else {
			tree = newnode(file); 
			tree->file_type = ft;
		}
	}
	update_tree (tree, base, reldir);

	return(tree);
}

void
create_file(char * file_to_create, char * file_from_backing_tree)
{
	char tmp_buf[MAXPATHLEN];
	char to_file[MAXPATHLEN];
	char from_file[MAXPATHLEN];
	char *tmp;

	strcpy (tmp_buf, file_to_create);
        canonicalize(tmp_buf, "", to_file, sizeof(to_file));
	strcpy (tmp_buf, file_from_backing_tree);
        canonicalize(tmp_buf, "", from_file, sizeof(from_file));

	concat (tmp_buf, sizeof(tmp_buf), head(to_file), "/.", NULL);
	tmp = strdup (tmp_buf);
   	Mkdir (tmp, (mode_t) S_IRWXU | S_IRGRP | S_IXGRP);
  	if (copy_op)
		copy_file (from_file, to_file);
	else
		symlink_file (from_file, to_file);

}

void
create_files (struct dir_entry * node, const char * reldir) 
{
	char new_reldir[PATH_LEN];
	struct dir_entry *subdirs;
	struct dir_entry *i;
	struct chainlist *ptr;
	char from_file[PATH_LEN];
	char to_file[PATH_LEN];
	char to_dir[PATH_LEN];

   
   if (link_fr_op) {
	concat(to_dir, sizeof(to_dir), link_to_entry, "/", NULL); 
   } else {
	concat(to_dir, sizeof(to_dir), sandbox_base, "/src/", NULL); 
   }

   /* Create path to files. */
   concat (to_file, sizeof(to_file), to_dir, reldir, "/", node->name, NULL);

   if (node->file_type == S_IFREG) { 
	ptr = node->chain_entry;
	concat (from_file, sizeof(from_file), sandbox_base, "/", ptr->link_levels, "/src/", reldir, "/", node->name, NULL);
	create_file (to_file, from_file);
	return;
   } 


   /* Process all the files in the current directory. */
   for (i = node->files ; i != NULL; i=i->next) {

   	concat (to_file, sizeof(to_file), to_dir,  
		reldir, "/", node->name, "/", i->name, NULL);
	ptr = i->chain_entry;
	concat (from_file, sizeof(from_file), sandbox_base, "/", 
		ptr->link_levels, "/src/", NULL);
	if ((reldir != NULL) && (strcmp(reldir, "/") != 0) &&
	    (strcmp(reldir, "/.") != 0 ) && (strcmp(reldir, "./") != 0 ) &&
	    (strcmp(reldir, "") != 0)) {
		strcat(from_file, "/");
		strcat(from_file, reldir);
	}
	if ((node->name != NULL) && (strcmp(node->name, "") != 0) &&
	    (strcmp(node->name, "/") != 0) &&
	    (strcmp(node->name, "/.") != 0 ) && (strcmp(node->name, "./") != 0 )) {
		strcat(from_file, "/");
		strcat(from_file, node->name);
	}
	if ((i->name != NULL) && (strcmp(i->name, "") != 0)) {
		strcat(from_file, "/");
		strcat(from_file, i->name);
	}
  	ui_print ( VDEBUG, "linking %s to %s\n", to_file, from_file);
	create_file (to_file, from_file);
   }

   if ((reldir == NULL) || (strcmp(reldir, "") == 0 ))
       	concat (new_reldir, sizeof(new_reldir), "/", node->name, NULL);
   else
       	concat (new_reldir, sizeof(new_reldir), reldir, "/", node->name, NULL);
		
   /* Process subdirectories. */
   subdirs = node->sub_dir_entries;
   while (subdirs != NULL) {
	create_files(subdirs, new_reldir);
	subdirs = subdirs->next;
   }
}

void
update_tree (struct dir_entry * node, const char * base, const char * reldir)
{
	char new_reldir[PATH_LEN];
	struct dir_entry *subdirs;

	if (file_type(base, reldir, node->name) == S_IFREG)
		return;

	/* "node" represents a directory node.
	   Update the list of files and 
	   subdirectories for this node. */
	get_lists (node, base, reldir);

	if (norecurse_op)
		return;

	concat (new_reldir, sizeof(new_reldir), reldir, "/", node->name, NULL);

	/* Iterate through each subdirectory updating its tree. */
	subdirs = node->sub_dir_entries;
	while (subdirs != NULL) {
		update_tree(subdirs, base, new_reldir);
		subdirs = subdirs->next;
	}
}

struct dir_entry *
getentries(const char * base, const char * reldir, const char * file)
{
   DIR           *d;         /* for reading directory */
   register struct dirent *dp; /* entry in directory */
   char file_path[PATH_LEN];
   struct dir_entry * head_dir = NULL;
   struct dir_entry * tail_dir = NULL;
   struct dir_entry * thisnode;

   concat (file_path, sizeof(file_path), base, "/", reldir, "/", file, NULL);
   if (f_exists(file_path) == FALSE)
	return ((struct dir_entry *) NULL);

   d = opendir (file_path);

   if (d == (DIR *) NULL)
	return ((struct dir_entry *) NULL);

   while ((dp = readdir (d)) != (struct dirent *) NULL) {
	if ((strcmp(dp->d_name, ".") == 0) ||
	    (strcmp(dp->d_name, "..") == 0))
		continue;
	thisnode = newnode(dp->d_name);
	if (head_dir == NULL) {
		head_dir = thisnode;
		tail_dir = thisnode;
	} else {
		tail_dir->next = thisnode;
		tail_dir = tail_dir->next;
	}
   }
   (void) closedir(d);
   return (head_dir);

}

void
get_lists(struct dir_entry * node, const char * base, const char * rel_path)
{

	struct dir_entry * sub_dir_head,
	 		 * sub_dir_tail,
	 		 * i,
	 		 * files,
	 		 * file_list_head,
	 		 * file_list_tail,
	 		 * thisnode;
	int found;
	char new_rel_path[PATH_LEN];

	/* Set ptr to head of subdirectory list. */
	sub_dir_head = node->sub_dir_entries;

	/* Set ptr to tail of subdirectory list. */
	for (sub_dir_tail = node->sub_dir_entries; 
		(sub_dir_tail != NULL) && (sub_dir_tail->next != NULL);
		sub_dir_tail = sub_dir_tail->next);
	file_list_head = node->files;
	for (file_list_tail = node->files;
		(file_list_tail != NULL) && (file_list_tail->next != NULL);
		file_list_tail = file_list_tail->next);

	/*  Get a list of all the files in this directory. */
	files = (struct dir_entry *)getentries(base, rel_path, node->name);

	/* Now need to refer to subdirectories */
	concat (new_rel_path, sizeof(new_rel_path), rel_path, "/", node->name, NULL);

	while (files != NULL) {
		if (file_type(base, new_rel_path, files->name) == S_IFDIR) {
			
			/* Create a node and add it to the list 
			   if it is not already there. */

			if (sub_dir_head == NULL) {
				thisnode = newnode(files->name);
				thisnode->file_type = S_IFDIR;
				node->sub_dir_entries = thisnode;
				sub_dir_head = thisnode;
				sub_dir_tail = thisnode;
			} else {
				found = FALSE;
				for (i = sub_dir_head; (i != NULL) && (found != TRUE); i = i->next) {
					if (strcmp(i->name, files->name) == 0) {
						found = TRUE;
					}
				}
				if (found == FALSE) { 
					thisnode = newnode(files->name);
					thisnode->file_type = S_IFDIR;
					sub_dir_tail->next = thisnode;
					sub_dir_tail = thisnode;
				}
			}
		} else { /* Update file list */
			files_exists_in_bt = TRUE;
			if (search_sandbox(new_rel_path, files->name) == FALSE) {
			   if (file_list_head == NULL) {
					thisnode = newnode(files->name);
					thisnode->file_type = S_IFREG;
					thisnode->chain_entry = chain;
					node->files = thisnode;
					file_list_head = thisnode;
					file_list_tail = thisnode;
			   } else {
				found = FALSE;
				for (i = file_list_head; (i != NULL) && (found != TRUE); i = i->next) {
                                        if (strcmp(i->name, files->name) == 0) {
                                                found = TRUE;
                                        }
                                }
                                if (found == FALSE) { 
                                        thisnode = newnode(files->name);
					thisnode->file_type = S_IFREG;
					thisnode->chain_entry = chain; 
                                        file_list_tail->next = thisnode;
                                        file_list_tail = thisnode;
                                }

			   }
			}
		}
		files = files->next;
	}
}

struct dir_entry *
newnode(const char * name)
{
	struct dir_entry *node;
	
	node = talloc();
	node->next = NULL;
	node->chain_entry = NULL;
	node->files = NULL;
	node->name = strdup((char *)name);
	node->sub_dir_entries = NULL;
	return (node);
}

struct dir_entry *
talloc(void)
{
	return((struct dir_entry *) malloc(sizeof(struct dir_entry)));
}


int symlink_file ( char * src, char * dst )
{
  char buf[MAXPATHLEN];

  if (query) {
	(void) concat (buf, sizeof(buf), "Link file ", src, " ?", NULL);
	if (!getbool(buf, TRUE))
		return(OK);
  }
  if ( symlink ( src, dst ) < 0 ) {
    if (!norefresh_op) {
	unlink (dst);
	if ( symlink ( src, dst ) < 0 ) {
		ui_print (VWARN, "symlink: %s '%s', cannot link file.\n", strerror(errno), dst);
    		return( ERROR );
	}

    } else {
	ui_print (VWARN, "symlink: %s '%s', cannot overwrite file with the -norefresh option.\n", strerror(errno), dst);
    	return( ERROR );
    } 
  } 
  return ( OK );
}                                                                 /* symlink */


void
cmdline_syntax (void)

	/* This procedure makes sure all the options agree with each
	   other. */

{
  if (( ui_is_set ( LINK_FR_OP ) && ! ui_is_set ( LINK_TO_OP )) ||
      ( ! ui_is_set ( LINK_FR_OP ) && ui_is_set ( LINK_TO_OP )))
    	uquit ( ERROR, TRUE, "\toptions %s and %s must be set together.\n",
	       		    LINK_FR_OP, LINK_TO_OP );

  if ( ui_is_set ( OVER_OP )) {
    	if ( ! ui_is_set ( COPY_OP ))
      		uquit ( ERROR, TRUE, 
			"\t%s option must be set to used the %s option.\n",
	      		COPY_OP, OVER_OP );
  } 

  if ( ui_is_set ( LINK_FR_OP ) && ui_is_set ( LINK_TO_OP )) {
    	if ( ui_is_set ( ARGS_OP ))
      		uquit ( ERROR, TRUE,
	      	"\tCannot set options %s and %s and still give directory.\n",
	       	 LINK_FR_OP, LINK_TO_OP );
       
  } else {
    	if ( ! ui_is_set ( ARGS_OP ))
      		uquit ( ERROR, TRUE,
	      "\tdirectory entry or the -link_ options required.\n" );
  } 


}  /* cmdline syntax */



int copy_file ( char * src, char * dst )
{
    struct 	stat st,
		     src_statbuf,
		     statbuf;
    struct utimbuf tv;
    int 	  fd1,
		  fd2;
    char buf[MAXPATHLEN];

  if (query) {
	(void) concat (buf, sizeof(buf), "Copy file ", src, " ?", NULL);
	if (!getbool(buf, TRUE))
		return (OK);
  }
  if ((fd1 = open(src, O_RDONLY, 0)) < 0) {
    ui_print ( VFATAL, "open %s: %s\n", src, strerror(errno));
    return( ERROR );
  } /* if */

  if (fstat(fd1, &st) < 0) {
    ui_print ( VFATAL, "fstat %s: %s\n", src, strerror(errno));
    (void) close(fd1);
    return( ERROR );
  } /* if */

  lstat (src, &src_statbuf);
  if (lstat (dst, &statbuf) == 0) {
	/* File already exists. */
	if ((statbuf.st_mode & S_IFMT) == S_IFLNK) {
		if (overwrite_op) {
			/* Overwrite links. */
			unlink(dst);
		} else
			return( ERROR );
	} else if ((statbuf.st_mode & S_IFMT) == S_IFREG) {
		if (overwrite_op) {
			chmod (dst, statbuf.st_mode | S_IWUSR);
		}
	}
  } else  {
	lstat (src, &statbuf);
  }
  if ((fd2 = open(dst, O_WRONLY|O_TRUNC|O_CREAT, 0666)) < 0) {
    ui_print ( VFATAL, "open %s: %s\n", dst, strerror(errno));
    (void) close(fd1);
    return( ERROR );
  } /* if */

  if (filecopy(fd1, fd2) < 0) {
    ui_print ( VFATAL, "filecopy: %s\n", strerror(errno));
    (void) close(fd1);
    (void) close(fd2);
    return( ERROR );
  } /* if */

  if (close(fd1) < 0) {
    ui_print ( VFATAL, "close %s: %s\n", src, strerror(errno));
    (void) close(fd1);
    (void) close(fd2);
    return( ERROR );
  } /* if */

  if (close(fd2) < 0) {
    ui_print ( VFATAL, "close %s: %s\n", dst, strerror(errno));
    (void) close(fd2);
    return( ERROR );
  } /* if */

  if (chmod(dst, src_statbuf.st_mode) < 0) {
    ui_print ( VFATAL, "chmod %s: %s\n", dst, strerror(errno));
    return( ERROR );
  } 

  tv.actime = st.st_atime;
  tv.modtime = st.st_mtime;
  if (utime(dst, &tv) < 0) {
    ui_print ( VFATAL, "utime %s: %s\n", dst, strerror(errno));
    return( ERROR );
  } /* if */

  return(0);
}                                                               /* copy file */



int cmp_files ( char * namebuf, char * curpath )
{
    static u_char buf1 [ MAXBSIZE ], buf2 [ MAXBSIZE ];
    int len1, len2;
    int fd1, fd2;

  if ((fd1 = open(namebuf, O_RDONLY, 0)) < 0) {
    ui_print ( VFATAL, "open %s: %s\n", namebuf, strerror(errno));
    return( ERROR );
  } /* if */

  if ((fd2 = open(curpath, O_RDONLY, 0)) < 0) {
    ui_print ( VFATAL, "open %s: %s\n", curpath, strerror(errno));
    return( ERROR );
  } /* if */

  for (;;) {
    len1 = read(fd1, (void *)buf1, sizeof(buf1));
    if (len1 < 0) {
      ui_print ( VFATAL, "read: %s\n", strerror(errno));
      return( ERROR );
    } /* if */

    len2 = read(fd2, (void *)buf2, (len1 == 0) ? 1 : len1);
    if (len2 < 0) {
      ui_print ( VFATAL, "read: %s\n", strerror(errno));
      return( ERROR );
    } /* if */

    if (len1 == 0 || len2 != len1) {
      (void) close(fd1);
      (void) close(fd2);
      return(len2 != len1);
    } /* if */

    if (memcmp((char *)buf1, (char *)buf2, len2) != 0) {
      (void) close(fd1);
      (void) close(fd2);
      return(1);
    } /* if */
  } /* for */
}                                                               /* cmp files */



void print_usage (void)
{
  printf ( "USAGE:\n" );
  printf ( "%s [-copy [-over] -norecurse] [sb_opts]\n", progname );
  printf ( "\t<directory> | [abs_opts]\n");
  printf ( "\t-copy: copy the files instead of linking them\n");
  printf ( "\t  -over: overwrite file on copy even if it exists\n");
  printf ( "\t-norecurse: do files in the directory, not sub-directories\n");
  printf ( "\tdirectory: the directory to link in from the backing tree.\n" );
  printf ( "\tabs_opts:\n" );
  printf ( "\t  -link_from <dir>: non-sandbox directory to link from\n");
  printf ( "\t  -link_to <dir>: non-sandbox directory to link to\n");
  printf ( "\t  -cmp: compare and link identical files\n");
  printf ( "\t  -query: with -cmp flag, query for each file to be relinked\n");
  printf ( "\tsb_opts:\n" );
  printf ( "\t  -sb <sandbox>, -rc <user rc> -sb_rc <sb rc>\n");
  printf ( "%s -usage | -rev\n", progname );
}                                                             /* print usage */

struct chainlist *
backing_chain(const char * sandboxdir) 
{
   char file_path[PATH_LEN];
   char temp[PATH_LEN];
   char tmp[PATH_LEN];
   char links[PATH_LEN];
   struct chainlist *chain2,
		    *node,
		    *chain_tail;
   
   struct stat statbuf;
   int n;

   if (ui_is_set (LINK_FR_OP)) {
	node = (struct chainlist *)malloc(sizeof(struct chainlist));
	node->next = NULL;
	node->path = strdup(ui_arg_value (LINK_FR_OP, 1, 1));
	return(node);
   }

   if (sandboxdir == NULL)
	return(NULL);

   strcpy (links, "");
   chain2 = NULL;
   chain_tail = NULL;

   concat (file_path, sizeof(file_path), sandboxdir, "/link", NULL);

   while (1) {

	if ((lstat(file_path, &statbuf) == -1) ||
    	    ((statbuf.st_mode & S_IFMT) != S_IFLNK)) {
		return(chain2);
	}
	n = readlink(file_path, temp, sizeof(temp));

	if (n == -1) {
		ui_print (VFATAL, "Cannot read links in backing chain\n");
		exit(1);
	} else {
		temp[n] = '\0';
		concat (file_path, sizeof(file_path), temp, "/link", NULL);
	}

	/* Allocate a new node for the chain list. */
	node = (struct chainlist *)malloc(sizeof(struct chainlist));
	if (strcmp (links, "") == 0)
		strcpy (links, "link");
	else {
	   strcpy (tmp, links);
	   concat (links, sizeof(links), tmp, "/link", NULL);
	}
	concat (temp, sizeof(temp), strdup(temp), "/src", NULL);
	node->path= strdup(temp);
	node->link_levels =  strdup(links);
	node->next = NULL;
	if (chain2 == NULL) {
		chain2 = node;
		chain_tail = node;
	} else {
		chain_tail->next = node;
		chain_tail = node;
	}

   }

}


char *
tail(const char * file_path) 
{
	char file[PATH_LEN];
	int i;

	if (file_path == NULL)
		return ((char *)".");
	if (strcmp(file_path, "") == 0)
		return ((char *)".");
	if (strstr (file_path, "/") == 0)
		return ((char *)file_path);

	concat(file, sizeof(file), file_path, NULL);

	for (i = strlen(file)-1; i > 0 && file[i] != '/'; i--);
	if (file[i] == '/')
	 	i++;

	if (file[i] == '\0')
		return ((char *)".");
	else
		return(strdup(&file[i]));	
}

char *
head (const char * file_path)
{
	char file[PATH_LEN];
	int i;

	if (file_path == NULL)
		return ((char *)".");
	if (strcmp(file_path, "") == 0)
		return ((char *)".");
	if (strcmp(file_path, "/") == 0)
		return ((char *)"/");

	concat(file, sizeof(file), file_path, NULL);

	if (strstr( file, "/" ) == 0)
		return ((char *)".");

	for (i = strlen(file)-1; i >= 0 && file[i] != '/'; i--);
	if ((i > 0) && (file[i] == '/') )
		file[i] = '\0';
	else
		file[i+1] = '\0';

	return (strdup(file));	
}

void
verify (char * link_from, char * link_to)
{
    char tmp_buf[MAXPATHLEN];
    char from[MAXPATHLEN];
    char to[MAXPATHLEN];

    strcpy (tmp_buf, link_from);
    canonicalize (tmp_buf, "", from, sizeof(from));
    strcpy (tmp_buf, link_to);
    canonicalize (tmp_buf, "", to, sizeof(to));
    ui_print  ( VNORMAL, "\n%sing:\n  From: %s\n  To:   %s\n\n",
                   ui_is_set ( COPY_OP ) ? "Copy" : "Link",
                   from, to);


    if ( ! ui_is_auto () && ! ui_is_info () ) {
        if ( !getbool ( "Is this correct?", TRUE ))
          uquit ( ERROR, FALSE, "Aborting...\n" );
    } /* if */

}

void 
get_current_directory (char * curdir, char sandboxdir[])
{
	char tmp_dir[MAXPATHLEN];
	char tmp_dir2[MAXPATHLEN];
	char * relpath = NULL;
	char sandbox_src[MAXPATHLEN];

	if ( (char *) getcwd (tmp_dir, sizeof(tmp_dir)) == NULL)
		uquit ( ERROR, FALSE, 
			"getcwd failed: %s.\n", strerror(errno) );
	if (strncmp (sandboxdir, tmp_dir, strlen (sandboxdir)) == 0) {
		strcpy (curdir, tmp_dir);
		return;
	}
	
	concat (sandbox_src, sizeof(sandbox_src), sandboxdir, "/src", NULL);
	chdir (sandbox_src);
	if ( (char *) getcwd (tmp_dir2, sizeof(tmp_dir2)) == NULL)
		uquit ( ERROR, FALSE, 
			"getcwd failed: %s.\n", strerror(errno) );

	if (strncmp (tmp_dir, tmp_dir2, strlen(tmp_dir2)) == 0) {
		chdir (tmp_dir);
		relpath = &tmp_dir [strlen (tmp_dir2) ];
		concat (curdir, MAXPATHLEN, sandboxdir, "/src", relpath, NULL);
		return;
	}

	uquit ( ERROR, TRUE, 
		"current directory %s not in sandbox.\n", tmp_dir);

}




/*
 * NAME: Mkdir
 *
 * FUNCTION: Calls mkdir with a pathname and a mode. 
 *           Calls report to generate error messages.
 *
 * RETURN VALUES: -1 on error, 0 for successful
 */
int
Mkdir(char * d, mode_t m)
{

    if (mkdirp(d) == 0)
	return(0);
		       
    report(d);
    return(-1);
}

/*
 * NAME: mkdirp
 *
 * FUNCTION: creates intermediate path directories if the -p
 *           option is specified.  All directories are created
 *           using the default mode of 0777.
 *           If the umask prevents the user wx bits from being set, chmod is
 *           called to ensure that those mode bits are set so that following
 *           path directories can be created.  If any directory already
 *           exists, it is silently ignored.
 *
 * RETURN VALUES: -1 on error, 0 for successful
 */
int
mkdirp(dir)
char *dir;
{
    mode_t dmode = 0777;
    char *dirp;
    char *ending_slashes;
    int	save_errno = errno;

    /*
     * Skip any leading '/' characters
     */

    for (dirp = dir; *dirp == '/'; dirp++)
	continue;
    
    /*
     * Ignore any ending slashes in the pathname for now
     */
    ending_slashes = strchr(dirp, '\0');
    if (ending_slashes != NULL && *(--ending_slashes) == '/')
    {
	while ( *(--ending_slashes) == '/')
	    ;
	*(++ending_slashes) = '\0';
    }
    else ending_slashes = NULL;

    /*
     * For each component of the path, make sure the component
     * exists.  If it doesn't exist, create it.
     */

    while ((dirp = strchr(dirp, '/')) != NULL) {
	*dirp = '\0';
	if (access (dir, F_OK) != 0) {
		if (mkdir(dir, dmode) != 0 && errno != EEXIST) {
	     		(void)ui_print(VFATAL, "Cannot create %s.\n", dir);
	     		perror(dir);
	     		return (-1);
		}
	}
	/*  If this directory did not already exist AND
	 *  the umask prevented the user wx bits from being set,
	 *  then chmod it to set at least u=wx so the next one can be
	 *  created.
	 */
	if((mask & 0300) && errno != EEXIST)
	    chmod(dir,(mode ^ mask) | 0300);

	for (*dirp++ = '/'; *dirp == '/'; dirp++)
	    continue;
    }
    if (ending_slashes)
	*ending_slashes = '/';
    errno = save_errno;
    return(0);
}

/*
 * NAME: getmode
 *
 * FUNCTION: takes the modestring (supplied by -m mode) and the default mode
 *           and returns a mode suitable for use as the mode
 *           argument to mkdir().  getmode has to know the default
 *           because the '+' and '-' operators are interpreted
 *           relative to the default for the file being created.
 *
 * RETURNS:  integer mode or -1 if unable to decipher modestring
 *
 * NOTES:    Some examples of the current mode formats currently 
 *           supported in getmode:
 *            
 *	     	    ug+x,o-w
 *	            755 (octal)
 *                  =w
 *                  g+x-w	
 */
int
getmode()
{
	char *ms; 		/* ptr to modestring */
	mode_t um;
	int m,md,mode_who,mode_perm;
	char mode_op;

	um = ~mask;

	/* check for an octal mode */
	/* return if octal */
	m=intmode(modestr);		
	if (m >= 0) 
	   return (m);
	m=(int)defmode;

	/*  Separate parts of the modestring -- may be comma-separated */
	msptr = strtok(modestr,",");
	while (msptr && *msptr) {
		usflag=0;

		/*  Determine to whom this part applies  */
		mode_who=who();

		/*  Loop for formats such as o-w+x where multiple operators
                 *  for a given who exist.
		 */
		do {
	 	      /*  Get operator  */
		      if ((mode_op=m_op())=='\0') {
			   return(-1);
		      }

		      /*  get permissions */
		      mode_perm=perm();

		      if (!mode_who) {
			   switch(mode_op) {
				case '+':
					md=mode_perm&(um|SETID); break;
				case '-':
					md=mode_perm; break;
				case '=':
					md=mode_perm&um; break;
				default:
					return(-1);
			   }
		      } 
		      else md = mode_perm&(usflag|mode_who);

		      switch (mode_op) {
			   case '+':
				   m|=md;
				   break;
			   case '-':
				   m&=(~md);
				   break;
			   case '=':
				   m=(m&~mode_who)|md;
				   break;
		       }
		       if ((ms=strtok(NULL,",")) != NULL) {
			     msptr = ms;
			     break;
		       }	
		} while (*msptr != '\0');
	}
	return(m);	
}

/*
 * NAME: who
 *
 * FUNCTION: for symbolic mode, determines who mode is for.
 *
 * RETURNS:  the results from bitwise or operation
 *
 */
int
who()
{
	char *ms = msptr;
	int md=0;

	for (;*ms;ms++) {
		switch(*ms) {
			case 'u':
				usflag |= SETUID;
				md |= USER;
				msptr++;
				break;
			case 'g':
				usflag |= SETGID;
				md |= GROUP;
				msptr++;
				break;
			case 'o':
				md |= OTHER;
				msptr++;
				break;
			case 'a':
				md = ALL;
				msptr++;
				break;
			default:
				return(md);
		}
	}
	return(md);
}

/*
 * NAME: m_op
 *
 * FUNCTION: checks for an operator in the mode string. 
 *
 * RETURNS:  the operator is found, or null
 *
 */
char
m_op()
{
	char *ms = msptr;

	switch(*ms) {
		case '+':
		case '-':
		case '=':
			msptr++;
			return(*ms);
	}
	return('\0');
}

/*
 * NAME: perm
 *
 * FUNCTION: creates permissions mask from mode string. 
 *
 * RETURNS: mask
 *
 */
int
perm()
{
	char *ms = msptr;
	int md=0;

	for (;*ms;ms++) {
		switch(*ms) {
			case 'r':
				md |= READ_MASK;
				msptr++;
				break;
			case 'w':
				md |= WRITE_MASK;
				msptr++;
				break;
			case 'x':
				md |= EXECUTE;
				msptr++;
				break;
			case 's':
				md |= SETID;
				msptr++;
				break;
			case 't':
				md |= STICKY;
				msptr++;
				break;
			default:
				return(md);
		}
	}
	return(md);
}

/*
 * NAME: intmode
 *
 * FUNCTION: strip out mode if supplied in octal integer form. 
 *
 * RETURNS:  the octal integer mode or -1 
 *           if mode is not in octal integer form. 
 */
int
intmode(ms)
char *ms;
{
        register c, i, j;

        i = j = 0;
        while ((c = *ms++) >= '0' && c <= '7') {
                i = (i << 3) + (c - '0');
		j++;
	}

	return(j ? i : -1);
}

/*
 * NAME: report
 *
 * FUNCTION: generates an error message if the directory could 
 *           not be created
 */
void
report(char *d)
{
	int save_errno = errno;

	/*
	 * For EACCES, ENOENT and ENOTDIR errors, print the name
	 * of the parent of the target directory instead of the
	 * target directory.
	 */
	if (errno == EACCES || errno == ENOENT || errno == ENOTDIR) {
		char *slash;

		if ((slash = strrchr(d, '/')) != NULL) {
			if (slash == d)
			      slash++;
			*slash = '\0';
		}
		else {
			d[0] = '.';
			d[1] = '\0';
		}

		(void)ui_print(VFATAL,
		    "mkdir: cannot access directory %s.\n", d);
	}
	else
		(void)ui_print(VFATAL,
		    "mkdir: cannot create %s.\n", d);

	errno = save_errno;
	perror(d);
}
