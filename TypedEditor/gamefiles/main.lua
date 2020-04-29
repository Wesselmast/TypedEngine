require "TEcore"

te = TEcore;

transform = te.TETransform()
t = te.TESprite()

function begin()
   transform.position.x = 150
   transform.rotation = 0
   t:init(transform, "res/textures/T_Tree.png")
end

function tick(deltaTime, time)
   transform.position.x = transform.position.x + (600 * deltaTime)
   t:setTransform(transform)
end
