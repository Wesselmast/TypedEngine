require "test2"
require "moreTests/test4"

function main()
	t = manipulatePosition()
	t = t + manipulatePosition()
	print(add(t.x, 50))
	print(add(t.y, 20))
	-- thatTookLong ()
	-- computesomethinghard()
end

function add(a, b) 
	return a + b 
end

function manipulatePosition()
	t1 = createVector()
	t2 = createVector()
	t1.x = 50
	t1.y = 2.5
	t2.y = 25
	t2.x = 195
	return t1 + t2
end