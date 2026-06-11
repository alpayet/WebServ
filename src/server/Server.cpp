#include "Server.hpp"

#include <iostream>
#include <string>

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
        const int fd = readable[i];
        std::cout << "fd move in run: " << fd << "..\n";

        std::string raw_data = m_transport->processEvent(fd);
        if (!raw_data.empty()) {
          // m_transfer->request(fd, raw_data);
          std::cout << "Raw data:\n" << raw_data << "\n";

          m_transport->sendResponse(
              fd, std::string("HTTP/1.1 200 OK\r\n\r\n<h1>Hello Webserv</h1>"));
        }
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Error, server stop running : " << e.what() << '\n';
  }

  std::cout << "Server stop.\n";
}
