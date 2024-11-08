#include <iostream>
using namespace std;

class AudioSystem {
public:
    void TurnOn() {
        cout << "Audio system is turned on." << endl;
    }
    void SetVolume(int level) {
        cout << "Audio volume is set to " << level << "." << endl;
    }
    void TurnOff() {
        cout << "Audio system is turned off." << endl;
    }
};

class VideoProjector {
public:
    void TurnOn() {
        cout << "Video projector is turned on." << endl;
    }
    void SetResolution(const string& resolution) {
        cout << "Video resolution is set to " << resolution << "." << endl;
    }
    void TurnOff() {
        cout << "Video projector is turned off." << endl;
    }
};

class LightingSystem {
public:
    void TurnOn() {
        cout << "Lights are turned on." << endl;
    }
    void SetBrightness(int level) {
        cout << "Lights brightness is set to " << level << "." << endl;
    }
    void TurnOff() {
        cout << "Lights are turned off." << endl;
    }
};

class HomeTheaterFacade {
    AudioSystem audio;
    VideoProjector projector;
    LightingSystem lights;

public:
    void StartMovie() {
        cout << "Preparing to start the movie..." << endl;
        lights.TurnOn();
        lights.SetBrightness(5);
        audio.TurnOn();
        audio.SetVolume(8);
        projector.TurnOn();
        projector.SetResolution("HD");
        cout << "Movie started." << endl;
    }

    void EndMovie() {
        cout << "Shutting down movie..." << endl;
        projector.TurnOff();
        audio.TurnOff();
        lights.TurnOff();
        cout << "Movie ended." << endl;
    }
};

int main() {
    HomeTheaterFacade homeTheater;

    homeTheater.StartMovie();
    cout << endl;
    homeTheater.EndMovie();

    return 0;
}
