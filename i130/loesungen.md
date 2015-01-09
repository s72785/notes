
# Lösungen zu ausgewählten Praktikumsaufgaben

## Aufgabe 2.2 a)

    fritzsch@ilux150:[~] >ls /bin/
    ...

    fritzsch@ilux150:[~] >ls /usr/bin
    ...


## Aufgabe 2.2 b)

    fritzsch@ilux150:[~] >ls /bin/a*
    /bin/arch /bin/awk
    fritzsch@ilux150:[~] >

## Aufgabe 2.2 c)

    fritzsch@ilux150:[~] >ls /bin/?s
    /bin/ls /bin/ps
    fritzsch@ilux150:[~] >

## Aufgabe 2.3 a)

    fritzsch@ilux150:[~] >ls /glb/studi
    artikel hkunst.c k kunst.f mail_pgp saetze up1.c
    auftraege hkunst.f korr-c lprog parmueb short up1.f
    auftraege.old hp.f korr-f mail_ai98 prakt stadt up2.f
    ausg hunix.c kunden mail_bs prakt_bs2 te1 uv
    bedien hunix.f kunden.orig mail_k98 prg.b5 unix.c w
    bla1 i kunst.c mail_k99 prog.b5 unix.f xinitrc
    fritzsch@ilux150:[~] >


