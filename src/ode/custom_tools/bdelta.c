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
 * $Log: bdelta.c,v $
 * Revision 1.1.11.5  1993/12/14  21:32:34  marty
 * 	CR # 883 - bdelta fix for ode2.3.3
 * 	[1993/12/14  21:32:13  marty]
 *
 * Revision 1.1.11.4  1993/12/08  18:05:39  marty
 * 	Get bdelta workon for ODE2.3
 * 	[1993/12/08  18:05:04  marty]
 * 
 * Revision 1.1.11.3  1993/12/03  17:32:49  marty
 * 	CR # 883 - Add -quiet option to reduce output.
 * 	[1993/12/03  17:32:36  marty]
 * 
 * Revision 1.1.11.2  1993/12/02  21:55:23  marty
 * 	CR # 883 - Add -lastrun and make it ODE2.3 compatible.
 * 	[1993/12/02  21:55:03  marty]
 * 
 * 	Add the "-lastrun" option and update for ODE2.3.
 * 	[1993/12/02  16:14:55  marty]
 * 
 * Revision 1.1.11.1  1993/11/29  20:07:46  marty
 * 	Updated bdelta for ode2.3.3.
 * 	[1993/11/29  20:07:20  marty]
 * 
 * Revision 1.1.2.4  1992/12/15  20:09:44  marty
 * 	Added include of <sys/param.h>.
 * 	[1992/12/15  20:09:28  marty]
 * 
 * Revision 1.1.2.3  1992/12/03  19:08:41  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:37:50  damon]
 * 
 * Revision 1.1.2.2  1992/12/01  23:13:18  pnh
 * 	First revision.
 * 	[1992/12/01  23:01:52  pnh]
 * 
 * $EndLog$
 */

static char * rcsid =
 "$RCSfile: bdelta.c,v $";

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <ode/odedefs.h>
#include <ode/parse_rc_file.h>
#include <ode/interface.h>
#include <ode/sci.h>



char * progname = "bdelta";

#define BDIFF_CMD	"bdiff"

#define C_OP		"-c"
#define W_OP		"-w"

#define OUTPUT_OP	"-o"
#define PATCHES_OP	"-patchesonly"
#define REVISION_OP	"-r"
#define TABLE_OP	"-tableonly"
#define START_OP	"-start"
#define	END_OP		"-end"
#define LAST_RUN_OP	"-lastrun"
#define QUIET_OP	"-quiet"

#define BDELTATABLE	"bdelta.table"
#define DATE_PATTERN    "[0-9]/[0-9]/[0-9][0-9] [0-9]/[0-9][0-9]/[0-9][0-9] [0-9][0-9]/[0-9]/[0-9][0-9] [0-9][0-9]/[0-9][0-9]/[0-9][0-9]"

#define MAXPATCHCOUNT	1000000

BOOLEAN bdelta(BOOLEAN, char *, char *, char *,
char *, char *, char *, BOOLEAN, BOOLEAN, BOOLEAN, BOOLEAN);
BOOLEAN make_difftable(char *, char *, BOOLEAN, char *, char *, char *);
BOOLEAN get_revision_element(char *, char *, char *, char *, char *);
BOOLEAN in_range(char *, char *, char *, char *, char *, char *);
BOOLEAN make_patchfile(char *, char *, char *, char *, char *, char *, BOOLEAN,
BOOLEAN);
void get_prevrev(char *, char *, char *, char *);
void print_revision_element (FILE *, char *,char *, char *, char *, char *, char *);

char last_run_date[ MAXPATHLEN ],
     last_run_time[ MAXPATHLEN ];
char sb_srcdir [ MAXPATHLEN ];
BOOLEAN use_last_run;
char *last_date_processed,
     *last_time_processed;
BOOLEAN build_table_from_scratch;



/* UUINIT is defined in include/interface.h (which is included by odedefs.h)
 * as:
 *
 *    patter, max_entries, h2hdl dups?, min args, maxargs, legal arg descr
 *
 * The legal arg description is a primitive regular expression capability
 * implemented in lib/libode/match.c (gmatch(), called by match_arg_list()
 * [lib/libode/interface.c] which processes legal arg descs).
 *
 * ARGS_OP [include/odedefs.h] seems to be "a real argument, anything not
 * beginning w/ -".
 * {START,END}_OP: I include 06/09/92 (leading zero) as legal because this 
 * corresponds to OT convention.
 */

UIINIT init [] = {

  { ALL_OP,      1, OVERWRITE, 0, 0, "" },
  { ARGS_OP,     1, OVERWRITE, 0, 1, "" },
  { C_OP,	 1, OVERWRITE, 0, 0, "" },
  { END_OP,      1, OVERWRITE, 1, 1, DATE_PATTERN },
  { OUTPUT_OP,   1, OVERWRITE, 1, 1, ARGS_OP },
  { PATCHES_OP,	 1, OVERWRITE, 0, 0, "" },
  { QUIET_OP,	 1, OVERWRITE, 0, 0, "" },
  { REVISION_OP, 1, OVERWRITE, 1, 1, "" },
  { START_OP,    1, OVERWRITE, 1, 1, DATE_PATTERN },
  { TABLE_OP,	 1, OVERWRITE, 0, 0, "" },
  { LAST_RUN_OP, 1, OVERWRITE, 0, 0, "" },
  { W_OP,	 1, OVERWRITE, 0, 0, "" }
};


