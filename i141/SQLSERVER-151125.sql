--
-- 1.
--
-- db auswählen
use iw14s72785;
--Mitarbeiter löschen
DELETE FROM Zuordnung; --bESSER: ERST zUORDNUNG LÖSCHEN
DELETE FROM Mitarbeiter;
--Neue Quelle lesen
SELECT * FROM depotN..quelleMitarbeiter;-- .. wird hier zu .dbo expandiert
--Mitarbeiter einlesen
INSERT INTO Mitarbeiter SELECT * FROM depotN.dbo.quelleMitarbeiter;
--Projekte, Zuordnung löschen
DELETE FROM Projekt;
--Projekte importieren
SELECT * FROM depotN.dbo.quelleProjekt;
--beachten: Ziel hat eine Spalte mehr als die Quelle, daher genauer fassen
INSERT INTO Projekt (ProNr, ProName, ProOrt, Aufwand, Leiter) SELECT * FROM depotN.dbo.quelleProjekt;
--Zuordnung übernehmen
INSERT INTO Zuordnung SELECT * FROM depotN.dbo.quelleZuordnung;
--
-- 2.
--
-- 2.1 Projektleiter in Tabelle Projekt eindeutig identifizierbar machen
-- Lsg: MitID verwenden statt Name
ALTER TABLE Projekt ADD LeiterMitID CHAR NULL;
-- 2.2 effizientes einfügen von der ID anhand der Namen
SELECT MitID,m.Nachname, p.ProNr,p.Leiter FROM Mitarbeiter m JOIN Projekt p ON m.Nachname = p.Leiter;
--UPDATE Projekt JOIN (SELECT MitID,m.Nachname, p.ProNr,p.Leiter FROM Mitarbeiter m JOIN Projekt p ON m.Nachname = p.Leiter) ON Mitarbeiter.Nachname = Projekt.Leiter SET Projekt.LeiterMitID = Mitarbeiter.MitID;
-- Falle: Spaölten müssen gleich definiert sein
ALTER TABLE Projekt ALTER COLUMN LeiterMitID CHAR(3) NULL;
--
SELECT m.MitID FROM Mitarbeiter m INNER JOIN Projekt p ON m.Nachname = p.Leiter;
UPDATE p SET p.LeiterMitID = m.MitID FROM Mitarbeiter m INNER JOIN Projekt p ON m.Nachname = p.Leiter;-- AND p.Leiter <> 'Hase';
--gewünschte Lsg:
SELECT MitID FROM Mitarbeiter, Projekt WHERE Projekt.Leiter = Mitarbeiter.Nachname;
UPDATE Projekt SET Projekt.LeiterMitID = (
  SELECT MitID FROM Mitarbeiter WHERE Projekt.Leiter = Mitarbeiter.Nachname AND Projekt.Leiter <> 'Hase'
);
-- 2.3 Alte MA durch aktuelle ersetzen
SELECT * FROM Projekt ;
SELECT * FROM Mitarbeiter;
--  das gibt es hier nicht?!
-- 2.4 Alte Spalte `Leiter` löschen
ALTER TABLE Projekt DROP COLUMN Leiter;
-- 3.1 Tragen Sie ihre persönlichen Daten in Tabelle `Mitarbeiter` ein. MitID '210', Beruf 'Student'
-- SELECT * FROM Mitarbeiter;
INSERT INTO Mitarbeiter ( MitID, Nachname, Vorname, Ort, Gebdat, Beruf, Telnr ) VALUES ( '210', 'Weber', 'Chris', 'Dresden', '1980-01-01', 'Student', '+49 351/0000' );
-- 3.2 Geben Sie in der Tabelle `Projekt` ein `Projekt` 'MS-SQL-PRakt' mit `ProNr` '46' ein,
-- die `Beschreibung` sei frei wählbar, der `Aufwand` sei eine Zahl zwischen 2 und 4, der `Leiter` sie selbst
SELECT * FROM Projekt;
INSERT INTO Projekt (ProNr,ProName,ProOrt,Beschreibung,Aufwand,LeiterMitID) VALUES ('46','MS-SQL-Prakt','Dresden','TSQL den Studenten aufzwingen','4','210');
-- 3.3 Orden Sie sich das Projekt (ProNr 46) in der Tabelle Zuordnung mit einem Istanteil <1.0 und einem Plananteil von min. 0.65 zu.
SELECT * FROM Zuordnung;
INSERT INTO Zuordnung VALUES('210','46','0.7','0.65');
-- 3.4 Ordnen Sie sich ein beliebiges weiteres Projekt zu! Die Summe der Istanteile und Plananteile soll 1.0 ergeben. Nutzen Sie eine Unterabfrage.
INSERT INTO Zuordnung VALUES('210','32',(1.0-(SELECT Sum(Istanteil) FROM Zuordnung WHERE MitID='210')),(1.0-(SELECT Sum(Plananteil) FROM Zuordnung WHERE MitID='210')));
-- 3.5 Erteilen Sie Herrn Rabe ein weiteres Projekt, so dass dessen Planateil-mme ebenfalls 1.0 beträgt
INSERT INTO Zuordnung (MitID,ProNr,Istanteil,Plananteil) VALUES(
  '33',
  (SELECT MitID From Mitarbeiter WHERE Nachname = 'Rabe'),
  (1.0 - (SELECT SUM(Plananteil) FROM Zuordnung WHERE MitID = (SELECT MitID From Mitarbeiter WHERE Nachname = 'Rabe'))),
  (1.0 - (SELECT SUM(Plananteil) FROM Zuordnung WHERE MitID = (SELECT MitID From Mitarbeiter WHERE Nachname = 'Rabe')))
);
-- 3.6 Tragen Sie ein weiteres Projekt (z.B. 'Oracle-Prakt.') mit `ProNr` '47' ohne Leiter mit `Aufwand` = '0' ein.
SELECT * FROM Projekt;
INSERT INTO Projekt (ProNr,ProName,ProOrt,Aufwand) VALUES ('47','Oracle-Prakt.','Dresden','0');
-- 4. Erstellen Sie eine Prozedur, die folgende Aufgaben erfüllt. In der Prozedur ist genau ein Cursor zu verwenden
-- a) Zu einer der Prozedur übergebenen `ProNr` sollen der `ProName` und der benötigte `Aufwand` angezeigt werden.
--    Des Weiteren sollen `MitID`, `Nachname` und `Vorname` des Projektleiters angezeigt werden.
--    (Ausgabe soll durch ein SELECT-Satement erfolgen)
-- b) Im 2. Ausgabeteil sollen die dem Projekt zugeordneten Mitarbeiter mit deren MitID, Nachname, Vorname, Beruf, Plananteil,Istanteil
--    sowie deren Abweichung (`Plananteil` - `Istanteil`) je Mitarbeiter ausgewiesen werden.
-- Ausgaben als Text erfolgen in der Form
--   print ' text ' + @char_variable
--  bzw.
--   print ' text ' + CONVERT( CHAR(n), @zahl_variable )
-- mit n-hinreichend große Zahl für die Konvertierung in eine Zeichenkette

