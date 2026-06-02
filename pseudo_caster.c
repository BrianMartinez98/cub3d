

typed     Function()
{
    Player_dir  
}


Direccion del personaje respecto a la horizontal para --> Corte Vertical
Direccion del personaje respecto a la Vertical para   --> Corte horizontal
si el angulo es mayor que 90 grados, solo hay que restar 90 y tienes el angulo relativo que es lo unico que importa
el cateto contiguo ya lo tenemos ya que es la altura relativa al tile. con el angulo y ese CC tengo la h y de ahi el CO
a partir de ahi, sumamos el tamaño del tile y comprobamos.
si esa zona (contando el borde) es de un muro, estamos listos
proceso homologo para vertical


¿cuantas lineas necesitamos para el ray-casting completo?
320, ya que esa es la resolucion que buscamos
Para el fov usaremos 90 grados como el doom
es decir, necesitamos un rayo cada 0.281 grados

Ojo con este detalle

Si quieres que el primer rayo sea exactamente:

player_angle - 45°

y el último exactamente:

player_angle + 45°

entonces usarías:

angle_step = 90 / (320 - 1)
angle_step = 90 / 319
angle_step ≈ 0.28213 grados


Que altura tienen las paredes?
tiene una altura relativa segun la proyeccion. no hay una formula exacta ya que solo tenemos la longitud del rayo
perspective projection
