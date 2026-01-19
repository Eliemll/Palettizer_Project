# FreeRTOS Palletizer - Factory IO Simulation

Ce projet implante le système de contrôle d'un palettiseur industriel automatisé. Le micrologiciel est conçu pour un microcontrôleur **STM32F072RB** et interagit avec un jumeau numérique sur **Factory IO**.

## Points Forts Techniques
* **OS Temps Réel :** Utilisation de FreeRTOS pour la gestion multitâche (ordonnancement des convoyeurs, moteurs, et capteurs).
* **Architecture BSP (Board Support Package) :** Séparation stricte entre la logique métier (`app/`) et les drivers matériels (`bsp/`), facilitant la portabilité.
* **Modèle Subscription :** Implémentation d'un système de gestion d'événements/abonnements (`subscription.c`) pour une communication fluide entre les tâches.
* **Jumeau Numérique :** Simulation hardware-in-the-loop avec Factory IO pour valider les comportements critiques avant déploiement.

## Architecture du Logiciel
Le projet est structuré pour répondre aux standards industriels :
* `app/src/myTasks.c` : Contient la machine à états finis (FSM) gérant le cycle de palettisation.
* `bsp/src/factory_io.c` : Driver de communication dédié à l'interface avec la simulation.
* `FreeRTOSConfig.h` : Configuration optimisée pour les ressources du STM32F0.


## Stack Technologique
* **Hardware :** STM32F072RB (Cortex-M0).
* **Software :** Langage C, FreeRTOS.
* **Outils :** STM32CubeIDE, Factory IO (Simulation).

## Démonstration