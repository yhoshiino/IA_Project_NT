# Projet IA
---

## 1. Le Projet

Dans ce projet afin de s'entrainer et pratiquer l'utilisation de **l'IA** dans le jeux vidéo, nous avons eu le choix entre plusieurs méthode : 
- **A*** : A* est une méthode de pathfinding qui sers a trouver des chemins tout en évitant les obstacles par calcul est totalement automatique.
- **FSM** (Finite State Machine) :  FSM permet de structurer les comportements des PNJ en différents états.
- **Behavior Trees** : Behavior Trees est une structure de données hiérarchique utilisée pour modéliser le comportement d'une intelligence artificielle (IA) dans un jeu vidéo.
- **GOAP** (Goal-Oriented Action Planning) : GOAP est une méthode de planification utilisée en intelligence artificielle pour permettre à un agent (par exemple, un personnage non-joueur, PNJ) de prendre des décisions de manière autonome en fonction de ses objectifs.

Nous avons a utiliser seulement trois méthode parmis ceux la, donc nous avons choisi d'utiliser :
- **A***
- **FSM**
- **GOAP**
---

## 2. Les Ennemies

Nos deux ennemies ont les mêmes actions, c'est-à-dire Suivre, Patrouiller, Fuir.

Notre première ennemie utilise **A*** et **FSM** en même temps pour pouvoir faire ces actions.
- **1er Option** : un statut "Patrolling" qui fait une patrouille qui utilise A* pour créé ces mouvements.
- **2ème Option** : un statut "Chasing" qui fait en sorte de suivre le joueur en utlisant A*.
- **3ème Option** : un statut "Fleeing" quand il a peu de points de vie il commmence a fuir le joueur.

Notre deuxième ennemie utilise **A*** et **GOAP** en même temps pour pouvoir faire ces actions.
- **1er Option** : un Objectif "Patrolling" qui fait une patrouille qui utilise A* pour créé ces mouvements.
- **2ème Option** : un Objectif "Chasing" qui fait en sorte de suivre le joueur en utlisant A*.
- **3ème Option** : un Objectif "Fleeing" quand il a peu de points de vie il commmence a fuir le joueur.

---
## 3. Attribution des tâches
---

**Nicolas** : 
- **A***
- **FSM**

**Thomas** :
- **GOAP**

