% 1
im = imread('dados/kid.bmp');
im = im(:);
im = vec2mat(im, 2);
alf = getpairs(0:255);
createHist(im, alf);
disp(entropy(im, alf) / 2);

% 2
im = imread('dados/homer.bmp');
im = im(:);
im = vec2mat(im, 2);
alf = getpairs(0:255);
createHist(im, alf);
disp(entropy(im, alf) / 2);

% 3
im = imread('dados/homerBin.bmp');
im = im(:);
im = vec2mat(im, 2);
alf = getpairs([0 255]);
createHist(im, alf);
disp(entropy(im, alf) / 2);

% 4
wav = audioread('dados/guitarSolo.wav');
wav = wav(:);
%wav = roundToNearest(wav, alf);
wav = vec2mat(wav, 2);
quant = 7;
d = 1 / (2^quant);
alf = getpairs(-1:d:1);
createHist(wav, alf);
disp(entropy(wav, alf) / 2);

% 5
englishAlphabet = ['a':'z' 'A':'Z'];
textFile = fopen('dados/english.txt');
text = fscanf(textFile, '%s');
fclose(textFile);
text = text(:);
text = vec2mat(text, 2);
alf = getpairs(englishAlphabet);
createHist(text, alf);
disp(entropy(text, alf) / 2);

