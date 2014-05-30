/*
 * @OSF_FREE_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: mkrelease.c,v $
 * Revision 1.2.2.7  1993/01/06  18:35:36  alan
 * 	@OSF_COPYRIGHT_INTERNAL_USE_ONLY@ and @OSF_COPYRIGHT_TEST_DRIVER@ were
 * 	checked for strlen("@OSF_COPYRIGHT_TOOLCHEST@").  They now check for
 * 	their own length.
 * 	[1993/01/06  18:33:49  alan]
 *
 * Revision 1.2.2.6  1992/12/15  20:35:03  marty
 * 	Added #include <sys/param.h>
 * 	[1992/12/15  20:34:46  marty]
 * 
 * Revision 1.2.2.5  1992/08/14  21:01:18  robert
 * 	clean up - get rid of backslashes after compund ifs,
 * 	expand usage, & ensure we get any lines BEFORE a
 * 	copyright marker
 * 	[1992/08/14  20:59:38  robert]
 * 
 * Revision 1.2.2.4  1992/08/06  18:58:54  robert
 * 	changes osf_no_copyright -> no_osf_copyright (yuk - this
 * 	should never have been invented as inconsisten witht
 * 	other osf_ style markers).
 * 
 * 	made error messages clearer
 * 	[1992/08/06  18:54:06  robert]
 * 
 * 	added 5 additional markers, which in upper case are:
 * 	osf_copyright_no_export, osf_copyright_toolchest,
 * 	osf_opyright_internal_use_only, osf_copyright_test_driver,
 * 	osf_no_copyright
 * 
 * 	added more detailed error messages, plus status to
 * 	reflect deleting a file that should not be shipped
 * 
 * 	added -d and debug info for printout
 * 	[1992/07/31  23:53:47  robert]
 * 
 * 	Changed fprintf of release string, rstr, to not
 * 	print out string within a C style comment.
 * 	Added routine makedir() using makepath.c in
 * 	libode by commenting out include of <unistd.h>
 * 	and adding include of <ode/odedefs.h>. Makefile
 * 	LIBS argument now specifies -lode. Hence, a makepath
 * 	automatically occurs in expansion and logs subdirs
 * 	before call to separate_file in while loop of main()
 * 	with calls to makedir().
 * 	[1992/01/16  23:20:18  robert]
 * 
 * Revision 1.2  1991/12/05  20:55:13  devrcs
 * 	Made a number of changes:
 * 	    - removed redundant code in separate_log
 * 	    - made expansion of multiple copyright markers selectable at
 * 	      compile time via -DDO_DUPS, but the default behavior is to
 * 	      print a warning message and not expand the extra occurances.
 * 	    - added extra processing if HISTORY is in a source file line.
 * 	      mkrelease will now only look for a log if the only thing on
 * 	      the line (besides a comment leader, is the string "HISTORY".
 * 	    - Add anything on the line after the copyright marker to each
 * 	      line of the expanded copyright as well as prefacing each line
 * 	      with the comment leader.
 * 	    - Added a check for lines of the type "/* <copyright_marker \n"
 * 	      which expand to broken 'C' code.  If any are detected, the
 * 	      expansion is done, but a warning is printed.
 * 	    - modified the copyright string arrays to allow parameterization of
 * 	      the years of the copyrights.
 * 	    - added code to print the first string in the copyright, the year
 * 	      specification, and then the second string on the first write of
 * 	      the expansion.
 * 	    - changed the form of the command to
 * 	        mkrelease -r rel-string -y yr_str -e expandbase -l logbase \
 * 	                  file | -f list-file [ -t tag ]
 * 	      where
 * 	          -r is followed by the release string; eg: "DCE Release 1.0"
 * 	          -y is followed by the year string; eg: "1990,1991"
 * 	          -e is followed by the base of the expanded tree.
 * 	          -l is followed by the base of the tree of logs
 * 	          -f is followed by the name of a file containing the paths
 * 	             to the files to expand
 * 	          -t (if speceified) is a suffix to attach to log files to
 * 	             avoid namespace collisions when running mkrelease in
 * 	             parallel on the same source tree.
 * 	          file is the name of a single file to process.
 * 
 * 	      Note that one and only one of file or -f list-file must be
 * 	      specified.  The first of 'file' or '-f list-file' encountered
 * 	      takes precedence; subsequent occurances of either are ignored
 * 	      with a message.
 * 
 * 	      Arguements may occur on the command line in any order.
 * 	    - Two log files are created as mkrelease runs; logbase/mkrel.slog[tag]
 * 	      and logbase/mkrel.elog[tag].  These list, respectively, the files for
 * 	      which processing was started and finished.  This feature allows easy
 * 	      identification of files on which processing was interrupted by some
 * 	      asyncronous event (read segv!!).
 * 	      Lines are appended to these files, if they exist, when processing
 * 	      single files.
 * 	[1991/11/26  21:44:40  mhickey]
 * 
 * 	added warning for duplicate EndLog tags and removed dead code
 * 	[91/10/16  17:24:10  ezf]
 * 
 * 	added mkrelease (aka prepfile) to ODE source tree
 * 	[91/10/16  16:35:31  ezf]
 * 
 * $EndLog$
 */
