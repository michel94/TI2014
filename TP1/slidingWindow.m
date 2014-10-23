function inf = slidingWindow(query, target, alf, step)
    
    s = length(target)-length(query)+1;
    
    inf = zeros(1, length(1:step:s));
    for i=1:step:s
        inf(floor(i/step) + 1) = mutualInf(query, target(i: i+length(query)-1), alf);
    end
    %inf = transpose(inf);

end
