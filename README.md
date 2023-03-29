# Conway's Game of Life

By Nevin Bonak and Patrick Niccolai

## Summary
Conway's Game of Life is a cellular automaton created by John Horton Conway.
The simulation is a grid with cells that are either alive (white) or dead (black).
The simulation works by applying rules to each cell which will, under the 
right condition cause a cell to change from alive to dead or vice versa. 

## Directions
This program will work as long as the computer has glut working.

For Mac, glut should work with no setup.

For Windows, follow these steps (From the graphics-starter lab)

    Unzip/extract the freeglut zip file (From the graphics-starter lab).
    
    Add a freeglut folder in this directory: C:/Program Files/Common Files/freeglut/
    
    Copy the include/ and lib/ folders from freeglut into that freeglut/ folder.
    
    Add freeglut.dll from freeglut/bin/ to the cmake-build-debug/ folder.
    
        Note: You will need to do this for every CLion graphics project you create.
        
    When you run the project, a black square graphics window should appear. You can press the escape key to exit.
    
    Troubleshooting:

        Q: Why am I getting a long, strange non-zero exit code?

        A: You may need to change the freeglut.dll file in the bin folder to the x64 version. In your freeglut download, the bin folder should have an x64 folder with freeglut.dll inside. Put that one in your CLion project cmake-build-debug folder.

        Q: Why does it say it cannot configure my lib files?

        A: You are using a 64-bit machine. Modify the following line in CMakeLists.txt:

        set(FREEGLUT_LIBRARY_DIRS "C:/Program\ Files/Common\ Files/freeglut/lib")

        to direct it into the x64 folder:

        set(FREEGLUT_LIBRARY_DIRS "C:/Program\ Files/Common\ Files/freeglut/lib/x64")
