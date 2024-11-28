// client.c

#include "../client.h"
#include <unistd.h>

void signal_handler(int signal) {
    char response[4096];
    char url[4096];
    snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/win-disconnect");
    post_request(url, "", response, sizeof(response));
    printf("\nResponse: %s", response);
    exit(0);
}

int main() {

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    char response[4096];
    char url[4096];
    snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/win-connect");
    post_request(url, "", response, sizeof(response));
    printf("Response: %s", response);
    response[0] = '\0';

    while (1) {
        snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/mac-status");
        get_request(url, response, sizeof(response));
        printf("Response: %s", response);
        response[0] = '\0';
        sleep(1);
    }

    return 0;
}