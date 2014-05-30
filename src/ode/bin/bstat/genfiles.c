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
 * $Log: genfiles.c,v $
 * Revision 1.1.2.2  1993/03/26  18:35:26  marty
 * 	Generate list of files for bstat by searching the source
 * 	tree of the backing chain.
 * 	[1993/03/26  18:34:01  marty]
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


#  include <ode/odedefs.h>
#  include <sys/param.h>
#  include <sys/stat.h>
#  include <errno.h>
#  include <sys/time.h>
#  include <fcntl.h>
#  include <utime.h>
#  include <ode/sci.h>

#  define  CMP_OP   	"-cmp"
#  define  LINK_FR_OP  	"-link_from"
#  define  LINK_TO_OP  	"-link_to"
#  define  NORECURSE_OP "-norecurse"
#  define  REFRESH_OP   "-refresh"
#  define  OVER_OP   	"-over"
#  define  QUERY_OP   	"-query"
#  define  MAX_ARGS	10
#  define  TRUE		1
#  define  FALSE	0

extern char curdir[];
extern SCI_LIST file_set;

    /* Global variables used to cut down calls to user
       interface routines. */
    int		refresh_op,		/* -refresh option 	*/
		copy_op,		/* -copy option		*/
		norecurse_op,		/* -norecurse option	*/
		link_fr_op,		/* -link_from option	*/
		overwrite_op;		/* -over option		*/
    char      * link_to_entry;		/* Value given with
					   -link_to option	*/
    struct chainlist *chain;		/* The backing chain.   */
    char *sandbox_base;			/* The users sandbox    */

   /* This structure represents a list of each directory
      in the backing chain. */
   struct chainlist {
	char *path;			
	struct chainlist *next;
   };

   /* This structure is used to represent all files and directories in
      the backing chain. */ 
   struct dir_entry {
	char *name;			/* Name of this file/directory in the tree. */
	char *base;			/* If it's a file,  this is a pointer to 
					   the backing tree it should be linked to. */
	int file_type;			/* File type (i.e. S_IFLNK, S_IFREG, ...)   */
	struct dir_entry *sub_dir_entries; /* If it's a directory, this is a list of
					      its sub-directories.		    */
	struct dir_entry *files;	/* If it's a directory, this is a list of 
					   its files.				    */
	struct dir_entry *next;		
   };

    struct sandbox_env {
                  char * sandboxdir;	/* string with sandbox and basedir */
                  char * reldir;        /* holds relative directory */
		  char * file;		/* The file/directory to link. */
    };

    /* Declarations for forward referencing. */
    char *malloc();			/* Space allocation. 	 */
    struct dir_entry *talloc();		/* Space allocation  	 */
    char *head();			/* returns directory component of pathname */
    char *tail();			/* returns file component of pathname */
    struct chainlist *backing_chain();  /* returns backing chain */
    struct dir_entry *newnode();	/* Creats nodes for file/directories in list */
    struct dir_entry *populate_tree();  /* Builds up list of all files in backing chain. */
    struct sandbox_env *get_sb_loc();   /* Get sandbox and file pathnames.    */
    int    symlink_file ();		/* Create symbolic link. */
    int    copy_file ();		/* Copy file to sandbox. */
    int    cmp_files (); 		/* Compare files 	 */


    extern int    errno;

genfiles ( reldir ) 
    char       * reldir;

{

    struct dir_entry *tree;  /* Represents the top of the generated tree. */
    struct sandbox_env *sb;



   /* Get sandbox info (i.e. sandbox location, relative directory in 
	sandbox, and the file to link */
   sb = get_sb_loc(reldir);

   sandbox_base = strdup(sb->sandboxdir);

   /* Get the backing chain. */
   chain = backing_chain(sb->sandboxdir);
   
   tree = NULL; 

   /* Build up the list of files in the backing chain to link to. */
   while ((chain != NULL) && (chain->path != NULL)) {
	tree = populate_tree(tree, chain->path, sb->reldir, sb->file); 
	chain = chain->next; 
   }

   /* Output all files built up from the backing chain. */
   if (tree != NULL)
	list_files (tree, sb->reldir);

   return( OK );
}                                                                    /* main */