/*
 * program to expand copyright marker, strip revision history
 * and place results in separate directories
 */
#include <sys/param.h>
#include <stdio.h>
#include <ctype.h>
/* #include <unistd.h> */
#include <string.h>
#include <ode/odedefs.h>

int DEBUG = 0;

char *copyright[] = {
    "(c) Copyright", 
    "OPEN SOFTWARE FOUNDATION, INC.",
    "ALL RIGHTS RESERVED",
    0
};

char *free_copyright[] = {
    "Copyright (c)",
    "",
    "Open Software Foundation, Inc.",
    "",
    "Permission is hereby granted to use, copy, modify and freely distribute",
    "the software in this file and its documentation for any purpose without",
    "fee, provided that the above copyright notice appears in all copies and",
    "that both the copyright notice and this permission notice appear in",
    "supporting documentation.  Further, provided that the name of Open",
    "Software Foundation, Inc. (\"OSF\") not be used in advertising or",
    "publicity pertaining to distribution of the software without prior",
    "written permission from OSF.  OSF makes no representations about the",
    "suitability of this software for any purpose.  It is provided \"as is\"",
    "without express or implied warranty.",
    0
};

char *ystr, *rstr;

char *sindex(big, small)
char *big, *small;
{
    register char *bp, *bp1, *sp;
    register char c = *small++;

    if (c == 0)
	return(NULL);
    for (bp = big; *bp; bp++)
	if (*bp == c) {
	    for (sp = small, bp1 = bp + 1; *sp && *sp == *bp1++; sp++)
		;
	    if (*sp == '\0')
		return(bp);
	}
    return(NULL);
}