#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))



/* 
 * bdelta [-all|-start <date> -end <date>] [-o outdir] [-r rev] [-c] [-w]
 *	[-n] [-tableonly] [-patchesonly] [input_file]
 *
 * There is one line in the bsubmit log of the following format for each 
 * file submitted:
 *
 * filename   CR#  new revision	previous revision 
 * filename.c 7077 1.27.22.3	1.27.22.2
 *
 * The first parameter (-all or [-start <date>] [-end <date>]...) 
 * determines the extent of the tables/diffs that the tool produces:
 *
 *     If -all is specified, the tool processes the entire bsubmit log file
 *         and produces output that reflects all the changes covered in that
 *         log file.  This is the default.
 *     If -start ..., -end ... option is used, the bsubmit log file would only
 *	   be processed within the range of the <startdate> and <enddate>.
 *
 * The -o option specifies the name of the parent directory that will
 * house the output files from the tool (see below for the definition of
 * the output files).  This defaults to the current directory if not 
 * specified.
 *
 * The -r option specifies that the diff should be performed against the
 * version of the file associated with the symbolic name represented by the
 * option's value.
 *
 * The -tableonly option specifies that bdelta should build bdelta.table and
 * then quit.  The -patchesonly option specifies that bdelta should build
 * the patches based on the information in bdelta.table.
 *
 * Old-style 'bsubmit.log' files are missing the previous revision field.
 * They can also be read by bdelta, which determines the number of fields
 * and, in the absence of the previous revision, uses bstat to obtain it
 * or a heuristic rule to guess it.
 *
 * The output files:
 *
 * 1: <current working directory>/bdelta.table will contain lines of the 
 * following format:
 *
 * pathA/filename.c	7077	1.27.22.2	1.27.22.3
 * pathB/otherfile.c	7077	1.31.2.5	1.31.2.6
 * pathA/filename.c	7023	1.27.22.3	1.27.22.4
 * pathB/filenm3.c	7023	1.13.15.9	1.13.15.10
 * pathA/filename.c	7134	1.27.22.4	1.27.22.5
 * pathB/otherfile.c	7064	1.31.2.6	1.31.2.7
 * pathB/filenm3.c	7110	1.13.15.10	1.13.15.11
 *
 * The columns in the file correspond directly to the fields in the bsubmit
 * log lines.  This file can be easily parsed with grep or awk by the user
 * to look for things like:
 * - all files affected by CR 7077
 * - all CRs that had an effect on filename.c
 * - what the revisions were surrounding the changes to filenm3.c for CR 7023.
 * 
 * The order of the filenames in the file indicate the chronological order
 * of the revisions to the files (oldest on top).
 * 
 * 2: a shadow hierarchy will be created under output_dir that mocks the
 * hierarchy implied by all the paths listed in the bdelta.table file.  In
 * the place of the actual files at the leaf points there will be a set of
 * files that contain the diffs for each CR affecting that files:
 * 
 * output_dir/pathA/
 *       filename.c.7077                all diffs for CR 7077 in filename.c
 *       filename.c.7023                all diffs for CR 7023 in filename.c
 *       filename.c.7134                ...
 * output_dir/pathB/
 *       otherfile.c.7077               ...
 *       otherfile.c.7064               ...
 *       filenm3.c.7023                 ...
 *       filenm3.c.7110                 ...
 * 
 * This set of files will isolate diffs by file and CR number so that any
 * given CR can be reviewed and applied assuming all the preceding diffs
 * are applied first.
 */

