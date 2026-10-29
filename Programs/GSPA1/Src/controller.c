/**
 * @file controller.c
 * @brief Entscheidet anhand des Tokens, was der Rechner tun soll,
 *        und zeigt Ergebnisse und Fehler auf dem Display an.
 */

#include "controller.h"
#include "display.h"
#include "fehler.h"
#include "rechner.h"
#include "stack.h"
#include <stdio.h>

#define TEXT_LAENGE 32 // Platz fuer eine Zeile Text

// 0 = alles normal, 1 = ein Fehler ist aufgetreten (dann nur noch C erlaubt)
static int fehler_aktiv = 0;

// Zeigt eine Zahl in einer eigenen Zeile an.
static void zahl_ausgeben(int zahl) {
   char text[TEXT_LAENGE];
   // Die Laenge ist mit TEXT_LAENGE begrenzt, snprintf_s gibt es hier nicht.
   // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
   snprintf(text, TEXT_LAENGE, "%d\n", zahl);
   if (is_bottom_line()) {
      clear_stdout(); // Fenster voll: erst leeren
   }
   print_stdout(text);
}

// p: oberste Zahl anzeigen. Danach wieder drauflegen, damit der
// Stack gleich bleibt.
static int oberste_anzeigen(void) {
   int zahl = 0;
   int status = pop(&zahl);
   if (status != OK) {
      return status;
   }
   zahl_ausgeben(zahl);
   return push(zahl);
}

// P: die drei obersten Zahlen anzeigen (weniger, wenn weniger da sind).
// Danach alle wieder in der alten Reihenfolge drauflegen.
static int drei_anzeigen(void) {
   int erste = 0;
   int zweite = 0;
   int dritte = 0;

   if (pop(&erste) != OK) {
      return FEHLER_STACK_LEER; // gar nichts auf dem Stack
   }
   zahl_ausgeben(erste);

   if (pop(&zweite) != OK) {
      return push(erste); // nur eine Zahl war da
   }
   zahl_ausgeben(zweite);

   if (pop(&dritte) != OK) {
      push(zweite);
      return push(erste); // nur zwei Zahlen waren da
   }
   zahl_ausgeben(dritte);

   push(dritte);
   push(zweite);
   return push(erste);
}

// d: oberste Zahl verdoppeln (zweimal drauflegen).
static int duplizieren(void) {
   int zahl = 0;
   int status = pop(&zahl);
   if (status != OK) {
      return status;
   }
   push(zahl);
   return push(zahl);
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
   push(oberste); // die alte oberste kommt nach unten
   return push(zweite); // die alte zweite kommt nach oben
}

// Zeigt zum Fehlercode den passenden Text in Rot an.
static void fehler_anzeigen(int code) {
   set_err_mode(); // Fenster leeren, Schrift rot
   if (code == FEHLER_STACK_VOLL) {
      print_stdout("Fehler: Stack voll\n");
   } else if (code == FEHLER_STACK_LEER) {
      print_stdout("Fehler: Stack leer\n");
   } else if (code == FEHLER_DIV_NULL) {
      print_stdout("Fehler: Division durch 0\n");
   } else if (code == FEHLER_UEBERLAUF) {
      print_stdout("Fehler: Ueberlauf\n");
   } else if (code == FEHLER_ZAHL_ZU_GROSS) {
      print_stdout("Fehler: Zahl zu gross\n");
   } else {
      print_stdout("Fehler: unbekannte Taste\n");
   }
   print_stdout("Weiter mit C\n");
}

void verarbeite_token(T_token token) {
   // Nach einem Fehler wird nur noch C angenommen.
   if (fehler_aktiv == 1) {
      if (token.tok == CLEAR) {
         stack_leeren();
         fehler_aktiv = 0;
         set_normal_mode(); // Fenster leeren, Schrift wieder schwarz
      }
      return;
   }

   int status = OK;

   switch (token.tok) {
   case NUMBER: // eine Zahl wurde eingegeben
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
   case PRT: // p
      status = oberste_anzeigen();
      break;
   case PRT_ALL: // P
      status = drei_anzeigen();
      break;
   case DOUBLE: // d
      status = duplizieren();
      break;
   case SWAP: // r
      status = tauschen();
      break;
   case CLEAR: // C
      stack_leeren();
      clear_stdout();
      break;
   case OVERFLOW: // Zahl war zu gross fuer int
      status = FEHLER_ZAHL_ZU_GROSS;
      break;
   default: // alles andere
      status = FEHLER_UNBEKANNTE_TASTE;
      break;
   }

   if (status != OK) {
      fehler_aktiv = 1;
      fehler_anzeigen(status);
   }
}

// EOF
