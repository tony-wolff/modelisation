# De l'acquisition à l'impression 3D

### Point Set Processing Simplification
On utilise l'algo BPA en expérimentant diff méthodes sur 4 types de données, dépendant de l'acquisition (synthèse d'images, CT, scanner...)
Conclure la simplification la plus approprié pour chauqe acquisition. L'objectif étant de préserver la forme originale du point cloud.

### Clustering

Partitionner le nuage de points en groupes. On peut subdiviser en grille régulière, octree...

**3 tactiques** :
- Croissange de régions : agglutiner un groupe/cluster en fonction de propriétés (e.g fusionner des groupes qui sont en dessous d'une certaine distance)
Chaque groupe serait associé à un certain point.

- Partition hiérarchique : 

- Consolidation par LOP : enlever des points considérés comme érronés.

- Consolidation par WLOP : 


### calcul des normals

**2 méthodes**

- Reconstruction par BPA : pivoter un disque de rayon fixe pour sélectionner et relier deux points.
Problème du disque de rayon fixe, on risque de sauter des échantillons;

- calcul de normales par ajustement du plan tangent
    - Choisir un voisinnage, construire le plan tangent qui minimise la distance aux voisins du point
    - chosir un voisinnage, triangulariser pour créer des plans(surfaces) faire la moyenne des normals de ces surfaces.

Un bord c'est quoi : 

topologie : relation de voisinnage

non variété : 

Vérifier que les reconstructions sont des 2D variétés































# Pépite de la prof
Les artéfects
FACIAAAALE
Que faire dans ce trou ?