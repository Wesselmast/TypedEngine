require "TEcore"

TE = TEcore;
   
quads = {}

function begin()
   transform = TE.TETransform()
   transform.position.x = 150
   transform.rotation = 0
   blubby = TE.TESprite()
   blubby:init(transform, "res/textures/T_Tree.png")
   
   textos = TE.TEText()
   local textT = TE.TETransform()
   textT.scale.x = 2.0
   textT.scale.y = 2.0
   textos:init(textT, "Are you ready for a disco party?!")
   textos:setColor(TE.color(1.0, 0.0, 1.0, 1.0))
end

function tick(deltaTime, time)
   if time % 2 < deltaTime then
      local s = TE.TEQuad()
      local t = TE.TETransform()
      s:init()
      table.insert(quads, {s, t})
   end

   for q in pairs(quads) do
      local t = quads[q][2]
      local s = quads[q][1]
      t.position.x = t.position.x + (q * deltaTime * 300)
      s:setTransform(t)
      local c = TE.color(math.sin(time * q), math.cos(time * q), math.tan(time * q), 1.0)
      s:setColor(c)
   end
   
   transform.position.x = transform.position.x + (600 * deltaTime)
   blubby:setTransform(transform)
end
