#include "Twiddle.h"
#include <iostream>
#include <math.h>

Twiddle::Twiddle(double k_p, double k_i, double k_d, double threshold)
  : m_k()
  , m_dk()
  , m_index(0U)
  , m_isIncrease(true)
  , THRESHOLD(threshold)
  , m_isInitial(true)
  , m_bestError(100000000.0)
{
    m_k[0] = k_p;
    m_k[1] = k_i;
    m_k[2] = k_d;
    m_dk[0] = fabs(k_p)/10.0;
    m_dk[1] = fabs(k_i)/10.0;
    m_dk[2] = fabs(k_d)/10.0;
}
  
Twiddle::~Twiddle()
{
}
  
void Twiddle::onResult(double error, double &k_p, double &k_i, double &k_d)
{
  if ( fabs(m_dk[0]) + fabs(m_dk[1]) + fabs(m_dk[2]) > THRESHOLD )
  {
    if ( m_isInitial )
    {
      // only initialize error
      m_bestError = error;
      m_isInitial = false;
    }
    else 
    {
      // prepare and switch to next step
      if ( error > m_bestError )
      {
        // revert current gain change and switch to next
        if ( m_isIncrease )
        {
          m_k[m_index] -= m_dk[m_index];

          // m_index remains constant, twiddle next tries to decrease the same gain
          m_isIncrease = false;
        }
        else
        {
          m_k[m_index]  += m_dk[m_index];
          m_dk[m_index] *= 0.8;
    
          m_index++;
          m_isIncrease = true;
        }
      }
      else
      {
        // accept current gain change and switch to next
        m_bestError = error;
        if ( m_isIncrease )
        {
          m_dk[m_index] *= 1.2;
    
          m_index++;
          // m_isIncrease remains constant, twiddle next tries to increase the next gain 
        }
        else
        {
          m_dk[m_index] *= 1.2;
    
          m_index++;
          m_isIncrease = true;
        }
      }
    }
    
    // ensure index stays in range (cyclic)
    if ( m_index > 2 ) m_index = 0;
    
    // execute current optimization step
    if ( m_isIncrease )
    {
      m_k[m_index] += m_dk[m_index];
    }
    else
    {
      m_k[m_index] -= m_dk[m_index];
    }
    
    // set output gain
    k_p = m_k[0];
    k_i = m_k[1];
    k_d = m_k[2];
    
    // debug output
    std::cout << "Twiddle updated: (k_p, k_i, k_d) = (" << m_k[0] << ", " << m_k[1] << ", " << m_k[2] << ")" << std::endl;
    std::cout << "        ... |dk| = |(" << m_dk[0] << ", " << m_dk[1] << ", " << m_dk[2] << ")| = "
              <<  fabs(m_dk[0]) + fabs(m_dk[1]) + fabs(m_dk[2]) << " >= " << THRESHOLD << std::endl;
  }
  else
  {
    // debug output
    std::cout << "Twiddle terminated: (k_p, k_i, k_d) = (" << m_k[0] << ", " << m_k[1] << ", " << m_k[2] << ")" << std::endl;
    std::cout << "        ... |dk| = |(" << m_dk[0] << ", " << m_dk[1] << ", " << m_dk[2] << ")| = "
              <<  fabs(m_dk[0]) + fabs(m_dk[1]) + fabs(m_dk[2]) << " < " << THRESHOLD << std::endl;
  }
  
  // debug output
  std::cout << "        ==> best error: " << m_bestError << std::endl;
}
