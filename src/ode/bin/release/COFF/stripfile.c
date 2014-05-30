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
 * $Log: stripfile.c,v $
 * Revision 1.1.2.4  1992/12/03  19:08:07  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:37:18  damon]
 *
 * Revision 1.1.2.3  1992/11/11  18:47:17  damon
 * 	CR 329. Added includes for file.h and a.out.h
 * 	[1992/11/11  18:46:49  damon]
 * 
 * Revision 1.1.2.2  1992/09/24  18:59:23  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/24  13:59:04  gm]
 * 
 * $EndLog$
 */

#include <a.out.h>
#include <sys/file.h>

stripfile(file, fd, fname)
char *file;
register int fd;
char *fname;
{
    int pid, status, w;
    extern int strip;
    struct {
	struct filehdr fhdr;
	struct aouthdr ahdr;
    } hdrs;

    if (!strip)
	return(0);
    (void) lseek(fd, (long)0, L_SET);
    if (read(fd, (char *)&hdrs, sizeof(hdrs)) != sizeof(hdrs))
	return(0);
#ifdef mips
    if (! ISCOFF(hdrs.fhdr.f_magic))
#endif
#ifdef multimax
    if (! ISMAGIC(hdrs.fhdr.f_magic))
#endif
	return(0);
    if ((hdrs.fhdr.f_flags & F_RELFLG) == 0)
	return 0;	/* Relocation information present in file */
#ifdef multimax
    if (hdrs.ahdr.magic != AOUT1MAGIC && hdrs.ahdr.magic != AOUT2MAGIC &&
	hdrs.ahdr.magic != PAGEMAGIC)
	return 0;
#endif
    if (hdrs.fhdr.f_symptr == 0) {
	diag("%s: already stripped", file);
	return(0);
    }
    diag("%s: stripping", file);
    if ((pid = fork()) == -1) {
	ewarn("strip fork failed");
	return(1);
    }
    if (pid == 0) {
	execl("/bin/strip", "strip", fname, 0);
	_exit(127);
    }
    do {
	w = wait(&status);
    } while (w != pid && w != -1);
    if (w != pid)
	return(1);
    return(0);
}