## Aufgabe 2.3 b)

    fritzsch@ilux150:[~] >ls /glb/studi/*.c
    /glb/studi/hkunst.c /glb/studi/kunst.c /glb/studi/up1.c
    /glb/studi/hunix.c /glb/studi/unix.c
    fritzsch@ilux150:[~] >


## Aufgabe 3.1 a)

    fritzsch@ilux150:[~] >cd uprakt/text # navigieren in das text-Verzeichnis
    fritzsch@ilux150:[text] >wc -l dat2 # die Datei kann auch anders heißen
    6 dat2
    fritzsch@ilux150:[text] >

## Aufgabe 3.1 b)

    fritzsch@ilux150:[text] >ls > dat1
    fritzsch@ilux150:[text] >wc -l < dat1 # Ausgabe ohne Dateiname; Eingabeumlenkung
    44
    fritzsch@ilux150:[text] >wc -l dat1 # Ausgabe mit Dateiname
    44 dat1
    fritzsch@ilux150:[text] >

    Hinweis: Pipe wurde noch nicht behandelt

## Aufgabe 3.1 c)

    Für nachfolgende Anwendungen export LANG=C eingeben!

    fritzsch@ilux150:[text] >egrep '[A-Z][a-z]+' /glb/studi/bedien

    "Wörter mit großem Anfangsbuchstaben" wird so verstanden, dass nach einem Großbuchstaben mindestens ein Kleinbuchstabe folgt. Es werden nur Zeilen ausgegeben, für die das zutrifft.

## Aufgabe 3.1 d)

    fritzsch@ilux150:[text] >egrep '[ ][-][ ]' /glb/studi/bedien | wc -l
    6
    fritzsch@ilux150:[text] >

## Aufgabe 3.1 e)

    fritzsch@ilux150:[text] >egrep '"(.)*"' /glb/studi/unix.c
     printf( "\nUNIX");
    fritzsch@ilux150:[text] >

    Der Punkt steht für ein beliebiges Zeichen.

## Aufgabe 3.2

    fritzsch@ilux150:[~] >egrep '^[ ]*ARQ([[:blank:]]|[)])' /glb/studi/short/abk
     ARQ automated repeat request
     ARQ) (wiederholte ?bertragung fehlerhafter Pakete)
    fritzsch@ilux150:[~] >

## Aufgabe 4.1 b)

    fritzsch@ilux140:~/uprakt/text> cc unix.c kunst.c
    fritzsch@ilux140:~/uprakt/text> ./a.out

    UNIX-Kunst
    **********

    fritzsch@ilux140:~/uprakt/text>


    Die Übersetzung erfolgt mittels des C-Compilers (Kommando cc) durch

    fritzsch@ilux140:~/uprakt/text> cc -c unix.c kunst.c

    Dabei werden die Objektmodule unix.o und kunst.o erzeugt. Mittels

    fritzsch@ilux140:~/uprakt/text> cc unix.o kunst.o

    wird dann aus diesen Moduln ein ausführbares Programm a.out erzeugt. Die Quellprogramme unix.c
    und kunst.c werden dazu nicht mehr benötigt. 

## Aufgabe 4.4)

     Prozedur proz4_5:

     echo "Zugriffsrechte fuer $HOME/$1:"
     ls -ld $HOME/$1
     echo "Zugriffsrechte fuer enthaltene Dateien:"
     ls -l $HOME/$1
     
     alternativ:

     ls -ld ~/$1
     echo "--------------------------------"
     ls -l ~/$1

     Anwendung:

     fritzsch@ilux140:~/uprakt/text> proz4_5 uprakt/text
     Zugriffsrechte fuer /u/fritzsch/uprakt/text:
     drwxr-xr-x 2 fritzsch fi 4096 2005-11-17 07:51 /u/fritzsch/uprakt/text
     Zugriffsrechte fuer enthaltene Dateien:
     insgesamt 212
     -rw-r--r-- 1 fritzsch fi 80066 2002-12-11 10:55 abk
     -rw-r--r-- 1 fritzsch fi 1595 2003-10-20 09:08 bedien
     -rw-r--r-- 1 fritzsch fi 6 2002-11-08 10:50 bingo
     -rw-r--r-- 1 fritzsch fi 7 2003-10-30 09:54 dat1
     -rw-r--r-- 1 fritzsch fi 408 2003-10-28 12:08 dat2
     -rw-r--r-- 1 fritzsch fi 15 2003-10-30 10:00 dat3
     .
     .
     .

## Aufgabe 5.1

    Text einer Kommandoprozedur proz5_1 :

    echo "Ausfuehrung von: $*"
    echo "Ausgabe (BS - b, Datei - d, Drucker - p):"
    read a
    case $a in
      b) $*;;
      d) echo "Dateiname:"
         read datei
         $* > $datei
         echo "Ausgabe in Datei $datei geschrieben!";;
      p) # $* | lpr;;
           $* | echo "Ausgabe auf Drucker";;
      *) echo "falsche Eingabe";;
    esac

          Bemerkung:
            Hinter p) beginnt ab #  ein Kommentar, der bis zum Zeilenende reicht und die Kommandofolge zum
            Drucken enthält. Statt wirklich zu Drucken, wird die Kommandofolge
              $* | echo "Ausgabe auf Drucker";;
            ausgeführt.

## Aufgabe 6.1

    Text einer Kommandoprozedur proz6_1 :

    if test $# -gt 0 
    then
      if test -d $1 
      then
        echo "aktueller Parameter ist Verzeichnis"
      elif test -f $1 
      then 
        echo "aktueller Parameter ist vorhandene Datei"
        if test -s $1 || (echo "Datei ist leer" && false) 
        then
          if test -r $1 || (echo "Datei ist nicht lesbar" && false) 
          then 
           echo "Datei ist nicht leer und ist lesbar"
          fi
        fi 
      else
        echo "aktueller Parameter ist kein Verzeichnis und "\
        "keine gewöhnliche Datei"
      fi 
    else
      echo "Prozeduraufruf ohne Parameter"
    fi

## Aufgabe 6.2

    Text einer Kommandoprozedur proz6_2 :

    if test $# -gt 0 
       then
       if test -d $1 
          then
          echo "aktueller Parameter ist Verzeichnis"
       elif test -f $1 
          then 
          echo "aktueller Parameter ist vorhandene Datei"
          if test -s $1 || (echo "Datei ist leer" && false) 
             then
             if test -r $1 || (echo "Datei ist nicht lesbar" && false) 
                then 
                echo "Datei ist nicht leer und ist lesbar"
                until false
                do
                   echo "Ausgabe (p - Drucker, b - Bildschirm, n - keine Ausgabe):"
                   read ausgabe
                   case $ausgabe in
                   p) echo "Druckerausgabe" ; break;;
                   b) cat $1 ; break;;
                   n) break;;
                   *) echo "Falsche Eingabe" ; continue;;
                   esac
                done
             fi
          fi     
       else
          echo "aktueller Parameter ist kein Verzeichnis und "\
                "keine gewöhnliche Datei"
       fi 
    else
       echo "Prozeduraufruf ohne Parameter"
    fi

    Die until-Schleife kann aufgrund der Bedingung false (d.h. die Bedingung liefert immer - bei jeder Auswertung - den logischen Wert falsch) nur über break verlassen werden.

## Aufgabe 7.2

    Text einer Kommandoprozedur proz7_2 :

    kudat=$1
    shift
    for i
    do
    echo "Geben Sie Zusatzinformationen fuer den Kunden \"$i\" ein:"
    read zusatz
    ed $kudat<<%
    /$i/a
     $zusatz
    .
    -1
    j
    w
    q
    %
    done

    Anwendung:

    ~> proz7_2 kunden Hagen Meier
    Geben Sie Zusatzinformationen fuer den Kunden "Hagen" ein:
    geb. am 9.12.1978
    622
    Hagen, Dagobert  91/0374  Meissen
    640
    Geben Sie Zusatzinformationen fuer den Kunden "Meier" ein:
    geb. am 12.4.1980
    640
    Meier, Isolde  91/0676  Dresden
    658
    ~> cat kunden
    Hagen, Dagobert  91/0374  Meissen geb. am 9.12.1978
    Meier, Isolde  91/0676  Dresden geb. am 12.4.1980
    Robinson, Frieder 92/0677  Inseldorf
    Mueller, Rene  92/0001  Dippoldiswalde
    Katzenellenbogen, Ivo 92/0014  Dresden
    Meier, Isolde  93/0001  Bautzen
    Niebuhr, Max  93/0003  Dresden
    Krause, Richard  94/0012  Freital
    Krause, Grit  94/0027  Dresden
    Haller, Albert  94/0033  Grossenhain
    Maennchen, Renate 95/0184  Pirna
    Laser, Matthias  95/0365  Heidenau
    Liebe, Elisabeth 95/0412  Dresden
    Rothe, Manfred  95/0577  Dresden
    Lehmann, Willi  96/0011  Dresden
    Kr³ger, Theobald 96/0134  Radebeul
    Horn, Marlene  96/0174  Pirna
    Leipold, Otte  97/0437  Dresden

    ~>

    Hinweise:

        nach dem ed-Kommando a darf kein Zeichen folgen, auch kein Leerzeichen.
        das Zeichen . als Abschluß der Editoreingabe muß in der ersten Spalte stehen. 

Last modified: Jan 09 2014; orig: http://www2.htw-dresden.de/~fritzsch/BS/bs_loesungen.html
