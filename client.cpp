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
  size_t number_of_keypoints = 0;
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

  // int BUFLEN = 512;
  // char buffer[BUFLEN];
  // client.receiveMsg(buffer);
  // cout << "message received: " << buffer << endl;

  // /* send packet to server */
  // test testPacket;
  // testPacket.x = 52;
  // testPacket.y = 78;
  // testPacket.flag = 1;
  // cout << "size of packet:" << sizeof(testPacket) << endl;
  // client.sendPacket(&testPacket, sizeof(testPacket));

  /* receive packet from server */
  // void* dataBuffer = malloc(sizeof(DavisKeypointPacketHeader));
  // client.receivePacket(dataBuffer, sizeof(struct DavisKeypointPacketHeader)); //receive packet header
  // DavisKeypointPacketHeader* headerBuffer = (DavisKeypointPacketHeader*) dataBuffer;
  // cout << "DavisKeypointPacket.flag: " << headerBuffer->flag << endl;
  // cout << "DavisKeypointPacket.flag: " << headerBuffer->number_of_keypoints << endl;
  
  DavisKeypointPacketHeader header;
  client.receivePacket(&header, sizeof(header));
  cout << "header flag: " << header.flag << endl;
  cout << "number of keypoints: " << header.number_of_keypoints << endl;

  // int n = headerBuffer->number_of_keypoints;
  // vector<DavisKeypoint> keypoints(n);
  // client.receivePacket( &keypoints[0], n * sizeof(DavisKeypoint) );

  // client.receivePacket(headerBuffer + sizeof(struct DavisKeypointPacketHeader),
  //                 headerBuffer->number_of_keypoints * sizeof(DavisKeypoint));
  // DavisKeypoint* keypoint0 = (DavisKeypoint*) (headerBuffer + sizeof(struct DavisKeypointPacketHeader));
  // cout << "keypoint0: " << keypoint0->coordinate << endl;
  // DavisKeypoint* keypoint1 = (DavisKeypoint*) (headerBuffer + sizeof(struct DavisKeypointPacketHeader) + 1 * sizeof(DavisKeypoint));
  // cout << "keypoint1: " << keypoint1->coordinate << endl;
  // DavisKeypoint* keypoint2 = (DavisKeypoint*) (headerBuffer + sizeof(struct DavisKeypointPacketHeader) + 2 * sizeof(DavisKeypoint));
  // cout << "keypoint2: " << keypoint2->coordinate << endl;
  // DavisKeypoint* keypoint3 = (DavisKeypoint*) (headerBuffer + sizeof(struct DavisKeypointPacketHeader) + 3 * sizeof(DavisKeypoint));
  // cout << "keypoint3: " << keypoint3->coordinate << endl;
  // DavisKeypoint* keypoint4 = (DavisKeypoint*) (headerBuffer + sizeof(struct DavisKeypointPacketHeader) + 4 * sizeof(DavisKeypoint));
  // cout << "keypoint4: " << keypoint4->coordinate << endl;
  // DavisKeypointPacket* packet = (DavisKeypointPacket*) dataBuffer;
  // cout << "in the packet: " << packet->keypoints_davis.at(0).coordinate << endl;
  // cout << "address of packet: " << packet << endl;
  // cout << "address of first vector" << &(packet->keypoints_davis) << endl;

  // cout << "DavisKeypointPacket.at1.idx: " << headerBuffer->keypoints_davis.at(0).idx << endl;
  // cout << "DavisKeypointPacket.at1.x: " << headerBuffer->keypoints_davis.at(0).coordinate.x << endl;

  client.closeConnection();

  return 0;
}