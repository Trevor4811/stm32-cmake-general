#pragma once

#include <arpa/inet.h>
#include <atomic>
#include <sys/socket.h>
#include <thread>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

class Server {
  public:
    Server() {}
    ~Server() { stop(); }

    void startThreaded();
    void stop();

    void run();
    bool isRunning() { return m_shouldRun; };

    static constexpr __socket_type SOCKET_TYPE = SOCK_STREAM;
    static constexpr uint8_t       SIN_FAMILY  = AF_INET;
    in_addr_t IP_ADDRESS = INADDR_ANY; // inet_addr(SERVER_IP); // Localhost IP
    in_port_t PORT       = htons(SERVER_PORT);

  private:
    void init();

    std::thread       m_worker;
    std::atomic<bool> m_shouldRun{true};

    int         m_serverSocket;
    int         m_clientSocket;
    sockaddr_in m_serverAddr;
};