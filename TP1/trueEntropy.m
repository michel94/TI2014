function [ent] = trueEntropy(c, huf)
    ent = sum((c/sum(c)) .* huf);
end