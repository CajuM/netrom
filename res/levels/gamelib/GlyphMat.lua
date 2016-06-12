local ffi = require('ffi')
local C = ffi.C

local function GlyphMat(mat)
  local function GlyphMat_new(mat)
    local h = table.getn(mat)
    local w = mat[1]:len()
    local arr = ffi.new('char*[?]', h)
    for i=1,h do
      arr[i-1] = ffi.new('char[?]', w + 1)
      ffi.copy(arr[i-1], mat[i])
    end
    return C.GlyphMat_new(arr, h)
  end

  local self = {}
  self.C = GlyphMat_new(mat)
  return self
end

return GlyphMat
