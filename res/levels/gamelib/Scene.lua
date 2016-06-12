local UIElement = require('UIElement')
local ffi = require('ffi')
local C = ffi.C

local function Scene()
  local self = UIElement()
  self.C = ffi.gc(C.Scene_new(currentLevel.C), C.Scene_gc)
  return self
end

return Scene
