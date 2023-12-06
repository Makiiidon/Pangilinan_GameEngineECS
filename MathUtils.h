#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "Vector3D.h"
#include <cmath>

class MathUtils
{
public:
	static float randomFloat(float a, float b);
	static int randomInt(int a, int b);

	static constexpr float PI = M_PI;

    struct Quaternion {
        float x, y, z, w;
    };

    //static Vector3D QuaternionToEulerAngles(const Quaternion& q) {
    //    Vector3D angles;
    //    float x, y, z;

    //    // Roll (x-axis rotation)
    //    float sinr_cosp = 2.0f * (qw * qx + qy * qz);
    //    float cosr_cosp = 1.0f - 2.0f * (qx * qx + qy * qy);
    //    z = std::atan2(sinr_cosp, cosr_cosp);

    //    // Pitch (y-axis rotation)
    //    float sinp = 2.0f * (qw * qy - qz * qx);
    //    if (std::abs(sinp) >= 1)
    //        x = std::copysign(M_PI / 2, sinp); // Use 90 degrees if out of range
    //    else
    //        x = std::asin(sinp);

    //    // Yaw (z-axis rotation)
    //    float siny_cosp = 2.0f * (qw * qz + qx * qy);
    //    float cosy_cosp = 1.0f - 2.0f * (qy * qy + qz * qz);
    //    y = std::atan2(siny_cosp, cosy_cosp);

    //    // Convert radians to degrees
    //    z = z * 180.0f / M_PI;
    //    y = y * 180.0f / M_PI;
    //    x = x * 180.0f / M_PI;
    //    return angles;
    //}

    static Vector3D QuaternionToEulerAngles(float qx, float qy, float qz, float qw) {
        Vector3D angles;
            float x, y, z;

            // Roll (x-axis rotation)
            float t0 = 2.0f * (qw * qx + qy * qz);
            float t1 = 1.0f - 2.0f * (qx * qx + qy * qy);
            z = std::atan2(t0, t1);

            // Pitch (y-axis rotation)
            float t2 = 2.0f * (qw * qy - qz * qx);
            if (std::abs(t2) >= 1)
                x = std::copysign(M_PI / 2, t2); // Use 90 degrees if out of range
            else
                x = std::asin(t2);

            // Yaw (z-axis rotation)
            float t3 = 2.0f * (qw * qz + qx * qy);
            float t4 = 1.0f - 2.0f * (qy * qy + qz * qz);
            y = std::atan2(t3, t4);

            // Convert radians to degrees
            z = z * 180.0f / M_PI;
            y = y * 180.0f / M_PI;
            x = x * 180.0f / M_PI;

            std::cout << "X: " << x << "\nY: " << y << "\nZ: " << z << "\n";
            angles = new Vector3D(x, y, z);

            return angles;
    }
};

