#!/bin/sh
which xmllint > /dev/null || echo "keine XML validator gefunden"
echo test DTD
xmllint --noout --valid katalog.xml && echo "kein Fehler"
echo test XSD
xmllint --noout --valid --schema katalog.xsd katalog2.xml && echo "kein Fehler"
