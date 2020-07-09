require 'TEcore'
require 'TEmath'
require 'flappymap'

player = TEcore.TESprite()
transform = TEcore.TETransform()

jump = 0
velocity = vec2:new()
mass = 5
dead = 0

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
   
   if dead == 1 then
      transform.rotation = transform.rotation + (7 * deltaTime)
   else
      tickMap(deltaTime)
   end

   if transform.position.y < -500 or transform.position.y > 500 then
      if dead == 0 then
	 die()
	 return
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
   if dead == 1 then
      return
   end
   condition = (key == "SPACE") --and (velocity.y < 0)
   if condition then 
      jump = 1
   else
      jump = 0
   end
end
