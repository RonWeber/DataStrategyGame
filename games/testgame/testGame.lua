function selfPunchAvailable (unitID)
  return true
end

function selfPunchAction (unitID)
  setValue(unitID, "hp", 0)
end

function teleportAction (unitID, x, y)
  setPos(unitID, x, y)
end