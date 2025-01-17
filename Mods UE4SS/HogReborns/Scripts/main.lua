-- Utilitaires de logging
local function log(message)
    if LogMessage then
        LogMessage("[HogReborns] " .. tostring(message))
    else
        print("[HogReborns] " .. tostring(message))
    end
end

-- Exploration des classes réseau
local function exploreNetworkClass(object, className)
    if not object then
        log(className .. " non trouvé")
        return
    end
    
    log(className .. " trouvé !")
    
    -- Obtenir le type de l'objet
    log("Type de " .. className .. ": " .. tostring(object:GetClass()))
    
    -- Vérifier quelques propriétés spécifiques au réseau
    if object.NetConnection then
        log("  A une NetConnection")
    end
    
    if object.ConnectionState then
        log("  État de la connexion: " .. tostring(object.ConnectionState))
    end
    
    if object.ConnectionTimeout then
        log("  Timeout de connexion: " .. tostring(object.ConnectionTimeout))
    end
    
    -- Essayer d'accéder à des fonctions courantes d'UE4
    if object.GetWorld then
        log("  Peut accéder au World")
    end
    
    if object.GetNetMode then
        log("  Mode réseau: " .. tostring(object:GetNetMode()))
    end
end

local function exploreNetworkClasses()
    log("Recherche des classes réseau...")
    
    -- Classes principales
    local netDriver = FindFirstOf("NetDriver")
    exploreNetworkClass(netDriver, "NetDriver")

    local worldContext = FindFirstOf("WorldContext")
    exploreNetworkClass(worldContext, "WorldContext")
    
    local gameInstance = FindFirstOf("GameInstance")
    exploreNetworkClass(gameInstance, "GameInstance")
    
    local world = FindFirstOf("World")
    exploreNetworkClass(world, "World")
    
    -- Classes spécifiques au multijoueur
    local gameMode = FindFirstOf("GameMode")
    exploreNetworkClass(gameMode, "GameMode")
    
    local gameState = FindFirstOf("GameState")
    exploreNetworkClass(gameState, "GameState")
end

-- Initialisation du mod
function OnModLoad()
    log("Mod HogReborns démarré - Test réseau natif")
    exploreNetworkClasses()
end

-- Point d'entrée
if ExecuteInGameThread then
    ExecuteInGameThread(OnModLoad)
else
    OnModLoad()
end