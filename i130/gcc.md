## Schlichter Compiler-Gang

Einfach (min.) eine Datei übersetzen, die Ausgabedatei heißt dann a.out

    gcc quelldatei.c [weitere quelldateien.c]

Eine Datei übersetzen und den Namen der Ausgabedatei festlegen:

    gcc -o ausgabedatei quelldatei.c

## Module hinzuladen, die für header-Dateien wichtig sind:

    gcc -lm -o ausgabedatei quelldatei.c

## Comiler-Symbole einbauen

Um den Debugger (gdb) sinvoll einsetzen zu können, müssen die Symbole ach dem Compilieren erhalten bleiben

    gcc -g -o ausgabedatei quelldatei.c
