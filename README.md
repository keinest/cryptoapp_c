# **CryptoApp** : Système de Chiffrement et de Gestion d'Utilisateurs

## Description du Projet

CryptoApp est une application console interactive développée en C qui offre une suite d'outils de chiffrement et de déchiffrement pour plusieurs algorithmes cryptographiques classiques. Le projet intègre également un système robuste de gestion d'utilisateurs, incluant l'authentification, la création de comptes avec vérification de la force du mot de passe, et la réinitialisation de mots de passe via envoi de mail simulé.

L'interface utilisateur est construite avec la bibliothèque `ncurses` pour une expérience interactive en mode texte. Le projet vise à démontrer l'implémentation et le fonctionnement de divers algorithmes cryptographiques, tout en intégrant des fonctionnalités de gestion de la sécurité des utilisateurs.

### **Fonctionnalités**

#### Authentification et Gestion des Utilisateurs

* **Création de Compte :** Permet aux nouveaux utilisateurs de s'inscrire avec une adresse e-mail et un mot de passe.
* **Vérification de la Force du Mot de Passe :** Implémente des règles pour garantir des mots de passe robustes (longueur minimale, caractères spéciaux, majuscules, chiffres).
* **Hachage de Mot de Passe :** Utilise `OpenSSL/sha.h` pour le hachage sécurisé des mots de passe avant stockage.
* **Connexion :** Authentifie les utilisateurs existants.
* **Réinitialisation de Mot de Passe :** Fonctionnalité de récupération de compte via envoi de code par e-mail simulé.
* **Mode Invité :** Permet d'explorer les fonctionnalités de chiffrement sans créer de compte.

### Algorithmes Cryptographiques Implémentés

Le système propose les chiffrements et déchiffrements pour les algorithmes suivants :

* **RSA :** Chiffrement asymétrique basé sur la factorisation de grands nombres premiers.
* **César :** Chiffrement par substitution simple.
* **Affine :** Une extension du chiffrement de César.
* **Vigenère :** Chiffrement polyalphabétique.
* **Vernam (One-Time Pad) :** Chiffrement symétrique, considéré comme indéchiffrable avec une clé aléatoire de la même taille que le message.
* **Transposition Rectangulaire :** Chiffrement par transposition des caractères.
* **Feistel (Générique) :** Implémentation d'une structure de Feistel, permettant de comprendre le fonctionnement de blocs de chiffrement comme DES/AES.
* **Hill :** Chiffrement polygraphique basé sur l'algèbre linéaire (nécessite une implémentation matricielle).
* **PGCD :** Implémentation de l'algorithme d'Euclide pour le calcul du Plus Grand Commun Diviseur, utile pour RSA et Affine.
* **Algorithme d'Euclide Étendu :** Utilisé pour calculer l'inverse modulaire, essentiel pour le déchiffrement RSA.

### Technologies Utilisées

