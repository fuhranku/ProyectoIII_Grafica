Proyecto desarrollado por Frank Ponte. V2390509
VisualStudio x86.

Interacción:
	Selección de elementos con el click izquierdo del ratón a modelos/luces. Deseleccionar con click derecho. Existen dos tipos de menús: 
	-Menú de luces
	-Menú de modelos
Dependiendo de lo que se seleccione cada menú estará disponible o no. Siempre que se deselecciona el programa vuelve al menú por defecto (Menú de modelos).

Las luces están precargadas y para apagarlas se deben seleccionar previamente.

Cosas que fallan o que me faltaron por hacer:
	- Gouraud (Está funcional pero me parece que no está bien.
	- Vertex pointer funciona a medias
	- VBO no visualiza
	- Al implementar la iluminación, el color de relleno de los modelos no se ve.
	- House.obj y Dragon.off no cargan (Intenté debuggear y ver qué pasó con el dragon pero no pude encontrar el motivo)

El escalamiento de los modelos es automático, se debe colocar en "0.0f" si se desea que no escale más.