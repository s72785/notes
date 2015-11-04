#!/bin/sh
if [ -d ./validator ]; then
	echo "validator found"
else
	echo "cloning validator ..."
	git clone https://github.com/amouat/xsd-validator.git validator
fi
echo "validating XML vs XSD ..."
./validator/xsdv.sh katalog.xsd katalog.xml
./validator/xsdv.sh katalog.xsd katalog2.xml