--4.
--DROP PROCEDURE CurseProc;
--CREATE PROCEDURE CurseProc @ProjNr INT
--AS
--BEGIN
--	IF @ProjNr NOT IN (SELECT ProNr FROM Projekt)
--		PRINT 'Mitarbeiter nicht vorhanden!'
--	ELSE BEGIN
  --a)
--		SELECT p.ProNr, p.ProName, p.Aufwand, m.MitID, m.Nachname, m.Vorname
--			FROM Projekt p JOIN Mitarbeiter m ON p.LeiterMitID=m.MitID
--			WHERE p.ProNr = @ProjNr
  --b)
--		DECLARE	@MID CHAR(3),
--				@MNName CHAR(20),
--				@MVName CHAR(20),
--				@MBeruf CHAR(15),
--				@MPAnt FLOAT,
--				@MIAnt FLOAT,
--				@MAAbw FLOAT
--		DECLARE MitCursor CURSOR FOR
--			SELECT m.MitID, m.Nachname, m.Vorname, m.Beruf,
--				z.Plananteil, z.Istanteil,
--				(z.Plananteil - z.Istanteil) AS Abweichung
--			FROM Zuordnung z JOIN Mitarbeiter m ON z.MitID=m.MitID
--			WHERE z.ProNr=@ProjNr
--		OPEN MitCursor
		--also: FETCH NEXT FROM @Cursor INTO @Var
