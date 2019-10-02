#define     GUI_VERSION         20


#define		SCREEN_WIDTH		1280
#define		SCREEN_HEIGHT		720
#define		LEFT_SIZE			8
#define		TOP_HEIGHT			40
#define		TOP_SIZE				8
#define		BOTTOM_HEIGHT		40
#define		BOTTOM				( SCREEN_HEIGHT - BOTTOM_HEIGHT )

#define		BUTTON_HEIGHT		32
#define		BUTTON_WIDTH		120
#define		BUTTON_BOTTOM		( SCREEN_HEIGHT - BUTTON_HEIGHT - 4)

#define		BATTERY_WIDTH		42
#define		BATTERY_HEIGHT		24

#define		ICON_SIZE			200
#define		ICON_NUM			7
#define		ICON_SELECT_SIZE	280


#define     HELP_WINDOW_LEFT        0
#define     HELP_WINDOW_WIDTH       ( SCREEN_WIDTH / 3 )
#define     SETTING_WINDOW_LEFT     ( SCREEN_WIDTH * 2 / 3 + 1)
#define     SETTING_WINDOW_WIDTH    ( SCREEN_WIDTH / 3 )
#define     WINDOW_HEIGHT           ( SCREEN_HEIGHT - TOP_HEIGHT - BOTTOM_HEIGHT )
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
//┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
//┃─┐┌──┐┌──┐┌──┐┌────┐┌──┐┌──┐┌──┐┌─┃
//┃ ││  ││  ││  ││    ││  ││  ││  ││ ┃
//┃─┘└──┘└──┘└──┘│    │└──┘└──┘└──┘└─┃
//┃              └────┘              ┃
//     1   2   3    4    5   6   7
//

#define		TEMP_PATH			"sdmc:/onsemu/temp"
#define		PATH				"sdmc:/onsemu"
#define		EXEPATH				"sdmc:/onsemu/exefs"
#define		DATA_PATH			"sdmc:/onsemu/onsdata"
#define		DEFAULT_ICON		"sdmc:/onsemu/onsdata/default_icon.png"
#define		DEFAULT_FONT		"sdmc:/onsemu/onsdata/default_font.ttf"

#define		CONFIG				"sdmc:/onsemu/onsdata/config.cfg"
#define		CMD_FILE			"startup.cfg"
