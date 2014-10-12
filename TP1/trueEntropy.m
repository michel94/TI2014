function ent = entropia(c, huf)
    ent = sum((c/sum(c)) .* huf);
end