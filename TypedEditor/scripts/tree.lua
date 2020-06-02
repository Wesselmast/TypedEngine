require "main"
TE = require "TEcore";

transform = TE.TETransform()
sprite = TE.TESprite()

function begin()
   sprite:init("res/textures/T_Tree.png")
end

function tick(deltaTime, time)
   print_that_it_works() -- Function from the main.lua file

   transform.position.x = transform.position.x + (200 * deltaTime)
   transform.rotation = transform.rotation + deltaTime
   sprite:setTransform(transform)
end
