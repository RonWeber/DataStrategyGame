function tileOpen(x, y)
  return withinBounds(x, y) and unitAt(x, y) == NO_UNIT and getTerrain(x, y) ~= "#"
end

function moveAvailable (unitID)
  return getValue(unitID, "movesRemaining") > 0
end
function actionAvailable (unitID)
  return getValue(unitID, "actionsRemaining") > 0
end

function move (unitID, x, y)
  addValue(unitID, "movesRemaining", -1)
  setPos(unitID, x, y)
end
function attack (unitID, x, y)
  if unitAt(x, y) ~= NO_UNIT then
    setValue(unitID, "movesRemaining", 0)
    attackBase(unitID, x, y)
  end
end
function attackBase (unitID, x, y)
  target = unitAt(x, y)
  if target ~= NO_UNIT then
    addValue(unitID, "actionsRemaining", -1)
    damage = getValue(unitID, "damage")
    addValue(target, "hp", -damage)
  end
end

function push(list, val)
  list[#list+1] = val
end
function pop(list)
  if (#list == 0) then return nil end
  val = list[#list]
  list[#list] = nil
  return val
end

function moveLocs (unitID)
  x, y = getPos(unitID)
  pos = {}
  xstack = {x}
  ystack = {y}
  spdstack = {getValue(unitID, "speed")}
  while #xstack > 0 do
    speed, xi, yi = pop(spdstack), pop(xstack), pop(ystack)
    xInc = {1, -1, 0, 0}
    yInc = {0, 0, 1, -1}
    for i = 1, #xInc do
      x = xi+xInc[i]
      y = yi+yInc[i]
      if tileOpen(x, y) and notIn(pos, x, y) then
        pos[#pos+1] = x
        pos[#pos+1] = y
        if (speed > 1) then
          push(spdstack, speed-1)
          push(xstack, x)
          push(ystack, y)
        end
      end
    end
  end
  return pos
end

function notIn(pos, x, y)
  for i = 1, #pos/2 do
    if pos[i*2-1] == x and pos[i*2] == y then
      return false
    end
  end
  return true
end

function tilesWithinRange(xinit, yinit, range)
  pos = {}
  for x = xinit-range,xinit+range do
    for y = yinit-range, yinit+range do
      if ((x-xinit)^2 + (y-yinit)^2 <= range^2) then
        pos[#pos+1] = x
        pos[#pos+1] = y
      end
    end
  end
  return pos
end

function attackLocs(unitID)
  xi, yi = getPos(unitID)
  range = getValue(unitID, "range")
  return tilesWithinRange(xi, yi, range)
end

function spawnAvailable(unitID)
  return getValue(unitID, "actionsRemaining") > 2
end
function spawn1 (unitID, x, y)
  addValue(unitID, "actionsRemaining", -3)
  addValue(unitID, "stored", -3)
  createUnit("P", x, y)
end
function spawn1a (unitID, x, y)
  addValue(unitID, "actionsRemaining", -3)
  addValue(unitID, "stored", -3)
  createUnit("p", x, y)
end
function spawn2 (unitID, x, y)
  addValue(unitID, "actionsRemaining", -3)
  addValue(unitID, "stored", -3)
  createUnit("X", x, y)
end
function spawn2a (unitID, x, y)
  addValue(unitID, "actionsRemaining", -3)
  addValue(unitID, "stored", -3)
  createUnit("x", x, y)
end
function spawnTurn (unitID)
  addValue(unitID, "stored", 2)
  setValue(unitID, "actionsRemaining", getValue(unitID, "stored"))
end
function spawnLocs(unitID)
  xi, yi = getPos(unitID)
  range = getValue(unitID, "range")
  return spawnTilesWithinRange(xi, yi, 2)
end
function spawnTilesWithinRange(xinit, yinit, range)
  pos = {}
  for x = xinit-range,xinit+range do
    for y = yinit-range, yinit+range do
      if tileOpen(x, y) and (x-xinit)^2 + (y-yinit)^2 <= range^2 then
        pos[#pos+1] = x
        pos[#pos+1] = y
      end
    end
  end
  return pos
end