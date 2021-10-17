#pragma once
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <vector>
#include <iostream>
using namespace sf;

class Textures {
public:
    std::vector<Texture> players;
    int n;
    Textures() {
        
    }
    void loadTextures(int n) {
        this->n = n;
        players.resize(n);
        for (int i = 0; i < n; ++i) {
            players[i].loadFromFile("Players/player" + std::to_string(i) + ".png");
            players[i].setRepeated(1);
        }
    }
    Texture& getTexture(int figure) {
        assert(figure < n && figure >= 0);
        return players[figure];
    }
};