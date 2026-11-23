#include "config.h"
#include "options.h"

#include "my-stdlib.h"
#include "my-string.h"

#include "list.h"
#include "net_wasm.h"
#include "network.h"
#include "server.h"
#include "storage.h"
#include "structures.h"
#include "utils.h"

#ifdef __wasm__
#define WASM_IMPORT(name) __attribute__((import_module("env"), import_name(name)))
#else
#define WASM_IMPORT(name)
#endif
extern void moo_host_output(const char *connection_id, const char *data,
			    size_t length) WASM_IMPORT("moo_host_output");
extern void moo_host_close(const char *connection_id) WASM_IMPORT("moo_host_close");

typedef struct wasm_nhandle {
    struct wasm_nhandle *next;
    char *connection_id;
    server_handle server;
    int binary;
} wasm_nhandle;

static wasm_nhandle *connections;

static wasm_nhandle *
find_connection(const char *connection_id)
{
    wasm_nhandle *h;
    for (h = connections; h; h = h->next)
	if (!strcmp(h->connection_id, connection_id))
	    return h;
    return 0;
}

static void
free_connection(wasm_nhandle *h)
{
    wasm_nhandle **p = &connections;
    while (*p && *p != h)
	p = &(*p)->next;
    if (*p)
	*p = h->next;
    free_str(h->connection_id);
    myfree(h, M_NETWORK);
}

int
wasm_network_connect(const char *connection_id)
{
    wasm_nhandle *h;
    network_handle nh;

    if (find_connection(connection_id))
	return 0;
    h = mymalloc(sizeof(*h), M_NETWORK);
    h->connection_id = str_dup(connection_id);
    h->binary = 0;
    h->next = connections;
    connections = h;
    nh.ptr = h;
    h->server = server_new_connection(null_server_listener, nh, 0);
    return 1;
}

int
wasm_network_input(const char *connection_id, const char *line)
{
    wasm_nhandle *h = find_connection(connection_id);
    if (!h)
	return 0;
    server_receive_line(h->server, line);
    return 1;
}

int
wasm_network_disconnect(const char *connection_id)
{
    wasm_nhandle *h = find_connection(connection_id);
    if (!h)
	return 0;
    server_close(h->server);
    free_connection(h);
    return 1;
}

const char *network_protocol_name(void) { return "cloudflare-net"; }
const char *network_usage_string(void) { return ""; }
int network_initialize(int argc, char **argv, Var *desc)
{
    (void) argc; (void) argv; *desc = zero; return 1;
}
enum error network_make_listener(server_listener sl, Var desc,
				 network_listener *nl, Var *canon,
				 const char **name)
{
    (void) sl; (void) desc; nl->ptr = 0; *canon = zero;
    *name = "@cloudflare/net"; return E_NONE;
}
int network_listen(network_listener nl) { (void) nl; return 1; }
int network_send_line(network_handle nh, const char *line, int flush_ok)
{
    wasm_nhandle *h = nh.ptr; (void) flush_ok;
    moo_host_output(h->connection_id, line, strlen(line));
    moo_host_output(h->connection_id, "\r\n", 2);
    return 1;
}
int network_send_bytes(network_handle nh, const char *data, size_t length,
		       int flush_ok)
{
    wasm_nhandle *h = nh.ptr; (void) flush_ok;
    moo_host_output(h->connection_id, data, length); return 1;
}
int network_buffered_output_length(network_handle nh) { (void) nh; return 0; }
void network_suspend_input(network_handle nh) { (void) nh; }
void network_resume_input(network_handle nh) { (void) nh; }
void network_set_connection_binary(network_handle nh, int binary)
{
    ((wasm_nhandle *) nh.ptr)->binary = binary;
}
int network_process_io(int timeout) { (void) timeout; return 0; }
const char *network_connection_name(network_handle nh)
{
    return ((wasm_nhandle *) nh.ptr)->connection_id;
}
Var network_connection_options(network_handle nh, Var list)
{
    (void) nh; return list;
}
int network_connection_option(network_handle nh, const char *option, Var *value)
{
    (void) nh; (void) option; (void) value; return 0;
}
int network_set_connection_option(network_handle nh, const char *option, Var value)
{
    (void) nh; (void) option; (void) value; return 0;
}
void network_close(network_handle nh)
{
    wasm_nhandle *h = nh.ptr;
    moo_host_close(h->connection_id);
    free_connection(h);
}
void network_close_listener(network_listener nl) { (void) nl; }
void network_shutdown(void)
{
    while (connections) {
	network_handle nh;
	nh.ptr = connections;
	network_close(nh);
    }
}
