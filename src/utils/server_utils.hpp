#ifndef SERVER_UTILS_HPP
#define SERVER_UTILS_HPP

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

void* getInAddr(sockaddr* sa);

#endif  // SERVER_UTILS_HPP
