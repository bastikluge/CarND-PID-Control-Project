# **PID Controller** 

**PID Controller Project**

The goals / steps of this project are the following:
* Implement the PID controller as taught in lesson 16 "PID Control"
* Tune the PID controller parameters such that the vehicle safely drives through the simulated race track
* Summarize the results with a written report


[//]: # (Video References)

[videoP]:   ./P_video.mp4   "P Controller Video"
[videoPD]:  ./PD_video.mp4  "PD Controller Video"
[videoPID]: ./PID_video.mp4 "PID Controller Video"


## Rubric Points

Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/824/view) individually and describe how I addressed each point in my implementation.  

## Implementation of PID Controller

#### Effect of P component

See [video](./P_video.mp4)...

#### Effect of D component

See [video](./PD_video.mp4)...

#### Effect of I component

See [video](./PID_video.mp4)...

## Parameter tuning

I chose twiddle, see lines...

| P-gain | I-gain | D-gain | error  |
|:------:|:------:|:------:|:------:|
| 0.10   | 0.0    | 0.05   | 0.5878 |
| 0.10   | 0.0    | 0.10   | 0.5082 |
| 0.10   | 0.0    | 0.15   | 0.5080 |
| 0.15   | 0.0    | 0.15   | 0.3461 |
| 0.15   | 0.0    | 0.20   | 0.3477 |
| 0.20   | 0.0    | 0.15   | 0.2683 |
| 0.20   | 0.0    | 0.20   | 0.2649 |
| 0.20   | 0.0    | 0.25   | 0.2744 |
| 0.25   | 0.0    | 0.15   | 0.2268 |
| 0.25   | 0.0    | 0.20   | 0.2251 |
| 0.25   | 0.0    | 0.25   | 0.2219 |
| 0.25   | 0.0    | 0.30   | 0.2300 |
| 0.30   | 0.0    | 0.30   | 0.1917 |
| 0.30   | 0.0    | 0.50   | 0.1982 |
| 0.30   | 0.0    | 0.70   | 0.1925 |
| 0.30   | 0.0    | 0.90   | 0.1971 |
| 0.30   | 0.0    | 1.00   | 0.1926 |
| 0.30   | 0.0    | 1.10   | 0.1934 |
| 0.30   | 0.0    | 1.20   | 0.1937 |
| 0.30   | 0.0    | 1.50   | 0.1950 |
| 0.30   | 0.1    | 1.00   | n.a.   |
| 0.30   | 0.01   | 1.00   | n.a.   |
| 0.30   | 0.001  | 1.00   | 0.0201 |
| 0.30   | 0.0001 | 1.00   | 0.1400 |

First look at reasonable P-gain and try to stay in local minimum of D-gain.
Then observe strong overshoots and try to reduce overshoots by increasing D-gain.
Next try to find reasonable magnitude for I-gain.