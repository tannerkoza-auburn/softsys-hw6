#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "imu_sub/imu_sub.h"

int main(int argc, char **argv)
{
  double dT;
  ros::init(argc, argv, "imu_sub");
  ros::param::set("/tstep", 1.0 / 100.0);
  ros::param::get("/tstep", dT);

  ImuFilt filter(dT); // class instance declaration
  ros::spin();
  return 0;
}