--		FETCH MitCursor
--			INTO @MID, @MNName, @MVName, @MBeruf, @MPAnt, @MIAnt, @MAAbw
--		IF @@FETCH_STATUS <> 0 
--			PRINT '<< Kein MA zugeteilt >>'   
--		ELSE
--			WHILE @@FETCH_STATUS = 0
--			BEGIN
--				PRINT 'MitID:		' + @MID
--				PRINT 'Nachname:	' + @MNName
--				PRINT 'Vorname:		' + @MVName
--				PRINT 'Beruf:		' + @MBeruf
--				PRINT 'Plananteil:	' + CONVERT(CHAR(10), @MPAnt)
--				PRINT 'Istanteil:	' + CONVERT(CHAR(10), @MIAnt)
--				PRINT 'Abweichung:	' + CONVERT(CHAR(10), @MAAbw)
				--fetch next
--				FETCH MitCursor
--			INTO @MID, @MNName, @MVName, @MBeruf, @MPAnt, @MIAnt, @MAAbw
--			END
--		CLOSE MitCursor
--		DEALLOCATE MitCursor
--	END
	
--END;

--EXEC CurseProc @ProjNr = '31';

-- 5. Abfragen
-- Formulieren Sie die folgenden Abfragen sowohl als implizite Joins (WHERE-Klausel), als auich als explizite Joins (JOIN ON-Klausel).
-- Unterabfragen sollen nur dann genutzt werden, wenn ein JOIN direkt über die Tabellen nicht möglich ist.
-- Setzen Sie nur die zwingend erforderlichen Tabellen im SQL-Statement ein!
-- 5.1 Zeigen Sie für alle Projektleiter deren `Nachname`(n), `Vorname`(n), `Ort` sowie die zu leitenden Projekte mit den jeweiligen Projektnamen an.
SELECT * FROM Projekt;
SELECT * FROM Mitarbeiter;
-- ohne LEFT um keine NULL für Leiter zu nehmen
SELECT m.Nachname,m.Vorname,m.Ort,p.ProName FROM Projekt p JOIN Mitarbeiter m ON p.LeiterMitID = m.MitID;
-- 5.2 Ermitteln Sie für die an Projekten arbeitenden Mitarbeiter die Mitarbeiterdaten,
-- an welchem Projekt (*nur* `ProNr`) sie arbeiten und welchen Istanteil sie in dem jeweiligen Projekt haben.
SELECT m.*,z.ProNr,z.Istanteil FROM Zuordnung z JOIN Mitarbeiter m ON z.MitID=m.MitID;
-- 5.3 Zeigen Sie die Projektdaten mit einem `Aufwand` >= 3 sowie die Daten der zugehörigen Projektleiter (Nachname,Vorname,Ort)
-- und deren Istanteil in dem jeweiligen Projekt an.
SELECT p.*,m.Nachname,m.Vorname,m.Ort,z.Istanteil FROM Projekt p JOIN Mitarbeiter m ON p.LeiterMitID = m.MitID JOIN Zuordnung z ON p.ProNr=z.ProNr AND p.LeiterMitID=z.MitID WHERE p.Aufwand >= 3;
-- 5.4 Listen Sie für ALLE Projekte ProNr, Proname und die Summe der Istanteile auf, auch für die Projekte, die z.Zt. nicht bearbeitet werden.
--     Erstellen Sie diese Abfrage
-- a) als JOIN (beachten Sie die Wahl des richtigen JOINs) sowie
SELECT p.ProNr, p.ProName, SUM(z.Istanteil) FROM Projekt p LEFT JOIN Zuordnung z ON p.ProNr = z.ProNr GROUP BY p.ProNr,p.ProName ;
-- b) als UNION (Für eine "leere" Spalte muss ein (konstanter) DUMMY-Wert mit passendem Datentyp im SELECT-Statement gesetzt werden).
SELECT p.ProNr, p.Proname, SUM(z.Istanteil) AS SummeIstanteile FROM Projekt p
JOIN Zuordnung z ON p.ProNr = z.ProNr
GROUP BY p.ProNr, p.Proname;
UNION
SELECT p.ProNr, p.Proname, 0 AS SummeIstanteile FROM Projekt p
LEFT JOIN Zuordnung z ON p.ProNr = z.ProNr
WHERE z.Istanteil IS NULL;


