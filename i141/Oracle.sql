
--Einstieg in Oracle SQL
--CREATE TABLE kunde (kunu INT, name CHAR(10));
SELECT * FROM sys.tab;
SELECT * FROM user_tables;
SELECT * FROM USER_CONSTRAINTS;--WHERE TABLE_NAME = 'KUNDE';
DROP TABLE kunde;
-- 0.

-- * Bauteil
--   + BauteilNr
--   + Name
--   + Einbauzeit
--   + Hersteller
--   + Baugruppe DEFAULT NULL --BauteilNr/
-- * Hersteller
--   + HerstellerNr
--   + Name
--   + Adresse (Straße, PLZ, Ort)
-- * Fahrzeug
--   + FahrzeugTypNr
--   + Bezeichnung
--   + Gewicht
--   + Listenpreis (Netto,USt,Brutto)
--   + Basisbauteil

-- 1.1 Richten Sie die Tabellen (s. Vorgabe) in ihrer Datenbank ein.

CREATE TABLE Fahrzeug (
	FzNr		NUMBER(5) CONSTRAINT PK_FZ PRIMARY KEY,
	--FzNr		NUMBER(5) PRIMARY KEY,
	Bezeichnung	VARCHAR2(15) NOT NULL,
	Gewicht		FLOAT(10)
);

DROP TABLE Bauteil;
CREATE TABLE Bauteil (
	--BtNr		NUMBER(5) PRIMARY KEY,
	BtNr		NUMBER(5) CONSTRAINT PK_BT PRIMARY KEY,
	Teilename	VARCHAR2(20) NOT NULL,
	Einbauzeit	NUMBER(5),
	HstNr		VARCHAR2(10),
	Baugruppe	NUMBER(5) CONSTRAINT FK_BTNR FOREIGN KEY (Baugruppe)      REFERENCES Bauteil(BtNr)
	--Baugruppe	NUMBER(5) REFERENCES Bauteil(BtNr)
);

DROP TABLE Einbau;
CREATE TABLE Einbau (
	EbNr VARCHAR2(10) CONSTRAINT PK_EB PRIMARY KEY,
	--EbNr VARCHAR2(10) Primary Key,
	--BtNr NUMBER(5) NOT NULL CONSTRAINT FK_BTNR FOREIGN KEY (BtNr) REFERENCES Bauteil(BtNr),
	BtNr NUMBER(5) NOT NULL REFERENCES Bauteil(BtNr),
	--FzNr NUMBER(5) NOT NULL CONSTRAINT FK_FZNE FOREIGN KEY (FzNr) REFERENCES Fahrzeug(FzNr) ON DELETE CASCADE,
	FzNr NUMBER(5) NOT NULL REFERENCES Fahrzeug(FzNr) ON DELETE CASCADE,
	Anzahl number(5)
);

-- 1.2 Stellen Sie sicher, dass die Kombination von *BtNr* und *FzNr* in der Tabelle Einbau eindeutig ist.
ALTER TABLE Einbau ADD CONSTRAINT CK_UNIQUE_BTFZ UNIQUE(BtNr, FzNr);

-- 1.3 Legen Sie die Tabelle *Hersteller* an. Kopieren Sie hierzu die Tabellendefinition und die Daten aus der Tabelle *Hersteller* des Datenbankbenutzers *db01*.
SELECT * FROM db01.Hersteller;
CREATE TABLE Hersteller AS (SELECT * FROM db01.Hersteller);
--läuft!
SELECT 
--ODER (auch)
CREATE TABLE Hersteller (
	HstNr VARCHAR2(10) NOT NULL,
	Name VARCHAR2(50 BYTE) NOT NULL,
	Strasse VARCHAR2(50),
	PLZ VARCHAR2(5),
	Ort VARCHAR2(50),
	Kontaktaufnahme DATE DEFAULT sysdate,
	CONSTRAINT PK_HERSTELLER PRIMARY KEY (HstNr) ENABLE 
);
SELECT * FROM Hersteller;
DELETE FROM Hersteller WHERE HstNr='134556';
DELETE FROM Hersteller WHERE HstNr='588797';

INSERT INTO Hersteller (HSTNR,NAME,STRASSE,PLZ,ORT,KONTAKTAUFNAHME)
	VALUES ('134556','Magna Heiligenstadt','Fabrikstrasse 32','37308','Heiligenstadt',to_date('12.06.07','DD.MM.RR'));
INSERT INTO Hersteller (HSTNR,NAME,STRASSE,PLZ,ORT,KONTAKTAUFNAHME)
	VALUES ('588797','MAN','Ginsheimerstr. 2','65462','Ginsheim',to_date('01.01.11','DD.MM.RR'));

