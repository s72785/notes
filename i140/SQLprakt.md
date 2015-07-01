## windows

0. Desktop
1. SQL Server Tools
2. SQL-Server Mgmt Studio
Anmeldung:
Server:141.56.2.45
SQL Server Auth
name: s72785
pwd: s72785
db: iw14s72785

## linux

/opt/sql/sqldeveloper/sqldeveloper.sh
oder
/u/opt/sql/sqldeveloper/sqldeveloper.sh
Warnung akzeptieren
Extras / Voreinstellungen / Datenbanken / JDBC-Treiber
Eintrag hinzufügen: /u/opt/sql/jdbc
Verbindung anlegen

# Übungsaufgaben für Praktikum SQL

--default db ändern
Exec sp_defaultdb @loginame='s72785', @defdb='iw14s72785'
--db auswählen
use iw14s72785
-- table erstellen
CREATE TABLE testen ( col1 char(10) )
-- table löschen
DROP TABLE "testen" 
--1.1
CREATE TABLE Mitarbeiter(
	MitID		char(3) NOT NULL PRIMARY KEY,
	Nachname	varchar(20) NOT NULL,
	Vorname		varchar(20),
	Ort		varchar(30) NOT NULL,
	Gebdat		date NOT NULL,
	Beruf		varchar(15) NOT NULL,
	Telnr		varchar(20)--,
);
CREATE TABLE Projekt (
        ProNr           int NOT NULL PRIMARY KEY,
        ProName         varchar(20) NOT NULL,
        ProOrt          varchar(30) NOT NULL,
        Beschreibung    varchar(30),
        Aufwand         int NOT NULL,
        Leiter          varchar(20)--,
--      PRIMARY KEY (ProNr)
);
CREATE TABLE Zuordnung (
        MitID           char(3) NOT NULL,
        ProNr           int NOT NULL,
        Istanteil       float NOT NULL,
        CONSTRAINT pk_MitProj PRIMARY KEY (MitID, ProNr),
        CONSTRAINT MitID FOREIGN KEY REFERENCES Mitarbeiter(MitID),
        CONSTRAINT ProNr FOREIGN KEY REFERENCES Projekt(ProNr)
);
--1.3
--1.3
ALTER TABLE Zuordnung ADD Plananteil	float NOT NULL;--sicherstelle, dass Werte einegetragen werden mit NOT NULL
--1.4
-- nur Ausgabe
SELECT * FROM depotN.dbo.quelleMitarbeiter;
-- mit Einfügen
INSERT INTO Mitarbeiter
  SELECT * FROM depotN.dbo.quelleMitarbeiter;
SELECT * FROM depotN.dbo.quelleProjekt;
SELECT ProNr, ProName, ProOrt, Aufwand, Leiter FROM depotN.dbo.quelleProjekt;
INSERT INTO Projekt (ProNr, ProName, ProOrt, Aufwand, Leiter)
  SELECT ProNr, ProName, ProOrt, Aufwand, Leiter FROM depotN.dbo.quelleProjekt;
INSERT INTO Zuordnung
  SELECT * FROM depotN.dbo.quelleZuordnung;
--1.5
-- Mitarbeiter    Zuordnung     Projekt
-- |-[MitID]------|-[MitID]     |-ProName
--                |-[ProID]-----|-[ProID]
-- Zusätzliche Beziehungen
-- Mitarbeiter.[MitID]--cm:cm--Projekt.Leiter
-- Mitarbeiter.Ort--cm:cm--ProOrt

--1.6 - hier ist keiner neben mir, nur davor...
INSERT INTO Mitarbeiter (MitID, Nachname, Vorname, Ort, Gebdat, Beruf) VALUES('200', 'Nachbar', 'Linker', 'Dresden', '1990-09-30', 'Praktikant');
INSERT INTO Mitarbeiter (MitID, Nachname, Vorname, Ort, Gebdat, Beruf) VALUES('201', 'Nachbar', 'Rechter', 'Dresden', '1980-12-24', 'Praktikant');

