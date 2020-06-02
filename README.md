# CMLS_FMSynth
CMLS Homework 3 , Group 2, Assignment 3 - FM Synthesizer by students:

- 10577360 
- 10650559 
- 10574134 
- 10532582

The goal of this homework is to realize an instrument based on FM synthesis and a graphic interface able to control its parameters. The synthesis part is implemented in SuperCollider, while the graphic interface is designed using JUCE. The source code files are:

• FMSynth.scd: SuperCollider file that contains the code for FM Synthesis,

• CMLS_FMSynth.jucer: JUCE project to build and display the GUI in JUCE. The source code of the GUI is inside source folder. 

The plugin CMLS_FMSynth UI can be tested using the AudioPluginHost environment and the FM synthesizer using SuperCollider.

1. Open SuperCollider interface, boot the server and and compile the definitions of Synthesizers, Network Adresses and OSCFunc responders. Now the FM Synthesizer is ready to receive incoming OSC messages and play the instruments.

2. Connect the MIDI input of the AudioPluginHost to the MIDI input of the CMLS_FMSynth to provide the audio plugin the MIDI messages to be sound using an external MIDI key- board or a virtual one. You can control the sound output using the knobs, sliders, menus and buttons.
