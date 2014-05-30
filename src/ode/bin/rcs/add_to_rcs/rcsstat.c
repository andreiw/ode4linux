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
 * $Log: rcsstat.c,v $
 * Revision 1.1.2.1  1995/05/18  02:42:49  robert
 * 	add to tree for free & unencumbered distribution
 * 	[1995/05/18  02:41:48  robert]
 *
 * Revision 1.1.2.4  1993/04/27  15:49:34  marty
 * 	Added "-f" option to read list from a file.
 * 	[1993/04/27  15:47:10  marty]
 * 
 * Revision 1.1.2.3  1993/01/12  00:11:55  damon
 * 	CR 386. Updated to rcs 5.6 from FSF
 * 	[1993/01/12  00:11:44  damon]
 * 
 * 	CR 386. Updated to rcs 5.6 from FSF
 * 	[1993/01/12  00:09:59  damon]
 * 
 * Revision 1.1.2.2  1993/01/11  18:08:46  damon
 * 	CR 386. Moved from ODE
 * 	[1993/01/11  18:08:20  damon]
 * 
 * Revision 1.2.2.3  1992/12/02  19:20:15  damon
 * 	CR 183. Added CMU notice
 * 	[1992/12/02  19:19:20  damon]
 * 
 * Revision 1.2.2.2  1992/07/26  17:30:08  gm
 * 	Fixed to remove warnings when compiling under OSF/1 R1.1.
 * 	[1992/07/17  20:51:32  gm]
 * 
 * Revision 1.2  1991/12/05  20:52:27  devrcs
 * 	ODE 2.1
 * 
 * Revision 1.1.2.4  1991/10/16  10:49:36  rec
 * 	Fixed core dump on OSF/1 (added in previous change) and allow
 * 	stdin for filenames.
 * 	[91/10/16  10:48:13  rec]
 * 
 * Revision 1.1.2.3  91/10/08  11:03:59  mckeen
 * 	Fixed build problems on OSF/1 systems
 * 	[91/10/08  11:01:03  mckeen]
 * 
 * Revision 1.1.2.2  91/09/19  15:26:55  mckeen
 * 	Added support for rcs 5.5.
 * 	[91/09/19  15:23:02  mckeen]
 * 
 * Revision 1.3  90/10/07  21:45:48  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  13:56:45  gm]
 * 
 * Revision 1.2  90/08/09  14:40:35  devrcs
 * 	Added -D flag to return defunct status.
 * 	[90/08/01  20:04:20  gm]
 * 
 * Revision 1.1  89/12/26  10:44:39  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 1.6  88/08/26  14:21:47  dorr
 * 	add defunct state checks.
 * 
 * Revision 1.5  88/06/23  09:59:47  dorr
 * 	force file names generated to begin with "." or "/" (for
 * 	snapshots).
 * 
 * Revision 1.4  88/06/21  16:05:59  dorr
 * 	add -P option.
 * 	add -P option.
 * 
 * Revision 1.3  88/06/08  08:41:12  dorr
 * 	add -R and '-' options.
 * 
 * Revision 1.2  88/06/02  16:24:50  dorr
 * 	change -V and -R to not be quiet by default.
 * 
 * $EndLog$
 */

#ifndef lint
static char rcsid[] = "$Id: rcsstat.c,v 1.1.2.1 1995/05/18 02:42:49 robert Exp $";
#endif

#include "time.h"
#include "rcsbase.h"
#include <sys/param.h>

static char rcsbaseid[] = RCSBASE;

/* Added from the old rcs commands, used to compile this file */
#define revlength          30 /* max. length of revision numbers */
#ifdef V4_2BSD
#  define NCPFN           256 /* number of characters per filename          */
#  define NCPPN          1024 /* number of characters per pathname          */
#else
#  define NCPFN            14 /* number of characters per filename          */
#  define NCPPN       6*NCPFN /* number of characters per pathname          */
#endif
/*
const char * RCSfilename;
char * workfilename;
*/
int  defunctflag;			/* print out defunct status */
int  nameflag;				/* print out rcs file name */
int  versflag;				/* print out the version number */
int  quietflag;
char * rev;
const char cmdid[] = "stat";