--doppelte 'Einträger vermeiden
CREATE UNIQUE INDEX PK_HERSTELLER ON Hersteller (HstNr);

-- 1.4 Beim Kopieren der Tabelle werden nicht alle Constraints und Spalteneigenschaften kopiert.
--     Ermitteln Sie die Eigenschaften der Tabelle *db01.Hersteller* und ergänzen Sie Ihre Tabelle
--     *Hersteller* um diese. Zur Recherche nutzen Sie bitte folgende Abfragen.
--     (Bitte das Abfrageergebnis in der vollst. Breite betrachten!)

SELECT * FROM ALL_CONSTRAINTS WHERE owner='DB01' AND TABLE_NAME='HERSTELLER';
--ergibt
--DB01	SYS_C0011121	C	HERSTELLER	"HSTNR" IS NOT NULL				ENABLED	NOT DEFERRABLE	IMMEDIATE	VALIDATED	GENERATED NAME			02.12.15				
--DB01	SYS_C0011122	C	HERSTELLER	"NAME" IS NOT NULL				ENABLED	NOT DEFERRABLE	IMMEDIATE	VALIDATED	GENERATED NAME			02.12.15				
--DB01	SYS_C0011123	P	HERSTELLER					ENABLED	NOT DEFERRABLE	IMMEDIATE	VALIDATED	GENERATED NAME			02.12.15		SYS_C0011123		
--=>
--HstNr NOT NULL
--Name NOT NULL
--HstNr PK

SELECT * FROM ALL_TAB_COLUMNS WHERE owner='DB01' AND TABLE_NAME='HERSTELLER';
--ergibt
--DB01	HERSTELLER	HSTNR	VARCHAR2			10			N	1			2	313334353536	353838373937	0,5	0	1	02.12.15	2	CHAR_CS	10	YES	NO	7	10	B	NO	YES	NONE
--DB01	HERSTELLER	NAME	VARCHAR2			50			N	2			2	4D414E	4D61676E61204865696C6967656E7374616474	0,5	0	1	02.12.15	2	CHAR_CS	50	YES	NO	12	50	B	NO	YES	NONE
--DB01	HERSTELLER	STRASSE	VARCHAR2			50			Y	3			2	46616272696B73747261737365203332	47696E736865696D65727374722E2032	0,5	0	1	02.12.15	2	CHAR_CS	50	YES	NO	17	50	B	NO	YES	NONE
--DB01	HERSTELLER	PLZ	VARCHAR2			5			Y	4			2	3337333038	3635343632	0,5	0	1	02.12.15	2	CHAR_CS	5	YES	NO	6	5	B	NO	YES	NONE
--DB01	HERSTELLER	ORT	VARCHAR2			50			Y	5			2	47696E736865696D	4865696C6967656E7374616474	0,5	0	1	02.12.15	2	CHAR_CS	50	YES	NO	12	50	B	NO	YES	NONE
--DB01	HERSTELLER	KONTAKTAUFNAHME	DATE			7			Y	6	8	"sysdate"	2	7866060C010101	786B0C01010101	0,5	0	1	02.12.15	2			YES	NO	8	0		NO	YES	NONE
--=>
--DATA_LENGTH ...
--Kontaktaufnahme=SYSDATE

SELECT * FROM ALL_CONS_COLUMNS WHERE owner='DB01' AND TABLE_NAME='HERSTELLER';
--ergibt
--DB01	SYS_C0011121	HERSTELLER	HSTNR	
--DB01	SYS_C0011122	HERSTELLER	NAME	
--DB01	SYS_C0011123	HERSTELLER	HSTNR	1

-- => also
ALTER TABLE Hersteller ADD CONSTRAINT PK_HERSTELLER PRIMARY KEY (HstNr);
--ALTER TABLE Hersteller ADD PRIMARY KEY (HstNr);
ALTER TABLE Hersteller MODIFY (KONTAKTAUFNAHME DEFAULT SYSDATE);

-- 1.5 Fügen Sie folgenden Datensatz in die Tabelle Hersteller ein:
--     HstNr	| HstName		| Strasse			| Plz	| Ort		| Kontaktaufnahme
--     693253	| Tower Zwickau	| Kopernikusstr. 60	| 08056	| Zwickau	| heute
SELECT * FROM Hersteller;
INSERT INTO Hersteller (HstNr, Name, Strasse, Plz, Ort)
	VALUES('693253','Tower Zwickau','Kopernikusstr. 60','08056','Zwickau');
--
DELETE FROM Hersteller WHERE HstNr='693253';
SELECT * FROM Hersteller;
--

-- 1.6 Geben Sie Namen, PLZ und Ort Ihrer *Hersteller* aus, geordnet nach PLZ
SELECT Name,Plz PLZ,Ort FROM Hersteller ORDER BY Plz ASC; 

