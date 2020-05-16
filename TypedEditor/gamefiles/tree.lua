require "main"
TE = require "TEcore";

local tree = {
   transform = TE.TETransform(),
   sprite = TE.TESprite()
}

tree.__index = tree

function new()
   local self = {}
   return setmetatable(self, tree)
end

function tree.begin(self)
   self.sprite:init(self.transform, "res/textures/T_Tree.png")
end

function tree.tick(self, deltaTime, time)
   print_that_it_works() -- Function from the main.lua file

   self.transform.position.x = self.transform.position.x + (200 * deltaTime)
   self.transform.rotation = self.transform.rotation + deltaTime
   self.sprite:setTransform(self.transform)
end