--1.7
-- index erstellen
CREATE INDEX index_beruf ON Mitarbeiter (Beruf);
-- index über zwei spalten mit sicherstellung der eindeutigkeit
CREATE UNIQUE INDEX index_mitarbeiter ON Mitarbeiter (Nachname, Vorname);
-- löschen eines index
DROP INDEX Mitarbeiter.index_beruf;

--1.8
-- erst Abfrage testen
SELECT MitID, Nachname, Vorname, Ort, Beruf FROM Mitarbeiter WHERE Beruf != 'Vertreter';
-- dann View davon erstellen
--CREATE VIEW vOrtBeruf AS
--  SELECT MitID, Nachname, Vorname, Ort, Beruf FROM Mitarbeiter WHERE Beruf != 'Vertreter';
SELECT * FROM vOrtBeruf;

--1.9
-- Abfrage zusammenbauen
SELECT m.MitID, Nachname, ProName AS Projektname, Plananteil
  FROM Mitarbeiter m, Zuordnung z, Projekt p
  WHERE m.MitID = z.MitID
    AND z.ProNr=p.ProNr;
-- View erstellen
--CREATE VIEW vPaz AS
--  SELECT m.MitID, Nachname, ProName AS Projektname, Plananteil
--FROM Mitarbeiter m, Zuordnung z, Projekt p
--WHERE m.MitID = z.MitID
--      AND z.ProNr=p.ProNr;
SELECT * FROM vPaz;


--1.10
-- sieht so aus als ob das hinhaut...

--2.1
--a) Mitarbeitrer, die in Dresden wohnen
SELECT * FROM Mitarbeiter WHERE Ort='Dresden';
--b) Mitarbieter, die nicht in Dresden wohnen
SELECT * FROM Mitarbeiter WHERE Ort!='Dresden';
--c) Projekte, deren Namen mit "R" beginnen
SELECT * FROM Projekt WHERE ProName LIKE 'R%';
--d) Mitarbeiter mit Diplom aus Radebeul, sortiert nach Nachname
SELECT * FROM Mitarbeiter WHERE Ort='Radebeul' AND Beruf LIKE 'Dipl.-%' ORDER BY Nachname ASC;
--e) Alle Daten aus Zurodnung bei denen Istanteil oder Plananteil größer 0.7 sind
SELECT * FROM Zuordnung WHERE Istanteil>0.7 OR Plananteil>0.7;
--f) Alle Projekte ohne Leiter
SELECT * FROM Projekt WHERE Leiter IS NULL;

--2.2 Abfragen mit Aggregatfunktionen
--a) Anzahl der Mitarbeiter
SELECT COUNT(MitID) FROM Mitarbeiter;
--b) Anzahl der am gleichen Ort wohnenden Mitarbeiter
SELECT Ort,COUNT(MitID) FROM Mitarbeiter GROUP BY Ort;
--c) Summe der Istanteile für Projekt 31
SELECT SUM(Istanteil) FROM Zuordnung WHERE ProNr=31;
--d) Differenz Plan-Ist je Mitarbeiter
--mal schauen
SELECT MitID,(Plananteil-Istanteil) AS Differenz FROM Zuordnung;
--und aufsummiert
SELECT MitID,SUM(Plananteil-Istanteil) AS GesDifferenz FROM Zuordnung GROUP BY MitID;
--e) Ausgabe: Maximaler Aufwand, Summe und Anzahl aller Projekte
SELECT MAX(Aufwand) as 'maximaler Aufwand', SUM(Aufwand) as Summe, COUNT(Aufwand) AS Anzahl FROM Projekt;

