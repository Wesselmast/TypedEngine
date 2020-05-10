TE = require "TEcore";

object = {
   transform = TE.TETransform(),
   tree = TE.TESprite(),
   quads = {},
   address = 0
}

object.__index = object

function new()
   local self = {
      
   }
   return setmetatable(self, object)
end

function object.begin(self, address)
   self.address = address
   self.transform.position.x = 150
   self.transform.rotation = 0
   self.tree:init(self.transform, "res/textures/T_Tree.png")
   
   textos = TE.TEText()
   local textT = TE.TETransform()
   textT.scale.x = 2.0
   textT.scale.y = 2.0

   textos:init(textT, "Are you ready for a disco party?!")
   textos:setColor(TE.color(1.0, 0.0, 1.0, 1.0))
end

function object.tick(self, deltaTime, time)
   if time % 2 < deltaTime then
      local s = TE.TEQuad()
      local t = TE.TETransform()
      s:init()
      table.insert(self.quads, {s, t})
   end

   for q in pairs(self.quads) do
      local t = self.quads[q][2]
      local s = self.quads[q][1]
      t.position.x = t.position.x + (q * deltaTime * 300)
      s:setTransform(t)
      local c = TE.color(math.sin(time * q), math.cos(time * q), math.tan(time * q), 1.0)
      s:setColor(c)
   end
   
   self.transform.position.x = self.transform.position.x + (200 * deltaTime * self.address)
   self.tree:setTransform(self.transform)
end
