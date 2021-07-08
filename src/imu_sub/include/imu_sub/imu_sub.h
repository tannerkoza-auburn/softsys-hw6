// IMU Sub Class Header File

#ifndef IMU_SUB_H
#define IMU_SUB_H

#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "imu_sub/imu.h"

class ImuFilt
{

public:
    double q[4] = {1.0, 0.0, 0.0, 0.0};
    double dT = 0.01;

    ImuFilt(); // constructor

private:
    IMU imu;

    double acc[3];
    double gyro[3];

    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Publisher pub;

    void qCall(const sensor_msgs::Imu::ConstPtr &msg);
    void publishQ();
};

#endif
