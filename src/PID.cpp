#include "PID.h"

using namespace std;

PID::PID(double Kp, double Ki, double Kd)
{
  init(Kp, Ki, Kd);
}

PID::~PID() {}

void PID::init(double Kp, double Ki, double Kd)
{
  mP_error = 0.0;
  mI_error = 0.0;
  mD_error = 0.0;

  mKp = Kp;
  mKi = Ki;
  mKd = Kd;
}

double PID::getControlValue(double cte)
{
  mD_error  = cte - mP_error;
  mP_error  = cte;
  mI_error += cte;
  return -(mKp*mP_error + mKi*mI_error + mKd*mD_error);
}

double PID::getTotalError() const
{
  return mI_error;
}