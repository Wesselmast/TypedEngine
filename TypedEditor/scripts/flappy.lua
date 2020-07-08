require 'TEcore'

player = TEcore.TESprite()

function begin()
   player:init("res/textures/T_Brick.jpg");
end

function tick(deltaTime, time)
   local transform = TEcore.TETransform()

   -- if TEcore.isKeyDown(TEcore.W) then
   --    transform.position.y = transform.position.y + (200 * deltaTime)
   -- end
   -- if TEcore.isKeyDown(TEcore.A) then
   --    transform.position.x = transform.position.x - (200 * deltaTime)
   -- end
   -- if TEcore.isKeyDown(TEcore.S) then
   --    transform.position.y = transform.position.y - (200 * deltaTime)
   -- end
   -- if TEcore.isKeyDown(TEcore.D) then
   --    transform.position.x = transform.position.x + (200 * deltaTime)
   -- end
   player:setTransform(transform)
end

function key_down(key)
   if key == "T" then
      print("i did it")
   end
end
