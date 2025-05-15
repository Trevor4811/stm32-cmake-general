#pragma once

#include <Server.hpp>
#include <arpa/inet.h>
#include <atomic>
#include <sys/socket.h>
#include <thread>

class Client {
  public:
    Client() {}
    ~Client() { stop(); }

    void startThreaded();
    void stop();

    void run();
    bool isRunning() { return m_shouldRun; };

    static constexpr __socket_type SOCKET_TYPE = Server::SOCKET_TYPE;
    static constexpr uint8_t       SIN_FAMILY  = Server::SIN_FAMILY;
    in_addr_t IP_ADDRESS = inet_addr(SERVER_IP); // Localhost IP
    in_port_t PORT       = htons(SERVER_PORT);

  private:
    void init();

    std::thread       m_worker;
    std::atomic<bool> m_shouldRun{true};

    int         m_clientSocket;
    sockaddr_in m_serverAddr;
};