separate_log(inf, outf, mesgf, fn)
FILE *inf, *outf, *mesgf;
char *fn;	/* name of current input file */
{
    char buffer[BUFSIZ];
    char leader[BUFSIZ];
    char ecomment[BUFSIZ];
    char file_message[BUFSIZ];
    char *bptr = NULL;
    char *bufptr = NULL;
    int padldrlen;	/* length of comment leader including trailing blanks */
    int leaderlen;	/* leader length without any trailing whitespace */
    char **pp = (char **)NULL,**spp = (char **)NULL; 
    int did_cr = 0;
 
    /* init to default of expand copyright, and write release string & remove RCS history */
    int copy_write = 1;	
    int file_expand = 1;
    int write_skip = 0;

    while ((bufptr = fgets(buffer, sizeof(buffer), inf)) != NULL) 
    {
	if ( ((bptr = sindex(bufptr, "@OSF_")) != NULL) || ((bptr = sindex(bufptr, "@NO_")) != NULL) ) 
	{
	    copy_write = 1;	/* OK to write out an expanded copyright header */
	    file_expand = 1;	/* OK to create am expanded/stripped file under arg to -e */ 

	    if (!strncmp(bptr, "@OSF_COPYRIGHT@",	strlen("@OSF_COPYRIGHT@")))
	    {
		if (did_cr)
		    fprintf(stderr, "Warning: multiple copyright markers (extras not expanded): %s\n",fn);
		else
		{
		  spp = pp = copyright;
		  /*---* get the end of comment string *---*/
		  sprintf(ecomment,"%s", bptr + strlen("@OSF_COPYRIGHT@"));
		  *(ecomment+(strlen(ecomment)-1)) = '\0';
		}
	    }
	    if (!strncmp(bptr, "@OSF_FREE_COPYRIGHT@",	strlen("@OSF_FREE_COPYRIGHT@")))
	    {
		if (did_cr)
		    fprintf(stderr, "Warning: multiple copyright markers (extras not expanded): %s\n",fn);
		else
		{
		    spp = pp = free_copyright;
		    /*---* get the end of comment string *---*/
		    sprintf(ecomment,"%s", bptr + strlen("@OSF_FREE_COPYRIGHT@"));
		    *(ecomment+(strlen(ecomment)-1)) = '\0';
		}
	    }
	    if  (  !(strncmp(bptr, "@OSF_COPYRIGHT_NO_EXPORT@",		strlen("@OSF_COPYRIGHT_NO_EXPORT@")))
		|| !(strncmp(bptr, "@OSF_COPYRIGHT_TOOLCHEST@",	strlen("@OSF_COPYRIGHT_TOOLCHEST@")))
		|| !(strncmp(bptr, "@OSF_COPYRIGHT_INTERNAL_USE_ONLY@",	strlen("@OSF_COPYRIGHT_INTERNAL_USE_ONLY@")))
		|| !(strncmp(bptr, "@OSF_COPYRIGHT_TEST_DRIVER@",	strlen("@OSF_COPYRIGHT_TEST_DRIVER@")))
		)
	    {
		/* For any of these, don't create a stripped/exapnded file under the expand subdir. */
		/* Since one was already openned there, currently 0 length, */
		/* delete outf at status check/return, and note in log or mesgf file */
		/* Don't care about did_cr */

		file_expand = 0;
		copy_write = 0;
		fprintf(stderr, "%s not copied over; non-src marker\n", fn);

		if (!strncmp(bptr, "@OSF_COPYRIGHT_NO_EXPORT@", strlen("@OSF_COPYRIGHT_NO_EXPORT@")))
			(void) strcpy (file_message, "with @OSF_COPYRIGHT_NO_EXPORT@ should not be expanded");

		if (!strncmp(bptr, "@OSF_COPYRIGHT_TOOLCHEST@", strlen("@OSF_COPYRIGHT_TOOLCHEST@")))
		        (void) strcpy (file_message, "with @OSF_COPYRIGHT_TOOLCHEST@ should not be expanded");

		if (!strncmp(bptr, "@OSF_COPYRIGHT_INTERNAL_USE_ONLY@", strlen("@OSF_COPYRIGHT_INTERNAL_USE_ONLY@")))
			(void) strcpy (file_message, "with @OSF_COPYRIGHT_INTERNAL_USE_ONLY@ should not be expanded");

		if (!strncmp(bptr, "@OSF_COPYRIGHT_TEST_DRIVER@", strlen("@OSF_COPYRIGHT_TEST_DRIVER@")))
			(void) strcpy (file_message, "with @OSF_COPYRIGHT_TEST_DRIVER@ should not be expanded");

		if (DEBUG) fprintf(stderr, "log message = %s %s\n", fn, file_message);
		(void) fprintf(mesgf, "%s %s\n", fn, file_message);
		if (DEBUG) fprintf(stderr, "any expanded file, %s, will be removed \n", fn);
		return(7);
	    }

	    if (!strncmp(bptr, "@NO_OSF_COPYRIGHT@",	strlen("@NO_OSF_COPYRIGHT")))
	    {
		/* for C files and scripts that precede the copyright marker with a */
		/* open comment, we've already outputted a comment leader */
		/* so we must skipt expanding the copyright and close the open comment */ 
		copy_write = 0;
		file_expand = 1;
		write_skip = 1;      /* skip putting in the copyright marker ! */

		if (did_cr)
		    fprintf(stderr, "Warning: multiple release markers(extras not expanded): %s\n",fn);
		else
		{
		    spp = pp = NULL;
		    did_cr = 1;		/* say we did cr after copyright*/
					/*---* get the end of comment string *---*/
		    sprintf(ecomment,"%s",bptr + strlen("@NO_OSF_COPYRIGHT@"));
		    *(ecomment+(strlen(ecomment)-1)) = '\0';
		}
	    }

	    if (spp != (char **)NULL)
	    {
		char *scp, *ecp;
        
		/*---* a quick check before we start dumping *---*/
		if (( (scp = strchr(leader, '/')) && *(scp+1) == '*') && !((ecp = strrchr(ecomment,'/')) && *(ecp-1) == '*' ))
		    fprintf(stderr,"Possible unclosed comment: %s\n",fn);
        	padldrlen = bptr - bufptr;
        	bcopy(bufptr, leader, padldrlen);
        	leader[padldrlen] = '\0';
        	if (*pp && copy_write && DEBUG) fprintf(stderr, "DEBUG #1: OUTPUTTING COPYRIGHT NOTICE\n");
        	while (*pp && copy_write)
        	{
        	    /*---* write each record of copyright notice, *---*/
        	    /*---* via pp in place of the marker, to outf *---*/ 
        	    /*---* start with the comment leader *---*/
        	    if (DEBUG) fprintf(stderr, "DEBUG #2: record leader -> %s\n", leader);
        	    (void) fputs(leader, outf);
        	    if (pp == spp)
        	    {
			/*---* But if first write, or both ptrs equal, then *---*/ 
			/*---* dump year string efore expanded header *---*/
			if (DEBUG) fprintf(stderr, "DEBUG #3: record -> %s	year string -> %s \n", *pp, ystr);
			fprintf(outf,"%s %s ", *pp++, ystr);
		    }
		    /*---* write record terminated with end comment *---*/ 
		    if (DEBUG) fprintf(stderr, "DEBUG #4: record -> %s	end comment -> %s \n", *pp, ecomment);
		    fprintf(outf,"%s %s\n",*pp++, ecomment);
		}
        	if (DEBUG) fprintf(stderr, "setting did_cr = 1\n"); 
        	did_cr = 1;
        	continue;
	    }
	}
        if ((bptr = sindex(bufptr, "HISTORY")) != NULL)
        {
            char commstart[20], *cptr, *cptr1;

	    if (DEBUG) fprintf(stderr, "DEBUG #5: OUTPUTTING RECORD WITH HISTORY REMOVED \n"); 
            leaderlen = bptr - bufptr;
            bcopy(bufptr, leader, leaderlen);
            leader[leaderlen] = '\0';
            /*---* reduce the leader to non-whitespace, *---*/
            for (cptr=leader; isspace(*cptr); cptr++);
            for (cptr1=commstart; !isspace(*cptr); *cptr1++ = *cptr++);
            *cptr1= '\0';

            /*---*  remove leading whitespace from line with "HISTORY" *---*/
            for (cptr=buffer; isspace(*cptr); cptr++);

            /*---*
             *---* compare next strlen(leader) characters of the line to the
             *---* leader, if they don't match...
             *---*/
            if (*cptr == *commstart)
            {
                 /*---*  remove whitespace between comm. start ... *---*/
                 char *cptr3, savechar;
                 for (; !isspace(*cptr); cptr++);
                 for (; isspace(*cptr); cptr++);
                 for (cptr3=buffer+(strlen(buffer)-1); isspace(*cptr3);cptr3--);savechar= *++cptr3; *cptr3 = '\0';
                 /*---* if what is left is "HISTORY", *---*/
                 if (!strcmp(cptr, "HISTORY"))
                    break;
                 /*---* else continue *---*/
                 else
                 {
                     /*---* restore line *---*/
                     *cptr3 = savechar;
                 }
            }
        }

	/*---* fall thru to output line *---*/

	if (file_expand && DEBUG) fprintf(stderr, "DEBUG #6: record -> %s \n", bufptr);
	if (file_expand && (write_skip == 0)) 
	{
	   (void) fputs(bufptr, outf);
	}
	if (write_skip != 0) write_skip--;	
    }

    if (bufptr == NULL)
	/* if did_cr = 0, then we haven't written either a  */
	/* copyright header or release string so return -2  */
	return(did_cr ? -1 : -2);
    (void) fputs(bufptr, mesgf);
    leaderlen = padldrlen = bptr - bufptr;
    while (leaderlen >= 1 && isspace(bufptr[leaderlen-1]))
	leaderlen--;	/* adjusted length without any trailing whitespace */

    bcopy(bufptr, leader, padldrlen);
    leader[padldrlen] = '\0';
    if ((bufptr = fgets(buffer, sizeof(buffer), inf)) == NULL) { 
	if (DEBUG) fprintf(stderr, "separate log return status = 1, premature EOF\n");
	return(1);	/* EOF */
    }
    if (strncmp(bufptr, leader, leaderlen) != 0) {
	if (DEBUG) fprintf(stderr, "separate log return status = 2, missing comment leader for $Log:\n");
	return(2);	/* missing comment leader */
    }
    if (strncmp(bufptr + padldrlen, "$Log:", 5) != 0) {
	if (DEBUG) fprintf(stderr, "separate log return status = 3, missing proper $Log:\n");
	return(3);	/* missing $Log: */
    }
    if (index(bufptr + padldrlen + 5, '$') == NULL) {
	if (DEBUG) fprintf(stderr, "separate log return status = 4, missing proper trailing $ after $Log:\n"); 
	return(4);	/* missing trailing '$' note that $Log:" is 5 chars */
    }
    (void) fputs(bufptr, mesgf);
    for (;;) {
	register char *ptr;

	if ((bufptr = fgets(buffer, sizeof(buffer), inf)) == NULL) {
	    if (DEBUG) fprintf(stderr, " separate log retruns status = 5, premature EOF\n");
	    return(5);	/* EOF */
	}
	ptr = bufptr;
	if (strncmp(bufptr, leader, leaderlen) != 0) {
	    if (DEBUG) fprintf(stderr, " separate log retruns status = 6, missing comment leader and/or $EndLog$\n");
	    return(6);	/* missing comment leader */
	}
	ptr += leaderlen;
	while (isspace(*ptr))
	    ptr++;	/* skip any whitespace */
	if (strncmp(ptr, "$EndLog$", 8) == 0)
	    break;	/* found $EndLog$ */
	(void) fputs(bufptr, mesgf);
    }
    (void) fputs(bufptr, mesgf);
    if (file_expand && DEBUG) fprintf(stderr, "DEBUG #7: record leader -> %s\n", leader);
    if (file_expand) (void) fputs(leader, outf);
    if (file_expand && DEBUG) fprintf(stderr, "DEBUG #8: release string -> %s\n", rstr);
    if (file_expand) (void) fprintf(outf, "%s\n", rstr);
    while ((bufptr = fgets(buffer, sizeof(buffer), inf)) != NULL) {
#ifdef DO_DUPS
	if ((bptr = sindex(bufptr, "@OSF_COPYRIGHT@")) != NULL) {
	    leaderlen = bptr - bufptr;
	    bcopy(bufptr, leader, leaderlen);
	    leader[leaderlen] = '\0';
	    for (pp = copyright; *pp != 0; pp++) {
		(void) fputs(leader, outf);
		(void) fputs(*pp, outf);
	    }
	    continue;
	}
	if ((bptr = sindex(bufptr, "@OSF_FREE_COPYRIGHT@")) != NULL) {
	    leaderlen = bptr - bufptr;
	    bcopy(bufptr, leader, leaderlen);
	    leader[leaderlen] = '\0';
	    for (pp = free_copyright; *pp != 0; pp++) {
		(void) fputs(leader, outf);
		(void) fputs(*pp, outf);
	    }
	    continue;
	}
#else
	if ((bptr = sindex(bufptr, "@OSF_")) != NULL) 
        {
            if ((  !strncmp(bptr, "@OSF_COPYRIGHT@",			strlen("@OSF_COPYRIGHT@"))
                || !strncmp(bptr, "@OSF_FREE_COPYRIGHT@",		strlen("@OSF_FREE_COPYRIGHT@"))
		|| !strncmp(bptr, "@OSF_COPYRIGHT_NO_EXPORT@",		strlen("@OSF_COPYRIGHT_NO_EXPORT@"))
		|| !strncmp(bptr, "@OSF_COPYRIGHT_TOOLCHEST@",		strlen("@OSF_COPYRIGHT_TOOLCHEST@"))
		|| !strncmp(bptr, "@OSF_COPYRIGHT_INTERNAL_USE_ONLY@",	strlen("@OSF_COPYRIGHT_INTERNAL_USE_ONLY@"))
		|| !strncmp(bptr, "@OSF_COPYRIGHT_TEST_DRIVER@",	strlen("@OSF_COPYRIGHT_TEST_DRIVER@"))
                ) && did_cr) fprintf (stderr,"Warning: multiple copyright markers: %s\n",fn);
        }
	if ((bptr = sindex(bufptr, "@NO_")) != NULL)
	{
	    if (  !strncmp(bptr, "@NO_OSF_COPYRIGHT@",			strlen("@NO_OSF_COPYRIGHT@")) && did_cr)
		fprintf (stderr,"Warning: multiple copyright markers: %s\n",fn);
	}
    
#endif /*---* DO_DUPS *---*/

	if (strncmp(bufptr, leader, leaderlen) == 0
	    && sindex(bufptr + leaderlen, "$EndLog$") != NULL) {
	      fprintf(stderr, "%s: warning duplicate $EndLog$\n", fn);
	      continue;
	}
	(void) fputs(bufptr, outf);
    }
    return(did_cr ? 0 : -3);
}

