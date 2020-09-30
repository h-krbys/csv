#ifndef __CSV_PLAYER_H__
#define __CSV_PLAYER_H__

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/JointState.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_SIZE 10000

class Player {
public:
  Player();
  ~Player();

  void timerCallback(const ros::TimerEvent &);

  void load();

private:
  ros::NodeHandle nh;
  ros::Timer      timer;
  ros::Publisher  pubJointState;

  sensor_msgs::JointState jointState;

  int   count, max;
  float data[FILE_SIZE][12];
};

#endif // __CSV_PLAYER_H__