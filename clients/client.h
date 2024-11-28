// client.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#if defined(_WIN32)
    #include <windows.h>
    #include "windows/curl/include/curl/curl.h"
#elif defined(__APPLE__)
    #include <curl/curl.h>
#endif

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *data) {
    size_t realsize = size * nmemb;
    char *response = (char *)data;
    strncat(response, ptr, realsize);
    return realsize;
}

void get_request(char *url, char *response, size_t response_size) {
    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "curl_easy_init() failed\n");
        exit(1);
    }

    // Set the URL for the request
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Set the callback function to handle the response
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    // Perform the request
    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    // Clean up
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

void post_request(char *url, char *data, char *response, size_t response_size) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "curl_easy_init() failed\n");
        exit(1);
    }

    // Set the URL for the request
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Set the callback function to handle the response
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    // Set the request method to POST
    curl_easy_setopt(curl, CURLOPT_POST, 1);

    // Set the POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    // Set the Content-Type header
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Perform the request
    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    // Clean up
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

void signal_handler(int signal) {
    char response[4096];
    char url[4096];

    #if defined(_WIN32)
        snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/win-disconnect");
    #elif defined(__APPLE__)
        snprintf(url, sizeof(url), "http://%s:%d%s", HOST, PORT, "/mac-disconnect");
    #endif

    post_request(url, "", response, sizeof(response));
    printf("\nResponse: %s", response);
    exit(0);
}

void OpenBrowser(char *url) {
    #if defined(_WIN32)
        ShellExecute(0, 0, url, 0, 0, SW_SHOWNORMAL);
    #elif defined(__APPLE__)
        char command[4096];
        snprintf(command, sizeof(command), "open \"%s\"", url);
        system(command);
    #endif
}

void CloseTask(char *task) {
    char command[4096];

    #if defined(_WIN32)
        snprintf(command, sizeof(command), "taskkill /IM %s /F", task);
    #elif defined(__APPLE__)
        snprintf(command, sizeof(command), "killall \"%s\"", task);
    #endif

    system(command);
}