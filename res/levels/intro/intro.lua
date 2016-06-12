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

function Character()
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

function tick()
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
      console:msg('Narator: Te apuci sa freci moneda de usa inchisorii...iti place...')
      console:msg('Gabor: Termina dracului cu prostia aia sau iti var bastonu-n gat !')
      gabor:setGoingTo(6, 12)
    end
    self:interact(who, how, what)
  end
end

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
