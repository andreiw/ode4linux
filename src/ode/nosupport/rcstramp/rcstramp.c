/*
 * @OSF_FREE_COPYRIGHT@
 */
/*
 * Copyright Hewlett-Packard Company 1993 
 *
 * To anyone who acknowledges that this software is provided "as is"
 * without any express or implied warranty, permission to use, copy,
 * modify, and distribute this software for any purpose is hereby
 * granted without fee, provided that the above copyright notice and
 * this notice appears in all copies, and that the name of
 * Hewlett-Packard Company not be used in advertising or publicity
 * pertaining to distribution of the software without specific,
 * written prior permission.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  
 */
/*
 * HISTORY
 * $Log: rcstramp.c,v $
 * Revision 1.1.2.2  1993/01/20  19:57:52  ezf
 * 	original version
 * 	[1993/01/20  19:56:22  ezf]
 *
 * $EndLog$
 */

/*
 * Trampoline an ODE remote command through to another system.
 * 
 * The command appears as argv[0]; its arguments are argv[1..n].
 * 
 * We actually exec a "cover" program, which we find through an
 * environment variable.
 * 
 * Before execing, we import environment variables from
 * "./rcstramp.conf", which has a series of "standard" name=value lines.
 * 
 * Lines in rcstramp.conf beginning with a "#" are comments.  "#" is
 * only special in column 1.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define REWRITE	1	/* replace current value of env. variable (if any) */

static void read_env();
int verbose = 0;

main(argc, argv)
    int argc;
    char **argv;
{
    char *cover;
    extern char **environ;
    char *nargv[100];
    char hostname[100];
    char *faketestdir, *realtestdir;
    int a, i;
    read_env("rcstramp.conf");
    
    gethostname(hostname, sizeof(hostname));
    fprintf(stderr, "[ via %s to %s ]\n", hostname, getenv("AUTHCOVER_HOST"));
    cover = getenv("RCS_COVER");
    if (!cover) {
        fprintf(stderr, "RCS_COVER not defined\n");
        exit(1);
    }
    faketestdir = getenv("FAKE_TESTDIR");
    realtestdir = getenv("AUTHCOVER_TESTDIR");
    if (getenv ("VERBOSE")) verbose = 1;
    a = 0;
    nargv[a++] = cover;
    for (i=0; i<argc; i++) {
        if (strncmp(argv[i], "./rcstemp", 9) == 0) {
            char *temp;
            temp = malloc(5);
            sprintf(temp, "%d", i);
            if (access(argv[i], R_OK) < 0) {
                nargv[a++] = "-t0";
            } else {
                nargv[a++] = "-t2";
            }
            nargv[a++] = temp;
        } 
    }
    for (i=0; i<argc; i++) {
        if (faketestdir &&
            strncmp(argv[i], faketestdir, strlen(faketestdir)) == 0) {
            char *temp;
            temp = malloc (strlen (realtestdir) + strlen(argv[i]));
            strcpy(temp, realtestdir);
            strcat(temp, argv[i]+strlen(faketestdir));
	    if (verbose)
                fprintf(stderr, "[ Translated %s to %s ]\n", argv[i], temp);
            nargv[a++] = temp;
        } else {
            nargv[a++] = argv[i];
        }
    }
    nargv[a++] = 0;
#ifdef ENVIRON_DEBUG
    for (i=0; environ[i]; i++) {
        fprintf(stderr, "%d: %s\n", i, environ[i]);
    }
    
    system ("printenv 1>&2");
#endif
    if (verbose) {
        fprintf(stderr, "[ command is");
        for (i=0; nargv[i]; i++)
            fprintf(stderr, " %s", nargv[i]);
        fprintf(stderr, " ]\n");
    }
    execve (cover, nargv, environ);
}
    

static void read_env(pathname)
    char *pathname;
{
    char buf[1024];
    char *cp;
    
    FILE *f = fopen(pathname, "r");
    if (!f) {
        perror(pathname);
        exit(1);
    }
    while (fgets(buf, sizeof(buf), f)) {
        if (buf[0] == '#')
            continue;
        
        cp = strchr(buf, '\n');
        if (cp)
            *cp = '\0';
        cp = strchr(buf, '=');
        if (cp) {
            *cp++ = '\0';
#ifdef ENVIRON_DEBUG
            fprintf(stderr, "setenv(%s, %s)\n", buf, cp);
#endif
            setenv(buf, cp, REWRITE);
        }
    }
}
