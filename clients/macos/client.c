// client.c

#include "../client.h"
#include <unistd.h>

int main() {

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    char response[4096];
    char url[4096];
    snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/mac-connect");
    post_request(url, "", response, sizeof(response));
    printf("mac-connect response: %s\n", response);

    while (1) {

        sleep(1);

        response[0] = '\0';
        snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/win-status");
        get_request(url, response, sizeof(response));
        printf("win-status response: %s\n", response);
        if (strcmp(response, "false") == 0) {
            continue;
        }

        response[0] = '\0';
        snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/win-joined");
        get_request(url, response, sizeof(response));
        printf("win-joined response: %s\n", response);
        if (strcmp(response, "false") == 0) {
            response[0] = '\0';
            snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/request-win-join");
            post_request(url, "", response, sizeof(response));
            printf("request-win-join response: %s\n", response);

            continue;
        }

        if (strcmp(response, "true") == 0) {

            sleep(5);

            response[0] = '\0';
            snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/mac-follow");
            get_request(url, response, sizeof(response));
            printf("mac-follow response: %s\n", response);
            OpenBrowser(response);

            sleep(10);
            CloseTask("Brave Browser");

            response[0] = '\0';
            snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/request-win-leave");
            post_request(url, "", response, sizeof(response));
            printf("request-win-join response: %s\n", response);

            continue;
        }
    }

    return 0;
}