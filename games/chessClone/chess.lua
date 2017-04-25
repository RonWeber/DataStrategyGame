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