-- 1.7 Geben Sie alle *Hersteller* aus, zu denen in den letzten 5 Jahren der Kontakt aufgebaut wurde
SELECT * FROM Hersteller;
--VARIABLE Jahre NUMBER;
--EXEC :Jahre := 5;
DEF Jahre = 5;
SELECT * FROM Hersteller WHERE to_char(Kontaktaufnahme, 'YYYY') > (to_char(SYSDATE, 'YYYY')-&Jahre);
SELECT * FROM Hersteller WHERE months_between(SYSDATE,Kontaktaufnahme) < (&Jahre*12)
UNDEF Jahre;
DEF;

-- 1.8 Definieren Sie in der Tabelle *Bauteil* den Fremdschlüssel auf die Tabelle *Hersteller*.
--ALTER TABLE Bauteil MODIFY (HstNr REFERENCES Hersteller(HstNr));
SELECT * FROM Bauteil;
SELECT * FROM ALL_TAB_COLUMNS WHERE  TABLE_NAME='BAUTEIL';
SELECT * FROM ALL_CONS_COLUMNS WHERE  TABLE_NAME='BAUTEIL';
ALTER TABLE Bauteil ADD CONSTRAINT FK_HSTNR FOREIGN KEY (HstNr) REFERENCES Hersteller(HstNr);

-- 2. Objekte, Methoden und Eigenschaften
-- Um den Listenpreis gemäß der Vorgabe zu definieren, wird ein Objekttyp mit entsprechenden Attributen und Methoden benötigt.

-- 2.1 Erstellen Sie einen neuen Objekttyp *TPreis* mit folgenden Attributen und Methoden:
-- Attribut	| Type
-- Preis	| Number(10,2)
--
-- Methode		| Parameter			| Rückgabewert
-- Netto		| --				| Number
-- Brutto		| --				| Number
-- Umrechnung	| Faktor(Number)	| Number
CREATE
OR REPLACE
TYPE TPreis AS OBJECT(
	Preis Number(10,2),
	MEMBER FUNCTION Netto RETURN NUMBER,
	MEMBER FUNCTION Brutto  RETURN NUMBER,
	MEMBER FUNCTION Umrechnung (Faktor NUMBER) RETURN NUMBER
);

-- 2.2 Implementieren Sie den Funktionsrumpf:
-- Dabei soll gelten:
-- *Netto*		- gibt den im Attribut Preis gespeicherten Wert zurück
-- *Brutto*		- gibt den im Attribut Preis gespeicherten Wert zurück + 19% USt
-- *Umrechn.*	- multipliziert den Preis mit einem Faktor und gibt diesen Wert zurück
CREATE
OR REPLACE
TYPE BODY TPreis AS 
	MEMBER FUNCTION Netto RETURN NUMBER IS
		BEGIN
			RETURN (Preis);
		END;
	MEMBER FUNCTION Brutto RETURN NUMBER IS
		BEGIN
			RETURN (Preis * 1.19);
		END;
	MEMBER FUNCTION Umrechnung (Faktor number) RETURN NUMBER IS
		BEGIN
			RETURN (Preis * Faktor);
		END;
END;

-- 2.3 Ergänzen Sie die Tabelle *Fahrzeug* um die Spalte *Listenpreis* vom Typ TPreis
--alter table Abteilung    add [column] Kuerzel CHAR(4) not null;
--s. https://de.wikibooks.org/wiki/Einf%C3%BChrung_in_SQL:_%C3%84nderung_der_Datenbankstruktur

ALTER TABLE Fahrzeug ADD 
--COLUMN
Listenpreis TPreis 
--NOT NULL
;

-- 3. Array Typen

-- 3.1 Erstellen Sie einen Array-Typ *AnzTueren* der *Größe 5*, welche Elemente vom Typ *char(10)* aufnimmt.
CREATE 
OR REPLACE
TYPE AnzTueren AS VARRAY(5) OF CHAR(10);

-- 3.2 Ergänzen Sie die Tabelle *Fahrzeug* um eine neue Spalte *Tuerzahl* vom Typ *AnzTueren*

ALTER TABLE Fahrzeug ADD 
--COLUMN 
Tuerzahl AnzTueren;

-- 3.3 Fügen Sie folgende Daten in die Tabelle Fahrzeug ein:
-- FzNr		| Bezeichnung		| Gewicht	| Listenpreis	| Tuerzahl
-- 10000	| BMQ Z4 Roadstar	| 900		| 60000			| 3-Türer
-- 10001	| VW Golf GTI		| 800		| 25000			| 3-Türer, 5-Türer
-- 10002	| Audi A3			| 850		| 30000			| 3-Türer
INSERT INTO Fahrzeug(FzNr,Bezeichnung,Gewicht,Listenpreis,Tuerzahl)
  VALUES(10000,'BMW Z4 Roadstar',900,TPreis(60000),AnzTueren('3-Türer'));