--2.3Abfragen mit Datumsfunktionen
--a) je Mitarbeiter: Namename, Vorname, Alter
SELECT Nachname, Vorname, DATEDIFF(yyyy, Gebdat, GETDATE()) 'Alter' FROM Mitarbeiter;
--b) Mitarbeiter, die älter als 30 sind
--Alter in Zahl konvertieren
SELECT * FROM Mitarbeiter WHERE CONVERT(INT, DATEDIFF(yyyy, Gebdat, GETDATE())) > 30;
--c) Mitarbieter die im Mai Geburtstag haben
SELECT Nachname, Vorname, Gebdat AS 'Geburtsdatum' FROM Mitarbeiter WHERE FORMAT(Gebdat, 'MM') = '05';
--d) GB-Kalender
SELECT Nachname, Vorname, Gebdat AS 'Geburtsdatum' FROM Mitarbeiter ORDER BY FORMAT(Gebdat, 'MMdd') ASC;
--e) Durchschnittalter der Mitarbeiter -> Summe/Anzahl
SELECT SUM(CONVERT(INT, DATEDIFF(yyyy, Gebdat, GETDATE())))/COUNT(MitID) AS 'Durschnitts-Alter' FROM Mitarbeiter;
--f) Ort und Durchschnittsalter der Einwohner je Ort
SELECT Ort, (SUM(CONVERT(INT, DATEDIFF(yyyy, Gebdat, GETDATE())))/COUNT(MitID)) AS 'Durschnitts-Alter' FROM Mitarbeiter GROUP BY Ort;

--2.4 Abfragen über mehrere Tabellen
--je als [INNER] JOIN und ohne
--a) je Mitarbeiter ProjNr und Istanteil, geordnet nach Mitarbeiternummer
-- erstmal alles
SELECT * FROM Mitarbeiter m, Zuordnung z, Projekt p WHERE m.MitID=z.MitID AND z.ProNr=p.ProNr;
-- und nun das was gefragt war:
SELECT m.MitID, m.Nachname, p.ProNr, z.Istanteil FROM Mitarbeiter m, Zuordnung z, Projekt p WHERE m.MitID=z.MitID AND z.ProNr=p.ProNr ORDER BY m.MitID;
-- nochmal mit JOIN...
SELECT m.MitID, m.Nachname, p.ProNr, z.Istanteil FROM Mitarbeiter m JOIN Zuordnung z ON m.MitID=z.MitID JOIN Projekt p ON z.ProNr=p.ProNr ORDER BY m.MitID;
--b) 
SELECT p.ProNr, p.ProName, m.Nachname, m.Vorname, m.Beruf FROM Mitarbeiter m, Zuordnung z, Projekt p WHERE m.MitID=z.MitID AND z.ProNr=p.ProNr ORDER BY p.ProNr;
SELECT p.ProNr, p.ProName, m.Nachname, m.Vorname, m.Beruf FROM Mitarbeiter m JOIN Zuordnung z ON m.MitID=z.MitID JOIN Projekt p ON z.ProNr=p.ProNr ORDER BY p.ProNr;
--c) 
SELECT m.MitID, m.Nachname, p.ProName AS Projektname, z.Plananteil FROM Mitarbeiter m, Zuordnung z, Projekt p WHERE m.MitID=z.MitID AND z.ProNr=p.ProNr AND p.ProName='Reportgenerator';
SELECT m.MitID, m.Nachname, p.ProName AS Projektname, z.Plananteil FROM Mitarbeiter m JOIN Zuordnung z ON m.MitID=z.MitID JOIN Projekt p ON z.ProNr=p.ProNr WHERE p.ProName='Reportgenerator';
--d) 
SELECT m.MitID, m.Nachname, m.Vorname, p.ProNr, p.ProName, p.Leiter FROM Projekt p, Mitarbeiter m WHERE p.Leiter=m.Nachname ;
SELECT m.MitID, m.Nachname, m.Vorname, p.ProNr, p.ProName, p.Leiter FROM Projekt p JOIN Mitarbeiter m ON p.Leiter=m.Nachname ;
--die Zuordnung ist ungenau, da die Datenbasis nicht normalisiert und sauber mit Fremdschlüsseln (MitID) verkettet ist weiß man nicht Welcher Hase hier Leiter ist
--e) Alle Projekte...
--SELECT p.*,z.MitID,z.Plananteil FROM Projekt p, Zuordnung z WHERE p.ProNr=z.ProNr OR true;
SELECT p.*,z.MitID,z.Plananteil FROM Projekt p LEFT OUTER JOIN Zuordnung z ON p.ProNr=z.ProNr ORDER BY z.ProNr, z.MitID;

