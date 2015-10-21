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
SELECT p.ProNr, p.ProName, SUM(z.Istanteil) FROM Projekt p RIGHT JOIN Zuordnung z ON p.ProNr = z.ProNr GROUP BY p.ProNr,p.ProName ;
-- b) als UNION (Für eine "leere" Spalte muss ein (konstanter) DUMMY-Wert mit passendem Datentyp im SELECT-Statement gesetzt werden).
SELECT * FROM Projekt;
-- 5.5 Ermitteln Sie für ALLE `Mitarbeiter` die Reserven als Differenz zwischen 1 und ihrer Gesamtplananteile.
--     (Hinweis: Nutzen Sie die Erfahrung aus Aufgabe 5.4)
--bei windows mit sp_help, unter sqldeveloper nicht mehr als eine zeile
--sp_help Mitarbeiter
--andere möglichkeiten muss man erst suchen
--SELECT * FROM SYSOBJECTS ORDER BY name ASC;
--SELECT * FROM SYSISCOLS;
