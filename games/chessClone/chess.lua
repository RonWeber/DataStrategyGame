function actionAvailable (unitID)
  return true
end

function move (unitID, x, y)
  setPos(unitID, x, y)
end

function bishop (unitID)
  xi, yi = getPos(unitID)
  xInc = {1, 1, -1, -1}
  yInc = {1, -1, 1, -1}
  return extendOut(xi, yi, xInc, yInc, getOwner(unitID))
end

function queen (unitID)
  xi, yi = getPos(unitID)
  xInc = {1, 1, -1, -1, 1, -1, 0, 0}
  yInc = {1, -1, 1, -1, 0, 0, 1, -1}
  return extendOut(xi, yi, xInc, yInc, getOwner(unitID))
end

function rook (unitID)
  xi, yi = getPos(unitID)
  xInc = {1, -1, 0, 0}
  yInc = {0, 0, 1, -1}
  return extendOut(xi, yi, xInc, yInc, getOwner(unitID))
end

function king (unitID)
  xi, yi = getPos(unitID)
  xInc = {1, 1, -1, -1, 1, -1, 0, 0}
  yInc = {1, -1, 1, -1, 0, 0, 1, -1}
  pos = {}
  side = getOwner(unitID)
  for i = 1, #xInc do
    x, y = xi+xInc[i], yi+yInc[i]
    if withinBounds(x, y) then
      u = unitAt(x, y)
      if (u == NO_UNIT or getOwner(u) ~= side) then
        pos[#pos+1] = x
        pos[#pos+1] = y
      end
    end
  end
  return pos
end

function knight (unitID)
  xi, yi = getPos(unitID)
  xInc = {1, 1, -1, -1, 2, 2, -2, -2}
  yInc = {2, -2, 2, -2, 1, -1, 1, -1}
  pos = {}
  side = getOwner(unitID)
  for i = 1, #xInc do
    x, y = xi+xInc[i], yi+yInc[i]
    if withinBounds(x, y) then
      u = unitAt(x, y)
      if (u == NO_UNIT or getOwner(u) ~= side) then
        pos[#pos+1] = x
        pos[#pos+1] = y
      end
    end
  end
  return pos
end

function extendOut(xi, yi, xInc, yInc, side)
  pos = {}
  for i = 1, #xInc do
    x, y = xi, yi
    while true do
      x, y = x+xInc[i], y+yInc[i]
      if not withinBounds(x, y) then break end
      u = unitAt(x, y)
      if u == NO_UNIT then
        pos[#pos+1] = x
        pos[#pos+1] = y
      else
        if getOwner(u) ~= side then
          pos[#pos+1] = x
          pos[#pos+1] = y
        end
        break
      end
    end
  end
  return pos
end

function markMove (unitID, x, y)
  setPos(unitID, x, y)
  setValue(unitID, "moved", 1)
end
function markInit (unitID)
  setValue(unitID, "moved", 0)
end

function pawnDown (unitID)
  x, y = getPos(unitID)
  pos = {}
  if unitAt(x, y+1) == NO_UNIT then
    pos[#pos+1] = x
    pos[#pos+1] = y+1
    if getValue(unitID, "moved") == 0 and unitAt(x, y+2) == NO_UNIT then
      pos[#pos+1] = x
      pos[#pos+1] = y+2
    end
  end
  mySide = getOwner(unitID)
  u = unitAt(x+1, y+1)
  if u ~= NO_UNIT and getOwner(u)~=mySide then
    pos[#pos+1] = x+1
    pos[#pos+1] = y+1
  end
  u = unitAt(x-1, y+1)
  if u ~= NO_UNIT and getOwner(u)~=mySide then
    pos[#pos+1] = x-1
    pos[#pos+1] = y+1
  end
  
  return pos
end
function pawnUp (unitID)
  x, y = getPos(unitID)
  pos = {}
  if unitAt(x, y-1) == NO_UNIT then
    pos[#pos+1] = x
    pos[#pos+1] = y-1
    if getValue(unitID, "moved") == 0 and unitAt(x, y+2) == NO_UNIT then
      pos[#pos+1] = x
      pos[#pos+1] = y-2
    end
  end
  mySide = getOwner(unitID)
  u = unitAt(x+1, y-1)
  if u ~= NO_UNIT and getOwner(u)~=mySide then
    pos[#pos+1] = x+1
    pos[#pos+1] = y-1
  end
  u = unitAt(x-1, y-1)
  if u ~= NO_UNIT and getOwner(u)~=mySide then
    pos[#pos+1] = x-1
    pos[#pos+1] = y-1
  end
  
  return pos
end

function kingDead (unitID)
  list = getAllUnits()
  mySide = getOwner(unitID)
  for u in list do
    if getOwner(u) == mySide then
      setValue(u, "hp", 0)
    end
  end
end