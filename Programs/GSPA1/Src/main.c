/**
 * @file main.c
 * @brief RPN-Taschenrechner fuer das ITS-Board: liest Token fuer Token
 *        und gibt jedes an den Controller weiter.
 */

#include "controller.h"
#include "display.h"
#include "init.h"
#include "scanner.h"
#include "token.h"

int main(void) {
   initITSboard(); // ITS-Board initialisieren
   init_display(); // Display und Touch-Tastatur initialisieren

   while (1) {
      T_token token = next_token(); // naechste Eingabe vom Scanner
      verarbeite_token(token);      // passende Aktion ausfuehren
   }
}

// EOF
