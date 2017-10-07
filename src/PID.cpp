#include "PID.h"
#include <iostream>

PID::PID(double Kp, double Ki, double Kd, bool runTwiddle)
  : mRunTwiddle(runTwiddle)
  , mStartedTwiddle(false)
  , mTwiddle(Kp, Ki, Kd)
{
  init(Kp, Ki, Kd);
}

PID::~PID() {}

double PID::getControlValue(double cte)
{
  // update counter and error
  mControlCount++;
  mD_error  = cte - mP_error;
  mP_error  = cte;
  mI_error += cte;

  if ( mRunTwiddle && (mControlCount % 10000 == 0) )
  {
    if ( !mStartedTwiddle )
    {
      // one initial round to get rid of impact of initial error
      init(mKp, mKi, mKd);
      mStartedTwiddle = true;
    }
    else
    {
      // do one twiddle step
      mTwiddle.onResult(getAverageError(), mKp, mKi, mKd);
      init(mKp, mKi, mKd);
    }
  }
  else if ( !mRunTwiddle && (mControlCount % 100 == 0) )
  {
    // debug output: error status
    std::cout << "==> Average control error[" << mControlCount << "]: " 
              << getAverageError() << std::endl;
  }

  // return control value
  return -(mKp*mP_error + mKi*mI_error + mKd*mD_error);
}

double PID::getAverageError() const
{
  return mI_error / double(mControlCount);
}

void PID::init(double Kp, double Ki, double Kd)
{
  mP_error = 0.0;
  mI_error = 0.0;
  mD_error = 0.0;

  mKp = Kp;
  mKi = Ki;
  mKd = Kd;

  mControlCount = 0;
}