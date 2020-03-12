#Début du scipt 


#!/bin/bash 
#On scanne le réseau pour savoir quelles ips sont deja prises et dons lesquelles ont peu prendre

zenity --info --text="<span color=\"red\" font-weight=\"bold\">Voici les IP qui sont déjà prises:</span>\n\n`arp-scan --localnet`" --title="Netsh"

#on crée une variable ip que l'utilisateur entre. Attention; le 'grep 1' à la fin de la ligne 
#est la car souvent les adresses ips locales commencent par 1 (exemples:192.xxx.xxx.xxx ou 172.xxx.xxx.xxx
ip=`zenity --entry --text="Quelle IP voulez-vous ?" --title="Netsh"|grep 1`

#Et on rentre cette variable dans le fichier de config
echo 'auto lo
iface lo inet loopback

auto eth0
iface eth0 inet static
address '$ip'
mask 255.255.255.0
gateway 192.168.0.254

auto wlan0
iface wlan0 inet dhcp
'>/etc/network/interfaces

#On redémarre l'interface (dans mon cas eth0, modifiez si vous en avez une autre, comme wlan0 pour la wifi

ifdown eth0
ifup eth0
ifdown eth0
ifup eth0

#Et on teste si on voit l'ip quand on fait ifconfig, si on ne la voit pas, cela affiche "erreur"
#sinon, cela affiche qu'on a réussi l'opération

test=`ifconfig|grep $ip`
nul=""
if [ -z "$test"]
then
zenity --info --text="<span color=\"red\" font-weight=\"bold\">Erreur !</span>" --title="Netsh"
else
zenity --info --text="<span color=\"red\" font-weight=\"bold\">Votre IP a été modifiée avec succès</span>" --title="Netsh"
fi

#Et voilà, c'est aussi simple que ça, n'hésitez surtout pas à me poser des questions :)


#Fin du script 
