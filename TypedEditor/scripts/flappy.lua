require 'TEcore'

local player = TEcore.TESprite()
local transform = TEcore.TETransform()

local jump = 0
local velocity = TEcore.vec2()
local mass = 5
local dead = 0

function begin()
   player:init("res/textures/T_Bird.png")
   transform.position.x = -500
   generateMap(250)
end

function tick(deltaTime, time)
   transform.position.y = transform.position.y + (velocity.y * deltaTime)
   if jump == 1 then
      velocity.y = 750
      jump = 0
   else
      velocity.y = velocity.y - (9.8 * mass)
   end
   player:setTransform(transform)
   
   local newPos = TEcore.vec2(transform.position.x, transform.position.y)
   newPos.x = newPos.x + 100
   newPos.y = newPos.y + 20
   
   if dead == 1 then
      transform.rotation = transform.rotation + (7 * deltaTime)
   else
      if tickMap(deltaTime, newPos) == 1 then
   	 die()
      end
   end

   if newPos.y < -500 or newPos.y > 500 then
      if dead == 0 then
	 die()
      end
   end
end

function die() 
   local dietext = TEcore.TEText()
   local dietrans = TEcore.TETransform()
   dietrans.position.x = -155
   dietrans.scale.x = 2.0
   dietrans.scale.y = 2.0
   dietext:init(dietrans, "YOU DIED!")
   dietext:setColor(TEcore.color(0.8, 0.6, 0.1, 1.0))
   dead = 1
end

function key_down(key)
   if dead == 0 then
      condition = (key == "SPACE") --and (velocity.y < 0)
      if condition then 
	 jump = 1
      else
	 jump = 0
      end
   end
end

-- map

local topPipes = {}
local bottomPipes = {}
local amt = 7
local distance = 500

function generatePipe(i, y) 
   local s = TEcore.TEQuad()
   local t = TEcore.TETransform()
   s:init()
   s:setColor(TEcore.color(0.1, 0.8, 0.0, 1.0))
   
   t.scale.x = 0.2
   t.position.x = (i - 1) * distance
   t.position.y = y
   t.scale.y = 2.0
   
   s:setTransform(t)
   return {s, t}
end 

function generateMap(leniency) 
   for i=1,amt do
      local random = math.random(-250.0, 350.0)
      local offset = random - (leniency + 1000)
      table.insert(topPipes, generatePipe(i, random))
      table.insert(bottomPipes, generatePipe(i, offset))
   end
end

function tickMap(deltaTime, playerPos)
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

      if s1:overlaps(playerPos) or s2:overlaps(playerPos) then
	 return 1
      end
   end

   return 0
end
