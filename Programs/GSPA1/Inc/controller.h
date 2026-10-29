/**
 * @file controller.h
 * @brief Steuert den Rechner: wertet ein Token aus und loest die Aktion aus.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "token.h"

/**
 * @brief Fuehrt die zum Token passende Aktion aus und zeigt Ergebnisse
 *        oder Fehler an. Nach einem Fehler wird nur noch C angenommen.
 * @param token Das vom Scanner gelieferte Token.
 */
void verarbeite_token(T_token token);

#endif /* CONTROLLER_H */
// EOF
