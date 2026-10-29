/**
 * @file stack.h
 * @brief Schnittstelle des Stack-Moduls (int-Werte, feste Groesse).
 */

#ifndef STACK_H
#define STACK_H

/**
 * @brief Legt einen Wert oben auf den Stack.
 * @param wert Der abzulegende Wert.
 * @return OK oder FEHLER_STACK_VOLL, wenn der Stack voll ist.
 */
int push(int wert);

/**
 * @brief Nimmt den obersten Wert vom Stack.
 * @param wert Adresse, an die der entnommene Wert geschrieben wird.
 * @return OK oder FEHLER_STACK_LEER, wenn der Stack leer ist.
 */
int pop(int *wert);

/**
 * @brief Loescht alle Eintraege des Stacks.
 */
void stack_leeren(void);

#endif /* STACK_H */
// EOF
