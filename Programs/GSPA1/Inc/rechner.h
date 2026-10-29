/**
 * @file rechner.h
 * @brief Grundrechenarten auf den beiden obersten Stack-Werten.
 *
 * Jede Funktion nimmt die zwei obersten Werte vom Stack, prueft auf
 * Bereichsueberschreitung und legt das Ergebnis wieder auf den Stack.
 * Bei - und / gilt: zweiter Wert von oben OP oberster Wert.
 */

#ifndef RECHNER_H
#define RECHNER_H

/**
 * @brief Addiert die beiden obersten Werte.
 * @return OK, FEHLER_STACK_LEER oder FEHLER_UEBERLAUF.
 */
int addieren(void);

/**
 * @brief Subtrahiert den obersten vom zweiten Wert.
 * @return OK, FEHLER_STACK_LEER oder FEHLER_UEBERLAUF.
 */
int subtrahieren(void);

/**
 * @brief Multipliziert die beiden obersten Werte.
 * @return OK, FEHLER_STACK_LEER oder FEHLER_UEBERLAUF.
 */
int multiplizieren(void);

/**
 * @brief Teilt den zweiten durch den obersten Wert (ganzzahlig).
 * @return OK, FEHLER_STACK_LEER, FEHLER_DIV_NULL oder FEHLER_UEBERLAUF.
 */
int dividieren(void);

#endif /* RECHNER_H */
// EOF
