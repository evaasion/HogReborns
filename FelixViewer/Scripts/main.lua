print("Spell Dumper Mod: Démarrage...")

-- Enregistrer une propriété personnalisée pour les sorts
RegisterCustomProperty({
    ["Name"] = "Spells",
    ["Type"] = PropertyTypes.ArrayProperty,
    ["BelongsToClass"] = "/Script/Engine.SpellManager", -- Classe cible (doit être ajustée)
    ["OffsetInternal"] = 0x100, -- Offset à vérifier
    ["ArrayProperty"] = {
        ["Type"] = PropertyTypes.ObjectProperty
    }
})

-- Enregistrer une touche pour afficher les sorts
RegisterKeyBind(Key.A, {ModifierKey.CONTROL}, function()
    print("Récupération des sorts...")
    local SpellManager = FindFirstOf("SpellManager") -- Trouver le SpellManager
    if not SpellManager then
        print("Erreur : SpellManager introuvable.")
        return
    end

    local Spells = SpellManager.Spells
    if not Spells then
        print("Erreur : Aucun sort trouvé.")
        return
    end

    Spells:ForEach(function(Index, ElemWrapper)
        local Spell = ElemWrapper:get()
        if Spell then
            print(string.format("0x%X %s\n", Spell:GetAddress(), Spell:GetFullName()))
        end
    end)
    print("Sorts récupérés avec succès.")
end)

print("Spell Dumper Mod: Prêt.")
