//
// Created by root on 3/30/20.
//

#include "httpd.h"

int main(int c, char **v) {
    serve_forever("8000");
    return 0;
}

void route() {
    if (strcmp("/", uri) == 0 && strcmp("GET", method) == 0) {
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("Hello! You are using %s", request_header("User-Agent"));
    } else if (strcmp("/test", uri) == 0 && strcmp("GET", method) == 0) {
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("List of request headers:\r\n\r\n");

        header_t *h = request_headers();

        while (h->name) {
            printf("%s: %s\n", h->name, h->value);
            h++;
        }
    } else if (strcmp("/", uri) == 0 && strcmp("POST", method) == 0) {
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("Wow, seems that you POSTed %d bytes. \r\n", payload_size);
        printf("Fetch the data using `payload` variable.");
    } else {
        printf("HTTP/1.1 500 Internal Server Error\n\n The server has no handler to the request.\n");
    }
}