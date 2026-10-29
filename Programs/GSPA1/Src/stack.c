/**
 * @file stack.c
 * @brief Stack fuer int-Werte: Array fester Groesse und Fuellstand.
 */

#include "stack.h"
#include "fehler.h"

#define STACK_SIZE 10

static int stack[STACK_SIZE]; // die Faecher des Stacks
static int anzahl = 0;        // belegte Faecher = Index des naechsten freien Fachs

int push(int wert) {
   if (anzahl == STACK_SIZE) {
      return FEHLER_STACK_VOLL;
   }
   stack[anzahl] = wert;
   anzahl++;
   return OK;
}

int pop(int *wert) {
   if (anzahl == 0) {
      return FEHLER_STACK_LEER;
   }
   anzahl--;
   *wert = stack[anzahl];
   return OK;
}

void stack_leeren(void) { anzahl = 0; }

// EOF
