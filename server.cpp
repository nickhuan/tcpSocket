#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include "tcpServer.hpp"

using namespace std;
using namespace cv;

/* Struct and Class */
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
  size_t number_of_keypoints = 0;
};

void sendKeypoints(tcpServer server, FrameType frame_type,
                  const vector<DavisKeypoint> &keypoints_vector)
{
  DavisKeypointPacketHeader bufferHeader;
  bufferHeader.number_of_keypoints = keypoints_vector.size();
  bufferHeader.flag = frame_type;
  server.sendPacket(&bufferHeader, sizeof(bufferHeader));

  // for each kp in keypoints_vector
  for (auto &&kp: keypoints_vector)
  {
    server.sendPacket(&kp, sizeof(DavisKeypoint));
  }
};

int main( int argc, char** argv )
{
	tcpServer server(9999);

  vector<DavisKeypoint> keypoints_vector(5);
  keypoints_vector.at(3).coordinate = Point2f (33,56);
  cout << "size of keypoints_vector: " << sizeof(keypoints_vector) << endl;
  cout << "keypoints_vector.size(): " << keypoints_vector.size() << endl;

  sendKeypoints(server, FRAME, keypoints_vector);

  server.closeConnection(); 

	return 0;
}