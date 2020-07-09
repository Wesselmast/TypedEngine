require 'TEcore'

topPipes = {}
bottomPipes = {}
amt = 7
distance = 500

function generatePipe(i, top, y) 
   local s = TEcore.TEQuad()
   local t = TEcore.TETransform()
   s:init()
   s:setColor(TEcore.color(0.1, 0.8, 0.0, 1.0))
   
   t.scale.x = 0.2
   t.position.x = (i - 1) * distance
   t.position.y = y
   t.scale.y = 2.0 * top
   
   s:setTransform(t)
   return {s, t}
end 

function generateMap(leniency) 
   for i=1,amt do
      local random = math.random(-250.0, 350.0)
      local offset = random - leniency
      table.insert(topPipes, generatePipe(i, 1, random))
      table.insert(bottomPipes, generatePipe(i, -1, offset))
   end
end

function tickMap(deltaTime)
   highest = -99999

   for p in ipairs(topPipes) do
      local t1 = topPipes[p][2]
      if t1.position.x > highest then
	 highest = t1.position.x
      end
   end

   for p in ipairs(topPipes) do
      local s1 = topPipes[p][1]
      local s2 = bottomPipes[p][1]
      local t1 = topPipes[p][2]
      local t2 = bottomPipes[p][2]
      
      t1.position.x = t1.position.x - (deltaTime * 200)
      t2.position.x = t2.position.x - (deltaTime * 200)
      
      if t1.position.x < -1000 then
	 t1.position.x = highest + distance
	 t2.position.x = highest + distance
      end

      s1:setTransform(t1)
      s2:setTransform(t2)
   end
end