INSERT INTO Fahrzeug(FzNr,Bezeichnung,Gewicht,Listenpreis,Tuerzahl)
  VALUES(10001,'VW Golf GTI',800,TPreis(25000),AnzTueren('3-Türer','5-Türer'));
INSERT INTO Fahrzeug(FzNr,Bezeichnung,Gewicht,Listenpreis,Tuerzahl)
  VALUES(10002,'Audi A3',850,TPreis(30000),AnzTueren('3-Türer'));
--COMMIT;
SELECT * FROM Fahrzeug;

-- 3.4 Ermitteln Sie die Bruttopreise Ihrer Fahrzeuge. Welcher Preis wäre zu zahlen, wenn der Umrechnungskurs 1:1,5 lauten würde?
SELECT
	v.Listenpreis.Brutto()			Bruttopreis,
	v.Listenpreis.Umrechnung(1.5)	Umrechnung
	FROM Fahrzeug v;

-- 4. Nested Table
-- Die Preise von Bauteilen bleiben nicht konstant. Um die Preisentwicklung über einen längeren Zeitraum verfolgen zu können,
-- soll diese mit einer Nested Table in der Tabelle Bauteil festgehalten werden.

-- 4.1 Erzeugen Sie einen Objekttyp namens *tPreisentwicklung* vom Typ *object* mit folgenden Spalten:
-- Spaltenname	| Typ
-- PeNr			| VARCHAR2(10)
-- Netto		| NUMBER(10,2)
-- Datum		| DATE
CREATE TYPE tPreisentwicklung AS OBJECT(
	PeNr	VARCHAR2(10),
	Netto	NUMBER(10,2),
	Datum	DATE
);

-- 4.2 Erzeugen Sie einen Objekttyp *ntPreisentwicklung* von Typ *table*, der aus dem Typ *tPreisentwicklung* besteht.
CREATE TYPE ntPreisentwicklung AS TABLE OF tPreisentwicklung;

-- 4.3 Ergänzen Sie die Tabelle *Bauteil* um eine weitere Spalte *Preis* vom Typ *ntPreisentwicklung*.
-- s. http://www.orafaq.com/wiki/NESTED_TABLE
ALTER TABLE Bauteil
	ADD Preis ntPreisentwicklung 
		NESTED TABLE Preis STORE AS ntPreise;


-- 4.4 Fügen Sie folgende Daten in die Tabelle *Bauteil* ein:
-- BtNr	| Teilename		| Einbauz	| HstNr		| Baugruppe	| Preis
-- 5000	| Tuer links	| 20		| 134556	| NULL		| (7007, 900, 12.10.2015)
-- 5001	| Spigeel recht	| 10		| 588797	| NULL		| (7008, 100, 12.10.2015)
-- 5002	| Auspuff		| 30		| 693253	| NULL		| (7009, 2000, 12.10.2015)
SELECT * FROM Bauteil;
INSERT INTO Bauteil (BtNr, Teilename, Einbauzeit, HstNr, Preis)
	VALUES (5000, 'Tuer links', 20, '134556', ntPreisentwicklung());
INSERT INTO TABLE (SELECT Preis FROM Bauteil WHERE Bauteil.BtNr = 5000)
	VALUES ('7007', 900, TO_DATE('12102015', 'DDMMYY'));

INSERT INTO Bauteil (BtNr, Teilename, Einbauzeit, HstNr, Preis)
	values (5001, 'Spiegel rechts', 10, '588797', ntPreisentwicklung());
INSERT INTO TABLE (SELECT Preis FROM Bauteil WHERE Bauteil.BtNr = 5001)
	VALUES ('7008', 100, TO_DATE('12102015', 'DDMMYY'));

INSERT INTO Bauteil (BtNr, Teilename, Einbauzeit, HstNr, Preis)
	values (5002, 'Auspuff', 30, '693253', ntPreisentwicklung());
INSERT INTO TABLE (SELECT Preis FROM Bauteil WHERE Bauteil.BtNr = 5002)
	VALUES ('7009', 2000, TO_DATE('12102015', 'DDMMYY'));

-- 4.5 Führen Sie das SQL-Script *PRAKT/GRAEFE/bauteil.sql* aus um Ihre Tabelle mit zusätzlichen Daten zu füllen.
-- Überprüfen Sie danach den Inhalt der Tabelle *Bauteil* (BtNr, Teilename, Einbauz., HstNr, Baugruppe).
@./bauteil.sql
--erreiche ich nicht