struct sandbox_env *
get_sb_loc(reldir)
char *reldir;
{
   struct sandbox_env *sb_files;
   char * sb, 
	* basedir = NULL,
	* sb_rcfile,
	* rc_file,
	  sandboxdir [ PATH_LEN ],
	* directory,
	* curpath;

   sb_files = (struct sandbox_env *)malloc(sizeof (struct sandbox_env));
   sb_files->sandboxdir = NULL;
   sb_files->reldir = NULL;
   sb_files->file = NULL;

	/* linking files in this sandbox to the backing chain. */
  	/*if ( current_sb ( &sb, &basedir, &sb_rcfile, &rc_file ) != OK )
    		uquit ( ERROR, FALSE, "could not get current sandbox information.\n" ); */
	sb  = "ode2_3";
	basedir = "/usr/users/marty";
	
  	concat ( sandboxdir, PATH_LEN, basedir, "/", sb, NULL );

    	if ( strncmp ( sandboxdir, curdir, strlen ( sandboxdir )) != OK )
      		uquit ( ERROR, TRUE,
	 	   "directory given is relative; current directory not in sandbox.\n" );
   	curpath = &curdir [ strlen ( sandboxdir ) + 5 ];
  	if ( *(directory = strdup(reldir)) == '/' ) {
    		sb_files->file = strdup(directory);
    		sb_files->reldir = "";
  	} else { 
		/* Relative pathnames cause all processing to be done from the
		   current directory. */
		if (strcmp(directory, ".") == 0) {
			sb_files->file = tail(curpath);
			sb_files->reldir = head(curpath);
		} else {
    			sb_files->file = strdup(directory);
    			sb_files->reldir= strdup(curpath);
		}
	}

  	sb_files->sandboxdir = strdup(sandboxdir);

   return (sb_files);
}


int 
file_type (base, reldir, file)
char *base;
char *reldir;
char *file;
{
   char path[PATH_LEN];
   struct stat statbuf;
	
   concat (path, sizeof(path), base, "/", reldir, "/", file, NULL);

   lstat(path, &statbuf);
   return (statbuf.st_mode & S_IFMT);
}

int
x_exists(path)
char *path;
{
   struct stat statbuf;
   int status;
   status = lstat(path, &statbuf) ;

   if ((status == -1) || ( (statbuf.st_mode & S_IFMT) == S_IFLNK) ) 
	return (FALSE);
   else
	return (TRUE);
}


struct dir_entry *
populate_tree (tree, base, reldir, file)
struct dir_entry *tree;
char * base;
char * reldir;
char * file;
{
	char path[PATH_LEN];
	int  ft;

	concat (path, sizeof(path), base, "/", reldir, "/", file, NULL);
	if (x_exists (path) == FALSE)
		return(tree);

	if (tree == NULL) {

		if ( (ft = file_type(base, reldir, file)) == S_IFREG) {
			tree = newnode(file); 
			tree->base = chain->path; 
			tree->file_type = ft;
		} else {
			tree = newnode(file); 
			tree->file_type = ft;
		}
	}
	update_tree (tree, base, reldir);

	return(tree);
}

create_file(file)
char *file;
{
    int ct;
    char tmp_file[PATH_LEN];

    if (*file == '/') {
    	sci_add_to_list ( file_set, file );
    } else {
	concat (tmp_file, sizeof(tmp_file), "./", file, NULL);
    	sci_add_to_list ( file_set, tmp_file );
    }
	

}

list_files (node, reldir) 
struct dir_entry *node;
char *reldir;
{
	char new_reldir[PATH_LEN];
	struct dir_entry *subdirs;
	struct dir_entry *i;
	char from_file[PATH_LEN];
	char to_file[PATH_LEN];
	char to_dir[PATH_LEN];
	char file[PATH_LEN];

   
   if (node->file_type == S_IFREG) { 
	concat (file, sizeof(file), reldir, "/", node->name, NULL);
	create_file(file);
	return;
   } 

   /* Process all the files in the current directory. */
   for (i = node->files ; i != NULL; i=i->next) {

	concat (file, sizeof(file), reldir, "/", node->name, "/", i->name, NULL);
	create_file(file);
   }

   if ((reldir == NULL) || (strcmp(reldir, "") == 0 ))
       	concat (new_reldir, sizeof(new_reldir), "/", node->name, NULL);
   else {
       	concat (new_reldir, sizeof(new_reldir), reldir, "/", node->name, NULL);
   }
		
   /* Process subdirectories. */
   subdirs = node->sub_dir_entries;
   while (subdirs != NULL) {
	list_files(subdirs, new_reldir);
	subdirs = subdirs->next;
   }
}

update_tree (node, base, reldir)
struct dir_entry *node;
char *base;
char *reldir;
{
	char path[PATH_LEN];
	char new_reldir[PATH_LEN];
	struct dir_entry *subdirs;

	if (file_type(base, reldir, node->name) == S_IFREG)
		return;

	/* "node" represents a directory node.
	   Update the list of files and 
	   subdirectories for this node. */
	get_lists (node, base, reldir);

	concat (new_reldir, sizeof(new_reldir), reldir, "/", node->name, NULL);

	/* Iterate through each subdirectory updating its tree. */
	subdirs = node->sub_dir_entries;
	while (subdirs != NULL) {
		update_tree(subdirs, base, new_reldir);
		subdirs = subdirs->next;
	}
}

