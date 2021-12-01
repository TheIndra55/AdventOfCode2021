local increases = 0
local previous

for line in io.lines("input.txt") do
	local depth = tonumber(line)
	
	if previous ~= nil and previous < depth then
		increases = increases + 1
	end
	
	previous = depth
end

print(increases)