extern int nerror;
extern RILE * finptr;
extern FILE * RCSfilefp;
extern int relativepathflag;
extern char * relativepath;

extern struct hshentry * findrev();

main (argc, argv)
int argc;
char * argv[];
{
        char * cmdusage;
	struct hshentry * ptr;
	int wasdefunct;

	FILE * RCSfilefp = NULL;
	int relativepathflag;
	char * relativepath;

	char tempfilename2[MAXPATHLEN];  /* used for derived file names */
	char * fil;


	cmdusage = "command format:\nrcsstat -R -D -V -q -cconfig -ddate -rrev -P[relpath] - file ...";
	defunctflag = nameflag = quietflag = false;
	rev = nil;

	suffixes = X_DEFAULT;
        while (--argc,++argv, argc>=1 && ((*argv)[0] == '-')) {
                switch ((*argv)[1]) {

		case 'D':
			defunctflag = true;
			break;

		case 'R':
			nameflag = true;
			break;

		case 'V':
			versflag = true;
			break;

		case 'P':
			relativepathflag=true;
			relativepath=(*argv)+2;
			break;

		case 'n':
		case 'c':
                case 'r':
		revno:
			if( rev != nil ) warn( "conflicting version specifications" );
			rev = (*argv)+2;
                        break;

                case 'd':
			if ((*argv)[2] != '<') {
				/* fudge up a date */
				(*argv)--;
				(*argv)[2] = '<';
			}
			goto revno;

		case 'q':
			quietflag = true;
			break;
		case 'f':
			fil = (*argv)+2;
			RCSfilefp = fopen (fil, "r");
			break;

		case '\0':
			RCSfilefp = stdin;
			break;

                default:
                        faterror("unknown option: %s\n%s", *argv,cmdusage);

                };
        } /* end of option processing */

        if ( (argc<1) && (RCSfilefp == NULL) ) faterror("No input file\n%s",cmdusage);


        /* now handle all filenames */
        do {

	  /* file coming in on stdin */
	  if ( RCSfilefp != NULL )  {
	    if ( fgets( tempfilename2, sizeof(tempfilename2), RCSfilefp ) != NULL ) {
	      int len = strlen(tempfilename2);
	      /* ditch the trailing nl */
	      if ( len > 0 && tempfilename2[len-1] == '\n' )
		tempfilename2[len-1] = '\0';
	      *argv = tempfilename2;
	      /* RCSfilefp = NULL; */
	      if (!pairfilenames(1,argv,rcsreadopen,true,false)) continue;
	    } else {
		exit(0);
	    }
	  }
	  else {
	    if (!pairfilenames(argc,argv,rcsreadopen,true,false)) continue;
	  }

            /* now RCSfilename contains the name of the RCS file, and finptr
             * the file descriptor. Workfilename contains the name of the
             * working file.
             */

#ifdef notdef
            if ( !trysema(RCSfilename, false)) goto loopend; /* give up */
#endif

	    gettree();
	    if (Head == nil) {
		    error( "no revisions present for this file" );
	    } else {
		    if ( (ptr = findrev(rev)) == nil ) {
			    if ( quietflag )
				    ++nerror;
			    else
				    error( "selected revision of %s not present", RCSfilename );
			    goto loopend;
		    }

		    /* defunct revisions have no status */
		    if(( wasdefunct = isdefunct(ptr) ) && !defunctflag )
			    goto loopend;

		    if( nameflag || versflag || wasdefunct ) {
			    /* print out diagnostic info */
			    if( nameflag ) {
				    /* 
				     * make relative path names explicitly relative 
				     * (for config parsing) 
				     */
				    if (RCSfilename[0] != '.'
					&& RCSfilename[0] != '/'
					&& RCSfilename[0] != '\0' )
					    fputs( "./", stdout );
				    fputs( RCSfilename, stdout );
			    }
			    if( versflag ) {
				    if (nameflag) fputs( "\t", stdout );
				    fputs( ptr->num, stdout );
			    }
			    if( wasdefunct ) {
				    if (nameflag || versflag)
					    fputs( " ", stdout );
				    fputs( "(defunct)", stdout );
			    }
			    fputs( "\n", stdout );
		    }
		    else if ( !quietflag )
			    diagnose( "version %s selected%s\n", ptr->num,
				      wasdefunct ? " (defunct)" : "");
	    }

    loopend:;
	    Izclose(&finptr);
        } while( (RCSfilefp != NULL) || (++argv, --argc >= 1) );
        exit(nerror!=0);
}