struct dir_entry *
getentries(base, reldir, file)
char *base;
char *reldir;
char *file;
{
   DIR           *d;         /* for reading directory */
   register struct dirent *dp; /* entry in directory */
   char path[PATH_LEN];
   struct dir_entry * head = NULL;
   struct dir_entry * tail = NULL;
   struct dir_entry * thisnode;

   concat (path, sizeof(path), base, "/", reldir, "/", file, NULL);
   if (x_exists(path) == FALSE)
	return ((struct dir_entry *) NULL);

   d = opendir (path);

   if (d == (DIR *) NULL)
	return ((struct dir_entry *) NULL);

   while ((dp = readdir (d)) != (struct dirent *) NULL) {
	if ((strcmp(dp->d_name, ".") == 0) ||
	    (strcmp(dp->d_name, "..") == 0))
		continue;
	thisnode = newnode(dp->d_name);
	if (head == NULL) {
		head = thisnode;
		tail = thisnode;
	} else {
		tail->next = thisnode;
		tail = tail->next;
	}
   }
   (void) closedir(d);
   return (head);

}

get_lists(node, base, rel_path)
struct dir_entry *node;
char *base;
char *rel_path;
{

	struct dir_entry * sub_dir_head,
	 		 * sub_dir_tail,
	 		 * i,
	 		 * files,
	 		 * curr_file,
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
			   if (file_list_head == NULL) {
					thisnode = newnode(files->name);
					thisnode->file_type = S_IFREG;
					thisnode->base = chain->path;
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
					thisnode->base = chain->path; 
                                        file_list_tail->next = thisnode;
                                        file_list_tail = thisnode;
                                }

			   }
		}
		files = files->next;
	}
}

struct dir_entry *
newnode(name)
char * name;
{
	struct dir_entry *node;
	
	node = talloc();
	node->next = NULL;
	node->base = NULL;
	node->files = NULL;
	node->name = strdup(name);
	node->sub_dir_entries = NULL;
	return (node);
}

struct dir_entry *
talloc()
{
	return((struct dir_entry *) malloc(sizeof(struct dir_entry)));
}






struct chainlist *
backing_chain(sandboxdir) 
char *sandboxdir;
{
   char path[PATH_LEN];
   char temp[PATH_LEN];
   struct chainlist *chain,
		    *node,
		    *chain_tail;
   
   struct stat statbuf;

   if (ui_is_set (LINK_FR_OP)) {
	node = (struct chainlist *)malloc(sizeof(struct chainlist));
	node->next = NULL;
	node->path = strdup(ui_arg_value (LINK_FR_OP, 1, 1));
	return(node);
   }

   if (sandboxdir == NULL)
	return(NULL);

   chain = NULL;
   chain_tail = NULL;

   concat (path, sizeof(path), sandboxdir, "/link", NULL);

   while (1) {

	if ((lstat(path, &statbuf) == -1) ||
    	    ((statbuf.st_mode & S_IFMT) != S_IFLNK)) {
		return(chain);
	}
	readlink(path, temp, sizeof(temp));
	concat (path, sizeof(path), temp, "/link", NULL);

	/* Allocate a new node for the chain list. */
	node = (struct chainlist *)malloc(sizeof(struct chainlist));
	concat (temp, sizeof(temp), strdup(temp), "/src", NULL);
	node->path= strdup(temp);
	if (chain == NULL) {
		chain = node;
		chain_tail = node;
	} else {
		chain_tail->next = node;
		chain_tail = node;
	}

   }

}


char *
tail(path) 
char *path;
{
	char file[PATH_LEN];
	int i;

	if (path == NULL)
		return (NULL);
	if (strcmp(path, "") == 0)
		return (".");
	concat(file, sizeof(file), path, NULL);

	for (i = strlen(file)-1; i > 0 && file[i] != '/'; i--);
	if (file[i] == '/')
	 	i++;
	return(strdup(&file[i]));	
}

char *
head (path)
char *path;
{
	char file[PATH_LEN];
	int i;

	if (path == NULL)
		return (NULL);
	if (strcmp(path, "") == 0)
		return ("");

	concat(file, sizeof(file), path, NULL);

	for (i = strlen(file)-1; i > 0 && file[i] != '/'; i--);
	if (file[i] == '/')
		file[i] = '\0';
	return (strdup(file));	
}