-- 4.6 Geben Sie Baugruppen mit ihren zugehörigen bauteilen in folgender Form aus:
-- <baugruppe>
--   <bauteil>
--     <untergeordnetes bauteil>
SELECT LEVEL,LPAD(' ',2*LEVEL)||Teilename FROM Bauteil--s. http://www2.htw-dresden.de/~toll/dbs2/DBII_Kap3_LogDM10.pdf
CONNECT BY PRIOR BtNr=Baugruppe
START WITH Baugruppe IS NULL;

-- 4.7 Geben Sie für jedes Bauteil seine Preisentwicklung aus (BtNr, Teilename, Netto, Datum).
--SELECT * FROM Bauteil,TABLE(Bauteil.Preis);
SELECT BtNr,Teilename,HstNr,Netto,Datum FROM Bauteil,TABLE(Bauteil.Preis);

-- 4.8 Lesen Sie den Namen der ersten fünf Datensätze aus der Tabelle *Bauteil*, geordnet nach der BtNr, aus.
-- MySQL
--SELECT Teilename FROM Bauteil ORDER BY BtNr LIMIT 5;
-- Oracle
SELECT Teilename FROM Bauteil WHERE ROWNUM <= 5 ORDER BY BtNr;

-- 4.9 Ermitteln Sie für jede Baugruppe das Bauteil mit der beringsten Einbauzeit. Nutzen Sie hierzu die Funktion RANK() OVER.
SELECT Baugruppe,BtNr,Teilename,Einbauzeit,RANK() OVER (PARTITION BY Baugruppe ORDER BY Einbauzeit) "Rank"
	FROM Bauteil
	WHERE Baugruppe IS NOT NULL;

-- 5 Objektview

-- 5.1 Erstellen Sie einen Objekttyp *TAddresse* mit den Attributen Strasse, Plz und Ort analog der Definition der Tabelle *Hersteller*.
CREATE OR REPLACE TYPE TAdresse AS OBJECT(
	Strasse VARCHAR2(50),
	Plz VARCHAR2(5),
	Ort VARCHAR2(50)
);

-- 5.2 Erstellen Sie die Tabelle *Lieferant*:
-- Spaltenname	| Typ			| Bemerkung
-- LiefNr		| NUMBER(6)		| PRIMARY KEY
-- Name			| VARCHAR2(20)	| NOT NULL
-- Adresse		| TAdresse		|
CREATE TABLE Lieferant (
  LiefNr	NUMBER(6) PRIMARY KEY,
  Name		VARCHAR2(20) NOT NULL,
  Adresse	TAdresse
);

-- 5.3 Erstellen Sie eine View (*Lieferant_OV*) über die Tabelle *Lieferant*. Lösen Sie hierbei die im Typ *TAdresse* enthaltenen Informationen in einzelne Spalten (Strasse, PLZ, Ort) auf.
CREATE VIEW Lieferant_OV (LiefNr, Name, Strasse, Plz, Ort)
	AS SELECT l.LiefNr, l.Name, l.Adresse.Strasse, l.Adresse.Plz, l.Adresse.Ort
	FROM Lieferant l;

-- 5.4 Testen Sie, ob sich folgender Datensatz über die View (*Lieferanten_OV*) in die Tabelle *Lieferant* einfügen lässt.
-- LiefNr	| Name				| Strasse		| Plz	| Ort
-- 752443	| Laepple Teublitz	| Maxstr. 12	| 93158	| Teublitz
INSERT INTO Lieferanten_OV
	VALUES(752443,'Laepple Teublitz','Maxstr. 12','93158','Teublitz');
-- geht nicht, s.a. 6.2

-- 6 Sicherung der semantischen Integrität

-- 6.1 Nennen Sie Sicherungsmaßnahmen, die Sie bereits beim erstellen der Tabellen vorgenommen haben.

-- Datentypen
-- Not Null
-- DEFAULT
-- Private Key
-- Unique-Constraint
-- On-Delete-Constraint

-- 6.2 Um die View *Liefreant_OV* zum Einfügen von Daten in die Tabelle *Lieferant* nutzen zu könne, benötigen Sie einen Instead-Trigger. Erstellen Sie diesen.
-- Testen Sie den Trigger indem Sie die Daten aus der Aufgabe 5.4 erbeut eintragen.
CREATE OR REPLACE TRIGGER TR_Lieferant_OV_Insert
INSTEAD OF INSERT
ON Lieferant_OV
	FOR EACH ROW
	BEGIN
		INSERT INTO Lieferant VALUES  ( :new.LiefNr, :new.Name, TAdresse( :new.Strasse, :new.Plz, :new.Ort ) );
	END;
