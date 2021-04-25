export const BaseSettings = [
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

export const ColorSettings = [
	{
		label: "Color of the hour segments",
		type: "color",
		target: "HOUR",
		min: 0,
		max: 16777215
	},
	{
		label: "Color of the minute segments",
		type: "int",
		target: "MINUTE",
		min: 0,
		max: 16777215
	},
	{
		label: "Color of the internal LEDs",
		type: "int",
		target: "INTERNAL",
		min: 0,
		max: 16777215
	},
	{
		label: "Color of the separation dot LEDs",
		type: "int",
		target: "SEPARATION_DOT",
		min: 0,
		max: 16777215
	},
	{
		label: "Color of the LEDs for the OTA update progress bar",
		type: "int",
		target: "OTA_UPDATE",
		min: 0,
		max: 16777215
	},
	{
		label: "Color of the LEDs while searching for a WIFI network",
		type: "int",
		target: "WIFI_CONNECTING",
		min: 0,
		max: 16777215
	},
	{
		label: "Color of the LEDs signaling a successful WIFI connection",
		type: "int",
		target: "WIFI_CONNECTION_SUCCESSFUL",
		min: 0,
		max: 16777215
	},
	{
		label: "Color of the LEDs if system is waiting for WIFI smart config",
		type: "int",
		target: "WIFI_SMART_CONFIG",
		min: 0,
		max: 16777215
	},
	{
		label: "Color of the LEDs signaling an error of some sort",
		type: "int",
		target: "ERROR",
		min: 0,
		max: 16777215
	},
];

export const HWSettings = [
	{
		label: "Pin to which the led strip data pin is connected to",
		type: "int",
		target: "LED_DATA_PIN",
		min: 0,
		max: 42
	},
	{
		label: "Total number of segments that have LEDs in the shelf",
		type: "int",
		target: "NUM_SEGMENTS",
		min: 1,
		max: 65535
	},
	{
		label: "Number of LEDs in each segment",
		type: "int",
		target: "NUM_LEDS_PER_SEGMENT",
		min: 1,
		max: 255
	},
	{
		label: "If you wired the down lighter LEDs to the end of the LED strips set this to true",
		type: "bool",
		target: "APPEND_DOWN_LIGHTERS"
	},
	{
		label: "If you wired the down lighter LEDs to the end of the LED strips enable this",
		type: "int",
		target: "DOWNLIGHT_LED_DATA_PIN",
		min: 0,
		max: 42,
		onlyIf: "!APPEND_DOWN_LIGHTERS"
	},
	{
		label: "Number of LEDs For interior lights",
		type: "int",
		target: "ADDITIONAL_LEDS",
		min: 0,
		max: 65535
	},
	{
		label: "Number of seven segment displays on the clock",
		type: "int",
		target: "NUM_DISPLAYS",
		min: 4,
		max: 7
	},
	{
		label: "The number of segments to use for displaying a progress bar for the OTA updates. ATTENTION: this also depends on the configured animation which is used",
		type: "int",
		target: "NUM_SEGMENTS_PROGRESS",
		min: 1,
		max: 65535
	},
	//TODO: make a dropdown for this
	{
		label: "The display on which the separation dot should be shown",
		type: "enum selector",
		target: "DISPLAY_FOR_SEPARATION_DOT",
		enum: "DisplayIDs",
		min: 1,
		max: 7
	},
	//TODO: Make UI element to disable individual displays
	{
		label: "The indices of the displays in the order they are configured in",
		type: "customizable enum",
		elements: [
			{target: "HIGHER_DIGIT_HOUR_DISPLAY", label: "Higher digit hour display"},
			{target: "FIRST_INTERMEDIATE_DISPLAY", label: "First intermediate display"},
			{target: "LOWER_DIGIT_HOUR_DISPLAY", label: "Lower digit hour display"},
			{target: "SECOND_INTERMEDIATE_DISPLAY", label: "Second intermediate display"},
			{target: "HIGHER_DIGIT_MINUTE_DISPLAY", label: "Higher digit minute display"},
			{target: "THIRD_INTERMEDIATE_DISPLAY", label: "Third intermediate display"},
			{target: "LOWER_DIGIT_MINUTE_DISPLAY", label: "Lower digit minute display"}
		],
		target: "DisplayIDs",
		deactivated: -1,
		min: 1,
		max: 7
	},
	{
		label: "Enable automatic brightness adjustments based on a light sensor",
		type: "bool",
		target: "ENABLE_LIGHT_SENSOR"
	},
	{
		label: "ADC pin to which the light sensor is connected to",
		type: "int",
		target: "LIGHT_SENSOR_PIN",
		min: 0,
		max: 42,
		onlyIf: "ENABLE_LIGHT_SENSOR"
	},
	{
		label: "How many measurements shall be averaged. Higher number -> smoother but slower change",
		type: "int",
		target: "LIGHT_SENSOR_AVERAGE",
		min: 0,
		max: 255,
		onlyIf: "ENABLE_LIGHT_SENSOR"
	},
	{
		label: "Width of the median calculation. Higher number -> smoother change Should never be higher than the LIGHT_SENSOR_AVERAGE",
		type: "int",
		target: "LIGHT_SENSOR_MEDIAN_WIDTH",
		min: 0,
		max: "LIGHT_SENSOR_AVERAGE",
		onlyIf: "ENABLE_LIGHT_SENSOR"
	},
	{
		label: "Time that should pass in MS before the light sensor is read again. Higher number -> slower adjustments but also changes will be more sudden",
		type: "int",
		target: "LIGHT_SENSOR_READ_DELAY",
		min: 0,
		max: 65535,
		onlyIf: "ENABLE_LIGHT_SENSOR"
	},
	{
		label: "AnalogRead value if the light sensor reads complete darkness",
		type: "int",
		target: "LIGHT_SENSOR_MIN",
		min: 0,
		max: 4095,
		onlyIf: "ENABLE_LIGHT_SENSOR"
	},
	{
		label: "AnalogRead value if the light sensor reads the brightest",
		type: "int",
		target: "LIGHT_SENSOR_MAX",
		min: 0,
		max: 4095,
		onlyIf: "ENABLE_LIGHT_SENSOR"
	},
	{
		label: "How much the can the light sensor values influence the led brightness",
		type: "int",
		target: "LIGHT_SENSOR_SENSITIVITY",
		min: 0,
		max: 255,
		onlyIf: "ENABLE_LIGHT_SENSOR"
	},
	{
		label: "(Debugging Feature) Enable for a demo of all the digit transitions",
		type: "bool",
		target: "TIME_MANAGER_DEMO_MODE"
	},
	{
		label: "(Debugging Feature) The minimum delay between led updates in MS. Usually anything faster than 20MS causes problems. Increase if your LEDs do not refresh properly",
		type: "int",
		target: "FASTLED_SAFE_DELAY_MS",
		min: 0,
		max: 65535,
	},
];
