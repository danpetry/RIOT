local m = {}

function m.figlet(s)
    local chars = {}
    for i=1, #s do
        chars[i] = mineplex.char(s:byte(i,i))
    end

    for j=1, mineplex.HEIGHT do
       for i=1, #s do
            c = chars[i]
            for k=1, mineplex.WIDTH do
                b = c:index(k, j)
                local dot
                if (b) then
                    if (i%2 == 0) then
                       dot = "#"
                    else
                       dot = "X"
                    end
                else
                    dot = " "
                end
                io.write(dot)
            end
       end
       io.write('\n')
    end
end

return m
