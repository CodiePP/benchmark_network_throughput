# this gnuplot script has been taken from the gnuplot demo at:
# http://gnuplot.sourceforge.net/demo_5.0/boxplot.html
# set terminal canvas  rounded size 600,400 enhanced fsize 10 lw 1.6 fontscale 1
# name "boxplot_1" jsdir "."
set term png
set output 'boxplot.png'
set border 2 front lt black linewidth 1.000 dashtype solid
set boxwidth 0.5 absolute
set style fill   solid 0.25 border lt -1
unset key
set pointsize 0.5
set style data boxplot
set xtics border in scale 0,0 nomirror norotate  autojustify
set xtics  norangelimit 
set xtics   ("C++" 1.00000, "Java" 2.00000)
set ytics border in scale 1,0.5 nomirror norotate  autojustify
unset paxis 1 tics
unset paxis 2 tics
unset paxis 3 tics
unset paxis 4 tics
unset paxis 5 tics
unset paxis 6 tics
unset paxis 7 tics
set yrange [ 0.00000 : 150.000 ] noreverse nowriteback
set paxis 1 range [ * : * ] noreverse nowriteback
set paxis 2 range [ * : * ] noreverse nowriteback
set paxis 3 range [ * : * ] noreverse nowriteback
set paxis 4 range [ * : * ] noreverse nowriteback
set paxis 5 range [ * : * ] noreverse nowriteback
set paxis 6 range [ * : * ] noreverse nowriteback
set paxis 7 range [ * : * ] noreverse nowriteback
x = 0.0
## Last datafile plotted: "silver.dat"
plot 'localhost_10000.csv' using (1.0):2, '' using (2.0):3