* **Langage :** C
* **Interface Utilisateur :** `ncurses` (pour l'affichage en terminal et la gestion des entrées)
* **Cryptographie :**
    * Implémentations manuelles des algorithmes classiques (César, Vigenère, Affine, Vernam, Transposition, Feistel, Hill).
    * Utilisation de la bibliothèque `OpenSSL` pour le hachage SHA des mots de passe.
* **Gestion des Données :** Stockage des informations utilisateurs dans un fichier local (`Users.txt`).

## Structure des Fichiers

.
├── headers/
│   ├── crypto.h           # Déclarations pour les fonctions cryptographiques principales et utilitaires
│   ├── decrypt.h          # Déclarations pour les fonctions de déchiffrement
│   └── Users.h            # Déclarations pour les fonctions de gestion des utilisateurs
├── Help/
│   ├── CesarHelpEn.txt    # Fichier d'aide pour César (Anglais)
│   ├── FeistelHelpEn.txt  # Fichier d'aide pour Feistel (Anglais)
│   ├── HillHelpEn.txt     # Fichier d'aide pour Hill (Anglais)
│   ├── RSAHelpEn.txt      # Fichier d'aide pour RSA (Anglais)
│   ├── TransHelpEn.txt    # Fichier d'aide pour Transposition (Anglais)
│   ├── VernamHelpEn.txt   # Fichier d'aide pour Vernam (Anglais)
│   └── VigenereHelpEn.txt # Fichier d'aide pour Vigenere (Anglais)
├── crypto.c               # Implémentations des chiffrements César, RSA, Affine, et fonctions utilitaires
├── crypto1.c              # Implémentations des chiffrements Vigenère et Transposition Rectangulaire
├── crypto2.c              # Implémentations de la structure de Feistel et de ses fonctions auxiliaires
├── decrypt.c              # Fonctions de déchiffrement, Euclide Étendu, et animations
├── helps.c                # Fonctions pour l'affichage des pages d'aide
├── main.c                 # Point d'entrée principal de l'application, gestion du menu et de la navigation
└── Users.c                # Fonctions de gestion des utilisateurs (création, authentification, hachage, etc.)


## Compilation et Exécution

Pour compiler et exécuter ce projet, vous aurez besoin d'un compilateur C (comme GCC) et de la bibliothèque `ncurses`, ainsi que des en-têtes d'OpenSSL.

### Prérequis

* **GCC (ou Clang)**
* **Ncurses :** Sur Debian/Ubuntu, installez avec `sudo apt-get install libncurses5-dev libncursesw5-dev`. Sur Fedora, `sudo dnf install ncurses-devel`. Sur macOS, elle est généralement préinstallée ou peut être obtenue via Homebrew (`brew install ncurses`).
* **OpenSSL :** Sur Debian/Ubuntu, installez avec `sudo apt-get install libssl-dev`. Sur Fedora, `sudo dnf install openssl-devel`.

### Étapes de Compilation

1.  **Naviguez** jusqu'au répertoire racine du projet dans votre terminal.
2.  **Compilez** le projet en utilisant GCC et en liant les bibliothèques nécessaires :

    ```bash
    gcc -o cryptoapp main.c Users.c helps.c decrypt.c crypto.c crypto1.c crypto2.c -Iheaders -lncurses -lssl -lcrypto -lm
    ```

    * `-o cryptoapp`: Spécifie le nom de l'exécutable.
    * `main.c Users.c helps.c decrypt.c crypto.c crypto1.c crypto2.c`: Inclut tous les fichiers source C.
    * `-Iheaders`: Indique au compilateur de chercher les fichiers d'en-tête dans le répertoire `headers/`.
    * `-lncurses`: Lie la bibliothèque ncurses.
    * `-lssl -lcrypto`: Lient les bibliothèques OpenSSL (SSL et Crypto).
    * `-lm`: Lie la bibliothèque mathématique pour les fonctions comme `pow`.

### Exécution

Après une compilation réussie, exécutez l'application :

```bash
./cryptoapp
```

**Utilisation**

L'application est entièrement interactive via le terminal. Suivez les invites à l'écran pour naviguer dans les menus, créer un compte, vous connecter, et choisir les algorithmes de chiffrement ou de déchiffrement à utiliser.

Le mode "**Guest**" vous permet d'accéder directement aux fonctionnalités de chiffrement sans passer par l'authentification.

**Avertissement**

Ce projet est conçu à des fins éducatives et de démonstration des principes cryptographiques. Bien que certains algorithmes soient implémentés, il n'est pas destiné à une utilisation en production pour des données sensibles. Les implémentations de chiffrement réelles pour la production nécessitent des audits de sécurité rigoureux et des pratiques avancées non couvertes par ce projet.
Auteurs

    [Soul King] - Développeur principal

Licence

Ce projet est sous licence GPL. 
Pour plus d'informations, consultez le fichier LICENSE (si vous en ajoutez un).
