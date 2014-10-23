query = [2 6 4 10 5 9 5 8 0 8];
target = [6 8 9 7 2 4 9 9 4 9 1 4 8 0 1 2 2 6 3 2 0 7 4 9 5 4 8 5 2 7 8 0 7 4 8 5 7 4 3 2 2 7 3 5 2 7 4 9 9 6];
alf = 0:10;

expected = transpose([2.1219 1.9219 1.6464 2.1710 1.9710 1.7710 2.0464 2.1219 2.3219 2.5219 2.2464 2.2464 2.2464 2.2464 2.4464 2.4464 2.5219 2.7219 2.5219 2.3219 2.3219 2.1219 2.3219 2.3219 2.1219 2.0464 2.0464 2.0464 2.0464 2.0464 2.3219 2.3219 2.0464 2.1219 2.3219 1.8464 1.7710 2.0464 2.0464 2.0464 2.3219]);

r = slidingWindow(query, target, alf, 1);
%disp(r - expected);

