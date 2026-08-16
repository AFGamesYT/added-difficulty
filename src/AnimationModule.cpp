#include "AnimationModule.hpp"

#include <cmath>

AnimObject::AnimObject(double start, double end, double length, double offset)
{
    this->start = start;
    this->end = end;
    this->length = length;

    startTime = GetTime() - offset;
    timePassed = 0;
}

AnimObject::AnimObject(int frames, int frameWidth, int frameHeight, double length, bool loop, float offset)
{
    isBasic = false;

    this->frames = frames;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->length = length;
    this->loop = loop;

    startTime = GetTime() - offset;
    timePassed = 0;
}

double AnimHandler::quadraticInOut(int id) {
    AnimObject &anim = playingAnims.at(id);

    if (!anim.isBasic) return 0.0f;

    const double t = (GetTime() - anim.startTime) / anim.length;

    double x;
    if (t >= 1) {
        x = 1;
    } else {
        x = t < 0.5 ? t*t*2 : -1+(4-2*t)*t;
    }

    anim.timePassed = GetTime() - anim.startTime;

    anim.current = anim.start + (anim.end - anim.start) * x;

    return anim.start + (anim.end - anim.start) * x;
}

double AnimHandler::quadraticIn(int id) {
    AnimObject &anim = playingAnims.at(id);

    if (!anim.isBasic) return 0.0f;

    const double t = (GetTime() - anim.startTime) / anim.length;

    double x;
    if (t >= 1) {
        x = 1;
    } else {
        x = t*t;
    }

    anim.timePassed = GetTime() - anim.startTime;

    anim.current = anim.start + (anim.end - anim.start) * x;

    return anim.start + (anim.end - anim.start) * x;
}

double AnimHandler::quadraticOut(int id) {
    AnimObject &anim = playingAnims.at(id);

    if (!anim.isBasic) return 0.0f;

    const double t = (GetTime() - anim.startTime) / anim.length;

    double x;
    if (t >= 1) {
        x = 1;
    } else {
        x = t * (2 - t);
    }

    anim.timePassed = GetTime() - anim.startTime;

    anim.current = anim.start + (anim.end - anim.start) * x;

    return anim.start + (anim.end - anim.start) * x;
}

double AnimHandler::linear(int id) {
    AnimObject &anim = playingAnims.at(id);

    if (!anim.isBasic) return 0.0f;

    const double t = (GetTime() - anim.startTime) / anim.length;

    double x;
    if (t >= 1) {
        x = 1;
    } else {
        x = t;
    }

    anim.timePassed = GetTime() - anim.startTime;

    anim.current = anim.start + (anim.end - anim.start) * x;

    return anim.start + (anim.end - anim.start) * x;
}

Rectangle AnimHandler::spriteAnim(int id) {
    AnimObject &anim = playingAnims.at(id);

    if (!anim.isBasic) {
        double t = (GetTime() - anim.startTime) / anim.length;

        int i = t*anim.frames;
        if (t >= 1) {
            if (anim.loop) {
                t = std::fmod(t, 1);
            } else {
                i = anim.frames - 1;
            }
        }

        anim.timePassed = GetTime() - anim.startTime;

        return Rectangle{(float)anim.frameWidth*i, 0, (float)anim.frameWidth, (float)anim.frameHeight};
    }
    return Rectangle{0, 0, 0, 0};
}

void AnimHandler::createAnim(int id, float startV, float endV, float length, float offset) { // create a basic anim | quadratic, linear
    if (playingAnims.count(id) != 1) {
        playingAnims.insert({id, AnimObject(startV, endV, length, offset)});
    }
}

void AnimHandler::createSpriteAnim(int id, int frameAmount, int frameW, int frameH, float length, bool loop, float offset) { // create a spritesheet anim | spriteAnim()
    if (playingAnims.count(id) != 1) {
        playingAnims.insert({id, AnimObject(frameAmount, frameW, frameH, length, loop, offset)});
    }
}

void AnimHandler::overrideAnim(int id, float startV, float endV, float length, float offset) {
    playingAnims.at(id) = AnimObject(startV, endV, length, offset);
}

AnimObject AnimHandler::getAnim(int id) {
    return playingAnims.at(id);
}

bool AnimHandler::animFinished(int id) {
    return playingAnims.at(id).timePassed >= playingAnims.at(id).length;
}

void AnimHandler::stopAnim(int id) {
    if (playingAnims.count(id) > 0) playingAnims.erase(id);
}

void AnimHandler::stopAnims(const std::vector<int>& ids) {
    for (const int id : ids) {
        stopAnim(id);
    }
}

