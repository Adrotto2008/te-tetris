#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class AudioManager {
public:
    void caricaMusiche(const std::string& cartella);
    bool avviaMusica(const std::string& file);
    void avviaMusicaCasuale();
    void aggiornaMusica();   
    void fermaMusica();
    void setVolumeMusica(float volume);

    void caricaSuono(const std::string& nome, const std::string& file);
    void suona(const std::string& nome);
    void setVolumeSuoni(float volume);

private:
    sf::Music musica;
    std::vector<std::string> playlist;

    std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> buffers;
    std::unordered_map<std::string, std::shared_ptr<sf::Sound>> sounds;
};
