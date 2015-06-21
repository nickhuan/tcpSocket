#include "tcpClient.hpp"

tcpClient::tcpClient(const char *ipAddress, int PORT)
{
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    this->dieWithError("ERROR opening Socket");
  else
    printf("-> Socket open\n");

  server = gethostbyname(ipAddress);
  if (server == NULL)
  {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(PORT);
  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
      this->dieWithError("ERROR connecting");

  // bzero(buffer, BUFLEN);
  // if ((n = read(sockfd, buffer, BUFLEN)) < 0)
  //   this->dieWithError("Error reading from socket");
  // printf("-> Received packet from %s:%d\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
  // printf("-> Data: %s\n", buffer);
}

tcpClient::~tcpClient()
{
}

// void tcpClient::readMsg(const std::string& msg)
// {
//   if ((n = read(sockfd, msg.c_str(), msg.length())) < 0)
//     dieWithError("Error reading from Socket");
// }
void tcpClient::sendMsg(const std::string& msg)
{
  if ((n = write(sockfd, msg.c_str(), msg.length())) < 0)
    dieWithError("Error writing to Socket");
}

void tcpClient::closeConnection()
{
  close(sockfd);
}

void tcpClient::dieWithError(const char *s)
{
  perror(s);
  exit(1);
}
