% 1
im = imread('dados/kid.bmp');
createHist(im, 1:255);
entropia(im, 1:255)
% 2
im = imread('dados/homer.bmp');
createHist(im, 1:255);
entropia(im, 1:255)
% 3
im = imread('dados/homerBin.bmp');
createHist(im, [0 255]);
entropia(im, [0 255])
% 4
wav = wavread('dados/guitarSolo.wav');
quant = 8;
d = 1 / (2^quant);
alf = -1:d:1;
r = roundToNearest(wav, alf);
createHist(r, alf);
entropia(r, alf)
