# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.

*La méthode `void TowerSimulation::create_keystrokes() const`*

Sur quelle touche faut-il appuyer pour ajouter un avion ?

*Sur la touche <kbd>C</kbd>.*

Comment faire pour quitter le programme ?

*Appuyer sur les touches <kbd>Q</kbd> ou <kbd>X</kbd>.*

A quoi sert la touche 'F' ?

*Elle sert à passer en plein-écran. (Crash sous Mac)*

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?

*L'avion atterri, attend quelque temps sur le tarmac et redécolle.*

Quelles informations s'affichent dans la console ?

*Le nom de l'avion et ce qu'il fait.*

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

*Trois avions peuvent être au sol simultanément. 
Le dernier avion attend en tournant autour de l'aéroport.*

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

- `aircraft.hpp` : Représente un avion.
- `aircraft_types.hpp` : Définit les différents types d'avions.
- `aiport.hpp` : Représente un aéroport.
- `airpot_type.hpp` : Définit les différents types d'aéroports.
- `config.hpp` : Stocke la configuration du jeu.
- `geometry.hpp` : Définit les structures géométriques (points en 2D et 3D).
- `runway.hpp` : Représente une piste de décollage/atterrissage.
- `terminal.hpp` : Représente un terminal auquel un avion peut s'arrêter.
- `tower.hpp` : Représente une tour de contrôle, donc la gestion d'un aéroport.
- `tower_sim.hpp` : Décrit la logique d'un aéroport.
- `waypoint.hpp` : Définit un point de passage, utilisé pour créer des routes.

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.

- `Tower`
  - `WaypointQueue get_instructions(Aircraft& aircraft)` :

    Récupère les points de passage par lesquels passer avant d'atterrir.
  - `void arrived_at_terminal(const Aircraft& aircraft)` :

    Signale qu'un avion a atterri et commence l'embarquement.
- `Aircraft`
  - `const std::string& get_flight_num() const`

    Récupère le numéro de vol d'un avion.
  - `float distance_to(const Point3D& p) const`

    Calcule la distance séparant un avion d'un point donné.
  - `void display() const`

    Fonction d'affichage de l'avion.
  - `void Aircraft::move()`
  
    Fait se déplacer l'avion jusqu'au prochain point de passage.
- `Airport`
  - `Tower& get_tower()`

    Récupère la tour de contrôle de l'aéroport.
  - `void display() const`

    Fonction d'affichage de l'aéroport.
  - `void move()`

    Fonction de placement de l'aéroport.
- `Terminal`
  - `bool in_use() const`

    Détermine si le terminal est utilisé par un avion.
  - `bool is_servicing() const`

    Détermine si un embarquement ou un débarquement est en cours.
  - `void assign_craft(const Aircraft& aircraft)`
    
    Rattache un avion au terminal.
  - `void start_service(const Aircraft& aircraft)`

    Commence le service du terminal (débarquement et embarquement).
  - `void finish_service()`

    Termine le service au terminal.
  - `void move()`

    Fonction de rafraichissement.

Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?

*Le chemin d'un avion est défini par une succession de `Waypoint`.*

Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?

*Les points de passage sont stockés dans une `deque`.*

Expliquez les intérêts de ce choix.

*Ce choix est cohérent, car un avion doit passer par tous les points, dans l'ordre de lesquels il les reçoit (FIFO)* 

## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion. 
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

*Les vitesses sont stockées dans `config.hpp`. Vitesse changée en 0,1.*

2) Identifiez quelle variable contrôle le framerate de la simulation.

*C'est la variable `ticks_per_sec` dans opengl_interface*

Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?

*Si on tente de baisser la framerate jusqu'à 0, ça fait tourner le jeu sans délais, donc à la vitesse maximum.*

Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

*J'ai rajouté un booléen qui dit si on doit appeler les méthodes `move()`.*

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

*C'est `SERVICE_CYCLES` dans la config.*

4) Lorsqu'un avion a décollé, il réatterrit peu de temps après.
Faites en sorte qu'à la place, il soit retiré du programme.\
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
A quel endroit de la callstack pourriez-vous le faire à la place ?\
Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

*On peut savoir que l'avion part après son service dans `get_instructions()` de la classe Tower.*

*On ne peut pas le supprimer ici, car ça invaliderait tous les itérateurs qui le contiennent.*

*Il faut faire remonter l'info dans la fonction move, afin de gérer la suppression dans la fonction `timer()`.*

*Dans la méthode `move()` de `Aircraft`, si nous n'avons plus de waypoints, alors on est sorti et donc on peut retourner `true`.*

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?

*Parce que l'avion est le seul élément amené à disparaître.*

6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

*La méthode est privée dans `Airport` et la classe `Tower` est friend de `Airport`.*

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passés par une référence ?
Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?

*Parce que la méthode `turn` modifie les valeurs du point, on ne veut pas que les modifications se propagent.*

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
