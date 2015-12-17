5.--
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

--sysprocedures?! wie kann man tabellen-details dann z.B. in SQLDeveloper oder mit ODBC abfragen?
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
CREATE FUNCTION AlterErmitteln ( @datum date )
	RETURNS tinyint
	AS
	BEGIN
			DECLARE @Alter tinyint
			SELECT @Alter = DATEDIFF(yyyy, @datum, GETDATE())
      IF (
				CONVERT(tinyint, FORMAT(@datum, 'dd')) > CONVERT(tinyint,FORMAT(GETDATE(),'dd'))
				AND CONVERT(tinyint, FORMAT(@datum, 'MM')) >= CONVERT(tinyint,FORMAT(GETDATE(),'MM'))
        AND CONVERT(int, FORMAT(@datum, 'yy')) > CONVERT(int,FORMAT(GETDATE(),'yy'))
			) 
  			SELECT @Alter = @Alter + 1
   		RETURN @Alter
	END;
SELECT MitID, Gebdat, dbo.AlterErmitteln(Gebdat) AS age FROM Mitarbeiter
-- test
--dbo.AlterErmitteln('1980-11-10'), dbo.AlterErmitteln('1980-11-30')
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
SELECT * FROM dbo.AuslastungTable(0.8);
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
ALTER TABLE Projekt ADD CONSTRAINT FK_MitarbeiterID FOREIGN KEY (LeiterMitID) REFERENCES Mitarbeiter(MitID);
--ALTER TABLE Projekt DROP CONSTRAINT FK_MitarbeiterID;
-- a) Geben Sie in die Tabellen *Mitarbeiter* und *Projekt* je einen neuen Datensatz mit gleicher *MitID* (in Projekt ist dies die Leiternummer) ein!
INSERT INTO Mitarbeiter(MitID, Nachname, Ort, Gebdat, Beruf) VALUES('234','Nord','Pol','1984-11-05','Spezialist');
INSERT INTO Projekt(ProNr,ProName,ProOrt,Aufwand,LeiterMitID) VALUES('55','DummyProjekt','Online',0,'234');
-- b) Versuchen Sie danach diesen neuen Datensatz in Mitarbeiter zu löschen.
DELETE Mitarbeiter WHERE MitID='234';--Fehlermeldung ist gewollt, alles OK
-- c) Ändern Sie diese neue Leiternummer {*LeiterMitID*} in *Projekt* in eine andere, in der Tabelle *Mitarbeiter* vorhandene *MitID*.
UPDATE Projekt SET LeiterMitID='101' WHERE ProNr='55';
--    Wiederholen Sie das Ändern und Löschen der MitID (aus Aufgabe a) in *Mitarbeiter*.
DELETE Mitarbeiter WHERE MitID='234';
-- d) Versuchen Sie, in *Projekt* einen Datensatz mit einer nicht existierenden Mitarbeiternummer einzutragen.
INSERT INTO Projekt(ProNr,ProName,ProOrt,Aufwand,LeiterMitID) VALUES('56','DummyProjekt2','Online',0,'234');--Fehlermeldung gewollt
-- e) Versuchen Sie, in *Projekt* einen Datensatz mit Projektleiter-Nr. = NULL einzutragen.
INSERT INTO Projekt(ProNr,ProName,ProOrt,Aufwand,LeiterMitID) VALUES('56','DummyProjekt2','Online',0,NULL);
-- *Hinweis*: Die Eigenschaft "NULL-Werte erlaubt" in einer Tabelle *Projekt* bedeutet inhaltlich, dass ein NULL-Wert steht, wenn für ein neues Projekt der *Leiter* noch nicht bestimmt ist oder das ein Projekt fertig gestellt und der Leiter von diesem Projekt entbunden ist.