separate_file(infile, outfile, mesgfile, slogf, elogf)
char *infile, *outfile, *mesgfile;
FILE *slogf, *elogf;
{
    FILE *inf, *outf, *mesgf;
    int status;

    if ((inf = fopen(infile, "r")) == NULL) {
	fprintf(stderr, "%s: error opening input file\n", infile);
	return(1);
    }
    (void) unlink(outfile);
    if ((outf = fopen(outfile, "w")) == NULL) {
	fprintf(stderr, "%s: error opening output file\n", outfile);
	(void) unlink(outfile);
	return(1);
    }
    (void) unlink(mesgfile);
    if ((mesgf = fopen(mesgfile, "w")) == NULL) {
	fprintf(stderr, "%s: error opening message file\n", mesgfile);
	(void) unlink(outfile);
	(void) unlink(mesgfile);
	return(1);
    }
   
    fprintf(slogf,"Starting separation of %s\n",infile);

    status = separate_log(inf, outf, mesgf, infile);

    if ((status == 0) || (status == 7)) fprintf (elogf, "Completed log separation of %s\n",infile);
    if ((status == 0) || (status == 7)) fprintf (stderr, "Completed log separation of %s\n",infile);  

    if (DEBUG) fprintf(stderr, "separate_log returns with status = %d\n", status);

    if (status == 7)
    {
	/* remove a (zero length) file from ./expand subdir*/ 
	(void) fclose(outf);
	(void) unlink(outfile);
	return(0);
    }

    if (status > 0)
    {
	if ((status > 0) && (status < 7))
	{
        	fprintf(stderr, "%s: log separation error = %d: ", infile, status);
		if (status == 1 || status == 5) fprintf(stderr,"premature EOF\n");
		if (status == 2) fprintf(stderr,"didn't copy over file - missing comment leader for $Log:\n");
		if (status == 3) fprintf(stderr,"didn't copy over file - missing proper $Log:\n");
		if (status == 4) fprintf(stderr,"didn't copy over file - missing proper trailing $ after $Log:\n");
		if (status == 6) fprintf(stderr,"didn't copy over file - missing comment leader and/or $EndLog$\n");
	}
	else 
		fprintf(stderr, "%s: error during log separation, status = %d\n", infile, status);
    }

    if (status < 0)
    {
	fprintf(stderr, "%s: log separation error = %d: ", infile, status);
	if (status == -1) fprintf(stderr,"didn't copy over file - missing proper HISTORY\n");
	if (status == -3) fprintf(stderr,"didn't copy over file - insufficient/bad markers to write copyright/release string\n");
	if (status == -2) fprintf(stderr,"didn't copy over file - insufficient/bad markers or keywords to process\n");
    }

    if ((status != 7) && (status != 0))
    {
	(void) fclose(inf);
	(void) fclose(outf);
	(void) fclose(mesgf);
	(void) unlink(outfile);
	(void) unlink(mesgfile);
	return(1);
    }

    if (ferror(inf) || fclose(inf) == EOF) {
	fprintf(stderr, "%s: error reading input file\n", infile);
	(void) fclose(inf);
	(void) fclose(outf);
	(void) fclose(mesgf);
	(void) unlink(outfile);
	(void) unlink(mesgfile);
	return(1);
    }
    if (ferror(outf) || fclose(outf) == EOF) {
	fprintf(stderr, "%s: error writing output file\n", outfile);
	(void) fclose(outf);
	(void) fclose(mesgf);
	(void) unlink(outfile);
	(void) unlink(mesgfile);
	return(1);
    }
    if (ferror(mesgf) || fclose(mesgf) == EOF) {
	fprintf(stderr, "%s: error writing message file\n", mesgfile);
	(void) fclose(mesgf);
	(void) unlink(outfile);
	(void) unlink(mesgfile);
	return(1);
    }
    return(0);
}

