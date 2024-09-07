/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cat                 read arbitrary file             path
 * cpu_freq            cpu frequency in MHz            NULL
 * cpu_perc            cpu usage in percent            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/)
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD/FreeBSD
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 */
static const struct arg args[] = {
	/* function format          argument */
	/* { username,		" | %s",			NULL }, */
	/* { hostname,		"@%s",				NULL }, */
	{ run_command,		"^fg(a3be8c)VOL: %s%%",		"wpctl get-volume @DEFAULT_AUDIO_SINK@ | cut -d ' ' -f 2-" },
	{ cpu_perc,		"^fg() | ^fg()CPU: %s%%",	NULL },
	{ cpu_freq,		" %s",				NULL },
	{ temp,			" %sC",				"/sys/class/thermal/thermal_zone0/temp" },
	{ temp,			" %sC",				"/sys/class/thermal/thermal_zone1/temp" },
	{ temp,			" %sC",				"/sys/class/thermal/thermal_zone2/temp" },
	{ temp,			" %sC",				"/sys/class/thermal/thermal_zone3/temp" },
	{ ram_used,		"^fg() | ^fg(a3be8c)RAM: %s/",	NULL },
	{ ram_total,		"%s",				NULL },
	/* { ram_perc,		"(%s%%)",			NULL }, */
	{ disk_used,		"^fg() | ^fg()DISK: %s/",	"/" },
	{ disk_total,		"%s",				"/" },
	/* { disk_perc,		"(%s%%)",			"/" }, */
	/* { netspeed_rx,		" | WIFI: IN %s",	"wlp1s0" }, */
	/* { netspeed_tx,		" OUT %s",		"wlp1s0" }, */
	{ battery_perc,		"^fg() | ^fg(a3be8c)BAT: %s%%",	"BAT1" },
	{ battery_state,	" %s",				"BAT1" },
	{ datetime,		"^fg() | ^fg()%s        ",	"%F %T^fg()" },
};