void
main ( argc, argv )
int argc;
char ** argv;
{
  char * odir = NULL,
       * start_date = NULL,
       * end_date = NULL,
       * input_file = NULL,
       * revision = NULL;
  BOOLEAN all, context, ws_ignore, patches_only, table_only;
  char curpath[MAXPATHLEN];
  struct rcfile contents;
  int file_mode;
  char * sb_base = NULL,
       * sb = NULL,
       * symbolic_name = NULL,
       * submit_set = NULL,
       * sbrc_file = NULL;
  char * coc_str;
  char co_buf [ MAXPATHLEN ];
  char * co_str = co_buf;
  FILE * lastrun_log;

  ui_init( argc, argv, MAX_ARGS, init, 0, NULL );
  build_table_from_scratch = FALSE;

  /*
   * The sci_init() routine seems to have as a side effect that the 
   * current working directory is changed.  We need to return to our original
   * location.
   */
  if ((char *) getcwd(curpath, sizeof(curpath)) == NULL) {
    ui_print( VFATAL, "getcwd \n" );
    exit( ERROR );
  }
  last_date_processed = NULL;
  last_time_processed = NULL;
  last_run_date[0] = '\0';
  last_run_time[0] = '\0';

  sci_init ( &contents, &sb, &sb_base, &symbolic_name, &submit_set,
    &sbrc_file, file_mode, FALSE );

  strcpy (sb_srcdir, "bdelta.lastrun");

  get_rc_value ( "check_out_config", &coc_str, &contents, FALSE );
  co_buf [0] = '\0';
  rci_expand_include ( &co_str, coc_str );

  ui_print( VDEBUG, "check_out_config string = |%s|\n", co_buf );

  /* Sample check_out_config string = ;ODE;<1991/12/18,09:00 */

  /*
   * Return to original working directory.
   */
  if ( chdir(curpath) < 0 ) {
    ui_print( VFATAL, "chdir %s \n", curpath );
    exit(1);
  }

  start_date = ui_arg_value( START_OP, 1, 1 );
  end_date = ui_arg_value( END_OP, 1, 1 );
  revision = ui_arg_value( REVISION_OP, 1, 1 );

  if ( (odir = ui_arg_value( OUTPUT_OP, 1, 1 )) == NULL ) {
    odir = curpath;
  }

  all = ui_is_set( ALL_OP );
  context = ui_is_set( C_OP );
  ws_ignore = ui_is_set( W_OP );
  patches_only = ui_is_set( PATCHES_OP );
  table_only = ui_is_set( TABLE_OP );
  use_last_run = ui_is_set( LAST_RUN_OP );

  if ( patches_only && table_only ) {
    ui_print( VFATAL, "Cannot use the %s switch with the %s switch\n",
      PATCHES_OP, TABLE_OP );
    exit( ERROR );
  }

  if ( (input_file = ui_entry_value( ARGS_OP, 1)) == NULL )
    input_file = "bsubmit.log";

  if ( (all && start_date) || (all && end_date) || (all && use_last_run) ) {
    ui_print( VFATAL, "Cannot use the %s switch with the %s or %s switch.\n",
	ALL_OP, START_OP, END_OP );
    exit( ERROR );
  }

  if ( (patches_only && use_last_run) || (table_only && use_last_run) ) {
    ui_print( VFATAL, "Cannot use the %s switch with the %s or %s switch.\n",
	LAST_RUN_OP, TABLE_OP, PATCHES_OP );
    exit( ERROR );
  }

  if ( use_last_run ) {
	if ( (lastrun_log = fopen ( sb_srcdir, READ)) == NULL) {
		/* Initial run. */
		all = TRUE;
		use_last_run = FALSE;
		build_table_from_scratch = TRUE;
	} else {
		fscanf (lastrun_log, "%s	%s",
			last_run_date, last_run_time);
		fclose (lastrun_log);
	}
  }

  if ( !start_date && !end_date && !use_last_run )
    all = TRUE;

  if (bdelta( all, start_date, end_date, odir, input_file, revision, co_buf, context, ws_ignore, patches_only, table_only))
    exit(0);
  else
    exit(1);

}

/* show invocation options */
void
print_usage(void)
{
  ui_print ( VALWAYS, "USAGE:\n" );
  ui_print ( VALWAYS, "%s [-all | -start sdate -end edate | -o outdir | -r symname] [bsubmit.log]\n", progname );
  ui_print ( VALWAYS, "%s [-tableonly | -patchesonly]\n", progname );
  ui_print ( VALWAYS, "%s %s\n", progname, USAGE_VER_USAGE );
}

BOOLEAN bdelta( all, start_date, end_date, odir, input_file, revision, ckout_config, context, ws_ignore, patches_only, table_only )
BOOLEAN all;
char *start_date;
char *end_date;
char *odir;
char *input_file;
char *revision;
char *ckout_config;
BOOLEAN context;
BOOLEAN ws_ignore;
BOOLEAN patches_only;
BOOLEAN table_only;
{
  BOOLEAN stat = TRUE;
  BOOLEAN diff_stat = TRUE;
  FILE *lastrun_log;


  ui_print( VDEBUG, "all %s\tstart_date %s\tend_date\t%s\n", (all == TRUE) ? "true" : "false", start_date ? start_date : "", end_date ? end_date : "" );
  ui_print( VDEBUG, "odir %s\tinput_file %s\trevision %s\tckout_config %s\n", odir, input_file, revision ? revision : "", ckout_config );
  ui_print( VDEBUG, "patches_only %d table_only %d\n", patches_only, table_only );

  if ( !patches_only )
    diff_stat = make_difftable( input_file, odir, all, start_date, end_date, ckout_config );

  if ( table_only ) {
    stat = diff_stat;
  } else if ( diff_stat ) {
    stat = make_patches( odir, revision, context, ws_ignore );
  } else
    stat = FALSE;

  if ( ui_is_set( LAST_RUN_OP ) ) {
	if (last_date_processed != NULL) {
		if ( (lastrun_log = fopen( sb_srcdir, WRITE )) == NULL ) {
			ui_print( VWARN, "ERROR: cannot write to file %s.\n",
				sb_srcdir );
		} else {
			fprintf (lastrun_log, "%s       %s\n",
				last_date_processed,
				last_time_processed);
		fclose (lastrun_log);
		}
	} 
	
  }
  return stat;
}

