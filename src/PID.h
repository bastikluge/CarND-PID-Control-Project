#ifndef PID_H
#define PID_H

#include "Twiddle.h"

class PID
{
public:

  /*
  * Constructor
  */
  PID(double Kp=0.3, double Ki=0.0001, double Kd=1.0, bool runTwiddle=false);

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Update the PID error variables given cross track error
  * and return the resulting control value.
  */
  double getControlValue(double cte);

  /*
  * Calculate the total PID error (sum of all observed errors).
  */
  double getAverageError() const;

private:
  
  /*
  * Initialize PID.
  */
  void init(double Kp, double Ki, double Kd);

private: // no impl

  PID(const PID& );
  PID& operator=(const PID&);

private:

  /*
  * Errors
  */
  double mP_error;
  double mI_error;
  double mD_error;

  /*
  * Coefficients
  */
  double mKp;
  double mKi;
  double mKd;

  /**
  * Counter of control actuations
  */
  unsigned mControlCount;

  /**
  * Flag, which indicates whether Twiddle algorithm will be executed
  */
  bool mRunTwiddle;
  bool mStartedTwiddle;

  /**
  * Twiddle control gain optimizer
  */
  Twiddle mTwiddle;

};

#endif /* PID_H */