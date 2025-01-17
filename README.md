# HogReborns

HogReborns est un projet ambitieux visant à créer une expérience multijoueur immersive et personnalisée pour un environnement basé sur **Hogwarts Legacy**. Ce projet combine des scripts client (via **UE4SS**) et un serveur créé avec la bibliothèque réseau **ENet**.

---

## Fonctionnalités principales

- **Connexion/Déconnexion dynamique** : Activez ou désactivez le mode multijoueur directement en jeu avec une touche configurable.
- **Affichage du ping** : Visualisez votre latence en temps réel directement dans l’interface utilisateur.
- **Serveur personnalisé** : Gestion efficace des connexions et synchronisation des joueurs avec un backend écrit en C++.
- **Scripts client évolutifs** : Exploitez la puissance de Lua via UE4SS pour enrichir le gameplay.

---

## Prérequis

### **Outils et dépendances**

- **Visual Studio 2019 ou 2022** (avec le module de développement C++)
- **CMake** (pour compiler la bibliothèque ENet)
- **Bibliothèques requises** :
  - [ENet](https://github.com/lsalzman/enet)
  - `Ws2_32.lib` et `Winmm.lib` (inclus avec Windows SDK)

### **Fichiers requis**

- UE4SS : Pour injecter des scripts Lua dans le client du jeu.
- Fichiers de configuration personnalisés pour UE4SS et ENet (disponibles dans ce dépôt).

---

## Installation

1. Clonez ce dépôt :

   ```bash
   git clone https://github.com/votre-utilisateur/HogReborns.git
   ```

2. Compilez la bibliothèque **ENet** :

   ```bash
   cd enet-master
   cmake .
   cmake --build .
   ```

   Cela générera le fichier `enet.lib` dans le répertoire `Debug` ou `Release`.

3. Configurez votre environnement :

   - Placez les fichiers compilés (serveur et scripts client) dans les répertoires correspondants.
   - Assurez-vous que **UE4SS** est installé correctement avec les fichiers Lua de ce projet.

4. Lancez le serveur :

   ```bash
   ./HogRebornsServer.exe
   ```

5. Lancez le client et appuyez sur la touche configurée (`Insert` par défaut) pour activer le mode multijoueur.

---

## Utilisation

### **Contrôles en jeu**

- **Activer/Désactiver le multijoueur** : Appuyez sur `Insert`.
- **Affichage du ping** : Visible dans le coin supérieur droit de l’écran une fois connecté au serveur.

### **Personnalisation**

- Modifiez les fichiers Lua pour ajuster les comportements client.
- Changez le port du serveur ou les paramètres de connexion dans le fichier de configuration principal.

---

## Contribution

Les contributions sont les bienvenues ! Voici comment vous pouvez aider :

1. Forkez ce dépôt.
2. Créez une branche pour vos modifications :
   ```bash
   git checkout -b ma-nouvelle-fonctionnalite
   ```
3. Faites vos modifications et soumettez une Pull Request.

---

## Support

Si vous avez des questions ou des problèmes, ouvrez une **Issue** sur ce dépôt ou contactez-moi directement.

---

## Licence

Ce projet est sous licence **MIT**. Consultez le fichier [LICENSE](LICENSE) pour plus de détails.

