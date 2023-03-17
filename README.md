# RetroWaveMIDIProxy

## Description
RetroWaveMIDIProxy is a software tool that connects modern DAWs and MIDI keyboards to RetroWave OPL3 hardware sound cards, allowing users to create authentic, vintage sounds in real-time. This software acts as a MIDI proxy, translating MIDI input into OPL3 commands that can be sent to the hardware synthesizer.

## Build
**Requirements**
- C++17 compatible compiler
- CMake 3.14+
- Qt5 libraries and header
- Platform-specific headers for MIDI support
- Working Internet connection

```shell
mkdir build
cd build
cmake ..
make -j `nproc`
```

## License
AGPLv3

## Acknowledgements
This project uses the following free software:
- rtmidi
- libADLMIDI
