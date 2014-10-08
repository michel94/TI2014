% 1
im = imread('dados/kid.bmp');
createHist(im, 1:255);
disp(entropia(im, 1:255));

% 2
im = imread('dados/homer.bmp');
createHist(im, 1:255);
disp(entropia(im, 1:255));

% 3
im = imread('dados/homerBin.bmp');
createHist(im, [0 255]);
disp(entropia(im, [0 255]));

% 4
wav = audioread('dados/guitarSolo.wav');
quant = 7;
d = 1 / (2^quant);
alf = -1:d:1;
r = roundToNearest(wav, alf);
createHist(r, alf);
disp(entropia(r, alf));

% 5
englishAlphabet = ['a' 'b' 'c' 'd' 'e' 'f' 'g' 'h' 'i' 'j' 'k' 'l' 'm' 'n' 'o' 'p' 'q' 'r' 's' 't' 'u' 'w' 'x' 'y' 'z' ];
textFile = fopen('dados/english.txt');
text = fscanf(textFile, '%s');
createHist(text, englishAlphabet);
disp(entropia(text, englishAlphabet));
