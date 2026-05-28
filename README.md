<div align="center">

<!-- Remplace ce placeholder par ton GIF/photo principal du spider-bot -->
<img src="https://media1.tenor.com/m/G-jz-3WNwFIAAAAd/spider-man-spider-bot-spider-bot.gif" width="450">

<br/>

# 🕷️ Spider-Bot — Robot araignée 8 pattes sur ESP32-S2

**TIC-RBT1 · Projet 3 · ETNA**

![ESP32](https://img.shields.io/badge/ESP32-S2_Mini-E7352C?style=flat-square&logo=espressif&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)
![Toolchain](https://img.shields.io/badge/Toolchain-ESP--IDF-informational?style=flat-square)
![Status](https://img.shields.io/badge/Status-Fonctionnel-brightgreen?style=flat-square)
![Rendu](https://img.shields.io/badge/Rendu-Mai%202026-orange?style=flat-square)

</div>

---

## 👥 Équipe

<table>
  <tr>
    <td valign="middle">
      <strong>Module :</strong> TIC-RBT1 &nbsp;·&nbsp; <strong>Rendu :</strong> Mai 2026<br/>
      <strong>Co-Labs ETNA</strong> · Groupe de 4<br/><br/>
      <code>corde_t</code><br/>
      <code>judea_d</code><br/>
      <code>kingki_n</code><br/>
      <code>brouar_l</code>
    </td>
    <td valign="middle" align="center">
      <!-- Remplace par ton GIF -->
      <img src="https://i.pinimg.com/originals/f3/8d/8d/f38d8ddde751b734217a16e45ec81ca9.gif" width="300">
    </td>
  </tr>
</table>

---

## 🎯 Présentation

Ce projet consiste en la construction et la programmation d'un **robot araignée à 8 pattes** (quadrupède à deux articulations par patte) à base d'**ESP32-S2 Mini**. Le firmware est développé en **C** avec la toolchain **ESP-IDF** (Espressif IoT Development Framework).

Chaque patte est composée de **2 servomoteurs MG90S** (articulation hanche + articulation jambe), soit **8 servos** au total, pilotés en PWM depuis les GPIO du microcontrôleur via un protoboard câblé à la main.

```
          Patte R1 ──┐      ┌── Patte L1
          Patte R2 ──┤      ├── Patte L2
                     │ ESP  │
          Patte R3 ──┤  32  ├── Patte L3
          Patte R4 ──┘      └── Patte L4
```

Un **afficheur OLED SSD1306** (128×64, I2C) monté sur le dessus du robot affiche l'état du système en temps réel.

---

## 🧩 Composants

| Composant                        | Quantité     | Rôle                                             |
| -------------------------------- | ------------ | ------------------------------------------------ |
| Lolin / WeMos ESP32-S2 Mini      | 1            | Microcontrôleur — USB-C natif, gestion PWM & I2C |
| Servomoteurs MG90S (métal)       | 8 (+2 spare) | Actionneurs hanches & jambes                     |
| Afficheur OLED SSD1306 0.96" I2C | 1            | Affichage état système (128×64)                  |
| Small protoboard (~5×7 cm)       | 1            | Matrice de headers & rails d'alimentation        |
| Headers mâles 3 broches          | 8            | Connecteurs servo sur protoboard                 |
| Buck converter (5–12V → 5V/3A)   | 1            | Alimentation stable pour ESP32 + servos          |
| Interrupteur à bascule KCD1      | 1            | Coupure alimentation principale                  |
| Câble silicone 22 AWG            | —            | Bus alimentation & masse                         |
| Câble silicone 30 AWG            | —            | Lignes de signal servo & I2C                     |
| Gaines thermorétractables        | —            | Isolation des jonctions                          |
| Serre-câbles                     | —            | Rangement du câblage interne                     |
| Pièces imprimées 3D              | —            | Châssis, hanches, jambes, couvercle              |
| Vis M2 auto-taraudeuses          | —            | Fixation de l'ensemble                           |
| Câble USB-C (5V/3A)              | 1            | Flashing & alimentation secteur                  |

---

## 🛠️ Toolchain & environnement

Le firmware est développé avec **ESP-IDF** (Espressif IoT Development Framework), la toolchain officielle Espressif pour les ESP32.

### Installation ESP-IDF

```bash
# 1. Cloner ESP-IDF
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf

# 2. Installer les outils pour ESP32-S2
./install.sh esp32s2

# 3. Sourcer l'environnement (à faire à chaque session)
. ./export.sh
```

> La version recommandée est **ESP-IDF v5.x** (LTS). Vérifier la compatibilité avec l'ESP32-S2 Mini avant d'utiliser une version plus récente.

---

## 📐 Configuration des pins

| Moteur / Composant | Index tableau | GPIO    | Position                          |
| ------------------ | ------------- | ------- | --------------------------------- |
| Motor 0            | 0             | GPIO 1  | R1 — hanche droite avant          |
| Motor 1            | 1             | GPIO 2  | R2 — hanche droite avant-centre   |
| Motor 2            | 2             | GPIO 4  | L1 — hanche gauche avant          |
| Motor 3            | 3             | GPIO 6  | L2 — hanche gauche avant-centre   |
| Motor 4            | 4             | GPIO 8  | R4 — hanche droite arrière        |
| Motor 5            | 5             | GPIO 10 | R3 — hanche droite arrière-centre |
| Motor 6            | 6             | GPIO 13 | L3 — hanche gauche arrière-centre |
| Motor 7            | 7             | GPIO 14 | L4 — hanche gauche arrière        |
| I2C SDA            | —             | GPIO 33 | SSD1306 data                      |
| I2C SCL            | —             | GPIO 35 | SSD1306 clock                     |

---

## 🔌 Schéma de câblage

> Le schéma complet est disponible dans le dossier `Spider-Bot/` du dépôt.

### Vue d'ensemble

```
Alimentation (batterie ou USB-C)
    │
    ├──► Interrupteur KCD1
    │        └──► Buck converter (→ 5V/3A régulés)
    │                  ├──► Rail 5V protoboard  ──► VCC servos (×8)
    │                  └──► ESP32-S2 Mini (5V)
    │
    └──► ESP32-S2 Mini
              ├── GPIO 1,2,4,6,8,10,13,14  ──► Signal servos (×8)
              ├── GPIO 33 (SDA) ──────────► SSD1306 SDA
              └── GPIO 35 (SCL) ──────────► SSD1306 SCL
```

### Règles de câblage respectées

- **22 AWG** — bus alimentation (5V) et masse
- **30 AWG** — lignes de signal servo et I2C
- Câbles les plus courts possible pour limiter l'encombrement
- Buck converter réglé à **5,0V exactement** au multimètre **avant** connexion de l'ESP32

> ⚠️ Ne jamais mettre sous tension sans avoir vérifié la tension de sortie du buck converter au préalable. Un déréglage au-delà de 5,5V détruit l'ESP32-S2 Mini et les servos.

---

## 🏗️ Architecture du firmware

```
SPIDERBOT/
├── .vscode/                  - Fichiers de configuration de l'éditeur VS Code
├── SpiderBot/                - Répertoire principal du projet ESP-IDF
│   ├── main/                 - Code source de l'application
│   │   ├── CMakeLists.txt    - Configuration de compilation pour le dossier main
│   │   ├── dance.c           - Logique et implémentation des mouvements/danses
│   │   ├── dance.h           - Définitions et en-têtes pour les mouvements
│   │   ├── face.c            - Gestion de l'affichage/visage du robot
│   │   ├── face.h            - En-têtes pour le visage
│   │   ├── idf_component.yml - Configuration des dépendances du composant ESP-IDF
│   │   ├── main.c            - Point d'entrée principal du programme
│   │   ├── servo.c           - Implémentation du contrôle des servomoteurs
│   │   └── servo.h           - En-têtes pour les servomoteurs
│   ├── .gitignore            - Règles d'exclusion pour Git
│   ├── CMakeLists.txt        - Configuration CMake globale du projet
│   └── sdkconfig             - Configuration générée par l'outil ESP-IDF
└── README.md
```

---

## 🚀 Installation & flashing

### Prérequis

- ESP-IDF v5.x installé et environnement sourcé (`. ./export.sh`)
- Câble USB-C 5V/3A
- L'ESP32-S2 Mini en **mode téléversement** (maintenir `BOOT` au démarrage)

### Build & flash

```bash
# Cloner le dépôt
git clone https://rendu-git.etna-alternance.net/module-10145/activity-55395/group-1076283
cd group-1076283/Spider-Bot

# Configurer la cible
idf.py set-target esp32s2

# Compiler
idf.py build

# Flasher (adapter le port série)
idf.py -p /dev/ttyUSB0 flash

# Monitor série (115200 baud)
idf.py -p /dev/ttyUSB0 monitor
```

> Sur Windows, remplacer `/dev/ttyUSB0` par `COM*` (vérifier dans le Gestionnaire de périphériques).  
> Quitter le monitor avec **Ctrl+]**.

---

## 🧪 Tests & réglages

| Étape                     | Description                                                   | Outil               |
| ------------------------- | ------------------------------------------------------------- | ------------------- |
| **1. Buck converter**     | Vérifier la sortie à 5,0V au multimètre avant toute connexion | Multimètre          |
| **2. Continuité câblage** | Tester chaque connexion au multimètre en mode continuité      | Multimètre          |
| **3. Boot ESP32**         | Vérifier les logs de démarrage dans le monitor série          | `idf.py monitor`    |
| **4. OLED**               | Vérifier l'affichage au boot sans les servos connectés        | Observation directe |
| **5. Un servo seul**      | Tester la position neutre puis les extrêmes sur un seul servo | Observation directe |
| **6. Tous les servos**    | Vérifier la cohérence des angles sur les 8 canaux             | Observation directe |
| **7. Séquence de marche** | Tester le gait complet, robot posé à plat                     | Terrain             |
| **8. Réglage fin**        | Ajuster les offsets de position neutre de chaque servo        | Itératif            |

---

## ⚡ Difficultés rencontrées

- **Réglage du buck converter** : une valeur trop haute (5,3V) a failli endommager un servo. Résolution par mesure systématique au multimètre avant chaque mise sous tension.
- **Encombrement du câblage** : 8 servos × 3 fils + I2C généraient une masse de câbles difficile à gérer dans le châssis. Résolution en utilisant exclusivement du 30 AWG pour les signaux et en serre-câblant les faisceaux par groupe de pattes.
- **Mise en place de la toolchain ESP-IDF** : le sourcing de l'environnement (`export.sh`) à chaque session était source d'erreurs. Résolution en ajoutant l'alias dans le `.bashrc` / `.zshrc`.
- **Offset des servos** : les positions neutres mécaniques ne correspondaient pas exactement à 1500 µs. Résolution en calibrant un offset par servo dans le firmware.

---

<div align="center">

<img src="https://media1.tenor.com/m/78GsECWnQ04AAAAC/thumbs-up-spider.gif" width="200"> &nbsp;
<img src="https://media1.tenor.com/m/TsVXIAMBZXoAAAAC/cat-thumbs-up-thumbs-up.gif" width="200"> &nbsp;
<img src="https://media1.tenor.com/m/spSgkqK707kAAAAd/ok-all.gif" width="280">

_Projet réalisé au Co-Labs ETNA · Module TIC-RBT1 · Mai 2026_

`corde_t` · `judea_d` · `kingki_n` · `brouar_l`

</div>
