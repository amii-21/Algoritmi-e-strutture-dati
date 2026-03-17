Il progetto implementa un programma in C che legge un da un file .csv, in cui:
- i nodi rappresentano città italiane,
- gli archi indicano collegamenti tra città con le relative distanze;
esegue una visita in ampiezza (BFS) partendo da una città di input;
salva su un file di output tutte le città visitate, nell’ordine di visita, una per riga.

## Funzionalità principali

- Costruzione del grafo:il grafo è caricato dal file CSV, creando un nodo per ogni città e inserendo archi secondo le distanze indicate.
- Visita BFS: viene effettuata una visita in ampiezza a partire dal nodo sorgente fornito, esplorando i nodi adiacenti in ordine di vicinanza.
- Output: l’elenco delle città visitate viene scritto su un file, una per riga, seguendo l’ordine della visita.


## Compilazione
```bash 
make all
```
## Esecuzione
```bash
./bin/main_ex3-4 ./data/italian_dist_graph.csv torino output.txt
```
Il programma:
legge il grafo da italian_dist_graph.csv, esegue la BFS a partire da torino, salva l’ordine di visita in output.txt.

## Test
```bash
./bin/test_ex3-4
```
Esegue gli unit test per la libreria graph.

## Risultati e Prestazioni

Numero di nodi visitati: 18636
Tempo di esecuzione (su macchina con processore moderno): ~0.55 secondi
Memoria usata: proporzionale al numero di nodi/archi, con efficienza elevata grazie all’uso della tabella hash.
Complessità BFS: O(N + M), dove N = nodi e M = archi. Confermata sperimentalmente.

## Considerazioni Finali

L'uso di una tabella hash per gestire i nodi rende le operazioni molto efficienti, in particolare in presenza di grafi sparsi
L’approccio adottato si adatta bene anche a dataset di grandi dimensioni.
I risultati sono compatibili con le attese teoriche e confermano l’efficienza della struttura dati implementata.