Questo progetto implementa una struttura dati hash table con concatenamento, supportando chiavi e valori di tipo generico. Viene utilizzata per risolvere un problema reale: trovare la parola più frequente di lunghezza almeno N in un file di testo (iliade.txt).

Il progetto include:

Implementazione della hash_table generica in C
Testing automatico con assert
Parsing file e analisi di frequenza parole
Utilizzo assistito di ChatGPT per progettazione, debug e refining

### Prompt iniziale a ChatGPT

Il primo prompt usato è stato:

“Vorrei implementare una hash table generica in C con concatenamento. Deve supportare inserimento, recupero, rimozione, keyset, ecc. Mi aiuti a scriverla in modo modulare (file .h e .c separati)?”

Output ricevuto:

    ChatGPT ha prodotto:
        -la definizione delle strutture HashNode e HashTable
        -prototipi e implementazioni per put, get, remove, contains_key, keyset, size e free
        -suggerimenti su tipizzazione generica (void*) e funzioni hash/comparazione come parametri


### Refinamento della struttura

Problema: Inizialmente il file .c conteneva doppie definizioni (hash_table_create), errori di compatibilità tra tipi (int vs size_t) e parametri inutilizzati.

Soluzione con ChatGPT:
“Ho un errore: redefinition of hash_table_create...”
ChatGPT ha analizzato e suggerito di rimuovere la duplicazione, correggere la firma coerentemente col .h, e di usare size_t per hash_table_size.

Per il testing ho chiesto:

“Scrivimi dei test semplici con assert per la hash_table: inserimento, sovrascrittura, rimozione, keyset.”
ChatGPT ha generato test chiari e modulari. In seguito abbiamo chiesto:

“Come faccio a vedere cosa sta succedendo nei test?”
E ChatGPT ha suggerito di aggiungere printf() nei test per rendere il feedback più informativo.


### Considerazioni finali

Vantaggi dell’uso del LLM
    -Velocità: sviluppo guidato in modo rapido e incrementale
    -Precisione: suggerimenti sintatticamente corretti e aderenti al C standard
    -Didattico: spiegazioni dei concetti (bucket, hash, macro, test) chiare e accessibili
    -Debug Assistito: spiegazioni degli errori di compilazione molto utili

Limiti riscontrati
    -Spesso bisogna chiedere esplicitamente chiarimenti o correzioni (es. gestione della memoria,
     strdup mancanti, free dimenticati)
    -Non sempre l’LLM propone le migliori pratiche (es. mancanza di const o free() approfondito)
    -È utile validare sempre quanto suggerito, soprattutto in C dove la gestione della memoria è cruciale


### Compilazione

```bash
make all
```

Esecuzione

```bash
./bin/main_ex3 ./data/iliade.txt 6
```

Test

```bash
./bin/test_ex3
```


### Conclusione

Questo esercizio ha mostrato come un LLM come ChatGPT possa essere un ottimo assistente di sviluppo, sia per generare codice, sia per comprenderlo, migliorarlo e testarlo. Tuttavia, il ruolo attivo del programmatore nel validare, testare e rifinire rimane fondamentale.