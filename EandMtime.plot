set terminal pngcairo size 800,600 enhanced font 'Verdana,10'

# Energe plot
set title 'Q = 100, T = 0.8, L = 64, T0 = inf'
set output 'Etime-Q100-T08-L64-Tinf.png'
set xlabel 'MCSweeps'
set ylabel 'Energy'
plot 'energyMet.dat' u 1:2 t 'Metropolis' w l, 'energyHB.dat' u 1:2 t 'Heat bath' w l

# Magnetization plot
set title 'Q = 100, T = 0.8, L = 64, T0 = inf'
set output 'Mtime-Q100-T08-L64-Tinf.png'
set xlabel 'MCSweeps'
set ylabel 'Magnetization'
plot 'magnetMet.dat' u 1:2 t 'Metropolis' w l, 'magnetHB.dat' u 1:2 t 'Heat bath' w l
