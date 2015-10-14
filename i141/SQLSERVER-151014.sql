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
