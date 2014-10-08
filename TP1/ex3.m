% 1
im = imread('dados/kid.bmp');
im = im(:);
createHist(im, 1:255);
entropia(im, 1:255)

% 2
im = imread('dados/homer.bmp');
im = im(:);
createHist(im, 1:255);
entropia(im, 1:255)

% 3
im = imread('dados/homerBin.bmp');
im = im(:);
createHist(im, [0 255]);
entropia(im, [0 255])

% 4
wav = audioread('dados/guitarSolo.wav');
wav = wav(:);
quant = 7;
d = 1 / (2^quant);
alf = -1:d:1;
r = roundToNearest(wav, alf);
createHist(r, alf);
entropia(r, alf)