/*********************************************************************/
/*                    CODE ADDED FROM OLD RCSREV.C                   */
/*********************************************************************/


/*
 *      implement a little stack of files/strings to read
 *      configuration info from.
 */
typedef int boolean;
typedef struct config {
        boolean is_file;
        FILE * fd;
        char * str;
        char * cur;
} * config_fp;









#define MAX_CONFIGS 20  /* maximum nesting */
#define datelength         20 /* length of a date in RCS format */
#if lint
#       define exiterr rmergeExit
#endif
        exiting void
exiterr()
{
        tempunlink();
        _exit(EXIT_TROUBLE);
}
struct hshentry * trace_trunk(); /* forward */
static struct config configs[MAX_CONFIGS];
static int config_level;
char semafilename [NCPPN];     /* name of semaphore file */
int  madesema;                 /* indicates whether a semaphore file has been set */
char * finaldate;
int RCSdebug;

int
isdefunct(delta)
struct hshentry * delta;
{
        if( delta == nil ) return false;
        return strcmp(delta->state,"defunct") == 0
                || strcmp(delta->state,"Defunct") == 0;
}

#ifdef notdef
int trysema(RCSname,makesema)
char * RCSname; int makesema;
/* Function: Checks whether a semaphore file exists for RCSname. If yes,
 * returns false. If not, creates one if makesema==true and returns true
 * if successful. If a semaphore file was created, madesema is set to true.
 * The name of the semaphore file is put into variable semafilename.
 */
{
        register char * tp, *sp, *lp;
        int fdesc;

        sp=RCSname;
        lp = rindex(sp,'/');
        if (lp==0) {
                semafilename[0]='.'; semafilename[1]='/';
                tp= &semafilename[2];
        } else {
                /* copy path */
                tp=semafilename;
                do *tp++ = *sp++; while (sp<=lp);
        }
        /*now insert `,' and append file name */
        *tp++ = ',';
        lp = rindex(sp, RCSSEP);
        while (sp<lp) *tp++ = *sp++;
        *tp++ = ','; *tp++ = '\0'; /* will be the same length as RCSname*/

        madesema = false;
        if (access(semafilename, 0) == 0) {
                error("RCS file %s is in use",RCSname);
                return false;
        }
        if (makesema) {
#ifdef V4_2BSD
                if ((fdesc=open(semafilename, O_CREAT|O_EXCL, 000)) == -1) {
			error("Can't create semaphore file for RCS file %s",RCSfilename);
                     return false;
                } else
                     VOID close(fdesc);
#else
                if ((fdesc=creat(semafilename, 000)) == -1) {
                     error("Can't create semaphore file for RCS file %s",RCSname
);
                     return false;
                } else
                     VOID close(fdesc);
#endif
                     madesema=true;
        }
        return true;
}
#endif

const char * lookupsym(id)
char * id;
/* Function: looks up id in the list of symbolic names starting
 * with pointer SYMBOLS, and returns a pointer to the corresponding
 * revision number. Returns nil if not present.
 */
{
        register struct assoc * next;
        next = Symbols;
        while (next!=nil) {
                if (strcmp(id, next->symbol)==0)
                        return(next->num);
                else    next=next->nextassoc;
        }
        return nil;
}

static void
cleanup_configs()
/*  cleanup_configs: close any remaining open config files
 */
{
        for ( ; config_level >= 0; --config_level ) {
                if (configs[config_level].is_file)
                        fclose( configs[config_level].fd );

        }

        config_level = 0;
}




static int cmpflds( s1, s2, f1, f2 )
        char * s1;
        char * s2;
        int f1;
        int f2;
{
        int rc;

        while( f1 <= f2 ) {
                if( rc = cmpnumfld( s1, s2, f1 ) )
                        return( rc );
                f1++;
        }
        return( 0 );
}


