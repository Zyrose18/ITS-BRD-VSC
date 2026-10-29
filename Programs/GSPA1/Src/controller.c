/**
 * @file controller.c
 * @brief Ordnet jedem Token eine Aktion zu und meldet Fehler einheitlich.
 */

#include "controller.h"
#include "display.h"
#include "fehler.h"
#include "rechner.h"
#include "stack.h"
#include <stdbool.h>
#include <stdio.h>

#define TEXT_LAENGE 32  // Puffer fuer eine Ausgabezeile
#define ANZAHL_GROSS_P 3 // P zeigt die drei obersten Werte

static bool fehler_aktiv = false; // true: nur noch C wird angenommen

// Gibt eine Zahl in einer eigenen Zeile auf dem Display aus.
static void zahl_ausgeben(int wert) {
   char text[TEXT_LAENGE];
   (void)snprintf(text, sizeof(text), "%d\n", wert);
   if (is_bottom_line()) {
      clear_stdout();
   }
   print_stdout(text);
}

// p: oberste Zahl anzeigen, ohne den Stack zu veraendern.
static int oberste_anzeigen(void) {
   int wert = 0;
   int status = pop(&wert);
   if (status != OK) {
      return status;
   }
   zahl_ausgeben(wert);
   return push(wert);
}

// P: die (bis zu) drei obersten Zahlen anzeigen, Stack bleibt gleich.
static int drei_anzeigen(void) {
   int werte[ANZAHL_GROSS_P];
   int gefunden = 0;
   while (gefunden < ANZAHL_GROSS_P && pop(&werte[gefunden]) == OK) {
      gefunden++;
   }
   if (gefunden == 0) {
      return FEHLER_STACK_LEER;
   }
   for (int i = 0; i < gefunden; i++) {
      zahl_ausgeben(werte[i]); // oberste zuerst
   }
   for (int i = gefunden - 1; i >= 0; i--) {
      (void)push(werte[i]); // in alter Reihenfolge zurueck
   }
   return OK;
}

// d: oberste Zahl verdoppeln.
static int duplizieren(void) {
   int wert = 0;
   int status = pop(&wert);
   if (status != OK) {
      return status;
   }
   (void)push(wert);
   return push(wert);
}

// r: die beiden obersten Zahlen tauschen.
static int tauschen(void) {
   int oberste = 0;
   int zweite = 0;
   int status = pop(&oberste);
   if (status != OK) {
      return status;
   }
   status = pop(&zweite);
   if (status != OK) {
      return status;
   }
   (void)push(oberste);
   return push(zweite);
}

// Liefert den Anzeigetext zu einem Fehlercode.
static char *fehler_text(int code) {
   switch (code) {
   case FEHLER_STACK_VOLL:
      return "Fehler: Stack voll\n";
   case FEHLER_STACK_LEER:
      return "Fehler: Stack leer\n";
   case FEHLER_DIV_NULL:
      return "Fehler: Division durch 0\n";
   case FEHLER_UEBERLAUF:
      return "Fehler: Ueberlauf\n";
   case FEHLER_ZAHL_ZU_GROSS:
      return "Fehler: Zahl zu gross\n";
   default:
      return "Fehler: unbekannte Taste\n";
   }
}

void verarbeite_token(T_token token) {
   if (fehler_aktiv) {
      if (token.tok == CLEAR) {
         stack_leeren();
         fehler_aktiv = false;
         set_normal_mode();
      }
      return;
   }

   int status = OK;
   switch (token.tok) {
   case NUMBER:
      status = push(token.val);
      break;
   case PLUS:
      status = addieren();
      break;
   case MINUS:
      status = subtrahieren();
      break;
   case MULT:
      status = multiplizieren();
      break;
   case DIV:
      status = dividieren();
      break;
   case PRT:
      status = oberste_anzeigen();
      break;
   case PRT_ALL:
      status = drei_anzeigen();
      break;
   case CLEAR:
      stack_leeren();
      clear_stdout();
      break;
   case DOUBLE:
      status = duplizieren();
      break;
   case SWAP:
      status = tauschen();
      break;
   case OVERFLOW:
      status = FEHLER_ZAHL_ZU_GROSS;
      break;
   default:
      status = FEHLER_UNBEKANNTE_TASTE;
      break;
   }

   if (status != OK) {
      fehler_aktiv = true;
      set_err_mode();
      print_stdout(fehler_text(status));
   }
}

// EOF
