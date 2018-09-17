//
// Created by Dio_V on 2018/9/13.
//

#include "android.h"
#include "log.h"

int protect_socket(int fd) {
    int sock;
    struct sockaddr_un addr;

    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        log_error(LOG_ERR, "[android] socket() failed: %s (socket fd = %d)\n", strerror(errno), sock);
        return -1;
    }

    // Set timeout to 3s
    struct timeval tv;
    tv.tv_sec  = 3;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(struct timeval));

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "protect_path", sizeof(addr.sun_path) - 1);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        log_error(LOG_ERR, "[android] connect() failed for protect_path: %s (socket fd = %d)\n",
             strerror(errno), sock);
        close(sock);
        return -1;
    }

    if (ancil_send_fd(sock, fd)) {
        log_error(LOG_ERR, "[android] ancil_send_fd");
        close(sock);
        return -1;
    }

    char ret = 0;

    if (recv(sock, &ret, 1, 0) == -1) {
        log_error(LOG_ERR, "[android] recv");
        close(sock);
        return -1;
    }

    close(sock);
    return ret;
}