getRCSpath(buf)
char * buf;
{
    int plen = strlen(RCSfilename);
    const char * path = RCSfilename;
    int rcslen = strlen("/RCS/");

    /* strip off component name */
    while( (plen > 0) && (path[plen-1] != '/') )
            plen--;

    /* look for . relative paths -- xxx,v or RCS/xxx,v */
    if( (plen == 0) || (plen == 4 && strncmp( path, "RCS/", 4 ) == 0 ) ) {
            strcpy( buf, "." );
            return;
    }

    /* look for /a/b/c/xxx,v  or /a/RCS/xxx,v */
    if( (plen <= rcslen) || strncmp( &path[plen-rcslen], "/RCS/", rcslen ) != 0
 )
            plen--;
    else
            plen -= rcslen;

    strncpy( buf, path, plen );
    buf[plen] = '\0';

}


static int
c_getc(fp)
config_fp fp;
{
        if (fp->is_file)
                return( getc(fp->fd) );
        else {
                if (*fp->cur)
                        return( *((fp->cur)++) );
                else
                        return( EOF );
        }
}

static void
c_ungetc(ch,fp)
int ch;
config_fp fp;
{
        if (fp->is_file)
                ungetc( ch, fp->fd );
        else
                if (fp->cur > fp->str)
                        *(--(fp->cur)) = ch;
}

static int
iseol(str)
char * str;
{
        return( str == nil
               || (*str == '\0')
               || (strcmp(str,";") == 0)
               || strcmp(str,"\n") == 0 );
}


static int patheq( relpath, p1, p2 )
/* patheq: figure out if two paths are equal.
 * they must both be relative path names.  only leading .'s and ..'s are allowed
 */
        char * relpath;
        char * p1;
        char * p2;
{

        static char * cwd = nil;
        char p1path[MAXPATHLEN];
        char p2path[MAXPATHLEN];

        extern char * getwd();
        extern char * strcat();


        /* get rid of relative path names */
        while (1) {
                /* handle (only) leading relative path junk */
                if (strncmp( "./", p1, 2 ) == 0) {
                        p1 += 2;
                }
                else
                if (strncmp( "../", p1, 3 ) == 0 ) {
			warn( "can't handle leading '..' in snapshot paths--skipping" );
                        p1 += 3;
                } else
                        break;
        }

        while (1) {
                if (strncmp( "./", p2, 2 ) == 0) {
                        p2 += 2;
                }
                else
                if (strncmp( "../", p1, 3 ) == 0 ) {
			warn( "can't handle eeading '..' in snapshot paths--skipping" );
                        p1 += 3;
                } else
                        break;
        }

        /* turn our pathnames into absolute pathnames */
        if ( *p1 != '/' ) {
                if ( !relpath || (*relpath == '\0') ) {
                        if (cwd == nil) cwd = getwd(malloc(MAXPATHLEN));
                        relpath = cwd;
                }
                strcpy(p1path, relpath);
                strcat(p1path, "/");
                p1 = strcat(p1path, p1);
        }

        if ( *p2 != '/' ) {
                if (cwd == nil) cwd = getwd(malloc(MAXPATHLEN));

                strcpy(p2path, cwd);
                strcat(p2path, "/");
                p2 = strcat(p2path, p2);
        }

        return( strcmp( p1, p2 ) == 0 );
}

static struct hshentry * trace_branch( bptr, rev, b )
        struct branchhead * bptr;
        char * rev;
        int  b;
/* Function: trace down a branch, looking for the indicated piece of the rev.
 * If found, either return true (if it's the last piece) or continue searching
 * for the rest of the component
 */
{
        int rc;
        int rcnt;

        if( bptr == nil ) return nil;

        /*  look for an entry ending in this rev number (1.2.3, for example) */
        while( (rc = cmpflds( bptr->hsh->num, rev, b, b )) != 0 )
                if( (bptr = bptr->nextbranch) == nil ) return nil;

        if( rc != 0 ) return nil;
        rcnt = countnumflds( rev );

        if( rcnt == b ) {
                /* rev is a branch name */
                struct hshentry * ptr;
                /* return the highest element on this branch */
                for( ptr=bptr->hsh; ptr->next; ptr=ptr->next );
                return( ptr );
        } else
                /* rev is an element name; trace down the trunk and find it */
                return( trace_trunk( bptr->hsh, rev, b ) );
}



