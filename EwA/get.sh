cat *.html|grep -o "href=.*" | cut -d'"' -f2|grep -e "pdf$" -e "doc$" -e "zip$"|sort|uniq| xargs wget -c 