--Test
INSERT INTO Lieferant_OV (Liefnr, Name, Strasse, PLZ, Ort)
	VALUES (752443, 'Laepple Teubnlitz', 'Maxstr. 12', '93158', 'Teublitz');

-- 6.3 Für die Tabelle *Einbau* soll der Primärschlüssel automatisch vergeben werden. Er soll sich aus einer fortlaufenden Nummer und dme vorangestellten buchstaben "E" bestehen (z.B. E2010).
-- Hierzu wird eine Sequence angelegt, die eine fortlaufende Zahl erzeugt und mittels eines Triggers beim Hinzufügen von Datensätzen in die Tabelle übernommen.

-- a.	Legen Sie eine Sequence *sq_einbau* an, die einen Startwert con 2000 hat und sich jedes Mal um den Wert 1 erhöht.

CREATE SEQUENCE sq_einbau
--	MINVALUE 2000
--	MAXVALUE 999999999999999999999999999
	INCREMENT BY 1
	START WITH 2000
--	CACHE 50
	;
DROP SEQUENCE sq_einbau;

-- s. https://de.wikibooks.org/wiki/Oracle:_Sequenzen

-- b.	Erstellen Sie einen Trigger für die Tabelle *Einbau*, der vor dem Einfügen für jede Zeile den nächsten Wert aus der Sequence *sq_einbau* ermittelt, diesem Wert ein ein "E" voransetzt und dem Feld EbNr zuweist. Bei Änderungen in der Tabelle soll der Trigger verhindern, dass der Primärschlüssel geändert werden kann.
--select sq_einbau.nextval from dual;
--DROP TRIGGER TR_Einbau;
CREATE OR REPLACE TRIGGER TR_Einbau
BEFORE INSERT OR UPDATE OF EbNr
ON Einbau
	FOR EACH ROW
	BEGIN
		--Sequence lesen,ID Zusammenbauen,in RbNr schreiben
		IF INSERTING THEN
			SELECT CONCAT('E',TO_CHAR(sq_einbau.NEXTVAL)) INTO :new.EbNr FROM dual;
		END IF;
		--Überschreiben verhindern -> :new = :old
		IF UPDATING THEN
			:new.EbNr := :old.EbNr;
		END IF;
	END;

-- c.	Testen Sie Ihren Trigger, indem Sie folgenden Datensatz in die Tabelle einfügen und sich den Inhalt der Tabelle anzeigen lassen.
INSERT INTO Einbau(EbNr,BtNr,FzNr, Anzahl) VALUES(NULL, 5000, 10000, 1);
SELECT * FROM Einbau;

-- 6.4 Ändern Sie Ihren Trigger und stellen Sie sicher, das snur solche Bauteile in der Tabelle *Einbau* enthalten sein könne, bei denen es sich um vollständige Baugruppen handelt (Bauteil.Baugruppe ist NULL). Sollte das Einfügen nicht möglich sein, geben Sie eine Exception aus.
CREATE OR REPLACE TRIGGER TR_Einbau
BEFORE INSERT OR UPDATE OF EbNr
ON Einbau
	FOR EACH ROW
		DECLARE 
			BtNr_keine_Baugruppe_Exception EXCEPTION;
			test_BtNr number(5);
		BEGIN
			SELECT BtNr INTO test_BtNr
				FROM Bauteil
				WHERE BtNr = :new.BtNr AND Baugruppe IS NULL;
      --Fehlerfall -> raus!
   			IF INSERTING THEN
      IF test_BtNr IS NULL THEN
        RAISE BtNr_keine_Baugruppe_Exception;
      END IF;
    			SELECT CONCAT('E',TO_CHAR(sq_einbau.NEXTVAL)) INTO :new.EbNr FROM dual;
      	END IF;
  			IF UPDATING THEN
      IF test_BtNr IS NULL THEN
        RAISE BtNr_keine_Baugruppe_Exception;
      END IF;
    			:new.EbNr := :old.EbNr;
      	END IF;
		
		EXCEPTION
			WHEN BtNr_keine_Baugruppe_Exception THEN
        DBMS_OUTPUT.PUT_LINE('Bauteilnummer ' || :new.BtNr || ' ist nicht zugelassen.');
				raise_application_error(-20000, 'Bauteilnummer ' || :new.BtNr || ' ist nicht zugelassen.');
      WHEN others THEN
				raise_application_error(-20124, 'Irgendwas geht schief.');
	END;