-- 5.5 Ermitteln Sie für ALLE `Mitarbeiter` die Reserven als Differenz zwischen 1 und ihrer Gesamtplananteile.
--     (Hinweis: Nutzen Sie die Erfahrung aus Aufgabe 5.4)
--ohne NULL
SELECT z.MitID, (1-SUM(Plananteil)) AS Reserve FROM Zuordnung z GROUP BY z.MitID;
--mit NULL
SELECT m.MitId, (1 - sum(z.Plananteil)) AS Reserve FROM Mitarbeiter m
JOIN Zuordnung z on m.MitId = z.MitId
GROUP BY m.MitId
UNION
SELECT m.MitId, 1 AS Reserve FROM Mitarbeiter m
LEFT JOIN Zuordnung z on m.MitId = z.MitId
WHERE z.Plananteil IS NULL;

--sysprocedures?! wie kann man tabellen-details dann z.B. in DQLDeveloper oder mit ODBC abfragen?
--bei windows mit sp_help, unter sqldeveloper nicht mehr als eine zeile
--sp_help Mitarbeiter
--andere möglichkeiten muss man erst suchen
--SELECT * FROM SYSOBJECTS ORDER BY name ASC;
--SELECT * FROM SYSISCOLS;
--Prof. Graefe will nochmal selbst nachlesen

-- Komplex 4 - Semantische Integrität
-- Teil I: Benutzerdefinierte Funktionen
-- 1. Skalarwertfunktion
-- Schreiben Sie eiune Skalarwertfunktion *AlterErmitteln*, die das richtige Alter zu einem übergebenen Datum berechnet.
-- Testen Sie Ihre Funktion, indem Sie sich alle Daten zu ihren Mitarbeitern sowie zusätzlich das Alter ausgeben lassen.
--DROP FUNCTION AlterErmitteln;
--CREATE FUNCTION AlterErmitteln ( @datum date )
--	RETURNS tinyint
--	AS
--	BEGIN
--			DECLARE @Alter tinyint
--			SELECT @Alter = DATEDIFF(yyyy, @datum, GETDATE())
--      IF (
--				CONVERT(tinyint, FORMAT(@datum, 'dd')) > CONVERT(tinyint,FORMAT(GETDATE(),'dd'))
--				AND CONVERT(tinyint, FORMAT(@datum, 'MM')) >= CONVERT(tinyint,FORMAT(GETDATE(),'MM'))
--        AND CONVERT(int, FORMAT(@datum, 'yy')) > CONVERT(int,FORMAT(GETDATE(),'yy'))
--			) 
--  			SELECT @Alter = @Alter + 1
--   		RETURN @Alter
--	END;
SELECT MitID, Gebdat, dbo.AlterErmitteln(Gebdat) AS age
-- test
--dbo.AlterErmitteln('1980-11-10'), dbo.AlterErmitteln('1980-11-30')
  FROM Mitarbeiter;
