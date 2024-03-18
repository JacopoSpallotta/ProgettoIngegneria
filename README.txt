Prerequisiti:
    -redis
    -compiler g++
    -Postgresql
    -librerie con2redis e con2db

    (Opzionale)
    - Se si vuole avviare anche il display è necessario Gtkmm 3.0,
      installabile in un environment linux attraverso i seguenti comandi:
      sudo apt install libgtkmm-3.0-dev
      sudo apt install libgstreamermm-1.0-dev
      Per il font basta fare doppio click sul file DS-DIGIT.TTF
    - Altrimenti è possibile eseguire il programma senza e leggere i print da console

Compilazione:

    - Versione display: 
      Spostarsi nella cartella models:
      Esesguire comando: make

    - Versione senza display:
      Spostarsi nella cartella models:
      Eseguire comando: make no_disp

    make clean per eliminare file oggetto e binari

Esecuzione:

    - Versione con display:
      avviare il file bash ./display.sh in un terminale
      avviare il file ./run.sh in un altro terminale
    
    - Versione senza display:
      avviare il file ./run.sh