struct hshentry * trace_trunk( ptr, rev, b )
        struct hshentry * ptr;
        char * rev;
        int  b;         /* rev component to compare */
/* Function: trace down a trunk (not necessarily "the" trunk) looking for
 * the indicated piece of the rev.  If found, either return true or continue
 * searching at the next component
 */
{
        int rcnt;
        int rc;

        if ( ptr == nil ) return nil;
        rcnt = countnumflds( rev );

        if ( rcnt == 1 && b == 1 ) {
                /* special case: our branch is the main trunk, but
                   it's not organized like a regular branch.  this
                   is the situation where you're looking for something
                   like -r1, so you wish to take the newest 1.* on the
                   branch that is the main trunk. */

                /*  find the first (newest) rev of our branch  */
                while( (rc = cmpflds( ptr->num, rev, b, b )) != 0) {
                        if( (ptr = ptr->next) == nil ) return nil;
                }
        } else {
                /* any fields left to compare? */
                if( rcnt < b+1 ) return nil;

                /* trace down the trunk, looking at the last two fields
                 * until you get a match
                 */
                while( (rc = cmpflds( ptr->num, rev, b, b+1 )) != 0) {
                        if( (ptr = ptr->next) == nil ) return nil;
                }

                /* you got a match, but you haven't matched the whole rev.
                 * look down the branches starting with this prefix for more
                 * information.
                 */
                if ( rcnt > b+1 )
                        return( trace_branch( ptr->branches, rev, b+2 ) );
        }

        if( rc == 0 )
                return( ptr );
        else
                return( nil );
}



/*
 *      openconfig: cache the config file
 */
FILE *
openconfig()
{
        char tmpbuf[4096];
        FILE * fd;
        static char * config = NULL;
        static FILE * save_fd = NULL;

        /* get the leading pathname */
        getRCSpath( tmpbuf );
        VOID strcat( tmpbuf, "/RCSconfig" );

        if ( (config != NULL)
        &&   (strcmp(tmpbuf,config) == 0) ) {
                if (save_fd != NULL) rewind(save_fd);
                fd = save_fd;
        } else {
                if (save_fd != NULL)
                        fclose(save_fd);

                fd = fopen(tmpbuf,"r");

                if (config != NULL) free(config);
                config = strcpy(malloc(strlen(tmpbuf)+1),tmpbuf);
        }

        /* stash a copy of the fd you came up with */
        if (fd != NULL)
                save_fd = fdopen(dup(fileno(fd)),"r");
        else
                save_fd = NULL;

        return fd;
}




static char *
gettok()
/*  gettok:  get the next token from the input stream
 */
{
	static char token[512];
	char * tp;
	int ch;
	config_fp fp = &configs[config_level];

	/*
	 * config entities are non-space tokens or end
	 * of line indicators (semicolons and newlines)
	 */

	/* find a config entity */
	ch = c_getc(fp);
	while (isspace(ch) && (ch != '\n')) ch = c_getc(fp);
	if ( ch == EOF ) {
		if (config_level == 0) 
			return nil;
		--config_level;
		return gettok();
	}

	tp = token;
	if ( ch == ';' || ch == '\n' ) {
		*tp++ = ch;
	} else
		while( (ch != EOF) && !isspace(ch) ) {
			if (tp == (token + sizeof(token)-1)) {
				error( "config file token exceeds %d bytes", sizeof(token)-1 );
				return nil;
			}

			*tp++ = ch;
			ch = c_getc(fp);
			
			if ((ch == ';') || (ch == '\n')) {
				c_ungetc( ch, fp );
				break;
			}
		}
	*tp = '\0';

	return token;
}


static	char * reldir;

static struct hshentry *
do_conf( rev, expandrev )
char * rev;
struct buf * expandrev;
{
	char * cb;
	struct hshentry * ptr;
	FILE * fd;
	struct hshentry * damon_h;
        char damon_s [100];

