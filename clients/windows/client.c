// client.c

#include <windows.h>
#include <signal.h>
#include "../client.h"

int main() {

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    char response[4096];
    char url[4096];
    snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/win-connect");
    post_request(url, "", response, sizeof(response));
    printf("win-connect response: %s\n", response);

    while (1) {
        
        Sleep(1000);

        response[0] = '\0';
        snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/mac-status");
        get_request(url, response, sizeof(response));
        printf("mac-status response: %s\n", response);
        if (strcmp(response, "false") == 0) {
            continue;
        }

        response[0] = '\0';
        snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/get-request");
        get_request(url, response, sizeof(response));
        printf("get-request response: %s\n", response);
        if (strcmp(response, "null") == 0) {
            continue;
        }

        if (strcmp(response, "win-join") == 0) {
            response[0] = '\0';
            snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/win-join");
            post_request(url, "", response, sizeof(response));
            printf("win-join response: %s\n", response);
            OpenBrowser(response);

            Sleep(10000);
            CloseTask("brave.exe");

            response[0] = '\0';
            snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/request-mac-test");
            post_request(url, "", response, sizeof(response));
            printf("clear-request response: %s\n", response);

            continue;
        }

        if (strcmp(response, "win-leave") == 0) {

            response[0] = '\0';
            snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/win-leave");
            post_request(url, "", response, sizeof(response));
            printf("win-leave response: %s\n", response);

            continue;
        }

        if (strcmp(response, "win-test") == 0) {

            for (int i = 0; i < 30; ++i) {
                Sleep(1000);
                printf("win-test: %d\n", i);
            }

            response[0] = '\0';
            snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/request-mac-join");
            post_request(url, "", response, sizeof(response));
            printf("request-win-join response: %s\n", response);

            continue;
        }
    }

    return 0;
}