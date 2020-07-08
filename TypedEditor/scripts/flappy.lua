require 'TEcore'

player = TEcore.TESprite()
input = TEcore.TETransform()
transform = TEcore.TETransform()

function begin()
   player:init("res/textures/T_Bird.png");
end

function tick(deltaTime, time)
   transform.position.x = transform.position.x + (input.position.x * 200 * deltaTime)
   transform.position.y = transform.position.y + (input.position.y * 200 * deltaTime)

   player:setTransform(transform)
end

function key_down(key)
   if key == "W" then 
      input.position.y =  1 
      input.position.x =  0
   elseif key == "A" then 
      input.position.x = -1 
      input.position.y =  0
   elseif key == "S" then 
      input.position.y = -1 
      input.position.x =  0
   elseif key == "D" then 
      input.position.x =  1 
      input.position.y =  0
   else
      input.position.x =  0
      input.position.y =  0
   end
end
