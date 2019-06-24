#define		SCREEN_WIDTH		1280
#define		SCREEN_HEIGHT		720
#define		LEFT				8
#define		TOP_HEIGHT			40
#define		TOP					8
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
//┏━━━━━━━━━━━━━━━━━━━━┓
//┣━━━━━━━━━━━━━━━━━━━━┫
//┃─┐┌─┐┌─┐┌──┐┌─┐┌─┐┌─┃
//┃  ││  ││  ││    ││  ││  ││  ┃
//┃─┘└─┘└─┘│    │└─┘└─┘└─┃
//┃                └──┘                ┃
//  1     2     3      4      5      6    7
//
#define		PATH				"sdmc:/onsemu"
#define		DATA_PATH			"sdmc:/onsemu/onsdata"
#define		DEFAULT_ICON		"sdmc:/onsemu/onsdata/default_icon.png"
#define		DEFAULT_FONT		"sdmc:/onsemu/onsdata/default_font.ttf"

#define		CONFIG				"sdmc:/onsemu/onsdata/config.cfg"
#define		CMD_FILE			"startup.cfg"