BOOLEAN make_difftable( input_file, odir, all, start_date, end_date, ckout_config )
char *input_file;
char *odir;
BOOLEAN all;
char *start_date;
char *end_date;
char *ckout_config;
{
  enum parse_states { log_entry, file_list, null_state } ;

  enum parse_states log_state;
  FILE *infile, *outfile;
  char line[MAXPATHLEN], *lp = line;

  char *cp;
  char date_buf[NAME_LEN];
  char time_buf[NAME_LEN];
  char cr_buf[NAME_LEN];
  char output_file[MAXPATHLEN];
  char srcname[MAXPATHLEN];
  char currev[NAME_LEN];
  char prevrev[NAME_LEN];
  BOOLEAN stat = TRUE;
  char * last_date_this_session = NULL,
       * last_time_this_session = NULL;

  ui_print( VDEBUG, "make_difftable input_file %s odir %s all %s start_date %s end_date %s ckout_config %s\n", input_file, odir, (all == TRUE) ? "true" : "false", start_date, end_date, ckout_config );

  date_buf[0] = time_buf[0] = cr_buf[0] = '\0';
  srcname[0] = prevrev[0] = currev[0] = '\0';

  (void)sprintf(output_file, "%s", BDELTATABLE );

  if ( use_last_run ) {
	if ( (outfile = fopen( output_file, "a+" )) == NULL ) {
	ui_print( VWARN, "ERROR: cannot write to file %s.\n", output_file );
	stat = FALSE;
	}
  } else
  if ( (outfile = fopen( output_file, WRITE )) == NULL ) {
    ui_print( VWARN, "ERROR: cannot write to file %s.\n", output_file );
    stat = FALSE;
  }

  if ( stat ) {
    if ( (infile = fopen(input_file, READ)) == NULL ) {
      ui_print( VWARN, "ERROR: cannot read input file %s.\n", input_file );
      stat = FALSE;
    }
  }
  log_state = null_state;

  /*
   * bsubmit.log format and assumed state transitions
   *
   *						   Start state: null_state
   *  Submission Log *****		           and null_state -> log_entry
   *    Date: <DATE>; Time: <TIME>		   and log_entry
   *    Defect number: <NUM>, <NUM>.
   *    List of files and revisions:		   and log_entry  -> file_list
   *	./<filename> checkin version
   *  Detailed description:                        and file_list  -> log_entry
   *  End Log *****				   and log_entry  -> null_state
   *						   Start state: null_state
   *
   * This machine is adopted from 'ot_bcs' and represents a primitive kind of
   * input validation.
   */
  while ( stat && (lp = fgets(line, MAXPATHLEN, infile)) != NULL ) {

    ui_print( VDEBUG, "state %d >> %s", log_state, lp );

    switch ( log_state ) {

      case null_state:

          if ( strstr(lp, "Submission Log *****") == lp ) {
	    log_state = log_entry;
	  }
	  break;

      case log_entry:

	  if ( strstr(lp, "  List of files and revisions:") == lp ) {

	    log_state = file_list;

	  } else if ( strstr(lp, "End Log *****") == lp ) {

	    log_state = null_state;
	    date_buf[0] = time_buf[0] = cr_buf[0] = '\0';

	  } else if ( strstr(lp, "  Date: ") ) {

	    (void)sscanf(lp, "  Date: %[0-9/:]; Time: %s", date_buf, time_buf);

	  } else if ( cp = strstr(lp, "Defect number: ") ) {

	    cp = strchr(cp, ':');
	    (void)strcpy(cr_buf, ++cp);

	  }

	  break;

      case file_list:

	  if ( strstr(lp, "  Detailed description:") == lp ) {

	    log_state = log_entry;

	  } else {

	    if ( *lp && (*lp != '\n') ) {

	      if ( all || in_range(date_buf, time_buf, start_date,
			end_date, last_run_date, last_run_time) ) {

		if (get_revision_element(lp, srcname, currev, prevrev, ckout_config)) {
		  ui_print( VDEBUG, "d %s\tt %s\tf %s\t# %s\tp %s\tc %s\n", 
		    date_buf, time_buf, srcname, cr_buf, prevrev, currev);
		  (void)print_revision_element(outfile, srcname, cr_buf, prevrev, currev, date_buf, time_buf);
		  srcname[0] = prevrev[0] = currev[0] = '\0';
		  if (last_date_this_session != NULL) {
			free (last_date_this_session);
		  }
		  last_date_this_session = strdup (date_buf);
		  if (last_time_this_session != NULL) {
			free (last_time_this_session);
		  }
		  last_time_this_session = strdup (time_buf);

		}
	      } 
	    }

	  }

	  break;

      default:
	  ui_print(VFATAL, "State error (%d)\n", log_state);
	  exit(ERROR);
	  break;
      }
  }

  if (last_date_this_session != NULL) {
	last_date_processed = last_date_this_session;
	last_time_processed = last_time_this_session;
  }

  (void)fclose(infile);
  (void)fclose(outfile);
  return stat;

}