--2.5 Abfragen mit Unterabfragen
--a) 
--erstmal alle Leiter
SELECT Leiter FROM Projekt WHERE NOT Leiter IS NULL;
--jetzt alle Mitarbeiter die keine Sind
SELECT * FROM Mitarbeiter WHERE Nachname NOT IN ( SELECT Leiter FROM Projekt WHERE NOT Leiter IS NULL);
--b) 
--jüngster
SELECT MIN(Gebdat) FROM Mitarbeiter WHERE Beruf LIKE '%Dipl.-Ing.%'; 
SELECT * FROM Mitarbeiter WHERE Gebdat = (SELECT MIN(Gebdat) FROM Mitarbeiter WHERE Beruf LIKE '%Dipl.-Ing.%');
--c)
SELECT MitID, MAX(Plananteil) AS Plananteil, ProNr FROM Zuordnung GROUP BY MitID, Plananteil, ProNr;
SELECT MitID, Plananteil, ProNr FROM (SELECT MitID, MAX(Plananteil) AS Plananteil, ProNr FROM Zuordnung GROUP BY MitID, Plananteil, ProNr) a WHERE MitID > 0;

--2.6 Having
--a) Alle MA bei denen der Istanteil in summe über 0.7 liegt
SELECT m.MitID,SUM(Istanteil) AS 'Summe Istanteil' FROM Mitarbeiter m , Zuordnung z WHERE z.MitID=m.MitID GROUP BY m.MitID HAVING  SUM(Istanteil)>0.7;
--b) Projekte bei denen der Plananteil unter dem Aufwand liegt
SELECT p.ProName,p.Aufwand,SUM(Plananteil) AS 'Summe Plananteil' FROM Projekt p, Zuordnung z WHERE p.ProNr=z.ProNr GROUP BY p.Aufwand, p.ProName HAVING p.Aufwand > SUM(z.Plananteil);

--2.7 Datenmanipulation
--a)
--gucken: Fuchs->Bau, Elster->Ast
SELECT * FROM Mitarbeiter WHERE Nachname='Fuchs' OR Nachname='Elster';
--ändern
UPDATE Mitarbeiter SET Ort = 'Dresden' WHERE Nachname='Fuchs' OR Nachname='Elster';
--gucken: Fuchs->Dresden, Elster->Dresden :D
SELECT * FROM Mitarbeiter WHERE Nachname='Fuchs' OR Nachname='Elster';
--b)
SELECT * FROM Mitarbeiter WHERE Nachname='Fuchs';
UPDATE Mitarbeiter SET Beruf = 'Dipl.Ing.' WHERE Nachname='Fuchs';
--c)
SELECT * FROM Mitarbeiter ;
DELETE FROM Mitarbeiter WHERE Beruf='Industriekauf.';--1 Zeile gelöscht
--d) alle MA löschen deren summierter Plananteil unter 0.3 liegt
SELECT * FROM Mitarbeiter ;
SELECT MitID FROM Zuordnung GROUP BY MitID HAVING SUM(Plananteil)<0.3; --Treffer 1: 101
DELETE FROM Mitarbeiter WHERE MitID IN (SELECT MitID FROM Zuordnung GROUP BY MitID HAVING SUM(Plananteil)<0.3);--y Zeile(n) gelöscht

