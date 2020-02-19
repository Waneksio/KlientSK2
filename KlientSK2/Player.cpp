//
// Created by matt on 18.02.20.
//

#include "Player.h"

Player::Player(int x, int y, int size, int id) {
    mX = x;
    mY = y;
    mSize = size;
    mId = id;
}

void Player::move(int newX, int newY, int newSize) {
    mX = newX;
    mY = newY;
    mSize = newSize;
}
