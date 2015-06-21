#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include "tcpServer.hpp"


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
	tcpServer server(9999);
	server.sendMsg("hello client, I'm server.");	
	return 0;
}