local ffi = require('ffi')
local UIElement = require('UIElement')
local C = ffi.C

local function MsgBox()
  local self = UIElement()
  self.C = ffi.gc(C.MsgBox_new(currentLevel.C), C.MsgBox_gc)
  self.msg = function(self, msg)
    msgc = ffi.new('char[?]', msg:len() + 1)
    ffi.copy(msgc, msg)
    C.MsgBox_msg(self.C, msgc)
  end
  return self
end

return MsgBox
