#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include "tcpServer.hpp"


using namespace std;
using namespace cv;

/* Struct and Class */
struct test
{
  int x = 0;
  int y = 0;
  int idx = 0;
  bool flag = 0;
};
struct DavisKeypoint
{
  Point2f coordinate = Point2f(0,0);
  int idx = 0;
};
enum FrameType
{
  FRAME = 1,
  EVENT = 0
};
class DavisKeypointPacket
{
public:

  FrameType flag = EVENT;
  vector<DavisKeypoint> keypoints_davis;

  DavisKeypointPacket(int n = 0)
  : keypoints_davis(n)
  {}
};

int main( int argc, char** argv )
{
	tcpServer server(9999);
	server.sendMsg("hello client, I'm server.");

  // test testPacket;
  // struct test structTest;
  // cout << "size of packet:" << sizeof(testPacket) << endl;
  void *buffer;
  size_t bufferSize = 512;
  // uint8_t *buffer = malloc(bufferSize);
  test receivedPacket;
  server.receivePacket(&receivedPacket, sizeof(receivedPacket));
  cout << "received packet: " << receivedPacket.x << endl;

  struct DavisKeypoint davisPacket;
  cout << "size of struct DavisKeypoint: " << sizeof(davisPacket) << endl;

  DavisKeypointPacket classPacket1;
  cout << "size of class DavisKeypointPacket: " << sizeof(classPacket1) << endl; 

  DavisKeypointPacket classPacket2(2);
  cout << "size of class DavisKeypointPacket with vector size of 2: " << sizeof(classPacket2) << endl; 

  server.closeConnection(); 

	return 0;
}