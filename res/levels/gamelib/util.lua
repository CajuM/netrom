local util = {}


function util.Queue()
  local self = {}
  self.q = {}
  self.last = 0
  self.push = function(self, val)
    self.last = self.last + 1
    self.q[self.last] = val
  end
  self.pop = function(self, val)
    if not (self.last == 0) then
      local val = self.q[self.last]
      self.q[self.last] = nil
      self.last = self.last - 1
      return val
    end
    return nil
  end
  return self
end

function util.strToC(str)
  local len = str:len()
  cStr = ffi.new('char[?]', len)
  ffi.copy(cStr, str)
  return cStr
end

function util.dump(o)
  if type(o) == 'table' then
    local s = '{ '
    for k,v in pairs(o) do
      if type(k) ~= 'number' then k = '"'..k..'"' end
      s = s .. '['..k..'] = ' .. util.dump(v) .. ','
    end
    return s .. '} '
  else
    return tostring(o)
  end
end


return util
