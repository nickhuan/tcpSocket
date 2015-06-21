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
}

tcpClient::~tcpClient()
{
}

void tcpClient::sendMsg(const std::string& msg)
{
  if ((n = write(sockfd, msg.c_str(), msg.length())) < 0)
    dieWithError("Error writing message to socket");
}

void tcpClient::receiveMsg(char buffer[BUFLEN])
{
  bzero(buffer, BUFLEN);
  if ((n = read(sockfd, buffer, BUFLEN)) < 0)
    dieWithError("Error reading message from socket");
}

void tcpClient::sendPacket(const void *packet, size_t packetSize)
{
  if ((n = write(sockfd, packet, packetSize)) < 0)
    dieWithError("Error sending packet to socket");
}

void tcpClient::receivePacket(void *buffer, size_t bufferSize)
{
  bzero(buffer, bufferSize);
  if ((n = read(sockfd, buffer, bufferSize)) < 0)
    dieWithError("Error receiving packet from socket");
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