makedir (dir)
char	* dir;
{
	char	dbuf [MAXPATHLEN];
	char	* ptr;

	ptr = concat ( dbuf, sizeof ( dbuf ), dir, NULL );

	while (*ptr != '/')
		ptr--;

	*ptr++ = '/';
	*ptr++ = '.';
	*ptr++ = NULL;

	if ( makepath ( dbuf, NULL, TRUE, TRUE ) != 0 )
	{
		/* uquit ( ERROR, FALSE, "makepath %s failed.\n", dbuf ); */
		printf("makepath %s failed.\n", dbuf );
	}
}

main(argc, argv)
int argc;
char **argv;
{
    char i,
         infile[BUFSIZ],    /*---* path to (current) input file          *---*/
         outfile[BUFSIZ],   /*---* path to (current) output file         *---*/
         elogfile[BUFSIZ],  /*---* path to endof expand log file         *---*/
         slogfile[BUFSIZ],  /*---* path to start expand log file         *---*/
         mesgfile[BUFSIZ],  /*---*  "    " (current) history file        *---*/
         buff[BUFSIZ],      /*---* read buffer                           *---*/
         *lfilep=(char *)NULL, /*---* pntr to name of list file          *---*/
         *tagp=(char *)NULL, /*---* pntr to optional output file tag     *---*/
         *msgp,             /*---* pnter to variant part of history file.*---*/
         *outp,             /*---* pnter to variant part of output file. *---*/
         *ptr,              /*---* utility pointer                       *---*/
         **cp = argv+1;    /*---* pointer for arg parsing               *---*/
    int errors = 0;
    FILE *elogf,            /*---* fptr to (current) end expand log file *---*/
         *slogf,            /*---* fptr to (current) start expand log    *---*/
         *lfilef,           /*---* fptr to list file                     *---*/
         *fopen();

    if (argc < 10) {
        fprintf(stderr, "usage: mkrelease -r <string> -y <string> -e <pathname> -l <pathname> <pathname/file> | -f <list_of_files> [-t tag] \n");
	fprintf(stderr, "\n");
 	fprintf(stderr, "Examples: \n");
 	fprintf(stderr, "mkrelease -r \"OSF/1 1.3\" -y \"1990, 1991, 1992, 1993\" -e ./expand -l ./log test.c \n");  
	fprintf(stderr, "mkrelease -r \"OSF/1 1.2.1\" -y \"1990, 1991, 1992, 1993\" -e ./expand -l ./log -f file.list \n");
	fprintf(stderr, "\n");
	fprintf(stderr, "where file.list contains entries of the type: \n");
	fprintf(stderr, "./src/dev/MAKEDEV/AT386/MAKEDEV.sh \n");
	fprintf(stderr, "./src/etc/Makefile \n");
	fprintf(stderr, "etc... \n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Note that mkrelease will create whatever subdirs precede the file name \n");
	fprintf(stderr, "under the pathnames given as args to both the -e and -l switches \n"); 
	fprintf(stderr, "\n");
	exit(1); 
    }

    *infile = '\0';
    while (*cp)
    {
       if (**cp == '-' )
       {
          /*---* all flags require, values...make sure they are there *---*/
          if (!(*(cp+1)) || **(cp+1) == '-')
          {
             fprintf(stderr, "Missing value for %s\n",*cp);
	     fprintf(stderr, "usage: mkrelease -r rel-string -y year-string -e <expandbase> -l <logbase>  <file> | -f list-file [-t tag] \n");
             exit(1);
          }

          /*---* set pointers, etc, depending on flag *---*/
          switch(*((*cp)+1))
          {
              case 'e': sprintf(outfile,"%s/",*++cp);
                        outp=outfile+strlen(outfile);
                        break;

              case 'f': if (*infile == '\0')
                          lfilep= *++cp;
                        else
                        {
                          fprintf(stderr, "infile already specified, -f option ignored.");
                          cp++;
                        }
                        break;
  
              case 'l': sprintf(mesgfile,"%s/",*++cp);
                        msgp=mesgfile+strlen(mesgfile);
                        break;
 
              case 'r': rstr= *++cp; break;
 
              case 't': tagp= *++cp; break;
             
              case 'y': ystr= *++cp; break;

              default : fprintf(stderr, "unknown flag: %s\n",*cp);
 	                fprintf(stderr, "usage: mkrelease -r rel-string -y year-string -e <expandbase> -l <logbase>  <file> | -f list-file [-t tag] \n");
                        exit(1);
                        break;
          }  /*---* end switch *---*/
       }  /*---* end if (!(*cp   *---*/
       else
       {
          if ( lfilep )
             fprintf(stderr,"list file already specified, infile ignored.\n");
          else if (*infile != '\0')
             fprintf(stderr, "infile already specified, infile ignored.\n");
          else 
             strcpy(infile, *cp);
       } 
       
       cp++;
    }
   
          
    /*---* create name of startlog file; use mesgfile to avoid a buff *---*/
    sprintf(msgp, tagp? "%s.%s": "%s%s", "mkrel.slog", tagp? tagp:"");
    if (!(slogf = fopen(mesgfile,"a")))
    {
         perror("startlog file");
         exit(1);
    }
    /*---* create name of endlog file; use mesgfile to avoid a buff *---*/
    sprintf(msgp, tagp? "%s.%s": "%s%s", "mkrel.elog", tagp? tagp:"");
    if (!(elogf = fopen(mesgfile,"a")))
    {
         perror("endlog file");
         exit(1);
    }

    /*---* if infile is set... *---*/
    if ( *infile )
    {
        /*---* then we have one file to process *---*/
        strcpy(outp, infile);
        strcpy(msgp, infile);
	if (separate_file(infile, outfile, mesgfile,elogf, slogf))
	    errors = 1;
    }
    /*---* else ... *---*/
    else
    {
        /*---* we have a list of files.  Try to open the list file *---*/
        if (!(lfilef = fopen(lfilep,"r")))
        {
             perror("list file");
             exit(1);
        }

        /*---* read the list file till EOF... *---*/
        while ((fgets(buff, sizeof(buff), lfilef)) != NULL) 
        {
             buff[strlen(buff) -1] = '\0';
             /*---* create the outfile name *---*/
             strcpy(outp, buff);
	     /*---* do makepath for outfile path via libode *---*/
	     makedir(outfile);
             /*---* create the history file name *---*/
             strcpy(msgp, buff);
	     /*---* do makepath for mesgfile path via libode *---*/
	     makedir(mesgfile);
             /*---* process the file *---*/
             if (separate_file(buff, outfile, mesgfile,elogf, slogf))
                 errors = 1;
             
        }
     }
            
    exit(errors);
}
