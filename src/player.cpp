#include "player.h"

Player::Player() {
  pubJointState = nh.advertise<sensor_msgs::JointState>("joint_states_source", 1);

  timer = nh.createTimer(ros::Duration(0.05), &Player::timerCallback, this);

  jointState.header.stamp = ros::Time::now();
  jointState.name.resize(12);
  jointState.position.resize(12);

  jointState.name[0]  =   "front_left_shoulder";
  jointState.name[1]  =   "front_left_leg";
  jointState.name[2]  =   "front_left_foot";
  jointState.name[3]  =   "front_right_shoulder";
  jointState.name[4]  =   "front_right_leg";
  jointState.name[5]  =   "front_right_foot";
  jointState.name[6]  =   "rear_left_shoulder";
  jointState.name[7]  =   "rear_left_leg";
  jointState.name[8]  =   "rear_left_foot";
  jointState.name[9]  =   "rear_right_shoulder";
  jointState.name[10] =   "rear_right_leg";
  jointState.name[11] =   "rear_right_foot";

  for (int i = 0; i < 12; i++) {
    jointState.position[i] = 0;
  }

  load();
}

Player::~Player() {
}

void Player::load(){
  FILE  *fp = NULL;
  double buf[12];

  if ( ( fp = fopen("/home/kuribayashi/catkin_ws/file.csv", "r") ) == NULL) {
    ROS_INFO_STREAM("file open error...");
    exit(EXIT_FAILURE);
  }else{
    ROS_INFO_STREAM("file found!!");
  }

  max = 0;
  while( ( fscanf(fp, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                  &buf[0], &buf[1], &buf[2], &buf[3], &buf[4], &buf[5],
                  &buf[6], &buf[7], &buf[8], &buf[9], &buf[10], &buf[11])
           ) != EOF) {
    for(int i = 0; i < 12; i++) {
      data[max][i] = buf[i];
    }
    max++;
  }

  fclose(fp);
}

void Player::timerCallback(const ros::TimerEvent &) {
  jointState.header.stamp = ros::Time::now();

  if(count < max) {
    for (int i = 0; i < 12; i++) {
      jointState.position[i] = data[count][i];
    }
  }
  pubJointState.publish(jointState);
  count++;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "player");
  Player player;
  ros::spin();
}