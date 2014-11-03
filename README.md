parallella
==========

Repo para el tp final de orga2.

#### TODO (parcial):
- [ ] Medir ancho de banda para acceder a la SD.
- [ ] Averiguar finalidad del conector PEC POWER.
- [ ] Establecer el tiempo para realizar lecturas.
- [ ] Determinar qué sucede cuando llegan 2 pedidos al mismo nodo de eMesh.
- [ ] Medir tiempos de e/s.

#### Métodos:
- [ ] transferencia entre cores (lectura): varios tamaños, alineados,
  desalineados, a caballo, batch.
- [ ] transferencia entre cores (escritura): ida y vuelta, escribir en vecino,
  detectar cambios y escribir de vuelta.
- [ ] Transferencia de N bytes desde _shared_ a _bank_, usando todos los
  caminos posibles, para todos los cores.
