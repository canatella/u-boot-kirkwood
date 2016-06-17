/*
 * Copyright (C) 2014-2016 bodhi <mibodhi@gmail.com>
 * Based on 
 *
 * Copyright (C) 2013 Suriyan Ramasami <suriyan.r@gmail.com>
 *
 * Based on dockstar.h originally written by
 * Copyright (C) 2010  Eric C. Cooper <ecc@cmu.edu>
 *
 * Based on sheevaplug.h originally written by
 * Prafulla Wadaskar <prafulla@marvell.com>
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _CONFIG_GOFLEXHOME_H
#define _CONFIG_GOFLEXHOME_H

/*
 * Version number information
 */
#define CONFIG_IDENT_STRING	"\nSeagate GoFlex Home"

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_FEROCEON_88FR131	1	/* CPU Core subversion */
#define CONFIG_KW88F6281	1	/* SOC Name */
#define CONFIG_MACH_GOFLEXHOME		/* Machine type */
#define CONFIG_SKIP_LOWLEVEL_INIT	/* disable board lowlevel_init */

/*
 * Default GPIO configuration and LED status
 */
#define GOFLEXHOME_OE_LOW               (~(0))
#define GOFLEXHOME_OE_HIGH              (~(0))
#define GOFLEXHOME_OE_VAL_LOW           (1 << 29)       /* USB_PWEN low */
#define GOFLEXHOME_OE_VAL_HIGH          (1 << 17)       /* LED pin high */

/* PHY related */
#define MV88E1116_LED_FCTRL_REG         10
#define MV88E1116_CPRSP_CR3_REG         21
#define MV88E1116_MAC_CTRL_REG          21
#define MV88E1116_PGADR_REG             22
#define MV88E1116_RGMII_TXTM_CTRL       (1 << 4)
#define MV88E1116_RGMII_RXTM_CTRL       (1 << 5)

/*
 * Commands configuration
 */
#define CONFIG_SYS_NO_FLASH		/* Declare no flash (NOR/SPI) */
#define CONFIG_CONSOLE_MUX
#define CONFIG_SYS_CONSOLE_IS_IN_ENV

#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ENV
#define CONFIG_CMD_MII
#define CONFIG_CMD_NAND
#define CONFIG_CMD_PING
#define CONFIG_CMD_USB
#define CONFIG_CMD_IDE
#define CONFIG_CMD_DATE
#define CONFIG_SYS_MVFS         /* Picks up Filesystem from mv-common.h */
#define CONFIG_SYS_LONGHELP
#define CONFIG_PREBOOT 
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2 "> "
/*
 * mv-common.h should be defined after CMD configs since it used them
 * to enable certain macros
 */
#include "mv-common.h"

/*
 *  Environment variables configurations
 */
#ifdef CONFIG_CMD_NAND
#define CONFIG_ENV_IS_IN_NAND		1
#define CONFIG_ENV_SECT_SIZE		0x20000	/* 128K */
#else
#define CONFIG_ENV_IS_NOWHERE		1	/* if env in SDRAM */
#endif
/*
 * max 4k env size is enough, but in case of nand
 * it has to be rounded to sector size
 */
#define CONFIG_ENV_SIZE			0x20000	/* 128k */
#define CONFIG_ENV_ADDR			0xC0000
#define CONFIG_ENV_OFFSET		0xC0000	/* env starts here */

/*
 * Default environment variables
 */

#define CONFIG_BOOTCOMMAND \
	"run bootcmd_uenv; run bootcmd_usb; reset"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"arcNumber=2097\0" \
	"ethaddr=b6:d0:5e:0f:a1:17\0" \
	"mtdparts=mtdparts=orion_nand:1M(u-boot),4M(uImage),32M(rootfs),-(data)\0"\
	"baudrate=115200\0"\
	"bootcmd_usb=run usb_init; run set_bootargs_usb; run usb_boot;\0"\
	"bootdelay=10\0"\
	"console=ttyS0,115200\0"\
	"device=0:1\0"\
	"ethact=egiga0\0"\
	"led_error=orange blinking\0"\
	"led_exit=green off\0"\
	"led_init=green blinking\0"\
	"mainlineLinux=yes\0"\
	"mtdids=nand0=orion_nand\0"\
	"partition=nand0,2\0"\
	"rootdelay=10\0"\
	"rootfstype=ext2\0"\
	"set_bootargs_usb=setenv bootargs console=$console root=$usb_root rootdelay=$rootdelay rootfstype=$rootfstype $mtdparts\0"\
	"stderr=serial\0"\
	"stdin=serial\0"\
	"stdout=serial\0"\
	"usb_boot=mw 0x800000 0 1; run usb_load_uimage; if run usb_load_uinitrd; then bootm 0x800000 0x1100000; else bootm 0x800000; fi\0"\
	"usb_init=usb start\0"\
	"usb_load_uimage=ext2load usb $device 0x800000 /boot/uImage\0"\
	"usb_load_uinitrd=ext2load usb $device 0x1100000 /boot/uInitrd\0"\
	"usb_root=/dev/sda1\0" \
	"bootcmd_uenv=run uenv_load; if test $uenv_loaded -eq 1; then run uenv_import; fi\0" \
	"uenv_import=echo importing envs ...; env import -t 0x810000\0" \
	"uenv_load=usb start; ide reset; setenv uenv_loaded 0; for devtype in usb ide; do for disknum in 0; do run uenv_read_disk; done; done\0" \
	"uenv_read=echo loading envs from $devtype $disknum ...; if load $devtype $disknum:1 0x810000 /boot/uEnv.txt; then setenv uenv_loaded 1; fi\0" \
	"uenv_read_disk=if $devtype part $disknum; then run uenv_read; fi"

/*
 * File system
 */
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_FAT
#define CONFIG_CMD_JFFS2
#define CONFIG_JFFS2_NAND
#define CONFIG_JFFS2_LZO
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_MTD_DEVICE               /* needed for mtdparts commands */
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_MTDPARTS
#define CONFIG_LZO

/*
 * Ethernet Driver configuration
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE_PORTS	{1, 0}	/* enable port 0 only */
#define CONFIG_PHY_BASE_ADR	0
#endif /* CONFIG_CMD_NET */

/*
 *  * SATA Driver configuration
 *   */
#ifdef CONFIG_MVSATA_IDE
#define CONFIG_SYS_ATA_IDE0_OFFSET      MV_SATA_PORT0_OFFSET
#endif /*CONFIG_MVSATA_IDE*/

/*
 *  Date Time
 *   
*/
#ifdef CONFIG_CMD_DATE
#define CONFIG_RTC_MV
#define CONFIG_CMD_SNTP
#define CONFIG_CMD_DNS
#endif /* CONFIG_CMD_DATE */

/*
 * EFI partition
 */

#define CONFIG_EFI_PARTITION


#endif /* _CONFIG_GOFLEXHOME_H */