-- Teil IV: Sicherung der referentiellen bzw.  semantischen Integrität - Prouedurale Lösung
-- **Allgemeine Bemerkungen zur Aufgabenstellung für die TRIGGER**
-- - Die Trigger sollen stets für das Einfügen, Löschen, Ändern mehrerer Datensätze funktionieren.
-- - Zeigen Sie die eingefügten, gelöschten oder veränderten Datensätze und bei Fehlern die fehlerhaften Datensätze an!
-- - In der Testphase sollten Sie mit den Kommandos `begin transaction|rollback transaction` den Urzustand Ihrer Tabellen erhalten.
-- - Mit sp_depends `[[Tabellenname] | [Triggername]]` können Sie die Abhängigkeiten prüfen.
-- - Überprüfen Sie stets Ihre Ergebnisse!
-- - Beachten Sie, dass jeweils nur ein Inert-, Update- udn Delete-Trigger je Tabelle existieren kann. Erweitern Sie deshalb ggf. bereits vorhandene Trigger.
-- **Beachten Sie im Folgenden für das Testen der Trigger alle Constraints (Bedingungen) auf einer Tabelle bzw. zwischen den Tabellen. KEINE dieser Bedingungen soll gelöscht werden.
--
-- **Hinweise für das Arbeiten mit dem SQL Developer**
-- Auf Grund eines Problems mit der Kommunikation vom Client, JDBC-Treiber und Datenbank setzt der SQL-Developer nach jedem Befehl ein Autocommit. Um eine Transaktion zu starten, müssen Sie folgende Vorgehensweise nutzen:
-- /*sqldev:stmt*/begin transaction
-- select / update etc.
-- /*sqldev:stmt*/rollback / commit;
-- 
-- 4. Trigger zur Sicherung der Semantischen Integrität
-- 4.1 Sichern Sie ab, dass bei entsprechenden Datenmanipulationen die Summe der geplanten Projekttätigkeiten (Plananteil) für einen Mitarbeiter 1.0 nicht überschreitet.
SELECT SUM(z.Plananteil) FROM Zuordnung z GROUP BY z.MitID HAVING SUM(z.Plananteil) > 1.0
/*sqldev:stmt*/begin transaction
--CREATE
ALTER TRIGGER TR_MaxPlanateil
ON dbo.Zuordnung
AFTER INSERT, UPDATE 
AS --BEGIN
  --4.1
  IF EXISTS (SELECT COUNT(z.Plananteil) FROM Zuordnung z GROUP BY z.MitID HAVING z.Plananteil > 1.0) 
    ROLLBACK --TRANSACTION
    PRINT 'Test: Ausgabe nach Rollback'--test ob Ausgabe noch erfolgt
--END
/*sqldev:stmt*/rollback;-- / commit;
-- Testen Sie indem Sie
-- a) für alle Mitarbeiter des Projektes 31 den Plananteil um 0.3 erhöhen.
SELECT * FROM Zuordnung WHERE ProNr = 31;
UPDATE Zuordnung SET Plananteil=Plananteil + 0.3 WHERE ProNr = 31;
UPDATE Zuordnung SET Plananteil=Plananteil - 0.3 WHERE ProNr = 31;--zum Testen wieder vermindern
-- b) Den Plananteil für den Mitarbeiter 105 um 0.4 erhöhen.
SELECT * FROM Zuordnung WHERE MitID = '105';
UPDATE Zuordnung SET Plananteil = Plananteil + 0.4 WHERE MitID = '105';
-- 4.2 Stellen Sie sicher, dass mit dem Löschen des letzten Datensatzes zu ein und demselben Projekt aus der Tabelle *Zuordnung* das Projekt tatsächlich als erledigt gekennzeichnet wird.
---    (Kein Projektleiter)
-- Beachten Sie, dass es auch möglich ist, Projektnummern zu ändern.
SELECT COUNT(z.Plananteil) FROM Zuordnung z GROUP BY z.Plananteil HAVING z.Plananteil <= 0
/*sqldev:stmt*/begin transaction
--CREATE
ALTER
TRIGGER TR_d
ON dbo.Zuordnung
AFTER DELETE
AS --BEGIN
  --4.2
  IF EXISTS (SELECT COUNT(z.Plananteil) FROM Zuordnung z GROUP BY z.Plananteil HAVING z.Plananteil <= 0)
    ROLLBACK
    --UPDATE Projekt SET LeiterMitID=NULL WHERE  AND ProNr IN (SELECT deleted.ProNr FROM deleted)