--2.8 Relationale Algebra
--a) Equijoin (also mit JOIN .. ON Attribut1 = Attribut2)
SELECT m.*,p.* FROM Mitarbeiter m JOIN Projekt p ON m.Nachname=p.Leiter;
--b) Natural Join ( NATURAL JOIN hat SQLServer nicht, ohne ON / USING)
--SELECT * FROM Mitarbeiter NATURAL JOIN Projekt;
--c) kartesisches Produkt
SELECT * FROM Mitarbeiter, Projekt;
--d) Differenz
--einzeln
SELECT m.Ort FROM Mitarbeiter m;
SELECT p.ProOrt FROM Projekt p;
-- Orte ohne Projekte
SELECT m.Ort FROM Mitarbeiter m
EXCEPT
SELECT p.ProOrt FROM Projekt p;
--e) Orte mit Projekten
SELECT m.Ort FROM Mitarbeiter m
INTERSECT
SELECT p.ProOrt FROM Projekt p;
--f) Doppelungen aufheben
SELECT m.Ort FROM Mitarbeiter m
UNION
SELECT p.ProOrt FROM Projekt p;

--2.9 Abfragen mit CASE
SELECT CONVERT(INT,FORMAT(Gebdat,'MMdd') ) -  CONVERT(INT,FORMAT(GETDATE(),'MMdd')) FROM Mitarbeiter;
SELECT Nachname, Vorname, DATEDIFF(yyyy, Gebdat, GETDATE()) AS 'Alter', Vollendet =
  CASE 
    WHEN (CONVERT(INT,FORMAT(Gebdat,'MMdd') ) -  CONVERT(INT,FORMAT(GETDATE(),'MMdd')))>0 THEN 'J'
    ELSE 'N'
  END
FROM Mitarbeiter;


--3.1 Anzeige der Mitarbeiternamen und Projektnamen
--anfrage basteln
SELECT m.Nachname,p.ProName FROM Mitarbeiter m, Zuordnung z, Projekt p WHERE m.MitID=z.MitID AND z.ProNr=p.ProNr;
--in Prozedur verpacken
--CREATE PROCEDURE show_ma_pro
--AS
--BEGIN 
--  SELECT m.Nachname,p.ProName
--    FROM Mitarbeiter m, Zuordnung z, Projekt p
--    WHERE m.MitID=z.MitID
--      AND z.ProNr=p.ProNr
--END;
EXEC show_ma_pro;

--3.2
SELECT m.Nachname, m.Vorname, m.Beruf, p.ProName FROM Projekt p, Zuordnung z, Mitarbeiter m WHERE p.ProNr=z.ProNr AND z.MitID=m.MitID AND p.ProNr=31;
SELECT * FROM sys.objects WHERE type='P';
--IF NOT EXISTS (SELECT name FROM sys.objects WHERE type = 'P' AND name = 'show_ma_pro_nr' )
--BEGIN
--
--CREATE PROCEDURE show_ma_pro_nr @Nr INT
--AS
--BEGIN 
--   SELECT m.Nachname, m.Vorname, m.Beruf, p.ProName
--      FROM Projekt p, Zuordnung z, Mitarbeiter m
--      WHERE p.ProNr=z.ProNr AND z.MitID=m.MitID AND p.ProNr=@Nr
--END
--
--END
EXEC show_ma_pro_nr @Nr = 31;

--3.3
-- Alte Kopie löschen
DROP TABLE Mitarbeiter_copy;
-- Kopie zum Arbeiten anlegen
SELECT * INTO Mitarbeiter_copy FROM Mitarbeiter;
-- lange Version:
CREATE TABLE Mitarbeiter_copy(
	MitID		char(3) NOT NULL PRIMARY KEY,
	Nachname	varchar(20) NOT NULL,
	Vorname		varchar(20),
	Ort		varchar(30) NOT NULL,
	Gebdat		date NOT NULL,
	Beruf		varchar(15) NOT NULL,
	Telnr		varchar(20)--,
);
INSERT INTO Mitarbeiter_copy
  SELECT * FROM Mitarbeiter;

