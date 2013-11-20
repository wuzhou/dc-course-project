#include <stdio.h>
#include "server_main.h"

void listen_client_lookup(void) {
    run_lookupgrade_svc();

}

void listen_client_update() {
    run_update_svc();   
}

void listen_mainserver_update() {
    run_postupdate_svc();
}
