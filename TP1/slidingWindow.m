function inf = slidingWindow(query, target, alf, step)
    
    s = length(target)-length(query)+1;

    inf = zeros(1, s);
    for i=1:step:s
        i
        target(i: i+length(query)-1);
        inf(i) = mutualInf(query, target(i: i+length(query)-1), alf);
    end
    inf = transpose(inf);

end