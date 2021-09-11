.. _setup:

############################
The Development environment
############################

I find the default Arduino IDE very hard to use if programming more than just basic functionality. This is why I decided to code all of this using Visual Studio code with PlatformIO.
It is free, easy to install, really powerful and almost as easy to use as the Arduino IDE.

********************************
Step by step installation guide
********************************

#. Install VSCode from the official microsoft page `here. <https://code.visualstudio.com/>`_
    To make things a bit easier you can enable the right click menu entry option during the VSCode installation.
#. Start VSCode and install PlatformIO from the extension menu in the sidebar.

    .. image:: ../images/PlatformIO-Install.jpg

#. Now download or clone the code from github, and put it to your hard drive. (Unzip it if you downloaded it)
#. Navigate to the folder where you put your code and right click to open the context menu and choose open VSCode here:

    .. image:: ../images/Open-VSCode.jpg

#. After waiting for all the plugins to load you should see a PlatformIO button in your sidebar. Click on it and choose Libraries:

    .. image:: ../images/PlatformIO-Libraries.jpg

#. From here install the following libraries:

    * "Blynk" by Volodymyr Shymanskyy
    * "FastLED" by Daniel Garcia
    * "LinkedList" by Ivan Seidel

#. Now navigate to the :code:`lib/LED_clock` folder and choose one of the :code:`library_*.json` files and rename it to :code:`library.json`. There are multiple already pre configured versions available. Simply choose the one which is closest to your hardware.
#. If needed you can modify the configuration parameters by editing the files in :code:`lib/LED_clock/Config/Setup/<chosen_version>` where :code:`<chosen_version>` should be the version of the json file you chose in step 7.
#. Now you can test if the build is working by hitting the little check mark icon in the bottom bar of VScode. Uploading to the target is done by clicking the arrow button, just like in the Arduino IDE. You don't need to worry about your COM port as PlatformIO is smart enough to figure it out automatically.
#. For information on how to setup WIFI and Blynk take a look at the :ref:`first-startup`