#ifndef TWIDDLE_H
#define TWIDDLE_H

/**
 * @brief Observer-based implementation of twiddle algorithm
 */
class Twiddle
{
public:
  /**
  * Constructor
  * @param[in] k_p       optimization gain for proportional control
  * @param[in] k_i       optimization gain for integral control
  * @param[in] k_d       optimization gain for differential control
  * @param[in] threshold threshold of gain increment down to which optimization is executed
  */
  Twiddle(double k_p, double k_i, double k_d, double threshold = 0.01);
  
  /**
  * Denstructor
  */
  ~Twiddle();
  
  /**
  * Twiddle step execution on result of optimization error
  * @param[in] error optimization error
  * @param[in] k_p   optimization gain for proportional control
  * @param[in] k_i   optimization gain for integral control
  * @param[in] k_d   optimization gain for differential control
  */
  void onResult(double error, double &k_p, double &k_i, double &k_d);

private: // no impl

  Twiddle(const Twiddle &);
  Twiddle &operator=(const Twiddle &);

private:
  
  /** Optimization gains stored in array */
  double m_k[3];
  
  /** Optimization gain increments stored in array */
  double m_dk[3];
  
  /** Index of gain, which is currently optimized */
  unsigned m_index;
  
  /** Flag, which indicates whether the current optimization step is an increase of gain (value true) or a decrease of gain (value false) */
  bool m_isIncrease;
  
  /** Optimization threshold */
  const double THRESHOLD;
  
  /** Flag, which indicates initial state */
  bool m_isInitial;
  
  /** Best error encountered so far */
  double m_bestError;
  
};

#endif // TWIDDLE_H