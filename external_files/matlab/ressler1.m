function xdot = ressler1(t,x)
[a, b, c] = textread('ResslerParams.txt', '%f %f %f', 1);
xdot = [-x(2)-x(3);x(1)+a*x(2);b+x(3)*(x(2)+c)];