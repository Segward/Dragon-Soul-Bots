// client.c

#include "../client.h"

int main() {
    
    char response[4096];
    char url[4096];
    snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/mac-connect");
    post_request(url, "", response, sizeof(response));
    printf("Response: %s", response);
    response[0] = '\0';

    snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/win-status");
    get_request(url, response, sizeof(response));
    printf("Response: %s", response);
    response[0] = '\0';

    return 0;
}