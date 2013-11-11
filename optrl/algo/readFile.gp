
plot [-250:250][-250:250] 'points.txt' u 2:3 every 1::1::n
pause 0.5
n = n+1
reread