
function add(a, b) 
	c = c_add(a, b)
	return c, a, b
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