-- Alter ermitteln
--SELECT MitID, Gebdat, DATEDIFF(yyyy, Gebdat, GETDATE()) 'Alter' FROM Mitarbeiter_copy;
-- Jahr verringern
--UPDATE Mitarbeiter_copy SET Gebdat = DATEADD(year,-1,Gebdat) WHERE MitID=103;
-- Mitarbeiter in Ruhestand schicken
--DELETE FROM Mitarbeiter_copy WHERE MitID=103
-- für die iteration
--DECLARE @Current  int
--       ,@End      int
-- initialisierung
--SET @Current=0
--SET @End=@Zyklen
-- Schleife
--WHILE @Current<@End
--BEGIN
-- Abbruch auf weiterer Bedingung
--  IF result_true_false
--    BREAK;--CONTINUE geht auch
--END

--DROP PROCEDURE verrentnen;

--CREATE PROCEDURE verrentnen @zyklus INT 
--AS
--BEGIN
--WHILE (
--( select COUNT(*) from Mitarbeiter_copy) > 0
--and @zyklus > 0
--)
--BEGIN
--		UPDATE Mitarbeiter_copy
--		SET Gebdat=DATEADD(year,-1,Gebdat)
--		SELECT * FROM Mitarbeiter_copy
--		DELETE FROM Mitarbeiter_copy
--			WHERE DATEDIFF(year, Gebdat, GETDATE())>=60
--		SELECT @zyklus = @zyklus - 1
-- 1 Sekunde warten um aktualaisierung durchlaufen zu lassen
--		WAITFOR DELAY '00:00:01'
--		IF 0=(SELECT COUNT(*) FROM Mitarbeiter_copy)
--			PRINT 'Keiner mehr da!'
--		ELSE
--			PRINT 'Noch läuft der Laden!';
--END
--END
EXEC verrentnen @zyklus = 1;

--3.4
--a)
--DECLARE @Nr INT;--SET @Nr=103;
--DECLARE @out VARCHAR(200);
--SELECT INTO (@out) m.Nachname,m.Vorname,m.Beruf FROM Mitarbeiter m WHERE MitID=@Nr;

--CREATE PROCEDURE sp_Test()
--AS
--BEGIN
--
--  DECLARE @colA nvarchar(10)
--  DECLARE @colB nvarchar(10)
--  DECLARE @MyCursor CURSOR
--
--  SET @MyCursor = CURSOR FAST_FORWARD
--  FOR
--    Select colA,colB
--      From tableA
--
--  OPEN @MyCursor
--  FETCH NEXT FROM @MyCursor
--    INTO @ColA,@ColB
--
--  WHILE @@FETCH_STATUS = 0
--  BEGIN
--    PRINT @ColA
--    PRINT @ColB
--    FETCH NEXT FROM @MyCursor
--      INTO @ColA,@ColB
--  END
--
--  CLOSE @MyCursor
--  DEALLOCATE @MyCursor
--END

--DROP PROCEDURE CursorProz;
--CREATE PROCEDURE CursorProz @Mitnr CHAR(3)
--AS
--BEGIN
--	IF @Mitnr NOT IN (SELECT MitID FROM Mitarbeiter)
--		PRINT 'Mitarbeiter nicht vorhanden!'
--	ELSE
--		BEGIN
--			DECLARE	@Nachn CHAR(10),
--					@Vorn CHAR(10),
--					@Beruf Char(15)
--			SELECT @Nachn = m.Nachname, @Vorn = m.Vorname, @Beruf = m.Beruf 
--				FROM Mitarbeiter m
--				WHERE m.MitID = @Mitnr
--			PRINT 'Nachname:'+ @Nachn 
--			PRINT 'Vorname:	'+ @Vorn
--			PRINT 'Beruf:	'+ @Beruf
            
