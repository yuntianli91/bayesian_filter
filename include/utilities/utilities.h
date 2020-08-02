/**
 * @brief useful utilities 
 * 
 */
#pragma once
#include "common_headers.h"
#include "sensor/imu.h"
#include "sensor/beacon.h"
#include <Eigen/Dense>

using namespace std;

enum SAVE_FORMAT{
    KALIBR_ALLAN,
    TUM,
    EUROC,
};

/**
 * @brief write one ImuMotionData to file
 * 
 * @param fp 
 * @param t 
 * @param imuData 
 * @param format 
 */
void writeImuData(FILE *fp, ImuMotionData imuData, enum SAVE_FORMAT format);

/**
 * @brief save several ImuMotionData to file
 * 
 * @param fp 
 * @param t 
 * @param imuData 
 * @param format 
 */
void writeImuData(FILE *fp, std::vector<ImuMotionData> imuData, enum SAVE_FORMAT format);

/**
 * @brief write beacon location
 * 
 * @param fp 
 * @param all_beacons 
 * @param all_beacons_noise 
 */
void writeBeaconLocation(FILE *fp, std::map<int, Eigen::Vector3d> all_beacons, std::map<int, Eigen::Vector3d> all_beacons_noise);

/**
 * @brief write beacon status for one pose
 * 
 * @param fp 
 * @param time 
 * @param beaconStatus 
 */
void writeBeaconStatus(FILE *fp, double time, std::vector<bool> &beaconStatus);

/**
 * @brief write bacon measurements for one pose
 * 
 * @param filename 
 * @param relativeMeasurements 
 * @param interMeasurements 
 */
void writeBeaconMeasurements(string filepath, string filename, vector<BeaconMeasurement> &relativeMeasurements, vector<BeaconMeasurement> &interMeasurements);



