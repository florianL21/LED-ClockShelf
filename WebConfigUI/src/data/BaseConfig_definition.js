const definition = [
    {
      label: "Enable Blynk functionality",
      type: "bool",
      target: "ENABLE_BLYNK"
    },
    {
      label: "Blynk Auth token",
      type: "string",
      target: "BLYNK_AUTH_TOKEN",
      onlyIf: "ENABLE_BLYNK"
    },
    {
      label: "Blynk server URL",
      type: "string",
      target: "BLYNK_SERVER",
      onlyIf: "ENABLE_BLYNK"
    },
    {
      label: "Enable OTA Updates",
      type: "bool",
      target: "OTA_UPLOAD"
    },
    {
      label: "Host name",
      type: "string",
      target: "HOST_NAME"
    },
    {
      label: "Number of retries for WIFI reconnection before smart config is started (if enabled)",
      type: "int",
      target: "NUM_RETRIES",
      min: 1,
      max: 1000
    },
    {
      label: "Enable Smart config if WIFI connection was lost",
      type: "bool",
      target: "SMART_CONFIG"
    },
    {
      label: "NTP server URL",
      type: "string",
      target: "NTP_SERVER"
    },
    {
      label: "Enter a configuration string for you timezone according to this website: https://remotemonitoringsystems.ca/time-zone-abbreviations.php",
      type: "string",
      target: "TIMEZONE_INFO"
    },
    {
      label: "Time in seconds for the interval in which the time should be synchronized with the time (NTP) server",
      type: "int",
      target: "TIME_SYNC_INTERVAL",
      min: 1,
      max: 4294967295
    },
    {
      label: "Flash the current time in case a timer is expired instead of flashing 00:00",
      type: "bool",
      target: "TIMER_FLASH_TIME"
    },
    {
      label: "Number of flashes until an alarm is considered expired and the system goes back to normal",
      type: "int",
      target: "TIMER_FLASH_COUNT",
      min: 1,
      max: 65535
    },
    {
      label: "For how long the Display should flash when an alarm was fired in seconds. For example: An Alarm for 12:00 would stop flashing at 12:01 if this was set to 60",
      type: "int",
      target: "ALARM_NOTIFICATION_PERIOD",
      min: 1,
      max: 65535
    },
    {
      label: "How bright the clock should flash when an alarm or timer was triggered",
      type: "int",
      target: "NOTIFICATION_BRIGHTNESS",
      min: 0,
      max: 255
    },
    {
      label: "How often the time on the displays is updated in MS",
      type: "int",
      target: "TIME_UPDATE_INTERVAL",
      min: 1,
      max: 65535
    },
    {
      label: "If turned on the display will show 0 at midnight and 12 otherwise",
      type: "bool",
      target: "DISPLAY_0_AT_MIDNIGHT",
    },
    {
      label: "If turned on the higher digit displays will turn off in case they would show 0",
      type: "bool",
      target: "DISPLAY_SWITCH_OFF_AT_0"
    },
    {
      label: "If set to true 24 hour format will be used. Only usable if the hour display has all 7 segments",
      type: "bool",
      target: "USE_24_HOUR_FORMAT"
    },
    {
      label: "The time it shall take for one iteration of the loading animation",
      type: "int",
      target: "LOADING_ANIMATION_DURATION",
      min: 1,
      max: 65535
    },
    {
      label: "How fast the brightness interpolation shall react to brightness changes",
      type: "int",
      target: "BRIGHTNESS_INTERPOLATION",
      min: 1,
      max: 65535
    },
    {
      label: "Target frames per second for the smoothness of animations",
      type: "int",
      target: "ANIMATION_TARGET_FPS",
      min: 1,
      max: 255
    },
    {
      label: "Length of sooth animation transition from fully on to black and vice versa in percent. NOTE: The higher this number the less obvious easing effects like bounce or elastic will be",
      type: "float",
      target: "ANIMATION_AFTERGLOW",
      min: 0,
      max: 1
    },
    {
      label: "Length of the dot/s fading animation in MS. One flash fades in and out",
      type: "int",
      target: "DOT_FLASH_SPEED",
      min: 1,
      max: 65535
    },
    {
      label: "Interval in MS in which the dot/s should flash",
      type: "int",
      target: "DOT_FLASH_INTERVAL",
      min: 1,
      max: 65535
    },
    {
      label: "Number of separation dots that shall be displayed",
      type: "int",
      target: "NUM_SEPARATION_DOTS",
      min: 0,
      max: 2
    },
    {
      label: "The time it takes in MS for one digit to morph into another",
      type: "int",
      target: "DIGIT_ANIMATION_SPEED",
      min: 1,
      max: 65535
    },
];

export default definition;