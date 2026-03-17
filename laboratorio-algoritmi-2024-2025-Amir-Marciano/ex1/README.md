Di seguito i tempi (in secondi) misurati lanciando, per ciascun campo e algoritmo,
campo field per il tipo di dito : 1(stringa), 2(int) e 3(float)
campo algo per il tipo di algoritmo: 1(MergeSort) e 2 (QuickSort)

```bash
./bin/main_ex1 records.csv sorted.csv <field> <algo>
```

| Algoritmo   | Campo            | Tempo (s) |
|-------------|------------------|-----------|
| Merge Sort  | field1 (stringa) | 40.83     |
| Merge Sort  | field2 (intero)  | 39.92     |
| Merge Sort  | field3 (float)   | 44.27     |
|             |                  |           |
| Quick Sort  | field1 (stringa) | 42.36     |
| Quick Sort  | field2 (intero)  | 63.31     |
| Quick Sort  | field3 (float)   | 64.29     |



### Analisi:
-Merge Sort
I tempi sono molto omogenei attorno ai 40–44 s.
Questa stabilità è tipica di un algoritmo con complessità garantita O(n log n) e comportamento indipendente dalla distribuzione dei dati.

-Quick Sort
Per il campo stringa (field1), Quick Sort impiega circa 42 s, comparabile a Merge Sort.
Per i campi numerici (field2 e field3), i tempi schizzano a oltre 63 s, quasi il 50 % in più rispetto a Merge Sort su dati analoghi.
Ciò suggerisce una cattiva scelta dei pivot o una distribuzione dei valori (magari molti duplicati o quasi ordinati) che causa partizioni sbilanciate e degrade Quick Sort verso il caso quadratico O(n²).

### Dipendenza dal campo:
-Merge Sort: leggerissima variazione tra i campi (massimo ±3 s), praticamente invariante rispetto al tipo di dato.
-Quick Sort: forte dipendenza dal tipo di chiave, con prestazioni peggiori su interi e float. Questo indica che l’efficacia di Quick Sort è più sensibile alla natura e all’ordinamento parziale dei dati.


### Conclusioni e ipotesi
-Risultati attesi: Merge Sort più stabile, Quick Sort più rapido “in media”.
-Osservazioni: Quick Sort non è risultato sempre più veloce di Merge Sort sui 20 M di record; anzi sui campi numerici soffre molto.


