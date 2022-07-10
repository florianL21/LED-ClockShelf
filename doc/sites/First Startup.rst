.. _first-startup:

############################
The first Startup
############################

After the code has been flashed to the ESP it's time to test it. Plug all the LEDs into the ESP and power it on.
You will be greeted with a nice loading animation on the LEDs of your clock.

.. note::
    This table only applies if you did not change any of the default colors

The color of the animation determines the state that the ESP is in:

+---------+--------------------------------------------------------------+
| Color   | Meaning                                                      |
+=========+==============================================================+
| Blue    | ESP is trying to connect to WIFI                             |
+---------+--------------------------------------------------------------+
| Orange  | ESP is in smart config mode and waiting for WIFI credentials |
+---------+--------------------------------------------------------------+
| Red     | Connection to the WIFI network was unsuccessful              |
+---------+--------------------------------------------------------------+

.. note::
    This only applies if you did not turn off the :code:`smart config` option.

- If you had the ESP you used connected to your WIFI before it will automatically reconnect and after a few seconds you should see the time showing up.
- If you are using a new ESP that does not know your WIFI details yet wait a few seconds until the LEDs indicate that the system entered smart config mode.
- Once in smart config mode you can use for example the `EspTouch app <https://play.google.com/store/apps/details?id=com.khoazero123.iot_esptouch_demo>`_ (only available on android) to let the ESP know your wifi credentials.
- After a successful connection the Clock will be displaying the current time.

.. note::
    If you would like to rather not use smart config you can also still go the good old way of hardcoding the WIFI name and password into the code. You can change this setting in your Configuration.h file.


- If you want to use the Blynk functionality do not forget to set your blynk auth token and template ID in your Configuration.h file.