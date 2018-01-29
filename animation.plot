set term gif animate delay 1
set output 'animationHB.gif'
stats 'animationHB.dat' nooutput

unset border
unset xtics
unset ytics
unset key

t = 0

do for [i=1:int(STATS_blocks)] {
    set label 1 sprintf("MCS = %dk",t ) at 0.5, -4
    t = t + 10
    plot 'animationHB.dat' index (i-1) matrix with image
}