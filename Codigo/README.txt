Proyecto desarrollado por Frank Ponte. V2390509
VisualStudio x86.

Interacci�n:
	Selecci�n de elementos con el click izquierdo del rat�n a modelos/luces. Deseleccionar con click derecho. Existen dos tipos de men�s: 
	-Men� de luces
	-Men� de modelos
Dependiendo de lo que se seleccione cada men� estar� disponible o no. Siempre que se deselecciona el programa vuelve al men� por defecto (Men� de modelos).

Las luces est�n precargadas y para apagarlas se deben seleccionar previamente.

Cosas que fallan o que me faltaron por hacer:
	- Gouraud (Est� funcional pero me parece que no est� bien.
	- Vertex pointer funciona a medias
	- VBO no visualiza
	- Al implementar la iluminaci�n, el color de relleno de los modelos no se ve.
	- House.obj y Dragon.off no cargan (Intent� debuggear y ver qu� pas� con el dragon pero no pude encontrar el motivo)

El escalamiento de los modelos es autom�tico, se debe colocar en "0.0f" si se desea que no escale m�s.