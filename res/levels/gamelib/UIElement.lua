local ffi = require('ffi')
local C = ffi.C

local function UIElement()
  local self = {}
  self.setPos = function(self, x, y)
    self = ffi.cast('UIElement*', self.C)
    C.UIElement_setPos(self, x, y)
  end
  self.setSize = function(self, w, h)
    self = ffi.cast('UIElement*', self.C)
    C.UIElement_setSize(self, w, h)
  end
  return self
end

return UIElement
