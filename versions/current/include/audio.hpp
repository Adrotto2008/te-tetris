#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <unordered_map>

class AudioManager {
public:


    // ===== MUSICA DI SOTTOFONDO =====
    void caricaMusiche(const std::string& cartella);
    bool avviaMusica(const std::string& file);
    void avviaMusicaCasuale();
    void aggiornaMusica();   // da chiamare nel game loop
    void fermaMusica();
    void setVolumeMusica(float volume);

    // ===== EFFETTI SONORI =====
    void caricaSuono(const std::string& nome, const std::string& file);
    void suona(const std::string& nome);
    void setVolumeSuoni(float volume);

private:
    // Musica
    sf::Music musica;
    std::vector<std::string> playlist;

    // Effetti sonori
    std::unordered_map<std::string, sf::SoundBuffer> buffers;
    std::unordered_map<std::string, sf::Sound> sounds;
};

