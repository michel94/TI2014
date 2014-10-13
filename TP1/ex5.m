% 1
im = imread('dados/kid.bmp');
im = im(:);
im = vec2mat(im, 2);
%createHist(im, 0:255);
disp(entropia(im, getpairs(0:255))/2 );

% 2
im = imread('dados/homer.bmp');
im = im(:);
im = vec2mat(im, 2);
%createHist(im, 0:255);
disp(entropia(im, getpairs(0:255))/2 );

% 3
im = imread('dados/homerBin.bmp');
im = im(:);
im = vec2mat(im, 2);
%createHist(im, [0 255]);
disp(entropia(im, getpairs([0 255]))/2 );

% 4
wav = audioread('dados/guitarSolo.wav');
wav = wav(:);
wav = vec2mat(wav, 2);
quant = 7;
d = 1 / (2^quant);
alf = -1:d:1;
r = wav; %r = roundToNearest(wav, alf);
%createHist(r, alf);
disp(entropia(im, getpairs(alf))/2 );

% 5
englishAlphabet = ['a':'z' 'A':'Z'];
textFile = fopen('dados/english.txt');
text = fscanf(textFile, '%s');
fclose(textFile);
text = text(:);
text = vec2mat(text, 2);
%createHist(text, englishAlphabet);
disp(entropia(text, getpairs(englishAlphabet))/2 );

