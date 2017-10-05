#ifndef PID_H
#define PID_H

class PID
{
public:

  /*
  * Constructor
  */
  PID(double Kp=0.0, double Ki=0.0, double Kd=0.0);

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error
  * and return the resulting control value.
  */
  double getControlValue(double cte);

  /*
  * Calculate the total PID error (sum of all observed errors).
  */
  double totalError() const;

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

};

#endif /* PID_H */