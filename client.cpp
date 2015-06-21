#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include "tcpClient.hpp"


using namespace std;
using namespace cv;

/* Struct and Class */
struct DavisKeypoint
{
  Point2i coordinate = Point2i(0,0);
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

  return 0;
}