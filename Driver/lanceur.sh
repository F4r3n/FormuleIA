#!/bin/bash

#Lanceur pour jeu de course
#Fait le makefile
#Le copie dans le dossier driver
#Lance le gestionnaire

make clean
make
if [ $1 == "g" ]; then
cp fatMobile ~/GrandPrix/drivers
cd ~/GrandPrix/
./GrandPrix
fi

# pour manu, fais comme moi mais mets l'emplacement du grand prix
if [ $1 == "m" ]; then

fi