/*sqldev:stmt*/rollback;-- / commit;

--SELECT * FROM Projekt
CREATE TRIGGER TR_delete ON Zuordnung
AFTER DELETE
AS BEGIN
	    PRINT 'Folgende Projekte Wurden in der Tabelle Projekt als abgeschlossen markiert.'
	    SELECT ProNr FROM Projekt
			WHERE Projekt.ProNr NOT IN (SELECT DISTINCT ProNr FROM Zuordnung)
	    UPDATE Projekt SET LeiterMitID = NULL 
			WHERE Projekt.ProNr NOT IN (SELECT DISTINCT ProNr FROM Zuordnung)
--	    RETURN
	END

-- Testen Sie den Trigger indem Sie
-- a) nacheinander die Mitarbeiter zu Projekt 36 löschen.
-- b) alle Mitarbeiter des Projektes 37 in das Projekt 35 versetzen.
-- 5 Trigger zur Protokollierung von Datenänderungen und zum Kaskadierenden Löschen
-- Jede Änderung des *Berufes - und nur des Berufes -* eines Mitarbeiters soll mit Hilfe eines Triggers mitprotokolliert werden.  Es ist zunächst eine Tabelle aufzubauen, in der bei jeder UPDATE-Operation je ein Datensatz mit den Informationen zur Mitarbeiternummer, der Eintragung im Feld *Beruf* vor und nach der Änderung generiert wird.
-- Zusätzlich soll der Nutzer sowie Datum und Uhrzeit der Änderung erfasst werden. (Nutzen Sie dazu die Funktionen *user_name()* und *getdate()*).
--
-- 5.1 Richten Sie die Protokolltabelle in folgender Form ein: *Tabelle Bprotokoll*
-- MitID   | Nutzer   | Zeit     | Beruf_alt | Beruf_neu
-- char(3) | char(16) | datetime |  char(15) | char(15)

-- OR ?CHANGE, mal im Skript nachlesen
CREATE
TABLE Bprotokoll
	(MitID char(3), Nutzer char(16), Zeit datetime, Beruf_alt char(15), Beruf_neu char(15));

-- 5.2 Erstellen Sie einen Trigger, der jede Änderung (UPDATE) des *Berufes* eines/mehrerer (d.h. für die gleichzeitige Änderung mehrerer Datensätze) in der Tabelle Bprotokoll protokolliert.
CREATE TRIGGER TR_Beruf_update ON Mitarbeiter
FOR UPDATE AS
	IF	(SELECT COUNT(*) FROM inserted 
		INNER JOIN deleted ON inserted.MitID = deleted.MitID
		WHERE inserted.Beruf NOT LIKE deleted.Beruf) > 0
	BEGIN
		INSERT INTO Bprotokoll (MitID, Nutzer, Zeit, Beruf_alt, Beruf_neu)
			SELECT inserted.MitID, user_name(), getdate(), deleted.Beruf, inserted.Beruf
				FROM inserted, deleted
				WHERE inserted.MitID = deleted.MitID
	END;

-- 5.3 Führen Sie anschließend eine Änderung des *Berufes* bei ausgewählten Mitarbeitern durch, Überprüfen Sie die Eintragungen in der *Protokolltabelle!*
SELECT * FROM Mitarbeiter;
UPDATE Mitarbeiter SET Beruf = 'Maler' WHERE Ort='Ast';
UPDATE Mitarbeiter SET Beruf = '' WHERE Beruf='';
SELECT * FROM Bprotokoll;

