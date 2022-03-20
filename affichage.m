% On récupère les les constantes utiles utilisées dans le code cpp
C = readmatrix('const.csv');
N = C(1);
dt = C(2);
Taille = C(3);

% On récupère les positions des particules en fonctioni du temps
m = readmatrix('part.csv');

% On sépare ensuite chaques colonnes pour séparer les coordonnées
x = m(:,2);
y = m(:,3);
z = m(:,4);

for k = 1 : length(x)/N
  % Création du nuage de points
  scatter3([x(k) y(k) z(k)], [x(k+1) y(k+1) z(k+1)], [x(k+2) y(k+2) z(k+2)]);
  title( sprintf('T = %f',(k-1)*dt));
  %on représente la boîte racine
  axis([-Taille/2 Taille/2 -Taille/2 Taille/2 -Taille/2 Taille/2])
  hold off
  pause(1);
end

hold off
