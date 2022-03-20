% On récupère les positions des particules en fonctioni du temps
m=readmatrix('part.csv');

% On sépare ensuite chaques colonnes pour séparer positions et temps
x = m(:,2);
y = m(:,3);
z = m(:,4);
t = m(:,5);

for k = 1 : length(x)/3
  % Création du nuage de points
  scatter3([x(k) y(k) z(k)], [x(k+1) y(k+1) z(k+1)], [x(k+2) y(k+2) z(k+2)]);
  title( sprintf('T = %f',t(k*3)));
  %on représente la boîte racine
  axis([-5 5 -5 5 -5 5])
  hold off
  pause(1);
end

hold off