BOOLEAN get_revision_element(lp, fname, currev, prevrev, ckout_config)
char *lp;
char *fname;
char *currev;
char *prevrev;
char *ckout_config;
{
  int scan_count;
  BOOLEAN stat;
  char tmpname[MAXPATHLEN];
  char *cp;

  stat = TRUE;
  ui_print( VDEBUG, "lp %s currev %s prevrev %s ckout_config %s\n", lp, currev ? currev : "", prevrev ? prevrev : "", ckout_config ? ckout_config : "" );

  if ( scan_count = sscanf(lp, "%s\t%s\t%s\n", tmpname, currev, prevrev) ) {
    /*
     \t%s\t%s* Trim leading '.', trailing ',v' from filename.
     */
    cp = tmpname + (strlen(tmpname) - 2);
    if ( strcmp(cp, ",v") == 0 )
      *cp = '\0';
    if ( *(cp = tmpname) == '.' )
      cp++;
    (void)strcpy(fname, cp);
    ui_print( VDEBUG, "normalized source name: %s\n", fname);
  }

  if (scan_count == 3) {
    /*
     * New-style log.
     */
  } else if (scan_count == 2) {

    /*
     * Old-style bsubmit.log.  Get the previous revision number heuristically,
     * or by using the bstat command.
     */
    if ( (gmatch(currev, "(null)")) || (gmatch(currev, "defunct")) ) {
      ui_print( VDEBUG, "Matches null or defunct pattern: %s\n", lp );
      stat = FALSE;
    } else
      get_prevrev( fname, currev, prevrev, ckout_config );

  } else {
    /*
     * Some error.
     */
    ui_print( VWARN, "Illegal format in file/revision line: %s\n", lp );
    stat = FALSE;
  }

  return stat;

}

void print_revision_element(outfile, srcname, crs, prevrev, currev, datep,
	timep)
FILE *outfile;
char *srcname;
char *crs;
char *prevrev;
char *currev;
char *datep;
char *timep;
{
  char *cp;
  /* e.g., Defect number: 33, 22. */

#define DEFECT_SEP " ,.\n"

  if ( *crs == '\0' ) {
    memset( crs, 0, NAME_LEN );
    strcpy(crs, "0.");
  }  

  for( cp = strtok(crs, DEFECT_SEP); cp; cp = strtok(NULL, DEFECT_SEP) ) {
    (void)fprintf(outfile, "%s\t", srcname);

    /*
     * Validate CR number - if it is not a digit, substitute w/ 0.
     */
#ifdef notdef
    if ( gmatch(cp, "0") ) {
      ui_print( VWARN, "Change in %s without defect number\n", cp)
    }
#endif
    /*
     * The check on only the first character of the CR number is intentional.
     * This allows 'almost' numbers to pass through.
     */
    if ( !gmatch(cp, "[0-9]*") ) {
      (void)fprintf(outfile, "0\t");
      if ( (cp != NULL) && (strcmp(cp, "n/a") != 0) && 
		(strcmp(cp, "N/A") != 0) && (strcmp (cp, "nosupport") != 0) )
      	ui_print( VWARN, "Illegal CR number (%s) associated with %s: substituting 0\n", cp, srcname );
    }
    else
      (void)fprintf(outfile, "%s\t", cp);

    (void)fprintf(outfile, "%s\t%s\t%s\t%s\n", prevrev, currev, datep, timep);
  }

}

typedef struct {
    char *  s;              /* original string */
    char    comparison;     /*  -, <, > or nothing */
    int     month, day, year;
    int     days;
} OTDateComparison;

#define DATE_CHARS "-<>/."
#define DATE_COMP_CHARS "-<>"

BOOLEAN in_range( datep, timep, start_date, end_date, last_run_datep, 
	last_run_timep )
