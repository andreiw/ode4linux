/*
 * @OSF_FREE_COPYRIGHT@
 */
/*
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
/*
 * HISTORY
 * $Log: env.c,v $
 * Revision 1.1.2.2  1993/01/20  19:57:48  ezf
 * 	original version
 * 	[1993/01/20  19:56:20  ezf]
 *
 * $EndLog$
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)setenv.c    5.2 (Berkeley) 6/27/88";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <stdio.h>
#if 0
extern char *malloc();
#endif
#if     defined(P)
#undef  P
#endif
#ifdef  __STDC__
static char *_findenv(const char *, int *);
#else
#ifndef const
#define const
#endif
static char *_findenv();
#endif
#ifdef  KRB5
#include <krb5/config.h>
#include <krb5/osconf.h>
#include <krb5/ext-proto.h>
#else
#ifdef __STDC__
#include <stdlib.h>
#include <string.h>
#endif
#endif

/*
 * setenv --
 *      Set the value of the environmental variable "name" to be
 *      "value".  If rewrite is set, replace any current value.
 */
int
setenv(name, value, rewrite)
        register const char *name, *value;
        int rewrite;
{
        extern char **environ;
        static int alloced;                     /* if allocated space before */
        register char *C;
        register const char *CC;

        int l_value, offset;

        if (*value == '=')                      /* no `=' in value */
                ++value;
        l_value = strlen(value);
        if ((C = _findenv(name, &offset))) {    /* find if already exists */
                if (!rewrite)
                        return(0);
                if (strlen(C) >= l_value) {     /* old larger; copy over */
                        while (*C++ = *value++);
                        return(0);
                }
        }
        else {                                  /* create new slot */
                register int    cnt;
                register char   **P;

                for (P = environ, cnt = 0; *P; ++P, ++cnt);
                if (alloced) {                  /* just increase size */
                        environ = (char **)realloc((char *)environ,
                            (unsigned int)(sizeof(char *) * (cnt + 2)));
                        if (!environ)
                                return(-1);
                }
                else {                          /* get new space */
                        alloced = 1;            /* copy old entries into it */
                        P = (char **)malloc((unsigned int)(sizeof(char *) *
                            (cnt + 2)));
                        if (!P)
                                return(-1);
                        bcopy((char *)environ, (char *)P,
                              cnt * sizeof(char *));
                        environ = P;
                }
                environ[cnt + 1] = NULL;
                offset = cnt;
        }
        for (CC = name; *CC && *CC != '='; ++CC);       /* no `=' in name */
        if (!(environ[offset] =                 /* name + `=' + value */
            malloc((unsigned int)((int)(CC - name) + l_value + 2))))
                return(-1);
        for (C = environ[offset]; (*C = *name++) && *C != '='; ++C);
        for (*C++ = '='; *C++ = *value++;);
        return(0);
}

/*
 * unsetenv(name) --
 *      Delete environmental variable "name".
 */
void
unsetenv(name)
        const   char    *name;
{
        extern  char    **environ;
        register char   **P;
        int     offset;

        while (_findenv(name, &offset))         /* if set multiple times */
                for (P = &environ[offset];; ++P)
                        if (!(*P = *(P + 1)))
                                break;
}
/*
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)getenv.c    5.5 (Berkeley) 6/27/88";
#endif /* LIBC_SCCS and not lint */

/*
 * getenv --
 *      Returns ptr to value associated with name, if any, else NULL.
 */
char *
getenv(name)
        const char *name;
{
        int offset;

        return(_findenv(name, &offset));
}

/*
 * _findenv --
 *      Returns pointer to value associated with name, if any, else NULL.
 *      Sets offset to be the offset of the name/value combination in the
 *      environmental array, for use by setenv(3) and unsetenv(3).
 *      Explicitly removes '=' in argument name.
 *
 *      This routine *should* be a static; don't use it.
 */
static char *
_findenv(name, offset)
        register const char *name;
        int *offset;
{
        extern char **environ;
        register int len;
        register char **P, *C;
        register const char *CC;

        for (CC = name, len = 0; *CC && *CC != '='; ++CC, ++len);
        for (P = environ; *P; ++P)
                if (!strncmp(*P, name, len))
                        if (*(C = *P + len) == '=') {
                                *offset = P - environ;
                                return(++C);
                        }
        return(NULL);
}
