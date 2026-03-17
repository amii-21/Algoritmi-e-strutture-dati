L’obiettivo dell’esercizio è implementare una funzione per il calcolo della edit distance tra due stringhe, usando solo inserimenti e cancellazioni, secondo una definizione personalizzata (non standard). Questa funzione viene poi impiegata per correggere un file di testo (correctme.txt) confrontando ogni parola con un dizionario (dictionary.txt).

### Strategia adottata

È stata implementata sia una versione ricorsiva semplice (edit_distance) sia una versione ricorsiva con memoizzazione (edit_distance_dyn) per l’ottimizzazione tramite programmazione dinamica.
Il programma legge le parole dal file correctme.txt e, per ciascuna di esse, verifica se è contenuta nel dizionario:
Se la parola è nel dizionario, si considera corretta e non viene modificata.
Se non è nel dizionario, si calcola la edit distance con tutte le parole presenti e si propone una lista di parole con distanza minima.

### Considerazioni
Il programma non corregge errori grammaticali o semantici: ad esempio, se la parola "made" è ortograficamente corretta (cioè presente nel dizionario), non viene suggerita la parola "madre", anche se nel contesto potrebbe essere più adatta. Questo perché la correzione è basata esclusivamente sulla presenza nel dizionario e sulla distanza ortografica, non sul significato o sul contesto.
L’approccio garantisce un comportamento deterministico e chiaro, conforme ai vincoli dell’esercizio.

### Risultati
Dati dell’esperimento:
File di input (correctme.txt): 49 parole da analizzare.
File di dizionario (dictionary.txt): contenente l'elenco delle parole corrette.
Numero di esecuzioni: 6 test identici per verificare la stabilità e le performance dell’algoritmo.

Risultati:
| Test | Parole corrette  | Tempo di esecuzione (s)  |
|------|------------------|--------------------------|
| 1    | 7                | 20.95                    |
| 2    | 7                | 20.03                    |
| 3    | 7                | 20.54                    |
| 4    | 7                | 20.32                    |
| 5    | 7                | 21.86                    |
| 6    | 7                | 21.39                    |


Media dei tempi: ~20.85 s
Parole corrette : 7 su 49 (≈ 14.3%)
I tempi di esecuzione sono stati misurati utilizzando la funzione clock() della libreria <time.h>

Stabilità: I risultati sono consistenti in ogni test: lo stesso numero di parole corrette (7 su 49) e tempi di esecuzione simili, con variazioni fisiologiche legate alla gestione della memoria e al carico del sistema.
Performance: Il tempo medio di esecuzione (~21 secondi) indica che l’algoritmo, nella sua forma attuale, è computazionalmente oneroso, probabilmente a causa della complessità O(n × m) del confronto tra ogni parola del testo e tutte quelle del dizionario, e della mancanza di ottimizzazioni significative (es. pruning o threshold per distanza massima).