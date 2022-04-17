---
title: Projet \texttt{C++} - Tower Sim
author: Irwin Madet
date: 17 avril 2022
geometry: margin=.8in
output: pdf_document
---

## Choix

Durant ce projet, nous n'avons eu qu'à traiter un seul véritable choix : l'implémentation de la suppression des avions.
En effet, il nous a été conseillé de déléguer la suppression des avions à la classe elle-même.
Pour ce faire, j'ai fait le choix de retourner un booléen qui indique si la suppression doit être effectuée ou non.
Lors de la boucle de mise à jour, je vérifie si le booléen est à true, et si c'est le cas, je supprime l'avion.
Pour ce faire, on utilise le mot-clé `delete` sur le pointeur vers l'avion.
Ainsi, c'est le destructeur de la classe qui se charge de supprimer l'avion de la queue d'affichage et de déplacement.

## Problèmes

La plupart des problèmes que j'ai rencontrés lors de ce projet sont liés au langage C++.
J'ai notamment eu du mal à comprendre les tenants et aboutissants des différents concepts de référence,
référence universelle, pointeur 'vanilla', `unique_pointer`, `smart_pointer`, etc...

J'ai également eu beaucoup de mal à assimiler le système de templates, et notamment les variadic-templates.

## Appréciations et mépris

Très sincèrement, je n'ai pas aimé grand-chose... Le projet ne m'intéresse pas trop et, le langage ne m'a absolument
pas conquis. Je trouve que C++ est un langage qui autorise beaucoup trop de mauvaises pratiques, et qui a été conçus
dans le seul et unique but d'être inutilement complexe. Entre la syntaxe, que je qualifierai d'infâme et, les concepts
poussés à la limite de l'inutilité, je ne referai probablement plus aucun projet dans ce langage. Cependant, les
chapitres ont le mérite d'avoir des exemples et explication assez poussés, parfois peut-être trop loin.

Attention, la suite n'est rien d'autre qu'une diatribe.

Pour finir sur ce qui ne m'a pas plus, c'est probablement toute l'organisation du projet. Le système de travail du
"faites ceci. Ah en fait non, c'est pourri, faites plutôt cela" est très désagréable et, finalement peu pédagogue.
Cette méthode d'apprentissage est pénible, car elle entraîne beaucoup de refactoring et elle peut même décourager de
continuer à travailler.

Un dernier point qui me semble critique compte-tenu de notre niveau d'étude, c'est le retour aux bases de la 
programmation. Les questions bas niveau nous demandant par exemple, quelle structure de données utiliser, ne sont plus 
de notre niveau et sont déjà acquises depuis au moins un ou deux ans. Le projet en tant que tel pourrait être porté dans
n'importe quel autre langage. Il ne met pas assez en œuvre les concepts propres à C++ vu en cours à mon sens.
