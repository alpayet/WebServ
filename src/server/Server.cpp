#include "Server.hpp"

#include <iostream>

#include "transfer/ITransfer.hpp"
#include "transport/ITransport.hpp"

Server::Server(ITransport* transport, ITransfer* transfer)
    : m_transport(transport), m_transfer(transfer) {}

Server::~Server() {
  delete m_transport;
  delete m_transfer;
}

void Server::run() {
  std::cout << "Running server ...\n";
  m_transport->init();

  try {
    while (running) {
      std::vector<int> readable = m_transport->getReadableFds();

      for (size_t i = 0; i < readable.size(); ++i) {
        int fd = readable[i];

        std::cout << "fd move in run: " << fd << "..\n";
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Error, server stop running : " << e.what() << '\n';
  }

  std::cout << "Server stop.\n";
}
