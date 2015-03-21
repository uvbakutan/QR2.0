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

#include "L3G4200D.h"

L3G4200D::L3G4200D() {
  setGains(1.0,1.0,1.0);
  setOffsets(0.0,0.0,0.0);
  setRevPolarity(0,0,0);
  //Wire.begin();       //Normally this code is called from setup() at user code
                        //but some people reported that joining I2C bus earlier
                        //apparently solved problems with master/slave conditions.
                        //Uncomment if needed.
}

void L3G4200D::init( int scale) {
//From  Jim Lindblom of Sparkfun's code

   _dev_address = L3G4200D_Address;

  // Enable x, y, z and turn off power down:
  writemem(CTRL_REG1, 0b00001111);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writemem(CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writemem(CTRL_REG3, 0b00001000);

  // CTRL_REG4 controls the full-scale range, among other things:

  if(scale == 250){
    writemem(CTRL_REG4, 0b00000000);
  }else if(scale == 500){
    writemem(CTRL_REG4, 0b00010000);
  }else{
    writemem(CTRL_REG4, 0b00110000);
  }

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writemem(CTRL_REG5, 0b00000000);
}


void L3G4200D::readGyroRaw(int *_GyroX, int *_GyroY, int *_GyroZ){
  readmem(0x28, 1, &_buff[0]);
  readmem(0x29, 1, &_buff[1]);
  readmem(0x2A, 1, &_buff[2]);
  readmem(0x2B, 1, &_buff[3]);
  readmem(0x2C, 1, &_buff[4]);
  readmem(0x2D, 1, &_buff[5]);
  *_GyroX = (int16_t)((_buff[1] << 8) | _buff[0]);
  *_GyroY = (int16_t)((_buff[3] << 8) | _buff[2]);
  *_GyroZ = (int16_t)((_buff[5] << 8) | _buff[4]);
}

void L3G4200D::readGyroRaw(int *_GyroXYZ){
  readGyroRaw(_GyroXYZ, _GyroXYZ+1, _GyroXYZ+2);
}

void L3G4200D::setRevPolarity(bool _Xpol, bool _Ypol, bool _Zpol) {
  polarities[0] = _Xpol ? -1 : 1;
  polarities[1] = _Ypol ? -1 : 1;
  polarities[2] = _Zpol ? -1 : 1;
}

void L3G4200D::setGains(float _Xgain, float _Ygain, float _Zgain) {
  gains[0] = _Xgain;
  gains[1] = _Ygain;
  gains[2] = _Zgain;
}

void L3G4200D::setOffsets(int _Xoffset, int _Yoffset, int _Zoffset) {
  offsets[0] = _Xoffset;
  offsets[1] = _Yoffset;
  offsets[2] = _Zoffset;
}

void L3G4200D::zeroCalibrate(unsigned int totSamples, unsigned int sampleDelayMS) {
  int xyz[3];
  float tmpOffsets[] = {0,0,0};

  for (int i = 0;i < totSamples;i++){
    delay(sampleDelayMS);
    readGyroRaw(xyz);
    tmpOffsets[0] += xyz[0];
    tmpOffsets[1] += xyz[1];
    tmpOffsets[2] += xyz[2];
  }
  setOffsets(-tmpOffsets[0] / totSamples, -tmpOffsets[1] / totSamples, -tmpOffsets[2] / totSamples);
}

void L3G4200D::readGyroRawCal(int *_GyroX, int *_GyroY, int *_GyroZ) {
  readGyroRaw(_GyroX, _GyroY, _GyroZ);
  *_GyroX += offsets[0];
  *_GyroY += offsets[1];
  *_GyroZ += offsets[2];
}

void L3G4200D::readGyroRawCal(int *_GyroXYZ) {
  readGyroRawCal(_GyroXYZ, _GyroXYZ+1, _GyroXYZ+2);
}

void L3G4200D::readGyro(float *_GyroX, float *_GyroY, float *_GyroZ){
  int x, y, z;

  readGyroRawCal(&x, &y, &z); // x,y,z will contain calibrated integer values from the sensor
  *_GyroX =  x / 14.375 * polarities[0] * gains[0];
  *_GyroY =  y / 14.375 * polarities[1] * gains[1];
  *_GyroZ =  z / 14.375 * polarities[2] * gains[2];
}

void L3G4200D::readGyro(float *_GyroXYZ){
  readGyro(_GyroXYZ, _GyroXYZ+1, _GyroXYZ+2);
}


void L3G4200D::writemem(uint8_t _addr, uint8_t _val) {
  Wire.beginTransmission(_dev_address);   // start transmission to device
  Wire.write(_addr); // send register address
  Wire.write(_val); // send value to write
  Wire.endTransmission(); // end transmission
}

void L3G4200D::readmem(uint8_t _addr, uint8_t _nbytes, uint8_t __buff[]) {
  Wire.beginTransmission(_dev_address); // start transmission to device
  Wire.write(_addr); // sends register address to read from
  Wire.endTransmission(); // end transmission

  Wire.beginTransmission(_dev_address); // start transmission to device
  Wire.requestFrom(_dev_address, _nbytes);// send data n-bytes read
  while(!Wire.available()) {    /*waiting*/ }
   *__buff= Wire.read(); // receive DATA

  Wire.endTransmission(); // end transmission
}
