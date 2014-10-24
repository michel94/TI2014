function mmi = ex6mminf(file)
    query = audioread('dados/guitarSolo.wav');
    query = query(:);
    quant = 7;
    d = 1 / (2^quant);
    alf = -1:d:1;
    query = query*2^quant;
    
    wav = audioread(file);
    wav = wav(:);
    wav = wav*2^quant;
    r = slidingWindow(query, wav, alf, floor(0.25*length(query)) );
    figure;
    bar(r);
    mmi = max(r);
    
end
