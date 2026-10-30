# minishell

Un petit shell inspiré de bash, écrit en C pour le cursus 42, avec [Alexandre Stachnik](https://github.com/astachni).

- Prompt et historique avec readline
- Pipes, redirections `<`, `>`, `>>` et heredoc `<<`
- Variables d'environnement et code de retour `$?`
- Builtins : `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Gestion de `Ctrl-C`, `Ctrl-D` et `Ctrl-\`

```sh
make
./minishell
```

Nécessite la bibliothèque readline.
