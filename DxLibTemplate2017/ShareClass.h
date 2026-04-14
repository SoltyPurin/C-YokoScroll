#pragma once
struct PlayerImages {
    int _idle;
    int _move1;
    int _move2;
    int _jump;
    int _throw;
    int _skateRide;
    int _skateBrake;
    int _blowAway;
};


class ShareClass
{
public:
    ShareClass();
    ~ShareClass();
    static void GetImages();
    static void ReleaseImages();
	static float KoteiValue;
    static PlayerImages _playerImage;
};

