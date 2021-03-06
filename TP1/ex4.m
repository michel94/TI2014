% 1
im = imread('dados/kid.bmp');
im = im(:);
c = hist(im, 0:255);
huf = hufflen(c);
disp(trueEntropy(c, huf));

% 2
im = imread('dados/homer.bmp');
im = im(:);
c = hist(im, 0:255);
huf = hufflen(c);
disp(trueEntropy(c, huf));

% 3
im = imread('dados/homerBin.bmp');
im = im(:);
c = hist(im, [0 255]);
huf = hufflen(c);
disp(trueEntropy(c, huf));

% 4
wav = audioread('dados/guitarSolo.wav');
wav = wav(:);
quant = 7;
d = 1 / (2^quant);
alf = -1:d:1;
r = wav; %r = roundToNearest(wav, alf);
c = hist(r, alf);
huf = hufflen(c);
disp(trueEntropy(c, huf));

% 5
englishAlphabet = ['a':'z' 'A':'Z'];
textFile = fopen('dados/english.txt');
text = fscanf(textFile, '%s');
fclose(textFile);
text = text(:);
c = hist(text, englishAlphabet);
huf = hufflen(c);
disp(trueEntropy(c, huf));
