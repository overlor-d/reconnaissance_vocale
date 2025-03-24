# Reconnaissance Vocale – Projet Audio Bas Niveau (WinMM)

## 🧠 Description

Ce projet expérimental en langage C vise à manipuler des données audio brutes en utilisant exclusivement des bibliothèques natives de Windows (comme WinMM).

Il permet notamment :
- La **capture audio en temps réel** via le micro
- La **lecture directe** du signal audio enregistré
- Le tout sans formats intermédiaires complexes (pas de .wav, pas de libs externes)

## 🎯 Objectif

L’objectif est d’explorer les bases de la **reconnaissance vocale bas niveau**, avec un accent particulier sur :
- La compréhension de la structure d’un échantillon audio
- La manipulation directe des buffers sonores
- L’expérimentation autour de la **détection et l’analyse de phonèmes**
- En vue de poser les bases d’un système simple de **reconnaissance vocale personnalisée**

## 💡 Technologies utilisées

- C (standard)
- **WinMM** : pour la capture et la lecture audio
- Compilation avec `gcc` (MinGW)
