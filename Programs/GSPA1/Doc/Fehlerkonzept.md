# Fehlerkonzept – GSPA1 RPN-Taschenrechner

## Grundidee

C hat keine Exceptions. Darum gilt für jede Funktion, die scheitern kann:

- Der **Rückgabewert** (`return`) ist nur der **Status**: `OK` (0) oder ein **negativer Fehlercode**.
- Das **Ergebnis** wird getrennt geliefert: über einen **Zeiger-Parameter** (`pop(int *wert)`) oder auf dem Stack.

So ist ein Fehler nie mit einem negativen Ergebnis verwechselbar
(z. B. liegt -1 auf dem Stack vs. Stack leer).

## Fehlercodes (fehler.h)

| Code | Wert | Wo erkannt | Anzeige |
|---|---|---|---|
| OK | 0 | – | – |
| FEHLER_STACK_VOLL | -1 | stack: push auf vollen Stack (Overflow) | Fehler: Stack voll |
| FEHLER_STACK_LEER | -2 | stack: pop auf leeren Stack (Underflow) | Fehler: Stack leer |
| FEHLER_DIV_NULL | -3 | rechner: Division durch 0 | Fehler: Division durch 0 |
| FEHLER_UEBERLAUF | -4 | rechner: Ergebnis außerhalb von int | Fehler: Ueberlauf |
| FEHLER_ZAHL_ZU_GROSS | -5 | controller: Scanner meldet OVERFLOW-Token | Fehler: Zahl zu gross |
| FEHLER_UNBEKANNTE_TASTE | -6 | controller: unerwartetes Token | Fehler: unbekannte Taste |

## Weiterreichen

1. stack/rechner geben den Code per `return` an den Aufrufer zurück.
2. Jede Funktion prüft den Status ihrer Aufrufe (`if (status != OK) return status;`) und reicht ihn unverändert weiter.
3. Der controller zeigt den Text rot an (`set_err_mode`) und geht in den Fehlerzustand.
4. Im Fehlerzustand wird nur `C` angenommen: Stack leeren, Fehler zurücksetzen, normale Anzeige.

## Bereichsüberschreitung (vor dem Rechnen geprüft)

- Addition: `oberste > 0 && zweite > INT_MAX - oberste` oder `oberste < 0 && zweite < INT_MIN - oberste`
- Subtraktion (zweite - oberste): `oberste < 0 && zweite > INT_MAX + oberste` oder `oberste > 0 && zweite < INT_MIN + oberste`
- Multiplikation: `a * b <= INT_MAX <=> a <= INT_MAX / b`, für alle vier Vorzeichenfälle angepasst
- Division: Divisor 0 -> FEHLER_DIV_NULL; `INT_MIN / -1` -> FEHLER_UEBERLAUF
