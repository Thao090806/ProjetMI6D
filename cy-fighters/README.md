--Introduction--

Ce projet est un jeu de combat au tour par tour, où des équipes de personnages s'affrontent à l'aide de compétences variées. Le but est de proposer une expérience de jeu stratégique, avec gestion d'équipe, choix de compétences, effets temporaires et différents modes et difficultés de jeu (joueur vs univers, joueur vs joueur).

--Fonctionnement général--

* Le joueur choisit un mode de jeu (univers/joueur contre univers ou versus/joueur contre joueur).
* Chaque joueur compose son équipe à partir d'une liste de personnages chargés depuis des fichiers texte.
* Les combats se déroulent au tour par tour : chaque personnage choisit une compétence et une cible.
* Les compétences peuvent infliger des dégâts, appliquer des effets ou des bonus/malus.
* Le jeu gère les tours, les effets temporaires, la recharge des compétences et la fin de partie.

--Arborescence et description des fichiers--


cy-fighters/
├── entetes/
│   └── parametres.h           #Contient toutes les différentes structures                                (Personnage, Compétence, Effet, etc.) et les prototypes nécessaires à l’ensemble du projet.
├── modules/
│   ├── combat/
│   │   └── combat.c                # Gestion des combats, choix des compétences, déroulement des tours
│   ├── finjeu/
│   │   └── finjeu.c                # Gestion de la fin de partie, affichage des résultats, libération mémoire
│   ├── initialisation/
│   │   └── initialisation.c        # Création et initialisation des personnages et compétences
│   ├── logique/
│   │   └── logique.c               # Logique du jeu, gestion des modes, déroulement général
│   └── script/
│       └── script.c                # Affichage des introductions, histoires, scripts narratifs
├── donnees/
│   └── competences.txt 
|   └── personnages.txt             # (Fichiers de données: personnages.txt, compétences.txt)
├── jeu.c                           # Point d’entrée principal, boucle principale du jeu
├── README.md                       # Documentation du projet
├── Makefile                        # Script de compilation automatisée 


--Fonctionnalités disponibles--

* Chargement dynamique des personnages et compétences depuis des fichiers texte.
* Création et gestion d’équipes (choix manuel ou aléatoire).
* Deux modes de jeu : joueur vs robot (univers) et joueur vs joueur (versus).
* Système de compétences avec gestion de la recharge et des effets temporaires (bonus, malus, saignement, etc.).
* Affichage détaillé des personnages, équipes et actions en couleur dans la console.
* Gestion des tours : chaque équipe joue à tour de rôle de manière alternée.
* Gestion de la mémoire à la fin du jeu.

--Lancer le jeu--

1. Compiler le projet avec `make`.
2. Lancer l’exécutable généré.
3. Suivre les instructions à l’écran pour choisir le mode de jeu et composer votre équipe.