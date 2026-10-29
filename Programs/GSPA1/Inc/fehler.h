/**
 * @file fehler.h
 * @brief Einheitliche Fehlercodes des RPN-Rechners.
 *
 * Jede Funktion, die scheitern kann, gibt per return einen dieser Codes
 * zurueck: OK (0) bei Erfolg, eine negative Zahl im Fehlerfall.
 * Ergebnisse werden ueber Zeiger-Parameter oder den Stack geliefert.
 */

#ifndef FEHLER_H
#define FEHLER_H

#define OK 0                        //!< Aktion erfolgreich
#define FEHLER_STACK_VOLL (-1)      //!< push auf vollen Stack (Overflow)
#define FEHLER_STACK_LEER (-2)      //!< pop auf leeren Stack (Underflow)
#define FEHLER_DIV_NULL (-3)        //!< Division durch 0
#define FEHLER_UEBERLAUF (-4)       //!< arithmetische Bereichsueberschreitung
#define FEHLER_ZAHL_ZU_GROSS (-5)   //!< eingegebene Zahl passt nicht in int
#define FEHLER_UNBEKANNTE_TASTE (-6) //!< unerwartete Eingabe

#endif /* FEHLER_H */
// EOF