char *datep;		/*  Date of current entry in the bsubmit.log. */
char *timep;		/*  Time of current entry in the bsubmit.log. */
char *start_date;	/*  Start date for processing "-start" option */
char *end_date;		/*  End date for processing " "-end" option.  */
char *last_run_datep;	/*  Date of last run of bdelta.               */
char *last_run_timep;	/*  Time of last run of bdelta.               */
{
  OTDateComparison current_dc, start_dc, end_dc, last_run_dc;
  BOOLEAN stat;
  int last_hour, last_min, current_hour, current_min;
  char *i = NULL;

  stat = TRUE;
  ui_print( VDEBUG, "in_range %s %s %s %s %s %s\n", datep, timep, start_date, 
	end_date, last_run_datep, last_run_timep );

  if ( ! otParseDate( datep, &current_dc ) ) {
    stat = FALSE;
  } else
  if ( start_date && (!otParseDate( start_date, &start_dc )) ) {
    stat = FALSE;
  } else
  if ( end_date && (!otParseDate( end_date, &end_dc )) ) {
    stat = FALSE;
  } else
  if ( ui_is_set (LAST_RUN_OP) && (!otParseDate( last_run_datep, &last_run_dc )) ) {
    stat = FALSE;
  }
    
  if (stat) {

    if ( start_date && end_date ) {    
      if ((start_dc.days > current_dc.days) || (end_dc.days < current_dc.days))
	stat = FALSE;
    } else
    if ( start_date && (start_dc.days > current_dc.days) ) {
      stat = FALSE;
    } else
    if ( end_date && (end_dc.days < current_dc.days) ) {
      stat = FALSE;
    } else
    if ( ui_is_set (LAST_RUN_OP) && (last_run_dc.days > current_dc.days) ) {
	stat = FALSE;
    } else
    if ( ui_is_set (LAST_RUN_OP) && (last_run_dc.days < current_dc.days) ) {
	stat = TRUE;
    } else
    if ( ui_is_set (LAST_RUN_OP) && (last_run_dc.days == current_dc.days) ) {

	last_hour = 0;
	for (i = last_run_time ; *i != ':'; i++) {
		last_hour = last_hour * 10 + atoi (i);
	}
	last_min = 0;
	for (i++  ; *i != '\0'; i++) {
		last_min = last_min * 10 + atoi (i);
	}
	current_hour = 0;
	for (i = timep ; *i != ':'; i++) {
		current_hour = current_hour * 10 + atoi (i);
	}
	current_min = 0;
	for (i++  ; *i != '\0'; i++) {
		current_min = current_min * 10 + atoi (i);
	}
	ui_print (VDEBUG, "Current hour is %d, Current min is %d\n",
	current_hour, current_min);
	ui_print (VDEBUG, "Last hour is %d, Last min is %d\n",
	last_hour, last_min);
	if (current_hour < last_hour) {
		stat = FALSE;
	} else if (current_hour == last_hour) {
		if (current_min <= last_min) {
			stat = FALSE;
		}
	}
    }

  }    

  ui_print(VDEBUG, "in_range returns %s\n", (stat == TRUE) ? "true" : "false");
  return stat;

}


/*
 *  otParseDate()  -- Parse simple date string - mm/dd/yy
 *
 * Fills in the DateComparison to describe the date passed to it.  This
 * includes month, day, year, days-since-1970 (for date comparisons),
 * and any info about whether this was a "period" date like >3/2/91 (which
 * means "match any date since 3/2/91").
 *
 * The error return functions have been changed to harmonize w/ libode.a
 * and to avoid having to link all the error codes, strings etc of the OT 
 * environment for this utility.
 */
BOOLEAN otParseDate(s, dc)
char *s;
OTDateComparison *dc;
{
  register char *cp1, *cp2;
  int i, days;

  dc->s = s;
  /*
   * Make sure passed date contains only digits and special chars ( /.-<> ).
   */
  for (i=0; s[i]; i++)
    if (!isdigit(s[i]) && !strchr(DATE_CHARS, s[i])) {
      ui_print(VWARN, "Illegal date format %s\n", s);
      return FALSE;
    }

  /*
   * Find date comparison char, if any
   */
  if (strchr(DATE_COMP_CHARS, *s)) {      /* check for -,<,> */
    dc->comparison = *s;
    s++;
  } else				    /* else -- exact match */
    dc->comparison = '=';

  cp1 = (cp1 = strchr(s, '/')) ? cp1 : strchr(s, '.');

  if (!cp1) {
    ui_print(VFATAL, "Illegal date format: %s\n", s );
    return FALSE;
  }

  cp1++;
  cp2 = (cp2 = strchr(cp1, '/')) ? cp2 : strchr(cp1, '.');
  if (!cp2) {
    ui_print(VWARN, "Illegal date format\n", s );
    return FALSE;
  }
  cp2++;

  dc->month = atoi(s);
  dc->day   = atoi(cp1);
  dc->year  = atoi(cp2);
  dc->year  = (dc->year>1900) ? (dc->year-1900) : dc->year;

  if (dc->month < 1 || dc->month > 12) {
    ui_print( VWARN, "Illegal date format\n", s );
    return FALSE;
  }
  if (dc->day < 1   || dc->day > 31) {
    ui_print( VWARN, "Illegal date format\n", s );
    return FALSE;
  }
  if (dc->year < 87 || dc->year > 99) {
    ui_print( VWARN, "Illegal date format\n", s );
    return FALSE;
  }

  days = (dc->year * (31 * 12)) + (31 * dc->month) + dc->day;
  dc->days = days;

  return TRUE;
}


