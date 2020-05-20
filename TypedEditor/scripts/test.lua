require "TEcore"

TE = TEcore
   
quads = {}

function begin()
   transform = TE.TETransform()
   blubby = TE.TESprite()
   blubby:init(transform, "res/textures/T_Brick.jpg")
   
   textos = TE.TEText()
   local textT = TE.TETransform()
   textT.scale.x = 2.0
   textT.scale.y = 2.0
   textos:init(textT, "NACHOS ON THE HOUSE TONIGHT!!!!")
   textos:setColor(TE.color(1.0, 0.0, 1.0, 1.0))
end

function tick(deltaTime, time)
   transform.position.x = transform.position.x + (600 * deltaTime)
   blubby:setTransform(transform)
end
