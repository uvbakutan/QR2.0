/****************************************************************************
* L3G4200D.h - Interface L3G4200D gyroscop to an Arduino via i2c,           *
* this library is written for the freeIMU and is thus based on the code     *
* from the ITG3200 gyro in the freeIMU library.                             *
*                                                                           *
* author uvbakutan (GitHub)                                                 *
*                                                                           *
* This library is free software: you can redistribute it and/or modify      *
* it under the terms of the version 3 GNU General Public License as         *
* published by the Free Software Foundation.                                *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU Lesser General Public License for more details.                       *
*                                                                           *
* You should have received a copy of the GNU Lesser General Public License  *
* along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
****************************************************************************/

#ifndef L3G4200D_h
#define L3G4200D_h

#include "Arduino.h"
#include <Wire.h>

#define L3G4200D_Address  105 //I2C address of the L3G4200D

#define GYROSTART_UP_DELAY  70    // 50ms from gyro startup + 20ms register r/w startup

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

class L3G4200D {

public:
  float gains[3];
  int offsets[3];
  float polarities[3];

 L3G4200D();

  // Gyro initialization
  void init(int scale);

  // Gyro Sensors
  void readTemp(float *_Temp);
  void readGyroRaw(int  *_GyroXYZ);
  void readGyroRaw(int *_GyroX, int *_GyroY, int *_GyroZ);
  void setRevPolarity(bool _Xpol, bool _Ypol, bool _Zpol);	// true = Reversed  false = default
  void setGains(float _Xgain, float _Ygain, float _Zgain);
  void setOffsets(int _Xoffset, int _Yoffset, int _Zoffset);
  void zeroCalibrate(unsigned int totSamples, unsigned int sampleDelayMS);	// assuming gyroscope is stationary (updates XYZ offsets for zero)
  void readGyroRawCal(int *_GyroX, int *_GyroY, int *_GyroZ);
  void readGyroRawCal(int *_GyroXYZ);
  void readGyro(float *_GyroXYZ); // includes gain and offset
  void readGyro(float *_GyroX, float *_GyroY, float *_GyroZ); // includes gain and offset

  void writemem(uint8_t _addr, uint8_t _val);
  void readmem(uint8_t _addr, uint8_t _nbytes, uint8_t __buff[]);

private:

  uint8_t _dev_address;
  uint8_t _buff[6];
};
#endif
