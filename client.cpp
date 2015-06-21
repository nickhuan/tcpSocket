#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include "tcpClient.hpp"


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
  /* TCP Client Setup */
  tcpClient client("127.0.0.1", 9999);

  int BUFLEN = 512;
  char buffer[BUFLEN];
  client.receiveMsg(buffer);
  cout << "message received: " << buffer << endl;

  test testPacket;
  struct test structTest;
  cout << "size of packet:" << sizeof(testPacket) << endl;
  client.sendPacket(&testPacket, sizeof(testPacket));

  client.closeConnection();

  return 0;
}