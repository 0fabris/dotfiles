/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Terminus:size=15" };
static const char dmenufont[]       = "Terminus:size=15";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

//Custom Keys
#define XK_VolDown 	0x1008ff11
#define XK_VolMute 	0x1008ff12
#define XK_VolUp 	0x1008ff13
#define XK_MicMute 	0x1008ffb2
#define XK_Launch 	0x1008ff41
#define XK_BrightUp 	0x1008ff02
#define XK_BrightDn 	0x1008ff03
/* #define XK_Print 0xff61 */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "uxterm", NULL };

//Audio Control
static const char *volup[] = { "pactl", "set-sink-volume", "0", "+1%",    NULL };
static const char *voldown[] = { "pactl", "set-sink-volume", "0", "-1%",    NULL };
static const char *volmute[] = { "pactl", "set-sink-mute",   "0", "toggle", NULL };
static const char *micmute[] = { "thinkpad-mutemic", NULL};
/*
 * static const char *volup[] = { "amixer", "sset", "'master'", "1dB+", NULL};
 * static const char *voldown[] = { "amixer", "sset", "'master'", "1dB-", NULL};
 * static const char *volmute[] = { "amixer", "sset", "'master'", "toggle", NULL};
 */
//Backlight Control
#define light_step "3"
static const char *backlightincr[] = {"light", "-A", light_step, NULL};
static const char *backlightdecr[] = {"light", "-U", light_step, NULL};

//Custom Commands
static const char *firefoxcmd[] = {"firefox",NULL};
static const char *shutdown[] = {"poweroff", NULL};
static const char *reboot[] = {"reboot", NULL};
static const char *chromiumcmd[] = {"chromium", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	//dmenu
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	//spawn terminal
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	
	//Toggle Bar
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	
	//Window properties
	{ MODKEY,                       XK_Right,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_k,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	
	//Back to last view
	{ MODKEY,                       XK_Tab,    view,           {0} },
	
	//Close Screen
	{ MODKEY,             		XK_t,      killclient,     {0} },
	
	//Layouts
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY,			XK_space,  togglefloating, {0} },
	
	//Tab Selector and Tags
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	
	//Tab Changers
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	
	//Close dwm
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	//Custom Commands
	{ MODKEY|ShiftMask,		XK_f,	   spawn,	{.v =firefoxcmd}},
	{ MODKEY|ShiftMask, 		XK_c,      spawn, 	{.v = chromiumcmd }},
	{ MODKEY,			XK_r,      spawn, 	SHCMD("uxterm -e 'ranger \"$HOME\"'")},
	{ 0,			 	XK_Launch, spawn,	SHCMD("uxterm -e 'htop && exit'")},
	{ MODKEY, 			XK_Launch, spawn,	{.v = shutdown}},
	{ MODKEY|ShiftMask,		XK_Launch, spawn,	{.v = reboot  }},	
	{ 0,				XK_BrightUp, spawn,	{.v = backlightincr}},
	{ 0, 				XK_BrightDn, spawn, 	{.v = backlightdecr}},
	{ 0,				XK_VolUp, spawn,	{.v = volup}},
	{ 0, 				XK_VolDown, spawn, 	{.v = voldown}},
	{ 0,				XK_VolMute, spawn,	{.v = volmute}},
	{ 0,				XK_MicMute, spawn,	{.v = micmute}},
	{ 0,				XK_Print, spawn,	SHCMD("maim \"$HOME/Screenshot/$(date +%s).png\"")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

