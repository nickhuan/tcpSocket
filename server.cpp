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
  size_t number_of_keypoints = 0;
};

void sendKeypoints(tcpServer server, FrameType frame_type,
  const vector<DavisKeypoint> &keypoints_vector) {
  DavisKeypointPacketHeader bufferHeader;
  bufferHeader.number_of_keypoints = keypoints_vector.size();
  bufferHeader.flag = frame_type;
  server.sendPacket(&bufferHeader, sizeof(bufferHeader));

  for (DavisKeypoint kp : keypoints_vector) {
  }
};

int main( int argc, char** argv )
{
	tcpServer server(9999);
	// server.sendMsg("hello client, I'm server.");

 //  // test testPacket;
 //  // struct test structTest;
 //  // cout << "size of packet:" << sizeof(testPacket) << endl;
 //  // test *buffer;
 //  size_t bufferSize = 16;
 //  test *buffer = (test*) malloc(bufferSize);
 //  // test receivedPacket;
 //  // cout << "1";
 //  server.receivePacket(buffer, bufferSize);
 //  cout << "received" << endl;
 //  cout << "received packet.x: " << buffer->x << endl;
 //  cout << "received packet.y: " << buffer->y << endl;
 //  cout << "received packet.idx: " << buffer->idx << endl;
 //  cout << "received packet.flag: " << buffer->flag << endl;

  vector<DavisKeypoint> keypoints_vector(5);
  cout << "size of keypoints_vector: " << sizeof(keypoints_vector) << endl;
  cout << "keypoints_vector.size(): " << keypoints_vector.size() << endl;
  sendKeypoints(server, FRAME, keypoints_vector);

  // DavisKeypointPacket classPacket1;
  // cout << "size of class DavisKeypointPacket: " << sizeof(classPacket1) << endl; 

  // DavisKeypointPacket classPacket2(2);
  // cout << "size of DavisKeypointPacketHeader: " << sizeof(DavisKeypointPacketHeader) << endl; 
  // cout << "size of DavisKeypoint object: " << sizeof(DavisKeypoint) << endl; 
  // cout << "size of class DavisKeypointPacket with vector size of 2: " << sizeof(classPacket2) << endl; 
  // DavisKeypointPacket classPacket0(0);
  // cout << "size of class DavisKeypointPacket with vector size of 0: " << sizeof(classPacket0) << endl; 
  // DavisKeypointPacket classPacket5(5);
  // classPacket5.keypoints_davis.at(3).coordinate = Point2f (23,56);
  // cout << "size of class DavisKeypointPacket with vector size of 5: " << sizeof(classPacket5) << endl; 
  // cout << "size of vector of 5: " << sizeof(classPacket5.keypoints_davis) << endl; 
  // // std::vector<int> v;
  // // cout << "size of vector int: " << sizeof(v) << endl;
  // cout << "header flag: " << classPacket5.header.flag << endl;
  // cout << "number keypoints: " << classPacket5.header.number_of_keypoints << endl;   
  // cout << "vector size: " << classPacket5.keypoints_davis.size() << endl; 

  // server.sendPacket(&classPacket5, sizeof(classPacket5));

  server.closeConnection(); 

	return 0;
}