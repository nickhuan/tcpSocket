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
  void sendMsg(const std::string& msg);
  static const int BUFLEN = 512;
  void readMsg(char buffer[BUFLEN]);
  void closeConnection();
  void dieWithError(const char *s);
  int n;
  int sockfd, newsockfd;
private:
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
};

#endif // TCPSERVER_H
