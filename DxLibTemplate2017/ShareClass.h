#pragma once
struct NormalPlayerImages {
    int _idle;
    int _move1;
    int _move2;
    int _jump;
    int _throw;
};

struct SkatePlayerImages {
    int _ride;
    int _brake;
};

class ShareClass
{
public:
    ShareClass();
    ~ShareClass();
    static void GetImages();
    static void ReleaseImages();
	static float KoteiValue;
    static NormalPlayerImages _normalImage;
    static SkatePlayerImages _skateImage;
};