	config_level = 0;
	if (rev != nil) {
		if (rev[0] == '\0') rev = "<>";		/* -r <=> -r<> */

		configs[0].is_file = false;
		configs[0].str =
		configs[0].cur = rev;
	} else {
		if ( (fd = openconfig()) == NULL ) {
			expandrev -> string = strdup ( (char *)Head -> num );
			expandrev -> size = strlen ( Head -> num );
			return Head;
		}

		configs[0].is_file = true;
		configs[0].fd = fd;

	}

	/* 
	 * loop looking for a rule that matches 
	 */
	while( cb = gettok() ) {

		if ( iseol(cb) ) continue;

		/* is it a date */
		if( *cb == '<') {
			char finaldate[datelength];
			
			if (strcmp(cb, "<>") == 0) {
				/* special notation... latest version on the trunk */
				expandrev -> string = strdup ( (char *)Head->num );
				expandrev -> size = strlen ( Head -> num );
				if (RCSdebug > 0)
					diagnose( "rcsconfig: using '<>' (%s)", expandrev -> string );
				return Head;
			} else {
				struct hshentry * ptr;
				++cb;
				str2date(cb, finaldate);
				for( ptr=Head; ptr != nil; ptr=ptr->next ) {
					if (cmpnum(finaldate, ptr->date) >= 0) {
						/* got one before this date */
						if (RCSdebug > 0)
							diagnose( "rcsconfig: using '%s' (%s)", cb, expandrev -> string );
						expandrev -> string = strdup ( (char *)ptr->num );
						expandrev -> size = strlen ( ptr -> num );
						return ptr;
					}
				}
			}
		} else
		if( *cb == '-' ) {
			if (strcmp( cb, "-for" ) == 0 ) {
			} else if (strcmp( cb, "-include" ) == 0 ) {
				if (config_level+1 >= MAX_CONFIGS) {
					error( "maximum include file nesting exceeded" );
					return nil;
				}
				cb = gettok();
				if (cb == nil) {
					error( "missing include file name" );
					return nil;
				}

				if ((configs[config_level+1].fd = fopen( cb, "r" )) == NULL) {
					error( "couldn't open include file %s", cb );
					return nil;
				}

				if (RCSdebug > 0)
					diagnose( "rcsconfig: include '%s'", cb );

				/* pick up the trailing end-of-line */
				cb = gettok();
				++config_level;
				configs[config_level].is_file = true;
				goto end_stmt;

			} else if (strcmp( cb, "-relative_to" ) == 0 ) {
				/* 
				 * look for a pathname to make snapshot paths relative to;
				 * eg.  -relative_to /usr/dorr/work/rcs
				 */

				reldir = gettok();
				if (RCSdebug > 0)
					diagnose( "rcsconfig: using relative directory '%s'", reldir ? reldir : "<nil>" );

				if (iseol(reldir)) {
					error( "illegal relative_to construct in config file" );
					return nil;
				}
				reldir = strcpy( malloc(strlen(reldir)+1), reldir );
			} else {
				error( "illegal construct '%s' in config file", cb );
				return nil;
			}

		}   /* is it a file name? */
		else if( (*cb == '.') || (*cb == '/') ) {
			/* read pathname/rev pairs.  see if this path matches ours */
			if (RCSdebug > 10)
				diagnose( "rcsconfig: comparing with '%s'", cb );

			if ( patheq( reldir, cb, RCSfilename ) ) {
				char * rev;

				rev = gettok();
				if (iseol(rev)) {
					error( "missing revision in (pathname revision) pair in config" );
					return nil;
				}

				expandrev -> string = strdup ( rev );
				expandrev -> size = strlen ( rev );
				if (RCSdebug > 5) 
					diagnose( "rcsconfig: looking for rev (%s)", expandrev -> string );

				ptr = trace_trunk(Head, expandrev -> string, 1);
				if (ptr != nil) {
					if (RCSdebug > 0) 
						diagnose( "rcsconfig: found rev (%s)", expandrev -> string );
					return ptr;
				}

			}  else {
				(void)gettok();	/* eat up the rev # */
			}
		} else 	{
		if (expandsym2 ( cb, expandrev )) {
				ptr = trace_trunk(Head, expandrev -> string, 1);
				if (ptr != nil) return ptr;
			}
		}
	

		cb = gettok();
	    end_stmt:
		if ( !iseol(cb) ) {
			error( "config file syntax error" );
			return nil;
		}
	}

