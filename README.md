# Pseudorandom numbers generation with a LFSR in cpp

### C'est quoi un LFSR ? 

En quelques mots, un LFSR est un registre à décalage à rétroaction linéaire.<br>
C'est à dire que nous l'initialisons avec une séquence de n bit et à chaque "tour" on éffectue un décalage binaire avec rétroaction linéaire.<br>
Cette rétroaction est définit par une opération XOR entre différent bit de la séquence, ces bits sont définient par le polynome caractérisant le LSFR (exemple: $P(x) = x^2 + x^3 + 1$, la rétroaction sera définit par un XOR entre le 2 et 3 ieme bit).

Afin de comprendre plus en détail le fonctionnement d'un LFSR (notamment la notion de période), je vous invite à lire [ceci](https://en.wikipedia.org/wiki/Linear-feedback_shift_register).

### Où intervient le pseudo-aléatoire ?

Dans un LFSR, le pseudo-aléatoire provient de l'évolution de la séquence de n bits.
En effet, a chaque tour cette séquence évolue de manière "non prévisible", c'est à dire qu'a un tour `t` il est difficile de prévoir quel sera la séquence de bit du tour `t+3`. <br>En utilisant ces propriétées à notre avantage on peut réussir à génerer des nombres pseudo-aléatoire.

Le vrai problème est de bien choisir le vecteur d'initialisation ainsi que le polynome, car si on les choisit mal et qu'on obtient un LFSR de petite période, par exemple 3, notre LFSR bouclera toute les 3 itérations, ce qui le rends moins intéressant car nous aurons une fois sur trois le même nombre pseudo-aléatoire.

### Génération de nombre pseudo-aléatoire

Après avoir compris le principe du LFSR il faut maintenant comprendre comment génerer des nombres aléatoires.
Comme vu précedemment, la notion d'aléatoire intervient lors de l'évolution de la séquence de bits, nous allons donc choisir un LFSR avec une période pas trop courte afin de ne pas retomber sur les mêmes nombres.

Prenons `001011011` comme seed, avec $P(X) = x^8 + x^3 + x + 1$ comme polynome, nous aurons une période de 105.<br>

Imaginons que nous voulons générer 5 nombres aléatoire compris entre 5 et 15 (posons min=5, max=15).<br>

Nous allons alors faire 5 + 1 tours de LFSR et allons conserver l'état des 5 seeds (en négligeant donc l'état initiale car non "aléatoire").<br>

Nous allons ensuite convertir les seeds obtenus en nombre entier, notons ces nombres entiers $n_r$, avec $r \in [1;5]$, notons ensuite $m_r$ les nombres entier obtenues respectant l'interval $[5;15]$.<br>

Nous pouvons déterminer les $m_r$ en faisant :<br>
$$m_r = (n_r \bmod (max + 1 - min)) + min$$

Les nombres $m_r$ sont des nombres pseudos-aléatoire $\in [5;15]$.
<br>

Je tiens à préciser que ceci n'est que mon interprétation de la manière dont un LFSR peut générer des nombres aléatoire, il est possible que ce soit totalement faux (bien qu'après plusieurs tests je trouve les résultats assez intéressants).
<br>

Vous pouvez retrouver une implémentation en CPP de ce protocole dans le fichier `app.cpp`.
