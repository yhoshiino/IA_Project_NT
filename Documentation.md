# Projet IA
---

## 1. Le Projet

Dans ce projet, afin de s'entraîner et de pratiquer l'utilisation de **l'IA** dans le jeu vidéo, nous avons eu le choix entre plusieurs méthodes :

**A*** : A* est une méthode de pathfinding qui sert à trouver des chemins tout en évitant les obstacles par calcul et est totalement automatique.
**FSM** (Finite State Machine) : FSM permet de structurer les comportements des PNJ en différents états.
**Behavior Trees** : Les Behavior Trees sont une structure de données hiérarchique utilisée pour modéliser le comportement d'une intelligence artificielle (IA) dans un jeu vidéo.
**GOAP** (Goal-Oriented Action Planning) : GOAP est une méthode de planification utilisée en intelligence artificielle pour permettre à un agent (par exemple, un personnage non-joueur, PNJ) de prendre des décisions de manière autonome en fonction de ses objectifs.
Nous devions utiliser seulement trois méthodes parmi celles-ci, donc nous avons choisi d'utiliser :

**A***
**FSM**
**GOAP**
---

## 2. Les Ennemies

Nos deux ennemis ont les mêmes actions, c'est-à-dire Suivre, Patrouiller, Fuir.

Notre premier ennemi utilise **A*** et **FSM** en même temps pour pouvoir effectuer ces actions :

**1ère option** : un statut "Patrolling" qui effectue une patrouille en utilisant A* pour créer ses mouvements.
**2ème option** : un statut "Chasing" qui permet de suivre le joueur en utilisant A*.
**3ème option** : un statut "Fleeing" qui, lorsqu'il a peu de points de vie, le fait commencer à fuir le joueur.

Notre deuxième ennemi utilise **A*** et **GOAP** en même temps pour pouvoir effectuer ces actions :

**1ère option** : un objectif "Patrolling" qui effectue une patrouille en utilisant A* pour créer ses mouvements.
**2ème option** : un objectif "Chasing" qui permet de suivre le joueur en utilisant A*.
**3ème option** : un objectif "Fleeing" qui, lorsqu'il a peu de points de vie, le fait commencer à fuir le joueur.

---
## 3. Attribution des tâches
---

**Nicolas** : 
- **A***
- **FSM**

**Thomas** :
- **GOAP**

