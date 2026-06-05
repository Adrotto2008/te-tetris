#!/bin/bash
# Script per compilare il cmake e avviare il gioco se ha successo

cd cmake-build-debug
echo "Compilazione in corso..."
cmake --build .

if [ $? -eq 0 ]; then
    echo "Compilazione completata con successo!"
    echo "Avvio del gioco..."
    cd ../bin
    ./avvio.sh
else
    echo "Errore durante la compilazione!"
    exit 1
fi

