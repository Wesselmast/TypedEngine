TE = require "TEcore";

local object = {
   transform = TE.TETransform(),
   tree = TE.TESprite()
}

object.__index = object

function new()
   local self = {}
   return setmetatable(self, object)
end

-- @CleanUp: 'self' should be replaced with the parent object that hosts the script

function object.begin(self)
   self.tree:init(self.transform, "res/textures/T_Tree.png")
end

function object.tick(self, deltaTime, time)
   self.transform.position.x = self.transform.position.x + (200 * deltaTime)
   self.transform.rotation = self.transform.rotation + deltaTime
   self.tree:setTransform(self.transform)
end
