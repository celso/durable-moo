/*  bf_register.c  --  Generated from bf_register.c.in by /workspace/lambdamoo/bf_register.sh
 * _____________________ DO NOT EDIT ___________________________________ */

#include "bf_register.h"

#include "db.h"

typedef void (*regfn) (void);

static regfn all_regfns[] = {
    /*----------------------*
     |   @@FUNCTIONS@@ ==
     */
    register_db_tune,        /* db_tune.c:45       */
    register_disassemble,    /* disassemble.c:479  */
    register_execute,        /* execute.c:3002     */
    register_experiments,    /* experiments.c:218  */
    register_functions,      /* functions.c:509    */
    register_list,           /* list.c:1421        */
    register_log,            /* log.c:165          */
    register_numbers,        /* numbers.c:1303     */
    register_objects,        /* objects.c:589      */
    register_property,       /* property.c:318     */
    register_server,         /* server.c:1979      */
    register_str_intern,     /* str_intern.c:305   */
    register_tasks,          /* tasks.c:2237       */
    register_verbs,          /* verbs.c:566        */

/*  register_waif,            * waif.c:1076        */
/*  register_xml,             * ext-xml.c:388      */

    /*    END of generated content.
     *-------------------------------*/
};

void
do_all_registrations(void)
{
    regfn *rfn = all_regfns;
    regfn *rfn_after = rfn + sizeof(all_regfns) / sizeof(regfn);

    while (rfn < rfn_after)
	(*rfn++)();

    db_init_hooks();
}
