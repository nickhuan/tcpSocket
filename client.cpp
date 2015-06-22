#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include "tcpClient.hpp"

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

vector<DavisKeypoint> receiveKeypoints(tcpClient client)
{
  DavisKeypointPacketHeader header;
  client.receivePacket(&header, sizeof(header));
  cout << "header flag: " << header.flag << endl;
  cout << "number of keypoints: " << header.number_of_keypoints << endl;

  vector<DavisKeypoint> keypoints_vector(header.number_of_keypoints);
    for (auto &&kp: keypoints_vector)
  {
    client.receivePacket(&kp, sizeof(DavisKeypoint));
  }
  return keypoints_vector;
};

int main( int argc, char** argv )
{
  /* TCP Client Setup */
  tcpClient client("127.0.0.1", 9999);
  
  vector<DavisKeypoint> keypoints_vector = receiveKeypoints(client);

  cout << "in keypoints_vector at 3: " << keypoints_vector.at(3).coordinate << endl;
  cout << "in keypoints_vector at 4: " << keypoints_vector.at(4).coordinate << endl;

  client.closeConnection();

  return 0;
}