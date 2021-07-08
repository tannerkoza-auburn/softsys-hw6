// IMU Class Implementation

#include <iostream>
#include "imu_sub/imu.h"

using namespace std;

IMU::IMU(double q[4], double tstep) // constructor declaration
{
    // cout << *q << endl;
    cout << q[0] << "\t";
    cout << q[1] << "\t";
    cout << q[2] << "\t";
    cout << q[3] << endl;

    Q[0] = q[0]; // provide initial values to quaternion class variable when instance declared
    Q[1] = q[1];
    Q[2] = q[2];
    Q[3] = q[3];

    cout << Q[0] << "\t";
    cout << Q[1] << "\t";
    cout << Q[2] << "\t";
    cout << Q[3] << endl;

    dT = tstep; // provide value to timestep class variable when instance declared

    cout << dT << endl;
}

double *IMU::propagate(double *q, double *gyro)
{
    q[0] = (Q[0] + (Q[1] * -0.5 * gyro[0] * dT) + (Q[2] * -0.5 * gyro[1] * dT) + (Q[3] * -0.5 * gyro[2] * dT)); // filter calculations using class variable
    q[1] = ((Q[0] * 0.5 * gyro[0] * dT) + Q[1] + (Q[2] * 0.5 * gyro[2] * dT) + (Q[3] * -0.5 * gyro[1] * dT));
    q[2] = ((Q[0] * 0.5 * gyro[1] * dT) + (Q[1] * -0.5 * gyro[2] * dT) + Q[2] + (Q[3] * 0.5 * gyro[0] * dT));
    q[3] = ((Q[0] * 0.5 * gyro[2] * dT) + (Q[1] * 0.5 * gyro[1] * dT) + (Q[2] * -0.5 * gyro[0] * dT) + Q[3]);

    double *row_ptr = q; // create pointer for calculated array

    return row_ptr;
}

void IMU::normalize(double *ptr) // normalize function
{
    double temp;
    double mag;

    for (int i = 0; i < 4; i++)
    {
        temp += pow(*(ptr + i), 2); // add squares of 4 column elements together
    }

    mag = sqrt(temp); // find magnitude

    for (int i = 0; i < 4; i++)
    {
        *(ptr + i) = *(ptr + i) / mag; // divide the current contents by the mag and resave
    }
}

void IMU::update(double (&q)[4], double (&gyro)[3]) // update filter function
{
    double *row_ptr = propagate(q, gyro); // return pointer to calculated q array

    normalize(row_ptr); // normalize array

    Q[0] = q[0]; // assign new array (q[4] in main scope) to class variable indices
    Q[1] = q[1];
    Q[2] = q[2];
    Q[3] = q[3];
}