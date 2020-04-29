require "TEcore"

TE = TEcore;

transform = TE.TETransform()
sprite = TE.TESprite()

function begin()
   transform.position.x = 150
   transform.rotation = 0
   sprite:init(transform, "res/textures/T_Tree.png")
end

function tick(deltaTime, time)
   transform.position.x = transform.position.x + (600 * deltaTime)
   sprite:setTransform(transform)
end
