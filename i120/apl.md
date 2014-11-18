# APL Programmierung 1, Teil 1

* Abnahme am 15.12. bzw. 16.12. in den Praktika
* Aufgabe: Programmieren Sie ein interaktives Banksystem. Das System nimmt Eingaben von der Tastatur entgegen und erzeugt Ausgaben auf dem Bildschirm. Folgende Funktionen des Banksystems müssen implementiert werden:

1. Einen neuen Kunden anlegen. Dabei wird dem Kunden eine 4-stellige Kontonummer mitgeteilt, ein Konto mit Guthaben 0 angelegt und eine 4-stellige PIN, bestehend aus den Ziffern 0-9, festgelegt.
2. Einen Kunden anmelden. Dabei wird der Kunde nach Kontonummer und PIN gefragt. Wenn dreimal hintereinander eine falsche PIN eingegeben wird, kann sich der Kunde nicht mehr anmelden.
3. Geld einzahlen, auszahlen und auf ein Konto dieser Bank überweisen. Die Beträge müssen positiv sein und das Konto darf nicht überzogen werden.
4. 4-stellige PIN ändern.
5. Einen Kunden abmelden.

Die Funktionen 2 – 5 dürfen nur ausgeführt werden, wenn der Kunde angemeldet ist. Es muss eine Menüsteuerung implementiert werden.
Eigenschaften, die sich aus diesen Anforderungen als selbstverständlich ergeben, müssen bei der Implementierung beachtet werden.
Das Programm muss sinnvoll und übersichtlich strukturiert sein. Variablen müssen Datentypen besitzen, die für den angestrebten Zweck sinnvoll sind. Befehle zur Benutzerinteraktion (Eingabe über Tastatur, Ausgabe auf den Bildschirm) dürfen nur in der Menüsteuerung verwendet werden.
Die Programmierrichtlinien http://www.informatik.htw-dresden.de/~hollas/P1/Programmierrichtlinien.pdf müssen beachtet werden.
Sie müssen die Funktionsweise Ihres Programms vollständig erklären können. Wer dazu nicht in der Lage ist, erhält die Note 5.
