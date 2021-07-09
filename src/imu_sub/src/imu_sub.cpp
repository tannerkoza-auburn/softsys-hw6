#include "imu_sub/imu_sub.h"
#include "imu_sub/imu.h"

ImuFilt::ImuFilt(double dT_) : imu(q, dT_)
{
    sub = n.subscribe("imu_pub/imu", 1, &ImuFilt::qCall, this);
    pub = n.advertise<sensor_msgs::Imu>("imu_sub/imu", 1);

    ROS_INFO("IMU Data Subscribing & Publishing...");
}

void ImuFilt::qCall(const sensor_msgs::Imu::ConstPtr &msg)
{
    ROS_INFO("CALLBACK NOW.");

    acc[0] = msg->linear_acceleration.x;
    acc[1] = msg->linear_acceleration.y;
    acc[2] = msg->linear_acceleration.z;

    gyro[0] = msg->angular_velocity.x;
    gyro[1] = msg->angular_velocity.y;
    gyro[2] = msg->angular_velocity.z;

    imu.update(q, gyro);

    publishQ();
}

void ImuFilt::publishQ()
{
    sensor_msgs::Imu imu_msg;
    imu_msg.header.stamp = ros::Time::now();
    imu_msg.header.frame_id = "frame_id";

    imu_msg.orientation.x = q[0];
    imu_msg.orientation.y = q[1];
    imu_msg.orientation.z = q[2];
    imu_msg.orientation.w = q[3];

    imu_msg.angular_velocity.x = gyro[0];
    imu_msg.angular_velocity.y = gyro[1];
    imu_msg.angular_velocity.z = gyro[2];

    imu_msg.linear_acceleration.x = acc[0];
    imu_msg.linear_acceleration.y = acc[1];
    imu_msg.linear_acceleration.z = acc[2];

    pub.publish(imu_msg);
}