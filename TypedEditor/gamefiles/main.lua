require "TEcore"

TE = TEcore;

transform = TE.TETransform()
sprite = TE.TESprite()
quad = TE.TEQuad()
text = TE.TEText()

function begin()
   transform.position.x = 150
   transform.rotation = 0
   blubby = sprite:init(transform, "res/textures/T_Tree.png")
end

function tick(deltaTime, time)
   if time % 2 < deltaTime then
      local soxoo = sprite
      soxoo:init(transform)

   end

   print(blubby)
   
   transform.position.x = transform.position.x + (600 * deltaTime)
   sprite:setTransform(transform)
end
