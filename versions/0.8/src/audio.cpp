#include "audio.hpp"

#include <filesystem>
#include <random>
#include <iostream>

namespace fs = std::filesystem;




void AudioManager::caricaMusiche(const std::string& cartella) {
    playlist.clear();

    if (!fs::exists(cartella) || !fs::is_directory(cartella)) {
        std::cerr << "Cartella musica non trovata: " << cartella << std::endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(cartella)) {
        if (!entry.is_regular_file())
            continue;

        auto est = entry.path().extension().string();
        if (est == ".mp3" || est == ".ogg" || est == ".wav") {
            playlist.push_back(entry.path().string());
        }
    }

    if (playlist.empty()) {
        std::cerr << "Nessun file audio trovato in: " << cartella << std::endl;
    }
}

bool AudioManager::avviaMusica(const std::string& file){

    if (!musica.openFromFile(file)) {
        std::cerr << "Errore caricando musica: " << file << std::endl;
        return false;
    } 

    musica.play();
    return true;


}

void AudioManager::avviaMusicaCasuale() {
    if (playlist.empty())
        return;

    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<size_t> dist(0, playlist.size() - 1);

    const std::string& file = playlist[dist(rng)];

    avviaMusica(file);

}

void AudioManager::aggiornaMusica() {
    if (musica.getStatus() == sf::Music::Stopped) {
        avviaMusicaCasuale();
    }
}

void AudioManager::fermaMusica() {
    musica.stop();
}

void AudioManager::setVolumeMusica(float volume) {
    musica.setVolume(volume);
}

void AudioManager::setVolumeSuoni(float volume) {
    for (auto& [nome, sound] : sounds) {
        sound.setVolume(volume);
    }
}


void AudioManager::caricaSuono(const std::string& nome, const std::string& file) {
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile("../sounds/sfx/" + file + ".wav")) {
        std::cerr << "Errore caricando suono: " << file << std::endl;
        return;
    }

    buffers[nome] = buffer;

    sf::Sound sound;
    sound.setBuffer(buffers[nome]);

    sounds[nome] = sound;
}

void AudioManager::suona(const std::string& nome) {
    auto it = sounds.find(nome);
    if (it != sounds.end()) {
        it->second.play();
    }
}


