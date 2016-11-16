// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h> 
#include <conio.h>

#define INICIOX 9
#define INICIOY 13
#define FIN 80


struct Personaje {
	int x;
	int y;
	char * dibujo;
	Personaje(int px, int py, char * dib)
	{
		x = px;
		y = py;
		dibujo = dib;
	}
};

struct Bala {
	int x;
	int y;
	char * dibujo;
	Bala(int px, int py, char * d)
	{
		x = px;
		y = py;
		dibujo = d;
	}
};

void dibujarEscenario();
void dibujarBala(Bala * bala);
void moverBala(Bala * bala);
void dibujarPersonaje(Personaje pers);
void moverPersonaje(Personaje * pers, char * direccion);
void moverEnemigo(Personaje * enemigo);
Personaje * reaparicionEnemigo(Personaje pers);
Bala * disparar(Personaje pers, char * direccion);
void colisiones();
void hacerMundo();
void accionTecla();

Personaje pers = { INICIOX,INICIOY,"*" };
Bala * bala = nullptr;
Personaje * enemigo = nullptr;

void dibujarEscenario()
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("-------------------------------------------------------------");
	return;
}

void gotoxy(int x, int y)
{
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void hacerMundo() {
	dibujarEscenario();
	dibujarPersonaje(pers);


	if (bala != nullptr) {
		moverBala(bala);
		dibujarBala(bala);
	}

	if (enemigo != nullptr) {
		moverEnemigo(enemigo);
		dibujarPersonaje(*enemigo);
	}


	if (enemigo == nullptr) {
		enemigo = reaparicionEnemigo(pers);
		dibujarPersonaje(*enemigo);
	}
}

void colisiones() {
	if (enemigo != nullptr && bala != nullptr)
		if (enemigo->x == bala->x || enemigo->x - 1 == bala->x || enemigo->x + 1 == bala->x) {
			delete bala;
			bala = nullptr;
			delete enemigo;
			enemigo = nullptr;
		}

	if (bala != nullptr)
		if (bala->x <= 0 || bala->x > 80) {
			delete bala;
			bala = nullptr;
		}
}

Bala * disparar(Personaje pers, char * direccion)
{
	Bala * b;
	if (strcmp(direccion, "der") == 0)
		b = new Bala(pers.x + 1, pers.y, ">");
	else if (strcmp(direccion, "izq") == 0)
		b = new Bala(pers.x - 1, pers.y, "<");
	else return nullptr;
	return b;

}

void dibujarPersonaje(Personaje pers)
{
	gotoxy(pers.x, pers.y);
	printf(pers.dibujo);
	return;
}

void dibujarBala(Bala * bala) {
	gotoxy(bala->x, bala->y);
	printf(bala->dibujo);
	return;
}

void moverBala(Bala * bala)
{
	if (strcmp(bala->dibujo, ">") == 0)
		bala->x++;
	else if (strcmp(bala->dibujo, "<") == 0)
		bala->x--;
	else return;

	return;
}

void moverPersonaje(Personaje * pers, char * direccion)
{
	if (pers->x > 0 && pers->x < 80) {
		if (strcmp(direccion, "der") == 0)
			pers->x++;
		else if (strcmp(direccion, "izq") == 0)
			pers->x--;
	}
	else {
		if (pers->x == 0)
			pers->x++;
		else
			pers->x--;
	}
	return;
}

void moverEnemigo(Personaje * enemigo)
{

	int movimientoAleatorio = rand() % 2 + 1;
	if (enemigo->x > 0 && enemigo->x < 80) {
		if (movimientoAleatorio == 1)
			enemigo->x++;
		else if (movimientoAleatorio == 2)
			enemigo->x--;
	}
	else {
		if (enemigo->x == 0)
			enemigo->x++;
		else
			enemigo->x--;
	}
	return;
}

Personaje * reaparicionEnemigo(Personaje pers)
{
	Personaje * enemigo = nullptr;
	int movimientoAleatorio = rand() % 79 + 1;
	if (movimientoAleatorio != pers.x && movimientoAleatorio != pers.x + 1 && movimientoAleatorio != pers.x + 2 && movimientoAleatorio != pers.x - 1 && movimientoAleatorio != pers.x - 2) {
		enemigo = new Personaje(movimientoAleatorio, INICIOY, "/");
		return enemigo;
	}
	return nullptr;
}

void clear()
{
	system("cls");
}

void update() {
	clear();
	hacerMundo();
	colisiones();
}

void accionTecla() {
	int c;
	if (_kbhit()) {
		c = _getch();
		if (c == 'a')
			moverPersonaje(&pers, "izq");
		else if (c == 'd')
			moverPersonaje(&pers, "der");
		if (bala == nullptr) {
			if (c == 'q')
				bala = disparar(pers, "izq");
			else if (c == 'e')
				bala = disparar(pers, "der");
		}
		return;
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	while (1) {
		update();
		accionTecla();
		Sleep(100);
	}
	return 0;
}