-- 5.4 Welche(s) Attribut(e) würden einen geeigneten Primärschlüssel bilden?
-- MitID + Zeit, Zeit ist weitgehend eindeutig

-- ## Kaskadierendes Löschen
-- 5.5 Erstellen Sie einen Trigger, der mit dem Löschen von Mitarbeitern (Tabelle *Mitarbeiter*) deren Datensätze aus der Tabelle *Bprotocoll* löscht.

CREATE TRIGGER TR_delete_MA ON Mitarbeiter
FOR DELETE AS
	BEGIN
		PRINT 'BProtokoll-Datensätze für folgende Mitarbeiter werde gelöscht:'
		SELECT deleted.MitID, deleted.Nachname FROM deleted
		DELETE FROM Bprotokoll WHERE MitID IN (SELECT MitID FROM deleted)
	END;

alter TRIGGER TR_Delete_MA
ON Mitarbeiter
after delete
AS
declare @tbl table (mitid char(3))
insert into @tbl select mitid from deleted
delete from bprotokoll where mitid in (select mitid from @tbl)



select * from mitarbeiter
  
update mitarbeiter set Beruf='Azubi' where mitid=210
   
select * from bprotokoll
  
delete from mitarbeiter where mitid=210



-- Testen Sie den Trigger, wählen Sie dazu geeignete Daten.
-- ## Trigger zur Protokollierung von Datenänderungen

-- 5.6 Fügen Sie in der Tabelle Bprotokoll eine Spalte hinzu, die als *Datensatzzähler* im Sinne eines *AUTOINCREMENT* dient, der beim Einfügen von Datensätzen automatisiert zählt und gleichzeitig Primärschlüssel ist.
-- *Hinweis:* in der SYBASE-SQL-Referenz als Funktionalität (*IDENTIFY*-Spalte mit zwingend erforderlichem Datentyp) beschrieben.
ALTER TABLE bprotokoll
ADD BID int IDENTITY(1,1 )NOT NULL

--alter table bprotokoll drop column BID

--delete from bprotokoll
    
--select * from bprotokoll

-- Überprüfen Sie Ihre Tabelle **Bprotokoll** bezüglich der Daten und Metadaten.
-- 5.7 Passen Sie gf. den Trigger aus 6.2(?) an und testen Sie erneut.
-- 5.8 Legen Sie eine weitere Tabelle **Bprotokoll2** (analog zu **Bprotokoll**) mit einer zusätzlichen Spalte *DSNo* vom Typ *int* mit Primärschlüsseleigenschaft an.
--CREATE
DROP TABLE Bprotokoll2;
CREATE TABLE Bprotokoll2
(
	MitID 		CHAR(3) 	NOT NULL,
	Nutzer 		CHAR(16) 	NOT NULL,
	Zeit		DATETIME 	NOT NULL,
	Beruf_alt 	CHAR(15) 	NULL,
	Beruf_neu 	CHAR(15) 	NULL,
  DSNo INT NOT NULL,--identity,
  PRIMARY KEY (DSNo)
);
-- In dieser Spalte soll eine im folgenden Trigger eigenständig berechnete Datensatzzählung erfolgen.
CREATE
trigger TR_DSNo_AI
  on bprotokoll2
  after insert
  as
    UPDATE bprotokoll2 SET dsno = dsno + 1

DELETE FROM BProtokoll2 WHERE DSNo=0;
SELECT * FROM bprotokoll2;
-- 5.9 Erstellen Sie einen Trigger, der wiederum automatisch jede Änderung (UPDATE) eines *Berufs* in der Tabelle *Mitarbeiter*
-- - zur Vereinfachung nur Änderungen eines einzelnen Datensatzes - in der Tabelle **Bprotkoll2** protokolliert und dabei die Spalte *DSNo* bei jedem neuen Datensatz berechnet.
-- (Kein Cursor erforderlich).
ALTER trigger TR_Aenderung_Beruf
  on Mitarbeiter
  for update,insert
  as
    if update(Beruf)
      insert into bprotokoll2 select d.mitid, user_name(), getdate(), d.Beruf, i.Beruf, '' FROM inserted i, deleted d