BOOLEAN make_patches( odir, revision, context, ws_ignore )
char *odir;
char *revision;
BOOLEAN context;
BOOLEAN ws_ignore;
{
  FILE *infile;
  char input_file[MAXPATHLEN];
  char fnameb[MAXPATHLEN];
  char crnumb[NAME_LEN];
  char prevrevb[NAME_LEN];
  char currevb[NAME_LEN];
  BOOLEAN stat = TRUE;
  char datep[MAXPATHLEN];
  char timep[MAXPATHLEN];

  ui_print( VDEBUG, "make_patches %s %s\n", odir, (revision == NULL) ? "" :
    revision );

  /*
   * make patches in odir on the basis of table or revision
   */
  (void)sprintf(input_file, "%s", BDELTATABLE );
  if ( (infile = fopen( input_file, READ )) == NULL ) {
    ui_print( VWARN, "ERROR: cannot read input file %s.\n", input_file );
    stat = FALSE;
  }

  while ( stat && fscanf(infile, "%s\t%s\t%s\t%s\t%s\t%s\n", fnameb, crnumb, prevrevb, 
    currevb, datep, timep) == 6 ) {

    if ( ui_is_set (LAST_RUN_OP) ) {
	if ( (build_table_from_scratch) || (in_range ( datep, timep, NULL, NULL, last_run_date, last_run_time) == TRUE)) {
		if ( !make_patchfile( odir, fnameb, crnumb, prevrevb,
			currevb, revision, context, ws_ignore ) ) {
			stat = FALSE;
		}
	} else {
		ui_print (VDEBUG, "patch for %s/%s, %s, %s, %s not in range\n",
			odir, fnameb, crnumb, datep, timep);
	}
    } else {
	if ( !make_patchfile( odir, fnameb, crnumb, prevrevb, currevb, revision, context, ws_ignore ) ) {
	  stat = FALSE;
    	}
	stat = TRUE;
    }
  }
  (void) fclose(infile);

  ui_print(VDEBUG, "make_patches end\n");
  return stat;

}


BOOLEAN
make_patchfile( odir, fname, crnum, prevrev, currev, revision, context, ws_ignore )
char *odir;
char *fname;
char *crnum;
char *prevrev;
char *currev;
char *revision;
BOOLEAN context;
BOOLEAN ws_ignore;
{
  char patchname[MAXPATHLEN];
  char diff_line[MAXPATHLEN];
  char bdiff_switch[10];
  char revarg1[MAXPATHLEN], revarg2[MAXPATHLEN];
  char *diffp;
  BOOLEAN status = TRUE;
  int ret, i;
  FILE *outfile;
  struct stat statbuf;
  int p[2];
  int pid, stat_loc, wr;


  ui_print( VDEBUG, "make_patchfile odir %s fname %s crnum %s\n", odir, fname, crnum );
  ui_print( VDEBUG, "\tprevrev %s currev %s revision %s\n", prevrev, currev, revision );
  ui_print( VDEBUG, "\tcontext %s ws_ignore %s\n", context ? "yes" : "no", ws_ignore ? "yes" : "no" );
  /*
   * Create a filename of the form <odir>/<fname>.<crnum>.<patchnum>
   * for the patchfile.
   */
  for ( i=1; i < MAXPATCHCOUNT; i++) {
    (void)sprintf( patchname, "%s%s.%s.%d", odir, fname, crnum, i );
    if ( stat(patchname, &statbuf) != 0 )
      break;
  }
  if ( i == MAXPATCHCOUNT ) {
    ui_print( VWARN, "Exceeded %s maximum for file %s/%s\n", MAXPATCHCOUNT, odir, fname );
    status = FALSE;
  }

  if (status) {

    ui_print( VDEBUG, "odir %s fname %s crnum %s -> patchname %s\n",
      odir, fname, crnum, patchname );

    if ( makepath( patchname, NULL, TRUE, TRUE ) != 0 )
      uquit ( ERROR, FALSE, "makepath %s failed.\n", patchname );

    if ( (outfile = fopen( patchname, WRITE )) == NULL ) {
      ui_print( VWARN, "ERROR: cannot read input file %s.\n", patchname );
      status = FALSE;
    } else {

      if ( pipe(p) < 0 ) {
	status = FALSE;
	return status;
      } else if ( (pid = fork()) < 0 ) {
	status = FALSE;
	return status;
      }

      if (pid == 0) {
	/*
	 * In child.
	 * Here, only redirect standard output - standard error should
	 * go to the parent's control terminal.
	 */
	(void)close(p[0]);
	(void)close(1);
	(void)dup(p[1]);

	sprintf(bdiff_switch, "-");
	if (context)
	  strcat(bdiff_switch, "c");
	if (ws_ignore)
	  strcat(bdiff_switch, "w");
	sprintf(revarg1, "%s", revision ? revision : prevrev );
	sprintf(revarg2, "%s", currev);

	if (context || ws_ignore)
	  (void)execlp("bdiff", "bdiff", bdiff_switch, "-r", revarg1, "-R", revarg2, fname, 0);
	else
	  (void)execlp("bdiff", "bdiff", "-r", revarg1, 
		"-R", revarg2, fname, 0);

      } else {

	FILE *pfile;

	/*
	 * In parent.
	 */
	(void)close(p[1]);
	pfile = fdopen(p[0], "r");

	while ( (diffp = fgets(diff_line, MAXPATHLEN, pfile )) != NULL ) {
	  if ( (ret = fputs(diffp, outfile)) < 0 )
	    ui_print( VFATAL, "ERROR: cannot write to %s\n", patchname );
	}

	(void)fclose(pfile);
	(void)fclose(outfile);
	/*
	 * Wait for child to exit.
	 */
	wr = waitpid(pid, &stat_loc, 0);
	ui_print( VDEBUG, "wait returned %d\n", wr);
      }
    }
  }

  return status;

}