	return nil;

}


boolean
doconfig(rev,expandrev)
/* doconfig:  take an optional rev, look for a configuration file
 * if none specified, return true if some revision matches the
 * configuration.  fill the version number into expandrev
 */
char * rev;
struct buf * expandrev;
{
	struct hshentry * ptr;

	ptr = do_conf( rev, expandrev ) ;
	cleanup_configs();

	return ptr != nil;

}

int expandsym2(source, target)
        char const *source;
        struct buf *target;
/* Function: Source points to a revision number. Expandsym copies
 * the number to target, but replaces all symbolic fields in the
 * source number with their numeric values.
 * Expand a branch followed by `.' to the latest revision on that branch.
 * Ignore `.' after a revision.  Remove leading zeros.
 * returns false on error;
 */
{
        return fexpandsym2(source, target, (RILE*)0);
}

        static char const *
branchtip(branch)
        char const *branch;
{
        struct hshentry *h;
        struct hshentries *hs;

        h  =  genrevs(branch, (char*)0, (char*)0, (char*)0, &hs);
        return h ? h->num : (char const*)0;
}

        int
fexpandsym2(source, target, fp)
        char const *source;
        struct buf *target;
        RILE *fp;
/* Same as expandsym, except if FP is nonzero, it is used to expand KDELIM.  */
{
        register char const *sp, *bp;
        register char *tp;
        char const *tlim;
        register enum tokens d;
        unsigned dots;

        sp = source;
        bufalloc(target, 1);
        tp = target->string;
        if (!sp || !*sp) { /*accept nil pointer as a legal value*/
                *tp='\0';
                return true;
        }
        if (sp[0] == KDELIM  &&  !sp[1]) {
                if (!getoldkeys(fp))
                        return false;
                if (!*prevrev.string) {
                        error("working file lacks revision number");
                        return false;
                }
                bufscpy(target, prevrev.string);
                return true;
        }
        tlim = tp + target->size;
        dots = 0;

        for (;;) {
                switch (ctab[(unsigned char)*sp]) {
                    case DIGIT:
                        while (*sp=='0' && isdigit(sp[1]))
                                /* skip leading zeroes */
                                sp++;
                        do {
                                if (tlim <= tp)
                                        tp = bufenlarge(target, &tlim);
                        } while (isdigit(*tp++ = *sp++));
                        --sp;
                        tp[-1] = '\0';
                        break;

                    case LETTER:
                    case Letter:
                        {
                        register char *p = tp;
                        register size_t s = tp - target->string;
                        do {
                                if (tlim <= p)
                                        p = bufenlarge(target, &tlim);
                                *p++ = *sp++;
                        } while ((d=ctab[(unsigned char)*sp])==LETTER ||
                              d==Letter || d==DIGIT ||
                              (d==IDCHAR));
                        if (tlim <= p)
                                p = bufenlarge(target, &tlim);
                        *p = 0;
                        tp = target->string + s;
                        }
                        bp = lookupsym(tp);
                        if (bp==nil) {
/*
                                error("Symbolic number %s is undefined.", tp);
*/
                                return false;
                        }
                        do {
                                if (tlim <= tp)
                                        tp = bufenlarge(target, &tlim);
                        } while ((*tp++ = *bp++));
                        break;

                    default:
                        goto improper;
                }
                switch (*sp++) {
                    case '\0': return true;
                    case '.': break;
                    default: goto improper;
                }
                if (!*sp) {
                        if (dots & 1)
                                goto improper;
                        if (!(bp = branchtip(target->string)))
                                return false;
                        bufscpy(target, bp);
                        return true;
                }
                ++dots;
                tp[-1] = '.';
        }

    improper:
        error("improper revision number: %s", source);
        return false;
}

struct hshentry * 
findrev( rev )
/*  findrev: find the configured revision, if it exists and
 *  return its struct hshentry * info.  return nil otherwise
 */
char * rev;
{
	struct buf expandrev;
	struct hshentry * ptr;

	bufautobegin (&expandrev);
	ptr = do_conf(rev,&expandrev);
	cleanup_configs();		/* close fd's, etc */

	return ptr ;
}

