query = audioread('dados/guitarSolo.wav');
query = query(:);
query = query*2^7;

quant = 7;
d = 1 / (2^quant);
alf = -1:d:1;

wav = audioread('dados/target01 - repeat.wav');
wav = wav(:);

wav = wav*2^7;
r = slidingWindow(query, wav, alf, floor(0.25*length(query)));
disp(r);

waitfor(plot(r));

wav = audioread('dados/target02 - repeatNoise.wav');
wav = wav(:);

wav = wav*2^7;
r = slidingWindow(query, wav, alf, floor(0.25*length(query)));
disp(r);

waitfor(plot(r));
