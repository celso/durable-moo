/*  bf_register.h  --  Generated from bf_register.h.in by /workspace/lambdamoo/bf_register.sh
 * _____________________ DO NOT EDIT ___________________________________ */

#ifndef BF_Register_H
#define BF_Register_H 1

#include "config.h"
#include "options.h"

/*--------------------------*
 |  registration functions  |
 *--------------------------*/

/* ... are functions that are called exactly once during server
 * initialization before the database is loaded. They are allowed and
 * expected to contain combinations of calls to
 *
 *        register_function       (functions.h)
 *        register_db_load_hooks  (db_file.h)
 *        register_db_save_hooks  (db_file.h)
 *        register_task_queue     (tasks.h)
 *
 * The build process scans all COMMON_CSRCS and ALL_XT_CSRCS files for
 * functions matching the following criteria, collecting them below:
 *
 *  (1) have a name starting with 'register_'
 *      (base name of the file being the typical suffix)
 *
 *  (2) have void return type and (void) arguments,
 *
 *  (3) appear directly (i.e., not via #includes) with no indentation
 *      and return type on a separate line as per the usual style here
 *      for function definitions,
 *
 * For header purposes, registration functions are treated as if they
 * were defined in bf_register.c, meaning .c files that define or
 * otherwise reference them should #include "bf_register.h" internally
 * instead of publicly declaring the individual functions in their own
 * header (.h) files.
 */

extern void do_all_registrations(void);
                /* run all registration functions */

/*----------------------*
 |   @@EXTERNS@@ ==
 */
   extern void register_db_tune(void);        /* db_tune.c:45       */
   extern void register_disassemble(void);    /* disassemble.c:479  */
   extern void register_execute(void);        /* execute.c:3002     */
   extern void register_experiments(void);    /* experiments.c:218  */
   extern void register_functions(void);      /* functions.c:509    */
   extern void register_list(void);           /* list.c:1421        */
   extern void register_log(void);            /* log.c:165          */
   extern void register_numbers(void);        /* numbers.c:1303     */
   extern void register_objects(void);        /* objects.c:589      */
   extern void register_property(void);       /* property.c:318     */
   extern void register_server(void);         /* server.c:1979      */
   extern void register_str_intern(void);     /* str_intern.c:305   */
   extern void register_tasks(void);          /* tasks.c:2237       */
   extern void register_verbs(void);          /* verbs.c:566        */

/* extern void register_waif(void);            * waif.c:1076        */
/* extern void register_xml(void);             * ext-xml.c:388      */

/*    END of generated content.
 *-------------------------------*/

#endif		/* !BF_Register_H */
