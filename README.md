# FreeRTOS Palletizer - Factory IO Simulation

Ce projet implémente le système de contrôle d'un palettiseur industriel automatisé. Le micrologiciel est conçu pour un microcontrôleur **STM32F072RB** et interagit avec un jumeau numérique sur **Factory IO**.

## Démonstration
<video src="https://github.com/user-attachments/assets/bd209643-b508-41a8-8427-e25452aefa10" controls="controls" style="max-width: 100%;">
  Votre navigateur ne supporte pas la lecture de vidéos.
</video>

## Points Forts & Optimisations

### Efficacité Énergétique (-70%)
L'approche événementielle permet au système de rester en sommeil la majeure partie du temps (plus de 99% du temps).
* **Stratégie :** Utilisation de l'instruction `__WFI()` (Wait For Interrupt) dans la tâche `IDLE` de FreeRTOS.
* **Résultat :** Réduction de la consommation globale de **15,3 mA à 4,6 mA**.

### Gestion des Ressources (RAM < 50%)
L'architecture logicielle est optimisée pour une faible empreinte mémoire tout en garantissant une modularité totale.
* **RAM :** 8 Ko utilisés sur 16 Ko disponibles.
* **Flash :** Occupation maîtrisée sur le STM32F072RB.

<img width="893" height="179" alt="Screenshot from 2026-01-16 17-13-13" src="https://github.com/user-attachments/assets/d2cc35db-445f-42d8-871b-32c02e9d56ad" />


### Analyse Temps-Réel & Charge CPU
Grâce au modèle **Publisher/Subscriber**, la charge CPU applicative est quasi nulle en l'absence d'événements physiques.

#### Chronogramme des tâches (TraceAlyzer)
<img width="900" alt="Chronogramme TraceAlyzer" src="https://github.com/user-attachments/assets/dc857804-df5a-4c4d-bcd9-36f3f18f7328" />
*Le chronogramme montre le déterminisme des tâches et l'absence de préemption inutile.*

#### Graphique de charge CPU
<img width="857" alt="Charge CPU" src="https://github.com/user-attachments/assets/581850c4-39f2-49ec-82c5-5819151627d2" />

*On observe une charge processeur inférieure à 0.05% en régime stationnaire.*

## Architecture du Logiciel
Le projet suit une séparation stricte des responsabilités :
* `app/src/myTasks.c` : Machine à états (FSM) gérant le cycle de palettisation.
* `app/src/subscription.c` : Gestionnaire d'événements assurant la robustesse et la modularité.
* `bsp/src/factory_io.c` : Couche d'abstraction matérielle (HAL) pour l'interface de communication.

## Stack Technologique
* **Hardware :** STM32F072RB (Cortex-M0).
* **Software :** Langage C, FreeRTOS.
* **Simulation :** Factory IO, Node-RED (Bridge de communication).
* **Analyse :** TraceAlyzer, STM32 Build Analyzer.

---
**Auteur :** Elie Mollé - Étudiant Ingénieur en Systèmes Embarqués.
