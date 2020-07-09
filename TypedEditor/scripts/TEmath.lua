require 'TEcore'

vec2 = {}

function vec2:new(vec)
   vec = vec or {}
   out = {
      x = vec.x or 0,
      y = vec.y or 0
   }

   self.__index = self
   return setmetatable(out, self)
end
