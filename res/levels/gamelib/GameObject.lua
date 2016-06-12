local ffi = require('ffi')
local C = ffi.C
local GlyphMat = require('GlyphMat')

local function GameObject(icon, mask, name)
  local function GameObject_new(icon, mask)
    local licon = table.getn(icon)
    local vicon = ffi.new('GlyphMat*[?]', licon)
    local vmask = ffi.new('GlyphMat*[?]', licon)
    for i=1,licon do
      vicon[i-1] = GlyphMat(icon[i]).C
      vmask[i-1] = GlyphMat(mask[i]).C
    end
    return ffi.gc(C.GameObject_new(currentLevel.C, vicon, vmask, licon), C.GameObject_gc)
  end

  local self = {}
  self.name = name
  self.C = GameObject_new(icon, mask)
  self.setPos = function(self, x, y)
    C.GameObject_setPos(self.C, x, y)
  end
  self.getPos = function(self)
    local ret = C.GameObject_getPos(self.C)
    return ret.x, ret.y
  end
  self.add = function(self)
    currentLevel:addGO(self)
  end
  self.del = function(self)
    currentLevel:delGO(self)
  end
  self.move = function(self, x, y)
    C.GameObject_move(self.C, x, y)
  end
  self.setNormalSpeed = function(self, speed)
    C.GameObject_setNormalSpeed(self.C, speed)
  end
  self.getId = function(self)
    return tonumber(C.GameObject_getId(self.C))
  end
  self.interact = function(self, who, how, what)
    print('Interaction stub')
  end
  self.isNull = function(self)
    return C.GameObject_isNull(self.C)
  end
  self.setFrame = function(self, index)
    return C.GameObject_setFrame(self.C, index)
  end
  self.getOrientation = function(self)
    local p = C.GameObject_getOrientationX(self.C)
    return p.x, p.y
  end
  return self
end

return GameObject