/* A revision name is a string of the form "n{.n}*".  To get the previous
 * revision, find the last '.', look at the number after it, subtract
 * 1 from that number, and return it.  There is one exception
 * to this:  If the revision is of the form X.Y.Z.2, then use the bstat
 * command to obtain the previous version.
 *
 * Only value returned is value of prevrev.
 */

void get_prevrev(fname, currev, prevrev, ckout_config)
char *fname;
char *currev;
char *prevrev;
char *ckout_config;
{
  char *lastdot, *dot;
  int lastnumber;

  ui_print( VDEBUG, "get_prevrev currev %s prevrev %s\n", currev, prevrev );
  if ( ! (lastdot = strrchr(currev, '.')) ) {

    lastnumber = atoi(currev);
    sprintf(prevrev, "%d", lastnumber - 1);

  } else {

    strncpy(prevrev, currev, lastdot - currev + 1);
    prevrev[lastdot - currev + 1] = '\0';

    ui_print( VDEBUG, "lastdot %s, prevrev %s\n", lastdot + 1, prevrev );

    lastnumber = atoi(lastdot + 1);
    if (lastnumber == 2) {
      if ( ! get_prevrev_via_bstat( fname, prevrev, ckout_config ) ) {

	if ( dot = strchr(prevrev, '.') ) {
	  if ( dot = strchr(dot+1, '.') ) {
	    *dot = '\0';
	  }
	}
	if (! ui_is_set ( QUIET_OP ) )
		ui_print( VWARN, "heuristically determined revision (%s) for %s\n", prevrev, fname );
      }
    } else {
      ui_print( VDEBUG, "lastnumber = %d\n", lastnumber );
      sprintf(prevrev + strlen(prevrev), "%d", lastnumber - 1);
    }
  
  }
  ui_print( VDEBUG, "prevrev = %s\n", prevrev );

}


BOOLEAN
get_prevrev_via_bstat( fname, prevrev, ckout_config )
char *fname;
char *prevrev;
char *ckout_config;
{

  char *cp;
  char *statp;
  char bstat_command[MAXPATHLEN];
  char stat_line[MAXPATHLEN];
  FILE *pfile;
  BOOLEAN stat;
  int scan_count;
  int p[2];
  int pid, stat_loc, wr;

  stat = FALSE;
  ui_print( VDEBUG, "get_prevrev_via_bstat fname %s prevrev %s\n", fname, prevrev );
  /*
   * Use the bstat command to obtain a guess of the previous version.
   * Use the previous build label to get the latest revision number for
   * the branch associated with the label.
   */
  if ( *ckout_config == ';' )
    ckout_config++;

  if ( cp = strchr( ckout_config, ';' ) )
    ckout_config = ++cp;

  /*
   * Using a fork()/pipe() is necessary here because the bstat command
   * writes to standard error.  There are workarounds which can be used
   * 	like, popen("(command 2>1)", "r")
   * but these result in defunct processes for each invocation.
   */
  if ( pipe(p) < 0 ) {
    stat = FALSE;
    return stat;
  } else if ( (pid = fork()) < 0 ) {
    stat = FALSE;
    return stat;
  }

  if (pid == 0) {
    /*
     * In child.
     * Send standard out and standard error to parent (can't use
     * popen() here, unfortunately it reads standard output only).
     */
    (void)close(p[0]);
    (void)close(1);
    (void)dup(p[1]);
    (void)close(2);
    (void)dup2(p[1], 2);

    (void)sprintf(bstat_command, "-r %s", ckout_config);
    (void)execlp("bstat", "bstat", bstat_command, fname, 0);

  } else {

    /*
     * In parent.
     */

    (void)close(p[1]);
    pfile = fdopen(p[0], "r");

    while ( (stat == FALSE) && (statp = fgets(stat_line, MAXPATHLEN, pfile )) != NULL ) {

      ui_print( VDEBUG, "bstat returns %s\n", statp );

      if ((scan_count = sscanf(statp, "version %s selected", prevrev)) == 1) {
	stat = TRUE;
      }

    }
    (void)fclose(pfile);
    /*
     * Wait for child to exit.
     */
    wr = waitpid(pid, &stat_loc, 0);
  }

  return stat;

}
