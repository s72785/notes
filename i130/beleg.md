gem. 07.01.2015 BS1 Prof. Fritzsche

Übungen: http://www2.htw-dresden.de/~fritzsch/BS/bs_uebungen.html

6.1. Aufg. 8.1, 8.2

Beleg: Aufg. 10.5, 10.6, 12.2-12.6 vorzeigen/demonstrieren
13.1.
20.1.
27.1.

8.1
Schreiben Sie eine Shell-Prozedur, die mehrere Dateien aus dem Verzeichnis /glb/studi in ein Unterverzeichnis Ihres Home-Directories kopiert.
Die Namen der zu kopierenden Dateien sind als Parameter zu übergeben, Ihr Unterverzeichnis soll im Dialog abgefragt werden. Sollten kein bzw. mehr als 9 Parameter an die Prozedur übergeben worden sein, ist eine Fehlermeldung auszugeben und die Prozedur zu beenden. Im Fall, daß eine zu kopierende Datei nicht in /glb/studi enthalten ist, ist ebenfalls eine Fehlermeldung auszugeben. 

    #!/bin/sh
    sdir=/glb/studi
    if [ $# -eq 0 -o $# -gt 9 ]; then
    	echo "Fehler: 0 oder mehr als 9 Parameter";
    	echo denkbar sind:
    	ls ${sdir}
    	exit 1;
    fi
    #echo $#: $@
    echo Kopieren der Dateien $@
    echo -n In Verzeichnis ~/
    read tdir
    mkdir -p ~/${tdir}
    for i in $@; do
    	if [ -e ${sdir}/${i} ]; then
    		cp ${sdir}/${i} ~/${tdir}
    	else
    		echo "Nicht existierende Datei: ${sdir}/${i}"
    	fi
    done


8.2
Schreiben Sie eine Prozedur, die von allen gewöhnlichen Dateien eines der Prozedur als Parameter zu übergebenden Textverzeichnisses die Anzahl der Wörter ermittelt und die Dateinamen sowie (d.h. gefolgt von ...) die jeweilige Wortanzahl zeilenweise in eine einzurichtende Datei "Wortanalyse" schreibt. Der Name des Textverzeichnisses sei relativ zum aktuellen Verzeichnis.
Hinweis: Verwenden Sie das find-Kommando!

    #!/bin/sh
    ofile=Wortanalyse
    #dosnt work as it gives wc first followed by filename:
    #find $1 -xtype f -exec wc -w {} +
    echo -n > ./${ofile}
    if [ ! -d ./$1 ]; then
    	echo "Fehler! Verzeichnis existiert nicht: ./$1";
    	exit 1;
    fi
    for i in $(find ./$1 -xtype f); do
    	echo -n "${i} " >> ./${ofile}
    	cat ${i} | wc -w  >> ./${ofile}
    done


8.3
Schreiben Sie eine Prozedur del, der beliebig viele Namen von zu löschenden Dateien (Dateinamen relativ zum aktuellen Verzeichnis) als Parameter übergeben werden sollen. Die Prozedur soll die Dateien aber nicht endgültig löschen, sondern in ein vorher im Homedirectory einzurichtendes Verzeichnis .muell übertragen.
Nach mehrmaliger Benutzung der Prozedur soll dieses Verzeichnis je nach Bedarf (z.B. am Sitzungsende) mit dem üblichen UNIX-Kommando rm geleert werden. Die Dialog-Abfrage, ob das Verzeichnis geleert werden soll, soll über ein kleines Menü erfolgen.

    #!/bin/sh
    recycle=~/.muell
    mkdir -p ${recycle}
    for i in $@; do
    	mv ${i} ${recycle}
    done
    echo -n "Soll das Verzeichnis geleert werden? (j/N) "
    read answer
    if [ ${answer} = "j" -o ${answer} = "y" -o ${answer} = "J" -o ${answer} = "Y" ]; then
    	rm -d -I -- ${recycle}/*
    fi

9.1
Erzeugen Sie in Ihrem Heimat-Verzeichnis eine eigene bzw. erweitern Sie die bereits vorhandene .profile-Datei in der Weise, daß ein kurzer Begrüßungstext erzeugt und das Bereitschaftssymbol auf Ihre Initialen, gefolgt von einer spitzen Klammer eingestellt wird.
Sorgen Sie weiterhin dafür, daß Ihre neu angelegten Dateien alle Zugriffsrechte nur für Sie selbst erhalten. 

    #begruessungstext
    echo "albern aber gefordert: ein kurzer Begruessungstext"
    #initialen raussuchen, weil setzen ist langweilig
    mn=$(finger -s $USER|tac|head -1|tr -s [:blank:] ' ')
    fn=$(echo $mn|cut -d' ' -f3)
    cn=$(echo $mn|cut -d' ' -f2)
    initials=$(echo $cn|cut -c1)
    initials=${initials}$(echo $fn|cut -c1)
    PS1=${initials}\>
    export PS1
    #zugriffsrechte einschränken
    umask 077


9.2
Arbeiten Sie am Rechner iaix1.informatik das Programm lprog ab, das als Lademodul im Verzeichnis /glb/studi steht, und speichern Sie das Ergebnis in eine Datei mit dem Namen resultlprog in Ihrem text-Verzeichnis.
Hinweis: Fügen Sie einen neuen Kommandosuchpfad ein.

10.1
Richten Sie in Ihrem Home-Directory eine Verbindung zum Verzeichnis /glb/studi ein. 

10.2
Übertragen Sie aus der Datei stadt, die im Verzeichnis /glb/studi zu finden ist und alle deutschen Großstädte enthält, den Eintrag mit Ihrer Landeshauptstadt in Ihr eigenes Verzeichnis. 

10.3
Ermitteln Sie, wieviele Großstädte das Land Baden-Wuerttemberg hat. 

10.4
Schreiben Sie eine Funktion zur bequemeren Handhabung des find-Kommandos! 

10.5
Ermitteln Sie die Unterschiede zwischen den Programmen unix.f und hunix.f (beide im Verzeichnis /glb/studi) und gleichen Sie unix.f an hunix.f an (in Ihrem text-Verzeichnis). Geben Sie eine Kommandoprozedur an, die die Namen von zwei Texttadeien als Parameter übergeben bekommt und die erste Datei automatisch an die zweite angleicht. 

10.6
Schreiben Sie eine Prozedur, die alle die Dateien Ihres Home-Directories (einschließlich aller Unterverzeichnisse) anzeigt, die in den letzten n Tagen (Anzahl n als Parameter übergeben!) modifiziert worden sind. 

11.1
Schreiben Sie eine Prozedur, die ein Programm mit längerer Laufzeit im Hintergrund zur Abarbeitung bringt. Der Programmname soll als Parameter übergeben oder im Dialog abgefragt werden.
Das Programm soll außerdem die Eigenschaft haben, daß es seine Ergebnisse in verschlüsselter Form erzeugt. Den Klartext erhält man, wenn man folgende Zeichentransformationen vornimmt:

7 --> f     Q --> e     X --> r
Y --> l     Z --> i     J --> u     3 --> g

Testen Sie Ihre Prozedur anhand des Programms prog.b5, das im Verzeichnis /glb/studi steht. 

11.2
Stellen Sie eine Prozedur auf, die Ihnen jede Minute einmal die Uhrzeit anzeigt; aktivieren Sie sie zuerst im Vordergrund und dann im Hintergrund. Beenden Sie die Prozedur vor Sitzungsende wieder. 

12.1
Entwickeln Sie eine Kommandoprozedur, mit der Sie den Wochentag Ihrer Geburt ermitteln können! Der Prozedur sind beim Aufruf in der Kommandozeile Tag, Monat und Jahr des Geburtsdatums jeweils als Zahl und in dieser Reihenfolge zu übergeben. Der Wochentag soll auf stdout ausgegenen werden. Beispiel:

        ./proz12_1 15 3 1921
         Dienstag
         
12.2
Im Verzeichnis /glb/studi finden Sie die Dateien kunden, aktikel und auftraege mit Datensätzen, die folgendermaßen aufgebaut sind:

kunden: Kundenname Kundennummer Wohnort
artikel: Artikelname Artikelnummer Preis
auftraege: Kundennummer Auftragsnummer Artikelnummer Stückzahl Liefertermin

Sortieren Sie
a) die Datei kunden alphabetisch nach Namen
b) die Datei artikel nach Artikelnummern
c) die Datei auftraege erstens (erstrangig) nach Kundennummern und zweitens (zweitrangig) nach dem Liefertermin

12.3
Stellen Sie eine Datei kundenauftraege für alle Kunden auf, die einen Auftrag erteilt haben. Sie enthalte: Kundennr., Name, Ort, Artikelnr., Preis, Stückzahl und Auftragsnr. 

12.4
Sortieren Sie die Datei kundenauftraege
a) für den Versandt nach Orten,
b) für die Abrechnung nach Kunden
c) für die Lagerhaltung nach Artikelnummern.

12.5
Ordnen Sie die Datei Kundenaufträge so, daß bei (a) die Ortsnamen, bei (b) die Kundennamen und bei (c) die Artikelnummern zuerst ausgegeben werden. 

12.6
Die Datei stadt im Verzeichnis /glb/studi enthält alle deutschen Großstädte. Ermitteln Sie daraus die Städte mit mehr als einer halben Million Einwohner. Geben Sie die gefundenen Datensätze in der Reihenfolge
Einwohnerzahl - Städtename - Bundesland
aus und sortieren Sie die Städte der Größe nach! 

