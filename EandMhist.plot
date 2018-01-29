# Equilibrium time
teq = 30000

# Energy histogram
set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set key off
set style data histograms
set style fill solid 0.5
binwidth = 1
set boxwidth binwidth
bin(x,width) = width*floor(x/width) + binwidth/2.0

set output 'EhistHB.png'
set title 'Energy histogram'
set xlabel 'E'

plot 'energyHB.dat' every ::teq using (bin($2,binwidth)):(1.0) smooth freq with boxes

# Magnetization histogram
set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set key off
set style data histograms
set style fill solid 0.5
binwidth = 0.01
set boxwidth binwidth
bin(x,width) = width*floor(x/width) + binwidth/2.0

set output 'MhistHB.png'
set title 'Magnetization histogram'
set xlabel 'M'

plot 'magnetHB.dat' every ::teq using (bin($2,binwidth)):(1.0) smooth freq with boxes