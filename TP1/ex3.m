% 1
im = imread('dados/kid.bmp');
im = im(:);
createHist(im, 0:255);
disp(entropy(im, 0:255));

% 2
im = imread('dados/homer.bmp');
im = im(:);
createHist(im, 0:255);
disp(entropy(im, 0:255));

% 3
im = imread('dados/homerBin.bmp');
im = im(:);
createHist(im, [0 255]);
disp(entropy(im, [0 255]));

% 4
wav = audioread('dados/guitarSolo.wav');
wav = wav(:);
quant = 7;
d = 1 / (2^quant);
alf = -1:d:1;
r = wav; %r = roundToNearest(wav, alf);
createHist(r, alf);
disp(entropy(r, alf));

% 5
englishAlphabet = ['a':'z' 'A':'Z'];
textFile = fopen('dados/english.txt');
text = fscanf(textFile, '%s');
fclose(textFile);
text = text(:);
createHist(text, englishAlphabet);
disp(entropy(text, englishAlphabet));
