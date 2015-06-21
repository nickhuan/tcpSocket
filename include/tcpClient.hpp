#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>

class tcpClient
{
public:
  tcpClient(const char *ipAddress, int PORT);
  ~tcpClient();
  // void readMsg(const std::string& msg);
  void sendMsg(const std::string& msg);
  void closeConnection();
  void dieWithError(const char *s);
  int n;
  int sockfd;
  static const int BUFLEN = 512;
private:
  socklen_t clilen;
  char buffer[BUFLEN];
  struct sockaddr_in serv_addr;
  struct hostent *server;
};

#endif // TCPCLIENT_H
