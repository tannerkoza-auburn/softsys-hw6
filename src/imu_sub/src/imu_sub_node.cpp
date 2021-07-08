#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "imu_sub/imu_sub.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "imu_sub");
  ImuFilt filter; // class instance declaration
  ros::spin();
  return 0;
}