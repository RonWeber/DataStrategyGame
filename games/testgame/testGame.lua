function selfPunchAvailable (unitID)
  return true
end

function selfPunchAction (unitID)
  setValue(unitID, "hp", 0)
end

function teleportAvailable (unitID)
  return true
end

function teleportAction (unitID, x, y)
  setPos(unitID, x, y)
end

function teleportAllowedLocations (unitID)
  x, y = getPos(unitID)
  return tilesWithinRange(x, y, 4)
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