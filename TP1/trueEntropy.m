function ent = entropia(c, huf)
    total = sum(c);
    ent = 0;
    for i=1:length(c)
       ent = ent + (c(i) / total) * huf(i);
    end
end