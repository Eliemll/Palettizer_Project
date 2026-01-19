# FreeRTOS Palletizer - Factory IO Simulation

Ce projet implémente le système de contrôle d'un palettiseur industriel automatisé. Le micrologiciel est conçu pour un microcontrôleur **STM32F072RB** et interagit avec un jumeau numérique sur **Factory IO**.

## Points Forts & Optimisations

### Efficacité Énergétique (-70%)
L'approche événementielle permet au système de rester en sommeil la majeure partie du temps (plus de 99% du temps).
* **Stratégie :** Utilisation de l'instruction `__WFI()` (Wait For Interrupt) dans la tâche `IDLE` de FreeRTOS.
* **Résultat :** Réduction de la consommation globale de **15,3 mA à 4,6 mA**.

### Gestion des Ressources (RAM < 50%)
L'architecture logicielle est optimisée pour une faible empreinte mémoire tout en garantissant une modularité totale.
* **RAM :** 8 Ko utilisés sur 16 Ko disponibles.
* **Flash :** Occupation maîtrisée sur le STM32F072RB.

### Analyse Temps-Réel & Charge CPU
Grâce au modèle **Publisher/Subscriber**, la charge CPU applicative est quasi nulle en l'absence d'événements physiques.
* **Déterminisme :** Les tâches métier sont bloquées via des sémaphores et notifications FreeRTOS.
* **Diagnostic :** Validation des choix techniques via TraceAlyzer.

## Architecture du Logiciel
Le projet suit une séparation stricte des responsabilités :
* `app/src/myTasks.c` : Machine à états (FSM) gérant le cycle de palettisation.
* `app/src/subscription.c` : Gestionnaire d'événements assurant la robustesse et la modularité.
* `bsp/src/factory_io.c` : Couche d'abstraction matérielle (HAL) pour l'interface de communication.

## Démonstration
<video src="https://github.com/user-attachments/assets/bd209643-b508-41a8-8427-e25452aefa10" controls="controls" style="max-width: 100%;">
  Votre navigateur ne supporte pas la lecture de vidéos.
</video>

## Stack Technologique
* **Hardware :** STM32F072RB (Cortex-M0).
* **Software :** Langage C, FreeRTOS.
* **Simulation :** Factory IO, Node-RED (Bridge de communication).
* **Analyse :** TraceAlyzer, STM32 Build Analyzer.

---
**Auteur :** Elie Mollé - Étudiant Ingénieur en Systèmes Embarqués.