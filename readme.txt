+ 29/08/2022 +

1-Refonte du parsing a faire pour inclure pipex
  |
   ----> Pour include l'exec entre chaque block si il y a des pipes

2-Gestion d'err fd open == -1

3-Creation de fichier si < ?

4-Gestion des arguments de echo dans les pipes? pas de literature...

5- changer mechanique de redir > >> < avec dup ou dup2


Pour Hugo :
echo a | > b donne syntax error dans minishell mais pas dans bash posix. 