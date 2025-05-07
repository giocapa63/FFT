set terminal pngcairo size 800,400 enhanced font 'Arial,10'
set output 'sine_plot.png'

set title "Sine Wave"
set xlabel "Sample Index"
set ylabel "Amplitude"
set grid

plot "wave.txt" with lines title "Sine wave"