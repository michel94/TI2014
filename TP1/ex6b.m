query = audioread('dados/guitarSolo.wav');
query = query(:);

quant = 7;
d = 1 / (2^quant);
alf = -1:d:1;

wav = audioread('dados/target01 - repeat.wav');
wav = wav(:);
r = slidingWindow(query, wav, alf, floor(0.25 * length(query)));
disp(r);
disp(var(r));
waitfor(plot(r));

wav = audioread('dados/target02 - repeatNoise.wav');
wav = wav(:);
r = slidingWindow(query, wav, alf, floor(0.25 * length(query)));
disp(r);
disp(var(r));
waitfor(plot(r));