-- 6.5 Testen Sie ihren Trigger, indem Sie die folgenden Datensätze in die Tabelle *Einbau* einfügen und sich den Inhalt der Tabelle anzeigen lassen.
SELECT * FROM Bauteil;
SELECT * FROM Fahrzeug;
INSERT INTO Einbau(EbNr,BtNr,FzNr, Anzahl) VALUES(NULL, 5001, 10001, 1);
INSERT INTO Einbau(EbNr,BtNr,FzNr, Anzahl) VALUES(NULL, 5010, 10002, 2);
SELECT * FROM Einbau;
DELETE FROM Einbau WHERE EbNr='E2000';
-- 6.6 Löschen Sie den Datensatz mit der FzNr '10001' aus der Tabelle *Fahrzeug*. Überprüfen Sie vor und nach dem Löschen die Inhalte der Tabellen *Fahrzeug* und *Einbau*!
--erst gucken
SELECT * FROM Fahrzeug;
SELECT * FROM Einbau;
--Löschversuch
DELETE FROM Fahrzeug WHERE FzNr = 10001;
--Prüfen
SELECT * FROM Fahrzeug;
SELECT * FROM Einbau;

-- 7 Stored Procedures
-- Um die Ergebnisse der Prozeduren sehen zu können, müssen Sie für jede Session das Serveroutput einschalten.
--
set serveroutput on;
--

-- 7.1 Schrieben Sie eine Prozedur, die alle Fahrzeuge auflistet, die ein Gewicht besitzen, welches kleiner oder gleich einem bestimmten Wert ist.
-- Dieser Wert soll der Prozedur als Parameter übergeben werden.
--
-- Die Ausgabesoll folgendes Aussehen haben:
--		FzNr		: 10000
--		Bezeichnung	: BMW Z4 Roadstar
--		Gewicht		: 900
--
-- Hinweis: Nutzen Sie einen Cursor.

--ausgabe
set serveroutput on format wrapped;
begin
    DBMS_OUTPUT.put_line('simple comment');
end;
--

CREATE OR REPLACE PROCEDURE gewicht_proc( v_gewicht IN Fahrzeug.Gewicht%TYPE )
IS
CURSOR gewicht_cursor IS
	SELECT FzNr, Bezeichnung, Gewicht
  	FROM Fahrzeug
    WHERE Gewicht <= v_gewicht;
BEGIN
	DBMS_OUTPUT.PUT_LINE('');
	FOR car IN gewicht_cursor
	LOOP--rpad()
		DBMS_OUTPUT.PUT_LINE('FzNr        ' || ': ' || car.FzNr);
		DBMS_OUTPUT.PUT_LINE('Bezeichnung ' || ': ' || car.Bezeichnung);
		DBMS_OUTPUT.PUT_LINE('Gewicht     ' || ': ' || car.Gewicht);
		DBMS_OUTPUT.PUT_LINE('-----------------------------------');
	END LOOP;
END gewicht_proc;
set serveroutput on;
exec gewicht_proc(910);
-- 7.2 Kopieren Sie sich die Datei einbau.sql in das Verzeichnis *temp* und führen Sie das SQL-Script aus. Es fügt der Tabelle Einbau weitere Datensätze hinzu.
--
-- Entwickeln Sie eine Prozedur, die Inhalt der Tabelle Einbau wie folgt ausliest:
-- Cursor c1	liest die Bezeichnung der Fahrzeuge aus der Tabelle *Fahrzeug* für alle Fahrzeuge, die in der Tabelle Einbau referenziert werden.
-- Corsor c2	liest die Teilenamen der Bauteile aus der Tabelle *Bauteil*, für alle Bauteile, die in ein bestimmtes Fahrzeug eingebaut wurden.
--
-- Die Ausgabe soll folgendes Aussehen haben:
--		Audi A3
--		.	Tuer links
--		.	Spiegel rechts
--		BMW Z4 Roadstar
--		.	Tuer links
--		.	Spiegel rechts
--		.	Auspuff
CREATE OR REPLACE PROCEDURE einbau_proc 
IS
	v_car_nr Fahrzeug.FzNr%TYPE;
	CURSOR kfz_cur
	IS
		SELECT DISTINCT f.FzNr, f.Bezeichnung
  		FROM Einbau e, Fahrzeug f
    	WHERE e.FzNr = f.FzNr;
	CURSOR bauteile_cur
	IS
		SELECT e.EbNr, e.FzNr, e.BtNr, b.Teilename
		FROM Einbau e, Bauteil b
		WHERE e.FzNr = v_car_nr AND e.BtNr = b.BtNr;
	BEGIN
		DBMS_OUTPUT.PUT_LINE('');
		FOR car IN kfz_cur
		LOOP
			DBMS_OUTPUT.PUT_LINE('' || car.Bezeichnung);
			v_car_nr := car.FzNr;
			FOR bt IN bauteile_cur
			LOOP
				DBMS_OUTPUT.PUT_LINE('.   ' || bt.Teilename);
			END LOOP;
		END LOOP;
	END einbau_proc;
