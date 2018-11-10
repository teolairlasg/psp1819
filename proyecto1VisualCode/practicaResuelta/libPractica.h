#ifndef LIBPRACTICA_H
#define LIBPRACTICA_H
int crearYAbrirPipe(const char*);
void tratarSIGUSR1(int);
int prepararPipe(const char*);
void rellenarFechaYHora();
void tratarCtrlC(int);
void tratar2oCtrlC(int);
#endif