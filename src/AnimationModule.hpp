#pragma once
#include <map>
#include <raylib.h>
#include <vector>


// animation classes
class AnimObject {
    public:
        bool isBasic = true;

        // basic anim
        double current{};
        double start{};
        double end{};

        // spritesheet anim
        int frames{};
        int frameWidth{};
        int frameHeight{};
        bool loop{};

        // all anims
        double startTime;
        double length;
        double timePassed;

        AnimObject(double start, double end, double length, double offset);

        AnimObject(int frames, int frameWidth, int frameHeight, double length, bool loop, float offset);
};


class AnimHandler {
    std::map<int, AnimObject> playingAnims;

    public:
        double quadraticInOut(int id);
        double quadraticIn(int id);
        double quadraticOut(int id);
        double linear(int id);

        Rectangle spriteAnim(int id);

        void createAnim(int id, float startV, float endV, float length, float offset = 0.0f);
        void createSpriteAnim(int id, int frameAmount, int frameW, int frameH, float length, bool loop = false, float offset = 0.0f);
        void overrideAnim(int id, float startV, float endV, float length, float offset = 0.0f);

        void stopAnim(int id);
        void stopAnims(const std::vector<int>& ids);

        AnimObject getAnim(int id);
        bool animFinished(int id);
};