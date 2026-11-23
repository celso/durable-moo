#ifndef Net_Wasm_H
#define Net_Wasm_H 1

extern int wasm_network_connect(const char *connection_id);
extern int wasm_network_input(const char *connection_id, const char *line);
extern int wasm_network_disconnect(const char *connection_id);

#endif
