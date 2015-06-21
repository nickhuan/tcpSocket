#include "tcpServer.hpp"

tcpServer::tcpServer(const int PORT)
{
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    this->dieWithError("ERROR opening Socket");
  else
    printf("-> Socket open\n");
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    this->dieWithError("ERROR on binding");
  printf("-> Binding successful\n");
  printf("-> Start TCP client in new terminal: 'ncat -v localhost 9999'\n");
  fflush(stdout);
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);
  if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) < 0)
    this->dieWithError("Error on accept");
  else
    printf("-> Socket accepted: Press any key in TCP client terminal\n");
  // bzero(buffer, BUFLEN);
  // if ((n = read(newsockfd, buffer, BUFLEN)) < 0)
  //   this->dieWithError("Error reading from socket");
  // printf("-> Received packet from %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
  // printf("-> Data: %s\n", buffer);
}

tcpServer::~tcpServer()
{
}

void tcpServer::sendMsg(const std::string& msg)
{
  if ((n = write(newsockfd, msg.c_str(), msg.length())) < 0)
    dieWithError("Error writing to Socket");
}

void tcpServer::closeConnection()
{
  close(sockfd);
  close(newsockfd);
}

void tcpServer::dieWithError(const char *s)
{
  perror(s);
  exit(1);
}
