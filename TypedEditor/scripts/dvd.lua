require 'TEcore'

player = TEcore.TESprite()
input = TEcore.vec2()
transform = TEcore.TETransform()

function begin()
   player:init("res/textures/T_DVD.png");
   transform.scale.x = 0.25
   transform.scale.y = 0.25
   input.x = 1
   input.y = 1
end

function tick(deltaTime)
   transform.position.x = transform.position.x + (input.x * 200 * deltaTime)
   transform.position.y = transform.position.y + (input.y * 200 * deltaTime)

   if transform.position.y < -500 then
      input.y =  1 
   elseif transform.position.y > 330 then
      input.y = -1 
   elseif transform.position.x < -700 then
      input.x =  1 
   elseif transform.position.x > 390 then
      input.x = -1 
   end

   player:setTransform(transform)
end
