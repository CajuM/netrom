local UIElement = require('UIElement')
local ffi = require('ffi')
local C = ffi.C

local function Scene()
  local self = UIElement()
  self.C = C.Scene_new(currentLevel.C)
  return self
end

return Scene
