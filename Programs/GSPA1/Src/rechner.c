#include "rechner.h"
#include "fehler.h"
#include "stack.h"
#include <limits.h>

/* Holt die zwei obersten Zahlen vom Stack.
 * oberste = zuletzt eingegebene Zahl, zweite = die darunter. */
static int zwei_holen(int *oberste, int *zweite) {
   int status = pop(oberste);
   if (status != OK) {
      return status;
   }
   return pop(zweite);
}

int addieren(void) {
   int oberste;
   int zweite;
   int status = zwei_holen(&oberste, &zweite);
   if (status != OK) {
      return status;
   }

   if (oberste > 0 && zweite > INT_MAX - oberste) {
      return FEHLER_UEBERLAUF;
   }
   if (oberste < 0 && zweite < INT_MIN - oberste) {
      return FEHLER_UEBERLAUF;
   }
   return push(zweite + oberste);
}

/* Rechnet: zweite - oberste */
int subtrahieren(void) {
   int oberste;
   int zweite;
   int status = zwei_holen(&oberste, &zweite);
   if (status != OK) {
      return status;
   }

   if (oberste < 0 && zweite > INT_MAX + oberste) {
      return FEHLER_UEBERLAUF;
   }
   if (oberste > 0 && zweite < INT_MIN + oberste) {
      return FEHLER_UEBERLAUF;
   }
   return push(zweite - oberste);
}

int multiplizieren(void) {
   int oberste;
   int zweite;
   int status = zwei_holen(&oberste, &zweite);
   if (status != OK) {
      return status;
   }

   if (zweite > 0) {
      if (oberste > 0 && zweite > INT_MAX / oberste) {
         return FEHLER_UEBERLAUF;
      }
      if (oberste < 0 && oberste < INT_MIN / zweite) {
         return FEHLER_UEBERLAUF;
      }
   } else if (zweite < 0) {
      if (oberste > 0 && zweite < INT_MIN / oberste) {
         return FEHLER_UEBERLAUF;
      }
      if (oberste < 0 && zweite < INT_MAX / oberste) {
         return FEHLER_UEBERLAUF;
      }
   }
   return push(zweite * oberste);
}

/* Rechnet: zweite / oberste (ganzzahlig) */
int dividieren(void) {
   int oberste;
   int zweite;
   int status = zwei_holen(&oberste, &zweite);
   if (status != OK) {
      return status;
   }

   if (oberste == 0) {
      return FEHLER_DIV_NULL;
   }
   if (zweite == INT_MIN && oberste == -1) {
      return FEHLER_UEBERLAUF;
   }
   return push(zweite / oberste);
}