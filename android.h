//
// Created by Dio_V on 2018/9/14.
//

#ifndef MALUS_ANDROID_H
#define MALUS_ANDROID_H

#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ancillary.h>
#include <sys/un.h>
#include "utils.h"

int protect_socket(int fd);

#endif //MALUS_ANDROID_H