SELECT * FROM Fahrzeug;
SELECT * FROM Einbau;
SELECT * FROM Bauteil;
@./einbau.sql;
set serveroutput on;
EXEC einbau_proc;
-- 7.3 Erweitern Sie die Prozedur aus 7.2 um einen weiteren Cursor und geben Sie zusätzlich alle Bauteil, die zu den verbauten Baugruppen gehören, aus.
--
-- Die Ausgabe soll folgendes Aussehen haben:
-- Die Ausgabe soll folgendes Aussehen haben:
--		Audi A3
--		5000 -	Tuer links
--			5003 -	Tuergriff links
--			5004 -	Schlossriegel links
--			5005 -	Türgummi
--		5001 -	Spiegel rechts
--			5009 -	Spiegelglas
--			5010 -	Gehäuse
CREATE OR REPLACE PROCEDURE einbau_proc 
IS
	v_car_nr Fahrzeug.FzNr%TYPE;
	v_bt_nr Bauteil.BtNr%TYPE;
	v_bt_name Bauteil.Teilename%TYPE;
	CURSOR kfz_cur
	IS
		SELECT DISTINCT f.FzNr, f.Bezeichnung
      FROM Einbau e, Fahrzeug f
      WHERE e.FzNr = f.FzNr;
	CURSOR bauteile_cur
	IS
		SELECT e.EbNr, e.FzNr, e.BtNr, b.Teilename
      FROM Einbau e, Bauteil b
      WHERE e.FzNr = v_car_nr AND e.BtNr = b.BtNr;
	CURSOR a73_cur( en Bauteil.Baugruppe%TYPE )
	IS
		SELECT b.BtNr, b.Teilename
      FROM Bauteil b
      WHERE b.Baugruppe = en;
	BEGIN
		DBMS_OUTPUT.PUT_LINE('');
		DBMS_OUTPUT.PUT_LINE('');
		--OPEN kfz_cur;
		--OPEN bauteile_cur;
		--FETCH kfz_cur INTO car;
		--EXIT WHEN c_pos%NOTFOUND;
		FOR car IN kfz_cur
		LOOP
			DBMS_OUTPUT.PUT_LINE(car.FzNr || ' - ' || car.Bezeichnung);
			v_car_nr := car.FzNr;
			FOR bg IN bauteile_cur
			LOOP
				DBMS_OUTPUT.PUT_LINE('' || bg.EbNr || ' - ' || bg.Teilename);
			OPEN a73_cur(bg.EbNr);
			--FOR bt IN a73_cur
			LOOP
				FETCH a73_cur INTO v_bt_nr, v_bt_name;
				EXIT WHEN a73_cur%NOTFOUND;
				DBMS_OUTPUT.PUT_LINE('  ' || --bt.EbNr 
					v_bt_nr || ' - ' || 
					--bt.Teilename
					v_bt_name);
			END LOOP;
			IF a73_cur%ISOPEN THEN  -- cursor is open
				CLOSE a73_cur;
			END IF;
			
			END LOOP;
		END LOOP;
		IF bauteile_cur%ISOPEN THEN  -- cursor is open
			CLOSE bauteile_cur;
		END IF;
		IF kfz_cur%ISOPEN THEN  -- cursor is open
			CLOSE kfz_cur;
		END IF;
	END einbau_proc;
set serveroutput on;
EXEC einbau_proc;
SELECT * FROM Bauteil;

-- 8 Zugriffsschutz
-- Aufgabe zu den Rechten: Lösen Sie die folgenden Aufgaben wechselseitig mit einem Partner in Form eines Rollenspiels.

SELECT grantor, grantee, table_schema, table_name, privilege
	FROM all_tab_privs 
	WHERE table_name = UPPER('Hersteller');
--partner..usr
VARIABLE usr VARCHAR2(6);
EXEC usr := s72780;

-- 8.1 Erteilen Sie Ihrem Patrner die Leserechte für die Tabelle *Hersteller*
--s. https://docs.oracle.com/javadb/10.8.3.0/ref/rrefsqljgrant.html#rrefsqljgrant__grantprivtype
GRANT SELECT ON Hersteller TO :usr ;

-- 8.2 Ihr Patrner soll (erneut) versuchen, den Inhalt Ihrer Tabelle *Hersteller* zu lesen.
SELECT * FROM Hersteller;

-- 8.3 Fordern Sie Ihren Partner auf, einen Wert in *Hersteller* zu ändern.
UPDATE Hersteller SET Name='M.A.N.' WHERE Name='MAN';

-- 8.4 Nehmen Sie Ihrem Partner die Rechte an der Tabelle *Hersteller* wieder zurück.
REVOKE SELECT ON Hersteller FROM :usr ;
