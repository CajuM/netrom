local ffi = require('ffi')
local C = ffi.C

local function Netrom(ptr)
  local self = {}
  self.C = ffi.cast('Netrom*', ptr)
  self.getMatrixSize = function(self)
    return C.Netrom_getMatrixSize(self.C)
  end
  return self
end

return Netrom
