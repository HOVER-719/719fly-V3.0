#ifndef _KALMAN_H


#define _KALMAN_H

extern double xrate; // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate

extern double yrate; // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate

extern double zrate; // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate


void xInit_Kalman(void);

double xgetAngle(double newAngle, double newRate, double dt);

//void xKalmanSetAngle(double newAngle);


void yInit_Kalman(void);

double ygetAngle(double newAngle, double newRate, double dt);

//void yKalmanSetAngle(double newAngle);

void zInit_Kalman(void);

double zgetAngle(double newAngle, double newRate, double dt);

//void zKalmanSetAngle(double newAngle);
#endif
