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
  /* TCP Client Setup */
  tcpClient client("127.0.0.1", 9999);

  int BUFLEN = 512;
  char buffer[BUFLEN];
  client.receiveMsg(buffer);
  cout << "message received: " << buffer << endl;

  /* send packet to server */
  test testPacket;
  testPacket.x = 52;
  testPacket.y = 78;
  testPacket.flag = 1;
  cout << "size of packet:" << sizeof(testPacket) << endl;
  client.sendPacket(&testPacket, sizeof(testPacket));

  /* receive oacket from server */
  DavisKeypointPacket* davisbuffer = (DavisKeypointPacket*) malloc(BUFLEN);
  client.receivePacket(davisbuffer, BUFLEN);
  cout << "DavisKeypointPacket.flag: " << davisbuffer->header.flag << endl;
  // cout << "DavisKeypointPacket.at1.idx: " << davisbuffer->keypoints_davis.at(0).idx << endl;
  // cout << "DavisKeypointPacket.at1.x: " << davisbuffer->keypoints_davis.at(0).coordinate.x << endl;

  client.closeConnection();

  return 0;
}