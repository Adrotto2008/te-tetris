#!/bin/bash
# Script per eseguire la build del progetto

cd cmake-build-debug
cmake --build .

if [ $? -eq 0 ]; then
    echo "Build completata con successo!"
else
    echo "Errore durante la build!"
fi

