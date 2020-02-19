//
// Created by matt on 18.02.20.
//

#ifndef KLIENTSK2_PLAYER_H
#define KLIENTSK2_PLAYER_H


class Player {
public:
    int mX;
    int mY;
    int mSize;
    int mId;
    Player(int x, int y, int size, int id);
    void move(int newX, int newY, int newSize);
};


#endif //KLIENTSK2_PLAYER_H
