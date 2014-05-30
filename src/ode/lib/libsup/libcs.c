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
 * $Log: libcs.c,v $
 * Revision 1.3.7.2  1994/02/17  16:24:12  damon
 * 	CR 1056. Moved from bin/sup
 * 	[1994/02/17  16:22:30  damon]
 *
 * Revision 1.3.7.1  1994/02/15  17:36:05  damon
 * 	CR 1051. Made pedantic changes
 * 	[1994/02/15  17:35:42  damon]
 * 
 * Revision 1.3.2.7  1992/12/03  19:08:24  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:37:34  damon]
 * 
 * Revision 1.3.2.6  1992/11/09  22:15:51  damon
 * 	CR 296. Removed warnings
 * 	[1992/11/09  22:10:35  damon]
 * 
 * Revision 1.3.2.5  1992/09/24  18:59:46  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:18:22  gm]
 * 
 * Revision 1.3.2.4  1992/07/26  17:37:45  gm
 * 	Removed BSD unix dependencies.
 * 	[1992/07/17  20:54:28  gm]
 * 
 * Revision 1.3.2.3  1992/02/13  15:09:01  gm
 * 	Added malloc cast to remove compiler warning.
 * 	[1992/02/13  15:07:18  gm]
 * 
 * Revision 1.3.2.2  1992/01/08  15:28:47  damon
 * 	Removed code made redundant by libode
 * 	[1992/01/08  15:08:30  damon]
 * 
 * Revision 1.3  1991/12/05  20:53:50  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:07:02  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:46:33  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:16:35  zeliff]
 * 
 * Revision 1.2  90/10/07  21:36:06  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:46:11  gm]
 * 
 * Revision 1.3  90/07/17  12:26:24  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  17:03:44  gm]
 * 
 * Revision 1.2  90/06/29  14:18:32  devrcs
 * 	Created from defunct libcs library sources.
 * 	[90/06/23  15:03:13  gm]
 * 
 * $EndLog$
 */

/*
 * routines liberated from libcs
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/wait.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include <sys/param.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <ctype.h>
#include <setjmp.h>
#include <string.h>

/*
 *  expand - expand wildcard filename specifications
 *
 *  Usage:
 *	int expand(spec, buffer, bufsize);
 *	char *spec, **buffer;
 *	int bufsize;
 *
 *  Expand takes a file specification, and expands it into filenames
 *  by resolving the characters '*', '?', '[', ']', '{', '}' and '~'
 *  in the same manner as the shell.  You provide "buffer", which is
 *  an array of char *'s, and you tell how big it is in bufsize.
 *  Expand will compute the corresponding filenames, and will fill up
 *  the entries of buffer with pointers to malloc'd strings.
 *
 *  The value returned by expand is the number of filenames found.  If
 *  this value is -1, then malloc failed to allocate a string.  If the
 *  value is bufsize + 1, then too many names were found and you can try
 *  again with a bigger buffer.
 *
 *  This routine was basically created from the csh sh.glob.c file with
 *  the following intended differences:
 *
 *	Filenames are not sorted.
 *	All expanded filenames returned exist.
 */

static	jmp_buf	sjbuf;

static	char	pathbuf[MAXPATHLEN];
static	char	*ppath, *pathp, *lastpathp;

static	const char	*globchars = "{[*?";	/* meta characters */
static	char	*entp;			/* current dir entry pointer */

static	char	**BUFFER;		/* pointer to the buffer */
static	int	BUFSIZE;		/* maximum number in buffer */
static	int	bufcnt;			/* current number in buffer */

/*
 * FORWARD DECLARATIONS
 */
static int
execbrc( char *, char *);
static int
addpath( char );
static void
glob( char *);

static void
addone(char *s1, const char *s2 )
{
	register char *ep;

	if (bufcnt >= BUFSIZE) {
		bufcnt = BUFSIZE + 1;
		longjmp(sjbuf, 1);
	}
	ep = (char *)malloc(strlen(s1) + strlen(s2) + 1);
	if (ep == 0) {
		bufcnt = -1;
		longjmp(sjbuf, 1);
	}
	BUFFER[bufcnt++] = ep;
	while (*s1) *ep++ = *s1++;
	while ((*ep++ = *s2++));
}

static int
amatch(char *s, char *p )
{
	register int scc;
	int ok, lc;
	char *spathp;
	struct stat stb;
	int c, cc;

	for (;;) {
		scc = *s++ & 0177;
		switch (c = *p++) {
		case '{':
			return (execbrc(p - 1, s - 1));
		case '[':
			ok = 0;
			lc = 077777;
			while ((cc = *p++)) {
				if (cc == ']') {
					if (ok) break;
					return (0);
				}
				if (cc == '-') {
					if (lc <= scc && scc <= *p++)
						ok++;
				} else
					if (scc == (lc = cc))
						ok++;
			}
			if (cc == 0) return (0);
			continue;
		case '*':
			if (!*p) return (1);
			if (*p == '/') {
				p++;
				goto slash;
			}
			for (s--; *s; s++)
				if (amatch(s, p))
					return (1);
			return (0);
		case 0:
			return (scc == 0);
		default:
			if (c != scc) return (0);
			continue;
		case '?':
			if (scc == 0) return (0);
			continue;
		case '/':
			if (scc) return (0);
slash:
			s = entp;
			spathp = pathp;
			while (*s)
				if (addpath(*s++)) goto pathovfl;
			if (addpath('/')) goto pathovfl;
			if (stat(ppath, &stb) >= 0 &&
			    (stb.st_mode&S_IFMT) == S_IFDIR)
				if (*p == 0)
					addone(ppath, "");
				else
					glob(p);
pathovfl:
			pathp = spathp;
			*pathp = 0;
			return (0);
		}
	}
}

