#include "config.h"
#include "timers.h"

#include "my-stdlib.h"

#include "storage.h"

typedef struct timer_entry {
    struct timer_entry *next;
    Timer_ID id;
    uint64_t deadline;
    Timer_Proc proc;
    Timer_Data data;
} Timer_Entry;

static Timer_ID next_id = 1;
static Timer_Entry *timers;

static uint64_t
monotonic_milliseconds(void)
{
    struct timespec now;

    if (clock_gettime(CLOCK_MONOTONIC, &now) != 0)
	return (uint64_t) time(0) * 1000;
    return (uint64_t) now.tv_sec * 1000 + now.tv_nsec / 1000000;
}

Timer_ID
set_timer(unsigned seconds, Timer_Proc proc, Timer_Data data)
{
    Timer_Entry *timer = mymalloc(sizeof(*timer), M_TASK);

    timer->id = next_id++;
    timer->deadline = monotonic_milliseconds() + (uint64_t) seconds * 1000;
    timer->proc = proc;
    timer->data = data;
    timer->next = timers;
    timers = timer;
    return timer->id;
}

Timer_ID
set_virtual_timer(unsigned seconds, Timer_Proc proc, Timer_Data data)
{
    return set_timer(seconds, proc, data);
}

int virtual_timer_available(void) { return 0; }

unsigned
timer_wakeup_interval(Timer_ID id)
{
    Timer_Entry *timer;
    uint64_t now = monotonic_milliseconds();

    for (timer = timers; timer; timer = timer->next)
	if (timer->id == id) {
	    uint64_t remaining = timer->deadline > now ? timer->deadline - now : 0;
	    return (remaining + 999) / 1000;
	}
    return 0;
}

void timer_sleep(unsigned seconds) { (void) seconds; }

int
cancel_timer(Timer_ID id)
{
    Timer_Entry **entry = &timers;

    while (*entry) {
	if ((*entry)->id == id) {
	    Timer_Entry *timer = *entry;
	    *entry = timer->next;
	    myfree(timer, M_TASK);
	    return 1;
	}
	entry = &(*entry)->next;
    }
    return 0;
}

void reenable_timers(void) { }

void
timers_poll(void)
{
    uint64_t now = monotonic_milliseconds();
    Timer_Entry **entry = &timers;

    while (*entry) {
	Timer_Entry *timer = *entry;
	if (timer->deadline > now) {
	    entry = &timer->next;
	    continue;
	}
	*entry = timer->next;
	Timer_Proc proc = timer->proc;
	Timer_Data data = timer->data;
	Timer_ID id = timer->id;
	myfree(timer, M_TASK);
	if (proc)
	    proc(id, data);
    }
}
