# 42-Minishell

Un shell Unix minimaliste développé en C, répliquant les fonctionnalités de base de bash.

## 📋 Description

Minishell est un projet de l'école 42 qui consiste à créer un interpréteur de commandes simple, capable d'exécuter des programmes, gérer les pipes, les redirections et les signaux.

## ✨ Fonctionnalités

### Commandes Built-in
- `echo` avec option `-n`
- `cd` avec chemins relatifs/absolus
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### Opérateurs
- **Pipes** : `|` - connecte la sortie d'une commande à l'entrée de la suivante
- **Redirections** :
  - `<` : redirection d'entrée
  - `>` : redirection de sortie (écrasement)
  - `>>` : redirection de sortie (ajout)
  - `<<` : heredoc

### Gestion des Quotes
- **Simple quotes** `'...'` : préserve le contenu littéral
- **Double quotes** `"..."` : permet l'expansion de variables

### Variables d'environnement
- Expansion des variables avec `$VAR`
- Variable spéciale `$?` : code de retour de la dernière commande

### Signaux
- `Ctrl-C` : interrompt la commande en cours
- `Ctrl-D` : quitte le shell
- `Ctrl-\` : ne fait rien (comme bash)

## 🚀 Installation

```bash
git clone https://github.com/bhyant/42-Minishell.git
cd 42-Minishell
make
```

## 📦 Utilisation

```bash
./minishell
```

### Exemples

```bash
minishell$ echo "Hello World"
Hello World

minishell$ ls -la | grep minishell | wc -l
1

minishell$ cat < input.txt | grep pattern > output.txt

minishell$ export PATH=/usr/bin:/bin
minishell$ echo $PATH
/usr/bin:/bin

minishell$ cat << EOF
> ligne 1
> ligne 2
> EOF
ligne 1
ligne 2
```

## 🏗️ Architecture

```
├── includes/
│   └── minishell.h          # Structures et prototypes
├── libft/                   # Bibliothèque personnelle
├── srcs/
│   ├── minishell.c          # Point d'entrée
│   ├── built_in/            # Commandes built-in
│   │   ├── cd.c
│   │   ├── echo.c
│   │   ├── env.c
│   │   ├── exit.c
│   │   ├── export.c
│   │   ├── pwd.c
│   │   └── unset.c
│   ├── exec/                # Exécution des commandes
│   │   └── env_utils.c
│   ├── lexer/               # Tokenisation
│   │   ├── tokenisation.c
│   │   ├── tokenisation_utils.c
│   │   └── token_utils.c
│   ├── parsing/             # Analyse syntaxique
│   │   ├── parse_entry.c
│   │   ├── parse_utils.c
│   │   └── parsing.c
│   └── signal/              # Gestion des signaux
│       └── signal.c
└── Makefile
```

## 🔧 Compilation

- `make` : compile le projet
- `make clean` : supprime les fichiers objets
- `make fclean` : supprime les fichiers objets et l'exécutable
- `make re` : recompile entièrement le projet

## 📚 Concepts clés

### 1. Validation syntaxique (`parse_entry`)
Détection précoce des erreurs :
- Quotes non fermées
- Pipes mal placés
- Redirections invalides

### 2. Tokenisation (Lexer)
Découpage de l'input en tokens :
- `WORD` : commandes, arguments, fichiers
- `PIPE` : opérateur `|`
- `REDIR` : opérateurs `<`, `>`, `<<`, `>>`

### 3. Parsing
Construction de la structure de commandes :
- Liste chaînée de commandes
- Tableau d'arguments par commande
- Liste de redirections

### 4. Exécution
- Fork/exec pour les commandes externes
- Pipes entre processus
- Gestion des descripteurs de fichiers

## 📖 Ressources

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Programming in the UNIX Environment](https://stevens.netmeister.org/631/)
- [Readline Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)

## 👥 Auteurs

- **tbhuiyan** - [@bhyant](https://github.com/bhyant)
- **asmati** - [@karten1080](https://github.com/Karten1080)

## 📄 Licence

Ce projet fait partie du cursus de l'école 42.

## 🎯 Status du projet

- [x] Validation syntaxique
- [x] Tokenisation (Lexer)
- [ ] Parser (AST/Commandes)
- [ ] Expansion de variables
- [ ] Exécution de commandes
- [ ] Gestion complète des signaux
- [ ] Commandes built-in
- [ ] Pipes et redirections
