#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

class tcpServer
{
public:
  tcpServer(int PORT);
  ~tcpServer();
  static const int BUFLEN = 512;
  void sendMsg(const std::string& msg);
  void receiveMsg(char buffer[BUFLEN]);
  void sendPacket(const void *packet, size_t packetSize);
  void receivePacket(void *buffer, size_t bufferSize);
  void closeConnection();
  void dieWithError(const char *s);
  int n;
  int sockfd, newsockfd;
private:
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
};

#endif // TCPSERVER_H
