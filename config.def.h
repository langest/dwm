/* See LICENSE file for copyright and license details. */

/* appearance */

/* #define ORANGE    "#F26101" Orange that fits the colorscheme */
#define WHITE     "#eff0f1"
#define BLUE      "#3daee9"
#define BLACK     "#2D2D2D"

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = { "Inconsolata:size=11", "WenQuanYi Micro Hei:size=11", };
static const char dmenufont[] = "-*-Inconsolata-medium-r-*-*-16-*-*-*-*-*-*-*";

static const char col_fg_normal[]      = BLUE;
static const char col_bg_normal[]      = BLACK;
static const char col_boarder_normal[] = BLACK;
static const char col_fg_selected[]    = BLUE;
static const char col_bg_selected[]    = WHITE;
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg_normal, col_bg_normal, col_boarder_normal },
	[SchemeSel]  = { col_fg_selected, col_bg_selected,  col_bg_selected  },
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title       tags mask     isfloating   monitor */
	{ "Gimp",        NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",     NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Thunderbird", NULL,       NULL,       1 << 7,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]       = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg_normal, "-nf", col_fg_normal, "-sb", col_bg_selected, "-sf", col_fg_selected, NULL };
static const char *termcmd[]        = { "urxvtc", NULL };
static const char *firefoxcmd[]     = { "firefox", NULL };
static const char *thunderbirdcmd[] = { "thunderbird", NULL };
static const char *lockcmd[]        = { "sh", "/home/langest/dotfiles/scripts/lock.sh", NULL };
/*
static const char *mpdPrev[]        = { "mpc", "prev", NULL };
static const char *mpdNext[]        = { "mpc", "next", NULL };
static const char *mpdPlayPause[]   = { "mpc", "toggle", NULL };
static const char *mpdPlayStop[]    = { "mpc", "stop", NULL };
*/
static const char *randomwp[]       = { "feh", "--randomize", "--recursive", "--bg-fill", "/home/langest/currentWps/", NULL };
static const char *wicdgtk[]        = { "wicd-gtk", "--no-tray", NULL };

static const char *hdmiOff[]        = { "xrandr", "--output", "HDMI1", "--off", NULL };
static const char *hdmiMirror[]     = { "xrandr", "--output", "HDMI1", "--same-as", "eDP1", "--auto", NULL };
static const char *hdmiAbove[]    = { "xrandr", "--output", "HDMI1", "--above", "eDP1", "--auto", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	/* Launchers */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = firefoxcmd } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = thunderbirdcmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = randomwp } },

	/* Keyboard management */
	{ MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("setxkbmap us -option ctrl:nocaps && pkill dwmstatus -SIGUSR1") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("setxkbmap se -option ctrl:nocaps && pkill dwmstatus -SIGUSR1") },

  /* Screen management */
	{ MODKEY|ShiftMask,             XK_F7,     spawn,          {.v = hdmiOff} },
	{ MODKEY|ShiftMask,             XK_F8,     spawn,          {.v = hdmiMirror} },
	{ MODKEY|ShiftMask,             XK_F9,     spawn,          {.v = hdmiAbove} },

	/* Window management */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_l,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_h,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_k,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_j,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[3]} }, /* bstack */
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[0]} }, /* original */
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[4]} }, /* bstack horiz */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, /* floating */
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, /* monocle */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },


	/* Special keys */
	{ MODKEY,                       XK_F5,     spawn,          SHCMD("xbacklight -dec 10 && pkill dwmstatus -SIGUSR1") },
	{ MODKEY,                       XK_F6,     spawn,          SHCMD("xbacklight -inc 10 && pkill dwmstatus -SIGUSR1") },
	{ MODKEY,                       XK_F10,    spawn,          SHCMD("amixer set Master -c 1 0% && pkill dwmstatus -SIGUSR1") },
	{ MODKEY,                       XK_F11,    spawn,          SHCMD("amixer set Master -c 1 unmute 2- -M && pkill dwmstatus -SIGUSR1") },
	{ MODKEY,                       XK_F12,    spawn,          SHCMD("amixer set Master -c 1 unmute 2+ -M && pkill dwmstatus -SIGUSR1") },

//	/* Lenovo Special keys */
//	{ 0,                   0x1008FF2D,      spawn,          {.v = slimlockcmd } },
//	{ 0,                   0x1008FF95,      spawn,          {.v = wicdgtk } },
//	{ 0,                   0x1008FF11,      spawn,          {.v = amixDec } },
//	{ 0,                   0x1008FF12,      spawn,          {.v = amixSil } },
//	{ 0,                   0x1008ff13,      spawn,          {.v = amixInc } },
//	{ 0,                   0x1008FF14,      spawn,          {.v = mpdPlayPause } },
//	{ 0,                   0x1008FF15,      spawn,          {.v = mpdPlayStop } },
//	{ 0,                   0x1008FF16,      spawn,          {.v = mpdPrev } },
//	{ 0,                   0x1008FF17,      spawn,          {.v = mpdNext } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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