-- 2. Tabellenwertfunktion
-- Entwickeln Sie eine Tabellenwertfunktion, die Ihnen eine Tabelle mit den Spalten MitID und Auslastung zurück gibt. Auslastung soll hierbei die Summe der Istanteile für die Mitarbeiter sein.
-- Es sollen nur die Mitarbeiter ausgegeben werden, die in ihrer Auslastung über einem übergebenen Schwellenwert liegen.
-- Testen Sie die Funktion
--SELECT m.MitID, SUM(Istanteil) AS Auslastung  FROM Mitarbeiter m JOIN Zuordnung z ON m.MitID=z.MitID GROUP BY m.MitID, Istanteil HAVING SUM(Istanteil) >= 0.5;
--DROP FUNCTION dbo.AuslastungTable;
--CREATE FUNCTION dbo.AuslastungTable ( @Schwelle float )
--  RETURNS TABLE
--  AS 
--    RETURN SELECT m.MitID, SUM(Istanteil) AS Auslastung  FROM Mitarbeiter m JOIN Zuordnung z ON m.MitID=z.MitID GROUP BY m.MitID, Istanteil HAVING SUM(Istanteil) >= @Schwelle;
SELECT * FROM dbo.AuslastungTable(0.6);
-- Teil II; Sicherung der semantischen Integrität - Deklaratove Lösung
-- *Überprüfen* Sie stets Ihre nLösungen anhand geeigneter Beispiele!
-- 1. DEFAULTS
-- 1.1 In der Tabelle Mitarbeiter gelten die Annahmen,
-- a) dass die meisten Mitarbeiter ihren Wohnort (Ort) in Dresden haben,
ALTER TABLE Mitarbeiter ADD CONSTRAINT DF_Ort DEFAULT 'Dresden' FOR Ort;
-- test
--INSERT INTO Mitarbeiter (MitID, Nachname, Vorname, Gebdat, Beruf, Telnr) VALUES ('211', 'Müller', 'Hans', '1980-11-30', 'Student', NULL);
--SELECT Ort FROM Mitarbeiter WHERE MitID='211';
--DELETE FROM Mitarbeiter WHERE MitID='211';
-- b) dass der *Beruf* bei den meisten "Dipl.-Ing." ist.
ALTER TABLE Mitarbeiter ADD CONSTRAINT DF_Beruf DEFAULT 'Dipl.-Ing.' FOR Beruf;
-- test
--INSERT INTO Mitarbeiter (MitID, Nachname, Vorname, Gebdat, Beruf, Telnr) VALUES ('211', 'Müller', 'Hans', '1980-11-30', 'Student', NULL);
--SELECT Beruf FROM Mitarbeiter WHERE MitID='211';
--DELETE FROM Mitarbeiter WHERE MitID='211';
-- 2 CHECK
-- 2.1 Ergänzen Sie die Tabellendefinition *Mitarbeiter*:
-- c) Das Alter muss inzwischen einschließlich 18 und einschließlich 60 liegen.
--    Nutzen Sie Ihre benutzerdefinierte Funktion AlterErmitteln
ALTER TABLE dbo.Mitarbeiter ADD CONSTRAINT CK_Alter  CHECK (dbo.AlterErmitteln(Gebdat) >= 18 AND dbo.AlterErmitteln(Gebdat) <= 60);
--testfeld
--INSERT INTO Mitarbeiter (MitID, Nachname, Vorname, Gebdat, Telnr) VALUES ('211', 'Müller', 'Hans', '1984-11-05', NULL);
--INSERT INTO Mitarbeiter (MitID, Nachname, Vorname, Gebdat, Telnr) VALUES ('212', 'Müller', 'John', '1998-11-26', NULL);
--INSERT INTO Mitarbeiter (MitID, Nachname, Vorname, Gebdat, Telnr) VALUES ('213', 'Müller', 'John', '1956-11-26', NULL);
--SELECT MitID, Beruf, dbo.AlterErmitteln(Gebdat) FROM Mitarbeiter WHERE MitID>='211';
--DELETE FROM Mitarbeiter WHERE MitID>='211';
-- d) Jede der 3 Stellen mit *MitID* muss mit einer Ziffer belegt werden.
ALTER TABLE dbo.Mitarbeiter ADD CONSTRAINT CK_MitID  CHECK ( CONVERT( char(3), CONVERT( int, MitID ) ) = MitID );
--tests
--INSERT INTO Mitarbeiter (MitID, Nachname, Vorname, Gebdat, Telnr) VALUES ('211', 'Müller', 'John', '1956-11-26', NULL);
--INSERT INTO Mitarbeiter (MitID, Nachname, Vorname, Gebdat, Telnr) VALUES ('22O', 'Müller', 'John', '1956-11-26', NULL);
--SELECT MitID, Beruf, dbo.AlterErmitteln(Gebdat) FROM Mitarbeiter WHERE MitID>='211';
--DELETE FROM Mitarbeiter WHERE MitID>='211';
-- 2.2 In die Tabelle Zuordnung dürfen nur Datensaätze eingefügt werden, in denen der Istanteil <= 1,0 ist.
--ALTER TABLE dbo.Zuordnung ADD CONSTRAINT CK_Istanteil  CHECK ( Istanteil<= 1.0 );
--INSERT INTO Zuordnung (MitID, ProNr, Istanteil, Plananteil) VALUES ('211', '23', '0.1', '0');
--INSERT INTO Zuordnung (MitID, ProNr, Istanteil, Plananteil) VALUES ('211', '42', '1', '0');
--INSERT INTO Zuordnung (MitID, ProNr, Istanteil, Plananteil) VALUES ('211', '45', '1.5', '0');
--DELETE FROM Zuordnung WHERE MitID = '211';

