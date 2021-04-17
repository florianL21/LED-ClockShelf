.. _Advanced-config:

# Tweaking and adding animations

All animations are highly adjustable. First let's talk about the animations that come reconfigured in the code.
<br>
<br>
The most important animations in the system are the ones that are responsible for morphing one digit into another to provide a smooth transition.
These animations are defined in the file `/src/SevenSegment/SegmentTransitions.cpp`
But there is one additional animation that I provide with my code, and that is the startup loading animation. This animation can be found in the file `/src/DisplayManager/Animations.cpp` but it basically works exactly the same as the others.

## Changing animations
An animation consists of the following essentials:
 - A global struct variable that holds all the animation information.
 - An initialization function that is responsible for populating the values to the above mentioned variable.

Each animation has a number of steps, it must at least be one and it can be as many as you desire.
With each step multiple animations can be started, and as soon as they are finished all animations of the next step will be started.
Each step has two arrays. One array defines all the indices for which the animations shall be started. These indices are used to address the objects inside the AnimationObject array that has to be passed to the start animation function. the second array defines the actual animation effect for each of the objects.
The size of the arrays for each animation step has to be the same for all steps within one animation! And the `animationComplexity` attribute is set to the same value! Otherwise the system WILL CRASH!
If you need let's say 5 animations at once in the first step but only one in the second one you have to fill all unused array positions with `-1` for the indices. For the animations effects it does not matter but I fill them with 0 to make it clearer that there is nothing happening there.


## Adding new animations
If you want to create new transitions between two digits that currently do not have a animation just add a `ComplexAnimation` variable and a corresponding init function prototype to the `SevenSegmentTransitions.cpp` file. Simply following the example of the already defined animations. You should also add a definition to the new local variable to the `SevenSegmentTransitions.h` file and declare it as extern.
To register your new Animation to be called when the digits change simply add it to the TransformationLookupTable array at the right spot. There are comments there making it clear where you have to put the new animation.