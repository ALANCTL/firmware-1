// barometer.h


#ifndef __BAROMETER_H
#define __BAROMETER_H

#include "ADS1246_MPX6115A.h"

//#define USE_ADS1246_MPX6115A // <<< if define it here, it will work :)

#ifdef USE_ADS1246_MPX6115A

#define barometer_read_altitude() MPX6115_get_raw_altitude(ads1246_readADCconversion())
#define barometer_initialize() ads1246_initialize()
#define barometer_update_tare_value() mpu9250_calibrate_gyro_offset(offset,count)

#endif


#endif