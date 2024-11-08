#include <iostream>

using namespace std;

class TV {
public:
    void TurnOn() {
        cout << "TV is turned on." << endl;
    }
    void TurnOff() {
        cout << "TV is turned off." << endl;
    }
    void SetChannel(int channel) {
        cout << "TV channel set to " << channel << "." << endl;
    }
};

class AudioSystem {
public:
    void TurnOn() {
        cout << "Audio system is turned on." << endl;
    }
    void TurnOff() {
        cout << "Audio system is turned off." << endl;
    }
    void SetVolume(int level) {
        cout << "Audio volume set to " << level << "." << endl;
    }
};

class DVDPlayer {
public:
    void Play() {
        cout << "DVD is playing." << endl;
    }
    void Pause() {
        cout << "DVD is paused." << endl;
    }
    void Stop() {
        cout << "DVD is stopped." << endl;
    }
};

class GameConsole {
public:
    void TurnOn() {
        cout << "Game console is turned on." << endl;
    }
    void StartGame() {
        cout << "Game is starting..." << endl;
    }
};

class HomeTheaterFacade {
    TV tv;
    AudioSystem audio;
    DVDPlayer dvd;
    GameConsole console;

public:
    void WatchMovie() {
        cout << "Preparing to watch a movie..." << endl;
        tv.TurnOn();
        audio.TurnOn();
        audio.SetVolume(7);
        dvd.Play();
    }

    void EndMovie() {
        cout << "Shutting down movie..." << endl;
        dvd.Stop();
        audio.TurnOff();
        tv.TurnOff();
    }

    void StartGameConsole() {
        cout << "Starting game console..." << endl;
        console.TurnOn();
        console.StartGame();
    }

    void ListenToMusic() {
        cout << "Setting up music mode..." << endl;
        tv.TurnOn();
        audio.TurnOn();
        audio.SetVolume(5);
    }

    void SetVolume(int level) {
        audio.SetVolume(level);
    }
};

int main() {
    HomeTheaterFacade homeTheater;

    homeTheater.WatchMovie();
    cout << endl;
    homeTheater.EndMovie();
    cout << endl;
    homeTheater.StartGameConsole();
    cout << endl;
    homeTheater.ListenToMusic();
    cout << endl;
    homeTheater.SetVolume(10);

    return 0;
}