-- Teil III: Sicherung der referentiellen Integrität - Deklarative Lösung
-- 3. Sicherung der referentiellen Integrität auf deklarativem Wege
-- 3.1 Sichern Sie auf deklarativem Weg die referenteielle Integrität zwischen den Tabellen *Mitarbeiter* und *Projekt*.
-- a) Geben Sie in die Tabellen *Mitarbeiter* und *Projekt* je einen neuen Datensatz mit gleicher *MitID* (in Projekt ist dies die Leiternummer) ein!
--ADD CONSTRAINT sekundärschlüssel
-- b) Versuchen Sie danach diesen neuen Datensatz in Mitarbeiter zu löschen.
-- c) Ändern Sie diese neue Leiternummer in *Projekt* in eine andere, in der Tabelle *Mitarbeiter* vorhandene *MitID*. Wiederholen Sie das Ändern und Löschen der MitID (aus Aufgabe a) in 
*Mitarbeiter*.
-- d) Versuchen Sie, in *Projekt* einen Datensatz mit einer nicht existierenden Mitarbeiternummer einzutragen.
-- e) Versuchen Sie, in *ProjektÜ einen Datensatz mit Projektleiter-Nr. = NULL einzutragen.
-- *Hinweis*: Die Eigenschaft "NULL-Werte erlaubt" in einer Tabelle *Projekt* bedeutet inhaltlich, dass ein NULL-Wert steht, wenn für ein neues Projekt der *Leiter* noch nicht bestimmt ist oder das ein Projekt fertig gestellt und der Leiter von diesem Projekt entbunden ist.

-- Teil IV: Sicherung der referentiellen bzw.  semantischen Integrität - Prouedurale Lösung
-- **Allgemeine Bemerkungen zur Aufgabenstellung für die TRIGGER**
-- 