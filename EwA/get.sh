wget -c http://iasp2.informatik.htw-dresden.de/wiedem/lehre_ewa.html
sed -i -e "s/\"fileadmin\//\"http\:\/\/iasp2\.informatik\.htw\-dresden\.de\/wiedem\/fileadmin\//g" *.html
cat *.html|grep -o "href=.*" | cut -d'"' -f2|grep -e "pdf$" -e "doc$" -e "zip$"|sort|uniq| xargs wget -c 