--			IF @Mitnr NOT IN (SELECT m.MitID FROM Mitarbeiter m, Zuordnung z WHERE z.MitID=m.MitID)
--				PRINT 'Mitarbeiter arbeitet an keinem Projekt!'
--			ELSE
--				DECLARE @Projektbezeichnung CHAR(15),
--						@Plananteil float,
--						@Istanteil float,
--						@Abweichung float
--               DECLARE B Cursor FOR
--					SELECT p.Proname, z.Plananteil, z.Istanteil, z.Plananteil - z.Istanteil 
--						FROM Projekt p, Zuordnung z 
--						WHERE p.Pronr = z.Pronr AND z.MitID = @Mitnr
--               OPEN B
--               FETCH B INTO @Projektbezeichnung, @Plananteil, @Istanteil, @Abweichung
--				WHILE ( @@fetch_status = 0 )
--					BEGIN
--						PRINT 'Projektbezeichnung:	'+ @Projektbezeichnung
--						PRINT 'Plananteil:			'+ CONVERT(CHAR(10),@Plananteil)
--						PRINT 'Istanteil:			'+ CONVERT(CHAR(10),@Istanteil)
--						PRINT 'Abweichung:			'+ CONVERT(CHAR(10),@Abweichung)
--						FETCH B into @Projektbezeichnung, @Plananteil, @Istanteil, @Abweichung
--					END
--				CLOSE B
--				DECLARE	@SummePlan float,
--						@SummeIst float,
--						@SummeAbweichung float
--				SELECT @SummePlan = sum(z.Plananteil), @SummeIst=sum(z.Istanteil), @SummeAbweichung = SUM(z.Plananteil) - SUM(z.Istanteil) 
--					FROM Projekt p, Zuordnung z 
--					WHERE p.Pronr = z.Pronr AND z.MitID = @Mitnr
--				PRINT 'Summe Plananteil:	' + CONVERT(CHAR(10),@SummePlan )
--				PRINT 'Summe Istanteil:	' + CONVERT(CHAR(10),@SummeIst)
--				PRINT 'Summe Abweichung:	' + CONVERT(CHAR(10),@SummeAbweichung)

--				PRINT 'Mitarbeiter ... '
--				IF (@SummePlan>1)
--					PRINT 'ist ueberfordert'
--				ELSE
--					BEGIN                   
--						IF ( @SummeAbweichung = 0 )
--							PRINT 'ist optimal ausgelastet'
--						IF (@SummeAbweichung < 0 OR @SummeIst > 1)
--							PRINT 'ist ueberlastet'
--						IF (@SummeAbweichung > 0 OR @SummeIst = 0)
--							PRINT 'hat noch Reserven'
--					END             
--		END   
--		DEALLOCATE B
--END
EXEC CursorProz @Mitnr = '103';

--4.
--a)
SELECT ProNr,COUNT(MitID) AS "Anzahl" FROM Zuordnung GROUP BY ProNr;
--b)
SELECT COUNT(DISTINCT ProNr) FROM Zuordnung ;
-- wenn voriges nicht unterstützt
SELECT COUNT(ProNr) FROM (SELECT DISTINCT ProNr FROM Zuordnung) t;
--c)
SELECT * FROM Mitarbeiter
	WHERE	Ort IN ('Dresden','Radebeul','Freital')
			AND 30<DATEDIFF(yyyy, Gebdat, GETDATE())
			AND DATEDIFF(yyyy, Gebdat, GETDATE())<62;
--d)
--SELECT m.MitID,m.Nachname,COUNT(z.ProNr) AS "Anzahl" FROM Mitarbeiter m JOIN Zuordnung z ON z.MitID=m.MitID GROUP BY z.MitID,p.ProNr HAVING COUNT(p.ProNr)>1;
