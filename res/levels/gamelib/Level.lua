local util = require('util')
local ffi = require('ffi')
local C = ffi.C

local function Level(ptr)
  local self = {}
  self.gos = {}
  self.evs = util.Queue()
  self.C = ffi.cast('Level*', ptr)
  self.addGO = function(self, go)
    goid = go:getId()
    self.gos[goid] = go
    C.Level_addGO(self.C, go.C)
  end
  self.getGOByPos = function(self, x, y)
    cgo = C.Level_getGOByPos(self.C, x, y)
    cgoid = tonumber(C.GameObject_getId(cgo))
    return self.gos[cgoid]
  end
  self.getNearGO = function(self, go)
    cgo = C.Level_getNearGO(self.C, go.C)
    cgoid = tonumber(C.GameObject_getId(cgo))
    return self.gos[cgoid]
  end
  self.delGO = function(self, go)
    self.gos[go:getId()] = nil
    C.Level_delGO(self.C, go.C)
    go.C = nil
  end
  self.addUE = function(self, ue)
    ue = ffi.cast('UIElement*', ue.C)
    C.Level_addUE(self.C, ue)
  end
  self.getSP = function(self, fx, fy, tx, ty)
    ret = C.Level_getSP(self.C, fx, fy, tx, ty)
    return ret.x, ret.y
  end
  return self
end

return Level
