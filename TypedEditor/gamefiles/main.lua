require "TEcore"

te = TEcore;

function main()
   local transform = te.TETransform()
   transform.position.x = 150
   transform.rotation = 0
   t = te.TESprite()
   t:init(transform, "res/textures/T_Tree.png")
end
