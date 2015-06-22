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
enum FrameType {
  FRAME = 1,
  EVENT = 0
};
struct DavisKeypointPacketHeader
{
  FrameType flag = EVENT;
  int number_of_keypoints = 0;
};
class DavisKeypointPacket
{
public:

  DavisKeypointPacketHeader header;
  vector<DavisKeypoint> keypoints_davis;

  DavisKeypointPacket(int n = 0)
  : keypoints_davis(n)
  { header.number_of_keypoints = n; }
};

int main( int argc, char** argv )
{
	tcpServer server(9999);
	server.sendMsg("hello client, I'm server.");

  // test testPacket;
  // struct test structTest;
  // cout << "size of packet:" << sizeof(testPacket) << endl;
  // test *buffer;
  size_t bufferSize = 16;
  test *buffer = (test*) malloc(bufferSize);
  // test receivedPacket;
  // cout << "1";
  server.receivePacket(buffer, bufferSize);
  cout << "received" << endl;
  cout << "received packet.x: " << buffer->x << endl;
  cout << "received packet.y: " << buffer->y << endl;
  cout << "received packet.idx: " << buffer->idx << endl;
  cout << "received packet.flag: " << buffer->flag << endl;

  // DavisKeypointPacket classPacket1;
  // cout << "size of class DavisKeypointPacket: " << sizeof(classPacket1) << endl; 

  DavisKeypointPacket classPacket2(2);
  cout << "size of class DavisKeypointPacket with vector size of 2: " << sizeof(classPacket2) << endl; 
  cout << "header flag: " << classPacket2.header.flag << endl;
  cout << "number keypoints: " << classPacket2.header.number_of_keypoints << endl;   
  cout << "vector size: " << classPacket2.keypoints_davis.size() << endl; 
  // DavisKeypointPacket classPacket0(0);
  // cout << "size of class DavisKeypointPacket with vector size of 0: " << sizeof(classPacket0) << endl; 

  server.sendPacket(&classPacket2, sizeof(classPacket2));

  server.closeConnection(); 

	return 0;
}