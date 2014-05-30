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
 *  
 * Copyright (c) 1992 Carnegie Mellon University 
 * All Rights Reserved. 
 *  
 * Permission to use, copy, modify and distribute this software and its 
 * documentation is hereby granted, provided that both the copyright 
 * notice and this permission notice appear in all copies of the 
 * software, derivative works or modified versions, and any portions 
 * thereof, and that both notices appear in supporting documentation. 
 *  
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR 
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE. 
 *  
 * Carnegie Mellon requests users of this software to return to 
 *  
 * Software Distribution Coordinator  or  Software_Distribution@CS.CMU.EDU 
 * School of Computer Science 
 * Carnegie Mellon University 
 * Pittsburgh PA 15213-3890 
 *  
 * any improvements or extensions that they make and grant Carnegie Mellon 
 * the rights to redistribute these changes. 
 */
/*
 * HISTORY
 * $Log: release_db.h,v $
 * Revision 1.6.2.3  1992/12/02  19:39:43  damon
 * 	CR 183. Added CMU notice
 * 	[1992/12/02  19:39:15  damon]
 *
 * Revision 1.6.2.2  1991/12/30  21:26:24  damon
 * 	port to sparc_sunos and libsb to libode transition
 * 	[1991/12/20  20:13:54  damon]
 * 
 * Revision 1.5.1.2  1991/12/17  15:26:39  damon
 * 	Ported to hp300_hpux
 * 	[1991/12/17  14:31:36  damon]
 * 
 * Revision 1.5  1991/12/05  20:53:29  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:06:42  mckeen]
 * 
 * 	rcsid/RCSfile header cleanup
 * 	[90/12/01  18:56:21  dwm]
 * 
 * Revision 1.3  90/10/07  21:52:30  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:06:35  gm]
 * 
 * Revision 1.2  90/01/02  19:59:21  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:48:00  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 2.2  89/07/04  17:48:47  gm0w
 * 	Created.
 * 	[89/07/04            gm0w]
 * 
 * $EndLog$
 */
/* @(#)$RCSfile: release_db.h,v $ $Revision: 1.6.2.3 $ (OSF) $Date: 1992/12/02 19:39:43 $ */

#if	USE_REFERENCE_COUNTING
#define	DECL_REFCNT	u_short refcnt;
#else	/* USE_REFERENCE_COUNTING */
#define	DECL_REFCNT
#endif	/* USE_REFERENCE_COUNTING */

/* table of pointers */
struct table {
    u_short cur;
    u_short max;
    union {
	char **u_tab;
	struct string **u_stab;
	struct file_info **u_fitab;
	struct r_file **u_ftab;
	struct dir **u_dtab;
    } tab_u;
#define stab	tab_u.u_stab
#define fitab	tab_u.u_fitab
#define ftab	tab_u.u_ftab
#define dtab	tab_u.u_dtab
};

/* string header */
struct strhdr {
    struct strhdr *sh_first;
#define sh_next sh_first
    struct strhdr *sh_last;
#define sh_prev sh_last
};

/* string structure */
struct string {
    struct strhdr sh;		/* string header */
    u_short index;		/* index */
    DECL_REFCNT			/* reference count */
    u_short len;		/* length of string */
    u_char ahash;		/* add hash value */
    u_char xhash;		/* xor hash value */
    char *data;			/* contents */
};

struct loginfo {
    DECL_REFCNT			/* reference count */
    struct string *installer;	/* installer */
    struct string *message;	/* message */
    time_t itime;		/* installation time */
    time_t wtime;		/* when to warn about release status */
};

struct instance {
    struct instance *next;	/* next instance of this file */
    u_short index;		/* index for this instance */
    DECL_REFCNT			/* reference count */
    struct loginfo *loginfo;	/* log information */
    u_short flags;		/* flags */
#define	IF_COMPRESSED	1	/* file is compressed */
    time_t ctime;		/* last time "inode" changed */
    time_t mtime;		/* last time file data modified */
};

struct file_info {
    u_short index;		/* index for this file info */
    DECL_REFCNT			/* reference count */
    struct string *owner;	/* owner name */
    struct string *group;	/* group name */
    u_short mode;		/* file permission mode */
};

struct r_file {
    u_short index;		/* index for this file */
    DECL_REFCNT			/* reference count */
    struct dir *parent;		/* directory that contains this file */
    struct r_file *links;	/* other links to this file */
    struct dir *srcdir;		/* directory to build this file */
    struct string *name;	/* file name (shared) */
    struct file_info *info;	/* file info (shared) */
    struct instance *instances;	/* instances of file for distribution */
};

struct dir {
    u_short index;		/* index for this directory */
    DECL_REFCNT			/* reference count */
    struct dir *parent;		/* directory that contains this directory */
    struct string *name;	/* directory name (shared) */
    struct table ftable;	/* table of files in directory */
    struct table dtable;	/* table of subdirectories in directory */
    struct file_info *info;	/* directory info (shared) */
};
