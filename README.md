
# benchmarking massive data streams

First, we send a number to the echo server which doubles the value and adds 1,
then sends this back to the caller. This is repeated n times.
Second, the time is measured with a high-precision clock for the complete
sending and receiving path. This measurements are kept in an array which is then
sorted and output to a file.

# evaluation

Using **gnuplot** we analyse the time measurements with a boxplot.
This shows nicely in the box the expected time for a quarter, half, three quarters of the
total measurements. Additionally, atop are drawn the outliers which take
excessively long to return.

![benchmark where Java beats C++](demo01.png)

# example

```
> ./echo/c++/EchoServer_Release 11234 &

> java -jar ./echo/java/EchoServer.jar &

> ./caller/CallerServer_Release_1_0 localhost 11234 0 1000
  after 1000 repetitions: 29 < 38 < 217 us (10^-6 seconds)
  after 1000 repetitions: min: 29 q1[250]: 32 median[500]: 39 q3[750]: 41 max: 217 us (10^-6 seconds)

> ./caller/CallerServer_Release_1_0 localhost 24937 0 1000
  after 1000 repetitions: 29 < 39 < 449 us (10^-6 seconds)
  after 1000 repetitions: min: 28 q1[250]: 31 median[500]: 39 q3[750]: 43 max: 449 us (10^-6 seconds)

```
![benchmark almost identical](demo02.png)

