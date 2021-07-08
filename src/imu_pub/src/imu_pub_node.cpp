#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <boost/geometry/geometries/adapted/boost_array.hpp>
#include <fstream>

int main(int argc, char **argv)
{
    // ROS Setup
    ros::init(argc, argv, "imu_pub");
    ros::NodeHandle pnh("~");

    std::string frame_id;
    pnh.param<std::string>("frame_id", frame_id, "imu_frame");

    ros::Publisher imu_pub = pnh.advertise<sensor_msgs::Imu>("imu", 1);

    ros::Rate loop_rate(100);

    // File Reading Setup
    std::string input_file = "/home/tannerkoza/SFSAS/HW4/data/hw3_data.txt"; // declare file name
    std::ifstream infile(input_file);                                        // make class instance of read while opening respective file

    double acc[3], gyro[3], mag[3];                            // declare arrays to store values
    boost::array<double, 9> cov = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // declare covariance array

    if (infile.is_open())
    {
        ROS_INFO("IMU Data Publishing...");

        while (ros::ok())
        {

            sensor_msgs::Imu imu_msg;
            imu_msg.header.stamp = ros::Time::now();
            imu_msg.header.frame_id = frame_id;

            infile >> acc[0] >> acc[1] >> acc[2] >> gyro[0] >> gyro[1] >> gyro[2] >> mag[0] >> mag[1] >> mag[2]; // passes input file values to corresponding variables

            imu_msg.linear_acceleration.x = acc[0]; // assign message values
            imu_msg.linear_acceleration.y = acc[1];
            imu_msg.linear_acceleration.z = acc[2];
            imu_msg.linear_acceleration_covariance = cov;

            imu_msg.angular_velocity.x = gyro[0];
            imu_msg.angular_velocity.y = gyro[1];
            imu_msg.angular_velocity.z = gyro[2];
            imu_msg.angular_velocity_covariance = cov;

            imu_pub.publish(imu_msg);

            ros::spinOnce();
            loop_rate.sleep();
        }
    }
}
