local depths = {}
local increases = 0
local previousSum

for line in io.lines("input.txt") do table.insert(depths, tonumber(line)) end

for i, v in ipairs(depths) do
	if i < #depths-1 then
		local sum = depths[i] + depths[i + 1] +  depths[i + 2]
		
		if previousSum ~= nil and sum > previousSum then
			increases = increases + 1
		end
		
		previousSum = sum
	end
end

print(increases)