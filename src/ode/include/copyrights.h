/*
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
 * $Log: copyrights.h,v $
 * Revision 1.1.4.2  1993/11/08  17:58:25  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/08  16:08:19  damon]
 *
 * Revision 1.1.4.1  1993/11/05  22:43:08  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/05  22:42:28  damon]
 * 
 * Revision 1.1.2.2  1993/04/27  20:04:52  damon
 * 	CR 463. Added copyrights.h
 * 	[1993/04/27  20:04:37  damon]
 * 
 * $EndLog$
 */
#ifndef _COPYRIGHTS_H
#define _COPYRIGHTS_H

#include <ode/public/error.h>
#include <ode/odedefs.h>
#include <ode/parse_rc_file.h>

BOOLEAN
legal_copyright ( char *str );
ERR_LOG
read_legal_copyrights ( struct rcfile * contents );
char
*default_copyright ( void );
ERR_LOG
read_legal_copyrights2 ( char * copyright_file );
void
add_to_copy_section ( const char * leader, const char * buf );
void
free_copy_section(void);
BOOLEAN
copyrights_ok (void);
#endif
