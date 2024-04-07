# Arcade : A Retro Platform

## Vue d'ensemble

Arcade est un cadre de jeu polyvalent conçu pour exécuter plusieurs jeux d'arcade classiques. Axé sur l'extensibilité, il permet une intégration facile de nouveaux jeux et bibliothèques graphiques. Le projet présente des implémentations de jeux classiques tels que Snake et Pacman, ainsi qu'un support pour différentes interfaces graphiques telles que Ncurses et SDL.

## Fonctionnalités

- **Architecture Modulaire :** Les jeux et les bibliothèques graphiques sont chargés dynamiquement à l'exécution, favorisant une haute extensibilité.
- **Jeux Supportés :** Comprend des implémentations de Snake et Pacman.
- **Bibliothèques Graphiques :** Prend en charge plusieurs bibliothèques graphiques, dont Ncurses et SDL, avec des dispositions pour en ajouter d'autres.
- **Contrôles Personnalisables :** Les raccourcis clavier sont configurables, améliorant l'expérience de jeu à travers différents jeux et bibliothèques.
- **Suivi des Scores Élevés :** Conserve les scores élevés pour tous les jeux, ajoutant un aspect compétitif.

## Prérequis

- Compilateur compatible C++17 (GCC ou Clang)
- Make
- SDL2, SDL2_ttf (pour la bibliothèque graphique SDL)
- Ncurses (pour la bibliothèque graphique Ncurses)
- OS basé sur Linux (en raison du chargement dynamique avec dlopen)

## Installation

### Téléchargements Préliminaires

Assurez-vous d'avoir installé Ncurses, SFML, SDL et SDL_ttf sur votre système. Voici comment les installer sur un système basé sur Debian/Ubuntu :

```bash
sudo apt-get update
sudo apt-get install libncurses5-dev libsfml-dev libsdl2-dev libsdl2-ttf-dev
```

## Clonez le dépôt

```bash
git clone https://github.com/VotreGitHub/Arcade.git
cd Arcade
```
## Construisez le projet

```bash
make
```

## execute

Lancez l'application principale, en spécifiant la bibliothèque dynamique (.so) de l'interface graphique que vous souhaitez utiliser :

```bash
./arcade .lib/arcade_ncurses.so
```

## Comment Jouer

Après avoir lancé l'application, utilisez les flèches du clavier pour naviguer dans le menu et sélectionner un jeu à jouer. Chaque jeu a son propre ensemble de contrôles, qui sont affichés au début du jeu.

## Ajouter de Nouveaux Jeux ou Bibliothèques Graphiques

Pour étendre le cadre avec de nouveaux jeux ou interfaces graphiques :

1. **Implémentez le Jeu/Bibliothèque :** Suivez les interfaces abstraites existantes (`IGame` et `IGraphic`) pour la cohérence.
2. **Compilez votre bibliothèque dynamique :** Assurez-vous qu'elle se conforme au format de sortie attendu (.so).
3. **Placez le fichier .so :** Déplacez-le dans le répertoire approprié du projet (par exemple, `.lib/`).

## Contribuer

Les contributions sont les bienvenues ! Que ce soit pour ajouter de nouveaux jeux, améliorer les existants, ou améliorer le cadre, n'hésitez pas à forker le projet et à soumettre une pull request.

## Licence

Ce projet est sous licence MIT - voir le fichier LICENSE pour les détails.




