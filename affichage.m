% On récupère les les constantes utiles utilisées dans le code cpp
C = readmatrix('const.csv');
N = C(1);
dt = C(2);
Taille = C(3);

% On récupère les positions des particules en fonctioni du temps
m = readmatrix('part.csv');

% On sépare ensuite chaques colonnes pour séparer les coordonnées
num = m(:,1);
x = m(:,2);
y = m(:,3);
z = m(:,4);

for k = 1 :N: length(x)
  % Création du nuage de points
  scatter3(x(k:k+N-1), y(k:k+N-1), z(k:k+N-1));
  axis([-Taille Taille -Taille Taille -Taille Taille])
  title( sprintf('T = %f',(k-1)*dt));
  xlabel('x');
  ylabel('y');
  zlabel('z');
  %on représente la boîte racine
  hold off
  pause(0.2);
end

hold off