SELECT * FROM Mitarbeiter;
update mitarbeiter set Beruf='Student' where mitid=101

select * from bprotokoll2
-- Testen Sie den Trigger!
-- 5.10 Ändern Sie ihren Trigger 6.10(?) so, dass auch für meherere gleichzeitige Änderungen eines Berufes in der Tabelle Mitarbeiter in Bprotokoll2 protokolliert und die Spalte DSNo berechnet wird.
--alter trigger TR_Aenderung_Beruf
--  on Mitarbeiter
--  for update
--  as
--  if update(Beruf)
--    insert into bprotokoll2(mitid,nutzer,zeit,beruf_alt,beruf_neu,dsno) select d.mitid, user_name(), '', d.Beruf, i.Beruf, '' FROM inserted i, deleted d
--SELECT * FROM sys.triggers;
--DROP TRIGGER TR_delete_MA ON Mitarbeiter; 
ALTER TRIGGER TR_Aenderung_Beruf ON Mitarbeiter FOR UPDATE AS
  IF UPDATE(Beruf) BEGIN
      DECLARE @dMitID CHAR(3)
      DECLARE @dBeruf VARCHAR(1024)
      DECLARE @iBeruf VARCHAR(1024)
     
      DECLARE @cnt INT
      SET @cnt=1
      IF ( SELECT COUNT(DSNo) FROM bprotokoll2 ) = 0 -- (max() ) is null
          SELECT @cnt = 1
      ELSE
          SELECT @cnt = (SELECT MAX(DSNo) FROM bprotokoll2) + 1
      PRINT 'counter: ' + CONVERT(CHAR(10), @cnt)
      DECLARE cur CURSOR FOR
          SELECT d.MitID, d.Beruf, i.Beruf
            FROM deleted d, inserted i
            WHERE d.MitID = i.MitID

      OPEN cur
      FETCH cur INTO @dMitID, @dBeruf, @iBeruf

      IF ( SELECT COUNT(MitID) FROM inserted WHERE Beruf NOT IN (SELECT Beruf FROM deleted ) ) > 0
      BEGIN
          WHILE @@FETCH_STATUS = 0
           BEGIN
              INSERT INTO bprotokoll2 (MitID, Nutzer, Zeit, Beruf_alt, Beruf_neu, DSNo)
                VALUES( @dMitID, user_name(), getdate(), @dBeruf, @iBeruf, @cnt )
              SET @cnt = @cnt + 1
              FETCH cur INTO @dMitID, @dBeruf, @iBeruf
           END
      END
      CLOSE cur
      DEALLOCATE cur
END

SELECT * FROM Mitarbeiter;
SELECT * FROM Mitarbeiter WHERE Ort='Ast';
UPDATE Mitarbeiter SET Beruf='Bauer' WHERE Ort='Garten';
UPDATE Mitarbeiter SET Beruf='Student' WHERE Ort='Ast';
UPDATE Mitarbeiter SET Beruf='Neu' WHERE Beruf='Student';
UPDATE Mitarbeiter SET Beruf='Student' WHERE Beruf='Neu';
SELECT * FROM BProtokoll2;

SELECT * FROM bprotokoll2
DELETE BProtokoll2 WHERE DSNo=0;
-- Testen Sie diesen Trigger!


