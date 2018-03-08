# 42sh

Une imitation de Bash POSIX en C.

Tout deplacement de curseurs ont etes realiser avec les bibliotheques termcaps.
42sh respect la norme POSIX.

#### Principales fonctionnalités:

- édition de la ligne de commande à l’aide de la bibliothèque termcaps,
- Les fonctionnalités des combinaisons de touches ctrl+D et ctrl+C dans l’édition de la ligne et l’éxecution d’un processus,
- Le séparateur de commandes “;”,
- Les pipes “|”,
- Les redirections “<”, “>”, “<<” et “>>”,
- Le heredoc "<<",
- Les opérateurs logiques "&&" et "||",
- Les aggrégations de descripteurs de fichiers,
- Deplacement du curseur,
- Quotes et doubles quotes,
- L’historique des commandes et les builtins history et "!",
- table de hash pour les binaires,
- Les variables locales et les builtin unset et export,
- Complétion dynamique.
