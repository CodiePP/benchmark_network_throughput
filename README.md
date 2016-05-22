
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

[!demo01.png]

