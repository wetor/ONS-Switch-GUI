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
//------------------Default Config------------------------
//top text
#define		TEXT_TITLE			"ONScripter-Jh for Nintendo Switch"

#define		TEXT_0_0			"版本:"
#define		TEXT_0_1			"帮助"
#define		TEXT_0_2			"确认"
#define		TEXT_0_3			"返回"
#define		TEXT_0_4			"信息"
#define		TEXT_0_5			"资源查看"
#define		TEXT_0_6			"刷新"
#define		TEXT_0_7			"未发现ONS游戏！请将ONS游戏文件夹放至储存卡的\"/onsemu\"文件夹中。"


#define		TEXT_1_0			"Version:"
#define		TEXT_1_1			"Help"
#define		TEXT_1_2			"OK"
#define		TEXT_1_3			"Back"
#define		TEXT_1_4			"Info"
#define		TEXT_1_5			"Resource"
#define		TEXT_1_6			"Refresh"
#define		TEXT_1_7			"Not found ONS-Game. Please put ONS-Game-Directory in \"sdmc:/onsemu/\"."


//------------------Default Config------------------------