-- # 6.Aufgabenkomplex für das SQL-Praktikum - Zugriffsrechte
-- Hinweis für die Arbeit mit dem SQL-Developer ...
-- ## 1. Aufgaben zum Transaktionsprinzip - nur eigeneDB betreffend
-- ### 1.1. Beginnen Sie eine Transaktion, in der Sie dien Inhalt der Tabelle *Mitarbeiter* löschen und danach lesen.
/*sqldev:stmt*/begin transaction;
--DELETE FROM Mitarbeiter;
--SELECT * FROM Mitarbeiter;
-- ### 1.2. Setzen Sie die Transaktion zurück und lesen Sie *Mitarbeiter* erneut
/*sqldev:stmt*/rollback;
SELECT * FROM Mitarbeiter;
-- ### 1.3. Fassen Sie in Stichpunkten Ihre Erkenntnisse  zum ACID-Prinzip zusammen
-- - transactionen händeln die konsistenz
-- - funktioniert in einer DB mit SQL ganz gut, aber eher nicht verteilt
-- ## 2. Aufgaben und Zugriffsrechte
-- Lösen Sie die folgenden Aufgaben wechsleseitig mit einem Partner in Form eines Rolenspiels.
-- Protokollieren Sie Ihre Ergebnisse und Erkenntnisse ("Sie" als DBO -> user_a, "Partnmer" als Fremdnutzer -> user_b).
-- Nutzen Sie folgende System-Prozeduren, um Ihre Aktivitäten auf der Datenbank zu beobachten:
-- sp_who Gibt Informationen über alle aktuellen Server-Benutzer und -Prozesse bzw. über einen bestimmten Benutzer oder Prozess aus
-- sp_lock Gibt Informationen über Prozesse aus, die derzeit Sperren verursachen.
-- sp_helpuser Liefert Informationen über einen bestimmten Benutzer, eine Gruppe, ein Alias oder über alle Benutzer in der aktuellen Datenbank.
-- sp_helprotect Anzeige der Rechte eines Benutzers auf ein Objekt
-- 2.1 Lassen Sie ihren Partner als Anwender Ihrer Datenbank zu. Das Default-Schema soll extern heißen.
CREATE USER s72837 WITH DEFAULT_Schema=extern;
CREATE SCHEMA extern AUTHORIZATION s72837;--s72785
--CREATE GROUP extern WITH s72xxx;
--GRANT all TO extern;
sp_helpuser;-- extern;--s72785;--xxx;
--REVOKE all FROM extern;
--ALTER GROUP extern ADD USER s72xxx;
--ALTER GROUP extern DROP USER s72xxx;
-- 2.
-- 3.
use iw14s72837;
SELECT * FROM Mitarbeiter;
-- 4.
use iw14s72785;--837;
--REVOKE select FROM s72837;
GRANT select ON Mitarbeiter TO s72837;
-- 5.
--ok
-- 6.
sp_helpuser;
-- 7.
use iw14s72837;
/*sqldev:stmt*/begin transaction;
SELECT * FROM Mitarbeiter WITH (HOLDLOCK);
/*sqldev:stmt*/commit transaction;
-- sp_lock;--sagt uns nix sinnvolles
-- 8.
use iw14s72785;
SELECT * FROM Mitarbeiter;
--anderer user muss warten bis commit erfolgt
-- 9.
use iw14s72785;--837;
sp_lock ;
sp_who 59;
sp_helptext sp_who;
OBJECT_NAME();
-- 10.
--klappt gleich
-- 11.
use iw14s72785;
GRANT create table TO s72837;
-- 12.
use iw14s72837;
CREATE TABLE Mitarbeiter (MitID INT, Nachname CHAR(25), Vorname CHAR(25), GebDat DATE NULL, Ort CHAR(25), Beruf CHAR(25));
INSERT INTO Mitarbeiter (MitID, Nachname, Vorname, Ort, Beruf) VALUES ('111', 'Tester', 'John','Dresden','Student');
-- 13. 
SELECT * FROM extern.Mitarbeiter;--seine
SELECT * FROM Mitarbeiter;--meine
-- 14.
use iw14s72785;
sp_helprotect;
-- 15.
use iw14s72837;
DROP TABLE Mitarbeiter
-- 16.
use iw14s72785;
REVOKE create table, select FROM s72837;
DROP SCHEMA extern;
DROP USER s72837;
