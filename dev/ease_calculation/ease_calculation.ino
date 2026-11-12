// ButterServo
// ------------
// Ease calculation test
// - checking the results match spreadsheet values
//
// 12 Nov 2026
// Erin RobotZwrrl

#include <Streaming.h>

uint16_t resolution = 10; // max: 512-1
uint16_t duration = 1000;  // ms
float angle_start = 0;
float angle_end = 45;
uint8_t angles_lut[512];
uint16_t timing_lut[512];
float f_angles_lut[512]; // just for testing
unsigned long calculation_time[512]; // just for testing


void setup() {
  Serial.begin(9600);
}

void loop() {

  for(uint16_t i=0; i<resolution+1; i++) {

    float x = ( HALF_PI / resolution ) * i;
    float y = (float)sin((double)x);
    float angle_step = ( ( angle_end - angle_start ) / resolution ) * i;
    float angle_map = angle_step * y;

    timing_lut[i] = ( (uint16_t)floor( duration / resolution ) ) * i;
    f_angles_lut[i] = angle_map; // just for testing
    angles_lut[i] = (float)ceil((double)angle_map);
    calculation_time[i] = micros(); // just for testing
  }

  Serial << "x, timing, angle, angle (float), time (us)" << endl;
  for(uint16_t i=0; i<resolution+1; i++) {
    Serial << i << ", " << timing_lut[i] << ", " << angles_lut[i] << ", " << _FLOAT(f_angles_lut[i], 4);
    if(i > 0) {
      Serial << ", " << calculation_time[i]-calculation_time[i-1];
    }
    Serial << endl;
  }

}



/*

result:

x, timing, angle, angle (float), time (us)
0, 0, 0, 0.0000
1, 100, 1, 0.7040, 11
2, 200, 3, 2.7812, 11
3, 300, 7, 6.1289, 11
4, 400, 11, 10.5801, 10
5, 500, 16, 15.9099, 11
6, 600, 22, 21.8435, 15
7, 700, 29, 28.0667, 14
8, 800, 35, 34.2380, 19
9, 900, 41, 40.0014, 14
10, 1000, 45, 45.0000, 14

*/


