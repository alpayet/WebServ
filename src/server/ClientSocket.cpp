#include "ClientSocket.hpp"

ClientSocket::ClientSocket() {}

ClientSocket::ClientSocket(const ClientSocket& clientsocket) {}

ClientSocket& ClientSocket::operator=(const ClientSocket& clientsocket) {
  return *this;
}

ClientSocket::~ClientSocket() {}

void ClientSocket::handleNewClient(int fd) {}

void ClientSocket::handleKnownClient(ClientSocket* client) {}