static char
match( char *s, char *p )
{
	register int c;
	register char *sentp;

	if (*s == '.' && *p != '.') return(0);
	sentp = entp;
	entp = s;
	c = amatch(s, p);
	entp = sentp;
	return (c);
}

static void
matchdir( char *pattern )
{
	register struct dirent *dp;
	DIR *dirp;

	dirp = opendir(ppath);
	if (dirp == NULL)
		return;
	while ((dp = readdir(dirp)) != NULL) {
		if (dp->d_ino == 0) continue;
		if (match(dp->d_name, pattern))
			addone(ppath, dp->d_name);
	}
	closedir(dirp);
	return;
}

static int
execbrc( char *p, char *s)
{
	char restbuf[MAXPATHLEN + 1];
	register char *pe, *pm, *pl;
	int brclev = 0;
	char *lm, savec, *spathp;

	for (lm = restbuf; *p != '{'; *lm++ = *p++)
		continue;
	for (pe = ++p; *pe; pe++)
	switch (*pe) {
	case '{':
		brclev++;
		continue;
	case '}':
		if (brclev == 0) goto pend;
		brclev--;
		continue;
	case '[':
		for (pe++; *pe && *pe != ']'; pe++)
			continue;
		if (!*pe) break;
		continue;
	}
pend:
	if (brclev || !*pe) return (0);
	for (pl = pm = p; pm <= pe; pm++)
		switch (*pm & 0177) {
		case '{':
			brclev++;
			continue;
		case '}':
			if (brclev) {
				brclev--;
				continue;
			}
			goto doit;
		case ',':
			if (brclev) continue;
doit:
			savec = *pm;
			*pm = 0;
			strcpy(lm, pl);
			strcat(restbuf, pe + 1);
			*pm = savec;
			if (s == 0) {
				spathp = pathp;
				glob(restbuf);
				pathp = spathp;
				*pathp = 0;
			} else if (amatch(s, restbuf))
				return (1);
			pl = pm + 1;
			continue;

		case '[':
			for (pm++; *pm && *pm != ']'; pm++)
				continue;
			if (!*pm) break;
			continue;
		}
	return (0);
}

static int
addpath( char c )
{
	if (pathp >= lastpathp)
		return(1);
	*pathp++ = c;
	*pathp = 0;
	return(0);
}

static int
gethdir( char *home )
{
	register struct passwd *pp = getpwnam(home);

	if (pp == 0)
		return(1);
	strcpy(home, pp->pw_dir);
	return(0);
}

static void
glob( char *as )
{
	register char *cs;
	register char *spathp, *oldcs;
	struct stat stb;

	spathp = pathp;
	cs = as;
	if (*cs == '~' && pathp == ppath) {
		if (addpath('~')) goto endit;
		for (cs++; isalnum(*cs) || *cs == '_' || *cs == '-';)
			if (addpath(*cs++)) goto endit;
		if (!*cs || *cs == '/') {
			if (pathp != ppath + 1) {
				*pathp = 0;
				if (gethdir(ppath + 1)) goto endit;
				strcpy(ppath, ppath + 1);
			} else
				strcpy(ppath, getenv("HOME"));
			pathp = ppath;
			while (*pathp) pathp++;
		}
	}
	while (*cs == 0 || strchr(globchars, *cs) == 0) {
		if (*cs == 0) {
			if (lstat(ppath, &stb) >= 0) addone(ppath, "");
			goto endit;
		}
		if (addpath(*cs++)) goto endit;
	}
	oldcs = cs;
	while (cs > as && *cs != '/')
		cs--, pathp--;
	if (*cs == '/')
		cs++, pathp++;
	*pathp = 0;
	if (*oldcs == '{') {
		execbrc(cs, NULL);
		return;
	}
	/* this should not be an lstat */
	if (stat(ppath, &stb) >= 0 && (stb.st_mode&S_IFMT) == S_IFDIR)
		matchdir(cs);
endit:
	pathp = spathp;
	*pathp = 0;
	return;
}

int expand( char *spec, char **buffer, int bufsize )
{
	pathp = ppath = pathbuf;
	*pathp = 0;
	lastpathp = &ppath[MAXPATHLEN - 2];
	BUFFER = buffer;
	BUFSIZE = bufsize;
	bufcnt = 0;
	if (setjmp(sjbuf) == 0)
	    glob(spec);
	return(bufcnt);
}
