print("-----intro----")

netrom = require('netrom')
Netrom = netrom.Netrom
Level = netrom.Level
GameObject = netrom.GameObject
Scene = netrom.Scene
MsgBox = netrom.MsgBox

gameEngine = Netrom(gameEngine)
currentLevel = Level(currentLevel)

function Coin()
  local self = GameObject({{'¢'}}, {{' '}}, 'coin')
  self:setNormalSpeed(0)
  self.interact = function(self, who, how, what)
    if who == player then
      who:pickUp(self)
    end
  end
  return self
end

function Character(icon, mask, name)
  local self = GameObject(icon, mask, name)

  self.inventory = {}
  self.hostileTowards = nil
  self.goingTo = nil
  self.heldItem = nil
  self.movementLock = false

  self.superMove = self.move
  self.move = function(self, x, y)
    if not self.movementLock then
      self:superMove(x, y)
      self.movementLock = true
    end
  end

  self.inventoryAdd = function(self, go)
    table.insert(self.inventory, go)
  end

  self.pickUp = function(self, go)
     self:inventoryAdd(go)
     go:del()
     self.heldItem = go
  end

  self.setGoingTo = function(self, x, y)
    self.hostileTowards = nil
    self.goingTo = {}
    self.goingTo.x = x
    self.goingTo.y = y
  end

  self.setHostileTowards = function(self, go)
    self.goingTo = nil
    self.hostileTowards = go
  end
  
  self.animate = function(self)
    if self.hostileTowards then
      local sx, sy = self:getPos()
      local tx, ty = self.hostileTowards:getPos()
      local dx = tx - sx
      local dy = ty - sy
      local d = math.sqrt(dx * dx + dy * dy)
      if d <= 50 and d > 1 then
         nx, ny = currentLevel:getSP(sx, sy, tx ,ty)
         self:move(nx, ny)
      end
    end 

    if self.goingTo then
      local sx, sy = self:getPos()
      if sx == self.goingTo.x and sy == self.goingTo.y then
        self.goingTo = nil
        queueEvent({['eClass'] = 'Game', ['type'] = 'arrived', ['self'] = self})
        return 
      end
      nx, ny = currentLevel:getSP(sx, sy, self.goingTo.x ,self.goingTo.y)
      self:move(nx, ny)
    end
  end

  return self
end

function Player()
  local self = Character({{'@'}}, {{'@'}}, 'player')
  self:setNormalSpeed(1)
  return self
end

function Gabor()
  local self = Character({{'P'}}, {{'P'}}, 'gabor')
  self:setNormalSpeed(1)
  return self
end

function Wall(icon)
  local self = GameObject({icon}, {icon}, 'wall')
  return self
end

function Door(icon, key)
  local self = GameObject({icon, {' '}}, {icon, {' '}}, 'door')
  self.interact = function(self, who, how, what)
    if key == nil or what == key then
      self:setFrame(1)
    end
  end
  return self
end

function Key(name)
  local self = {}
  self.name = 'key#' .. name
  self.getName = function()
    return self.name
  end
  return self
end

tickn = 0

function tick()
	tickn = tickn + 1
  player.movementLock = false
  gabor.movementLock = false
  gabor:animate()
  while true do
    local e = nil
    e = currentLevel.evs:pop()
    if not e then
      break
    end
    processEvent(e)
  end
end

function queueEvent(e)
  currentLevel.evs:push(e)
end

function processEvent(e)
  if e.eClass == 'UI' and e.type == 'kbd' and e.val.state == 'down' then
    if e.val.keyName == 'Up' then
      player:move(0, -1)
    elseif e.val.keyName == 'Down' then
      player:move(0, 1)
    elseif e.val.keyName == 'Left' then
      player:move(-1, 0)
    elseif e.val.keyName == 'Right' then
      player:move(1, 0)
    elseif e.val.keyName == 'E' then
      local goi = currentLevel:getNearGO(player)
      if goi then
        local action = nil
        if player.heldItem then
          action = player.heldItem.action
        end
        currentLevel.evs:push({['eClass'] = 'Game', ['type'] = 'interaction', ['val'] = {
          ['self'] = goi,
          ['who'] = player,
          ['how'] = action,
          ['what'] = player.heldItem
       }})
      end
    end
  end

  if e.eClass == 'Game' and e.type == 'collision' then
    print(e)
  end

  if e.eClass == 'Game' and e.type == 'interaction' then
    local self = e.val.self
    local who = e.val.who
    local how = e.val.how
    local what = e.val.what
    if self == door and who == player and what == coin then
      if stage <= 3 then
        console:msg('Narator: Te apuci sa freci moneda de usa inchisorii...iti place...')
        console:msg('Gabor: Termina dracului cu prostia aia sau iti var bastonu-n gat !')
        stage = stage + 1
      elseif stage == 4 then
        console:msg('Gabor: Mai ce sa-ti spun, ce se-ntampla la militie ramane la militie')
        console:msg('Narator: Gaborul isi ia cheia si se indreapta cu pasi grabiti spre celula ta...pentru o clipa te bucuri ca iti va da drumul')
        gabor:setGoingTo(6, 13)
        stage = stage + 1
      end
    end
    self:interact(who, how, what)
  end

  if e.eClass == 'Game' and e.type == 'arrived' then
     if e.self == gabor and stage == 5 then
       console:msg('Narator: Gaborul deschide usa celulei...incepi sa te gandesti daca vei apuca sa-ti cureti panatalonii')  
       door:interact(gabor, nil, key)
       gabor:setHostileTowards(player)
       stage = stage + 1
     end 
  end
end

stage = 1

map = {
  '┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓',
  '┃                               ║          ┃',
  '┃                               ║          ┃',
  '┃                               ║          ┃',
  '┃                               ║          ┃',
  '┃                               ║          ┃',
  '┃                               ║          ┃',
  '┃                               ║          ┃',
  '┃                               ╚═══  ═════┃',
  '┃                                          ┃',
  '┃                                          ┃',
  '┃                                          ┃',
  '┃                                          ┃',
  '┃                                          ┃',
  '┃##### ####################################┃',
  '┃           #          #         #         ┃',
  '┃           #          #         #         ┃',
  '┃           #          #         #         ┃',
  '┃           #          #         #         ┃',
  '┃           #          #         #         ┃',
  '┃           #          #         #         ┃',
  '┃           #          #         #         ┃',
  '┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛'
}
map = Wall(map)
map:add()

key = Key('k1')

door = Door({'='}, key)
door:setPos(6, 14)
door:add()

gabor = Gabor()
gabor:setPos(33, 5)
gabor:inventoryAdd(key)
gabor:add()

player = Player()
player:setPos(5, 16)
player:add()

coin = Coin()
coin:setPos(5, 18)
coin:add()

screenSize = gameEngine:getMatrixSize()

scene = Scene()
scene:setSize(screenSize.x, screenSize.y - 7)
scene:add()

console = MsgBox()
console:setPos(0, screenSize.y - 7)
console:setSize(screenSize.x, 7)
console:add()
console:msg(
  'Narator: Esti intr-o celula la sectia de politie, habar n-ai cum ai ajuns aici... '..
  'Gaborul, ehem, domnul politist are o conversatie animata la telefon cu sotia lui\n'..
  'Gabor: Sa bagi bine la cap femeie ca nu iei nici un ban de pe urma mea !'
)
