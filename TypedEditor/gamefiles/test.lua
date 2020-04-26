require "test2"
require "moreTests/test4"
require "TypedLuaCollection"

function main()
   
   -- t = manipulatePosition()
   -- t = t + manipulatePosition()
   TypedLuaCollection.print_hello()
   TypedLuaCollection.print_hello()
   TypedLuaCollection.print_hello()
   TypedLuaCollection.print_hello()
   TypedLuaCollection.print_hello()
   TypedLuaCollection.print_hello()
   
   -- print(add(t.x, 80))
   -- print(add(t.y, 20))
   -- print(add(t.y, 20))
   -- print(add(t.y, 20))
   -- print(add(t.y, 20))
   -- print(add(t.y, 20))
   -- print(add(t.y, 20))
   -- print(add(t.y, 20))
   -- print(add(t.y, 20))
   -- print(add(t.y, 20))
   -- print(add(t.y, 20))
   -- thatTookLong ()
   -- computesomethinghard()

   --[[         ASYNC TEST!
   index = 0
   while true do
      print(index)
      index = index + 1
   end
   --]]
end

function add(a, b) 
   return a + b 
end

-- function manipulatePosition()
--  --  t1 = createVector()
--  --  t2 = createVector()
--    t1.x = 60
--    t1.y = 2.5
--    t2.y = 25
--    t2.x = 195
--    return t1 + t2
-- end
