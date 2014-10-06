% 1
im = imread('dados/kid.bmp');
c = hist(im, 1:255);
hufflen(c)
% 2
im = imread('dados/homer.bmp');
c = hist(im, 1:255);
hufflen(c)
% 3
im = imread('dados/homerBin.bmp');
c = hist(im, [0 255]);
hufflen(c)
% 4
wav = wavread('dados/guitarSolo.wav');
quant = 7;
d = 1 / (2^quant);
alf = -1:d:1;
r = roundToNearest(wav, alf);
c = hist(r, alf);
hufflen(c)
