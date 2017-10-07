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

The effect of the P component is to steer the car back to the middle of the road if it deviates from it (i.e., if the cross track error is different to 0). Using this control gain only, the car oscillates around the middle of the road. As long as speeds are low and the road is fairly straight the vehicle stays on the road. However, as soon as speeds are higher and the road has a curve, the oscillations become too wide and the car leaves the road. This can be observed in this [video](./P_video.mp4), which was recorded with a throttle control of 0.3 and a P controller with gain K_p = 0.22.

#### Effect of D component

The effect added by the D component to a P controller (resulting in a PD controller) is to steer the car back to the middle of the road more strongly while the cross track error is increasing and to steer the car back to the middle more slightly while the cross track error is decreasing. This damps the oscillation of the car around the road center observed with the P controller, as can be seen in this [video](./PD_video.mp4), which was recorded with throttle control of 0.3 and a PD controller with gains K_p = 0.22 and K_d = 3.1.

#### Effect of I component

As known from the lecture, the I gain is supposed to compensate for small drift errors within the system. However, when setting too high values it acts similar to the P-gain for the first/initial deviation from the middle of the road and leads to a strong overshoot followed by leaving the road on the opposite side. I measured that small values were able to further reduce the average error, but I could not observe a different driving behavior of the vehicle. 

## Parameter tuning

In order to find reasonable parameters for the PID I first limited the speed to 20 mph (by setting the throttle value to 0 whenever this speed was exceeded) and tried to find a reasonable magnitude of the P-gain. Because of the strong oscillations I observed with a pure P controller I simultaneously added a small D-gain, for which I tried to stay in local minimum of D-gain. (Without the D-gain, the car would have gotten off the road already in the first curve.) Below table shows the resulting average error over the first 2000 control steps:

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

As a P-gain in the magnitude of 0.3 showed reasonable performance and small average error, I next switched to searching for a reasonable magnitude of the D-gain. With the value of 0.3 I still observed strong oscillations, because of which I tried to significantly increase the D-gain. The next table shows the resulting average error over the first 2000 control steps (still with maximum speed 20 mph):

| P-gain | I-gain | D-gain | error  |
|:------:|:------:|:------:|:------:|
| 0.30   | 0.0    | 0.50   | 0.1982 |
| 0.30   | 0.0    | 0.70   | 0.1925 |
| 0.30   | 0.0    | 0.90   | 0.1971 |
| 0.30   | 0.0    | 1.00   | 0.1926 |
| 0.30   | 0.0    | 1.10   | 0.1934 |
| 0.30   | 0.0    | 1.20   | 0.1937 |
| 0.30   | 0.0    | 1.50   | 0.1950 |

After these test runs, the car drove still oscillating but fairly smoothly along the road, so I tried to find a reasonable magnitude for the I-gain. I found that high values result in a strong overshoot after the initial deviation from the middle of the road and lead to leaving the road on the opposite direction (so the 2000 control steps were never reached and the error is provided as 'n.a.' in below table). Small values in a range of 0.0001-0.001 seem to improve the average error however, as can be seen in the next table (still with maximum speed 20mph and showing the average error after 2000 control steps):

| P-gain | I-gain | D-gain | error  |
|:------:|:------:|:------:|:------:|
| 0.30   | 0.1    | 1.00   | n.a.   |
| 0.30   | 0.01   | 1.00   | n.a.   |
| 0.30   | 0.001  | 1.00   | 0.0201 |
| 0.30   | 0.0001 | 1.00   | 0.1400 |

Then I compared my above results to the performance of the PID controller with the values suggested in the PID lesson:

| P-gain | I-gain | D-gain | error  |
|:------:|:------:|:------:|:------:|
| 0.20   | 0.0001 | 3.10   | 0.1779 |

As these parameters had a similar performance as my best parameters found so far but resulted in much smoother driving (less oscillation due to higher D-gain) I ran the Twiddle algorithm based on these initial values to find a locally optimal solution. Here, I used a throttle control value of 0.3. The Twiddle algorithm is implemented in the files `Twiddle.h` and `Twiddle.cpp` and observes the average error of the PID controller after 2800 control steps (approximately one lap of the race track with throttle control value 0.3). The resulting locally optimal solution is:

| P-gain | I-gain | D-gain | error  |
|:------:|:------:|:------:|:------:|
| 0.22   | 0.00009| 3.1    | 0.1016 |
