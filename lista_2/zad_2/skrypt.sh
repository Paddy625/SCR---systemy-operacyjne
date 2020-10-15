#!/bin/bash

#nalezy upewnic sie ze zainstalowany i skonfigurowany jest program mutt

for mail in $(cat adresy.txt)
do
    cat tresc.txt | mutt -s "Zapytanie ofertowe okna PCV" $mail -a spec*.pdf
done
