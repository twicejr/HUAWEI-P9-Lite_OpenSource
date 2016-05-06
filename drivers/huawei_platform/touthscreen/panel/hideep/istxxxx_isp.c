/*******************************************************************************
 * Copyright (C) 2014 HiDeep, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *******************************************************************************/

#include "ist520e.h"

#define PGM_BURST_WR
#define PGM_VERIFY

#define YRAM_BASE (0x40000000)
#define PERIPHERAL_BASE (0x50000000)
#define ESI_BASE (PERIPHERAL_BASE + 0x00000000)
#define FLASH_BASE (PERIPHERAL_BASE + 0x01000000)
#define SYSCON_BASE (PERIPHERAL_BASE + 0x02000000)

#define SYSCON_MOD_CON (SYSCON_BASE + 0x0000)
#define SYSCON_SPC_CON (SYSCON_BASE + 0x0004)
#define SYSCON_CLK_CON (SYSCON_BASE + 0x0008)
#define SYSCON_CLK_ENA (SYSCON_BASE + 0x000C)
#define SYSCON_RST_CON (SYSCON_BASE + 0x0010)
#define SYSCON_WDT_CON (SYSCON_BASE + 0x0014)
#define SYSCON_WDT_CNT (SYSCON_BASE + 0x0018)
#define SYSCON_PWR_CON (SYSCON_BASE + 0x0020)
#define SYSCON_PGM_ID (SYSCON_BASE + 0x00F4)

#define FLASH_CON (FLASH_BASE  + 0x0000)
#define FLASH_STA (FLASH_BASE  + 0x0004)
#define FLASH_CFG (FLASH_BASE  + 0x0008)
#define FLASH_TIM (FLASH_BASE  + 0x000C)
#define FLASH_CACHE_CFG (FLASH_BASE  + 0x0010)


#define FLASH_TM (FLASH_BASE  + 0x0008)
#define FLASH_SFR (0)
#define FLASH_PIO (FLASH_BASE  + 0x500000)


#define ESI_TX_INVALID (ESI_BASE	  + 0x0008)
#define HIDEEP_VR_VERSION_ADDR_BASE             0x2ee

// flash commands
#define MERASE (0x00010000)
#define SERASE (0x00020000)
#define PERASE (0x00040000)
#define PROG (0x00080000)
#define WRONLY (0x00100000)
#define INF (0x00200000)

#define NVM_PAGE_SIZE  (128)

#define SET_FLASH_PIO(CE) pgm_w_reg(ext_io, FLASH_CON, 0x01 | ((CE) << 1))
#define SET_PIO_SIG(X, Y) pgm_w_reg(ext_io, (FLASH_BASE + 0x400000) + (X),Y)

typedef struct pgm_packet
{
	union
	{
		u8   b[8];
		u32  w[2];
	}header;
	u32 payload[NVM_PAGE_SIZE/sizeof(u32)];
}PGM_PACKET;

static int pgm_r_reg(struct ts_bus_info *ext_io, u32 addr, u32 *val)
{
	int ret = 0;
	u32 packet[3];
	u8* bulk = (u8*)packet + 3;

	packet[0] = htonl(0x00);
	packet[1] = htonl(addr);
#ifdef HIDEEP_REPEAT_START
	ret = huawei_ts_i2c_read(bulk, 5, (u8*)&(packet[2]), 4);
#else
	ret = ext_io->bus_read(bulk, 5, (u8*)&(packet[2]), 4);
#endif
	if(ret < 0)
		goto err;
	*val = ntohl(packet[2]);
err:
	return ret;
}

static int pgm_w_reg(struct ts_bus_info *ext_io, u32 addr, u32 data)
{
	int ret = 0;
	u32 packet[3];
	u8* bulk = (u8*)packet + 3;

	packet[0] = htonl(0x80);
	packet[1] = htonl(addr);
	packet[2] = htonl(data);
	ret = ext_io->bus_write(bulk, 9);
	if(ret < 0)
		goto err;
err:
	return ret;
}

#ifdef PGM_BURST_WR
static int pgm_w_mem(struct ts_bus_info *ext_io, u32 addr, struct pgm_packet *packet, u32 len)
{
	int ret   = 0;
	int i;

	if(len % 4 != 0)
		return -1;
	packet->header.w[0] = htonl( (0x80|(len/4-1)));
	packet->header.w[1] = htonl(addr);
	for(i=0; i<NVM_PAGE_SIZE/sizeof(u32); i++)
		packet->payload[i] = htonl(packet->payload[i]);

	ret = ext_io->bus_write((u8*)&packet->header.b[3],(len+5));
	if (ret < 0)
		goto err;
err:
	return ret;
}

static int pgm_r_mem(struct ts_bus_info *ext_io, u32 addr, struct pgm_packet *packet, u32 len)
{
	int ret   = 0;
	int i;

	if(len % 4 != 0)
	return -1;

	packet->header.w[0] = htonl( (0x00|(len/4-1)));
	packet->header.w[1] = htonl(addr);
#ifdef HIDEEP_REPEAT_START
	ret = huawei_ts_i2c_read((u8*)&packet->header.b[3], 5, (u8*)packet->payload, len);
#else
	ret = ext_io->bus_read((u8*)&packet->header.b[3], 5, (u8*)packet->payload, len);
#endif
	if (ret < 0){
		goto err;
	}
	for(i=0; i<NVM_PAGE_SIZE/sizeof(u32); i++)
	packet->payload[i] = htonl(packet->payload[i]);
err:
	return ret;
}
#endif

static void hideep_sw_reset(struct ts_bus_info *ext_io, u32 food)
{
	pgm_w_reg(ext_io, SYSCON_WDT_CNT, food);
	pgm_w_reg(ext_io, SYSCON_WDT_CON, 0x03);
	pgm_w_reg(ext_io, SYSCON_WDT_CON, 0x01);
	TS_LOG_INFO("sw reset\n");
	return;
}

static int hideep_enter_pgm(struct ts_bus_info *ext_io)
{
	s32 ret = 0;
	u32 status;
	u32 pattern = 0xDF9DAF39;

	TS_LOG_INFO("hideep_enter_pgm enter\n");
	ext_io->bus_write((u8*)&pattern, 4);
	mdelay(1);
	pgm_w_reg(ext_io, ESI_TX_INVALID,   0x01);
	pgm_r_reg(ext_io, SYSCON_PGM_ID, &status);
	if( status != htonl(pattern)){
		TS_LOG_ERR("enter_pgm : error(%08x):\n", status);
		return -1;
	}
	pgm_w_reg(ext_io, SYSCON_WDT_CON, 0x00);
	pgm_w_reg(ext_io, SYSCON_SPC_CON, 0x00); 
	pgm_w_reg(ext_io, SYSCON_CLK_ENA, 0xFF); 
	pgm_w_reg(ext_io, SYSCON_CLK_CON, 0x01);
	pgm_w_reg(ext_io, SYSCON_PWR_CON, 0x01);
	pgm_w_reg(ext_io, FLASH_TIM, 0x03);
	pgm_w_reg(ext_io, FLASH_CACHE_CFG,0x00);
	pgm_w_reg(ext_io, FLASH_CACHE_CFG,0x02);
	mdelay(1);
	return ret;
}

static s32 hideep_program_page(struct ts_bus_info *ext_io, u16 addr, struct pgm_packet *packet_w)
{
	u32  pio_cmd = PROG;
	u32  status;
	s32   i;
	int time_out =0;

	pgm_r_reg(ext_io, FLASH_STA, &status);                  // flash status
	if(status == 0)
		return -1;
	TS_LOG_DEBUG("addr = 0x%x",addr);
	addr = addr & ~(NVM_PAGE_SIZE-1);                   // address mask
	TS_LOG_DEBUG("addr = 0x%x",addr);
	SET_FLASH_PIO(0);
	SET_FLASH_PIO(1);
	if(addr>=0x10000 && addr<0xc400){
		addr -= 0x10000;
		pio_cmd |= INF;
	}
	SET_PIO_SIG(pio_cmd+addr, htonl(packet_w->payload[0]));
#ifdef PGM_BURST_WR
	pgm_w_mem(ext_io, (FLASH_BASE + 0x400000) + pio_cmd, packet_w, NVM_PAGE_SIZE);
#else
	SET_PIO_SIG(pio_cmd + addr + (i<<2), packet_w->payload[i]);
	for (i = 0; i < NVM_PAGE_SIZE/4; i++){
		SET_PIO_SIG(pio_cmd + addr + (i<<2), packet_w->payload[i]);
	}
#endif
	if(pio_cmd&INF)
		SET_PIO_SIG(124|INF, htonl(packet_w->payload[31]));
	else
		SET_PIO_SIG(124, htonl(packet_w->payload[31]));

	SET_FLASH_PIO(0);
	mdelay(1);
	while(1)
	{
		pgm_r_reg(ext_io, FLASH_STA, &status);
		if( (status) != 0)
			break;
		if(time_out++>100)
			break;
	}
	pgm_w_reg(ext_io, FLASH_CON, 0);
	return 0;
}

static struct pgm_packet packet_w;
static struct pgm_packet packet_r;

void hideep_pgm_protect(struct ts_bus_info *ext_io)
{
	unsigned int status[3];
	pgm_w_reg(ext_io, FLASH_TM,    0x06);
	pgm_r_reg(ext_io, FLASH_SFR,   &status[0]);
	pgm_r_reg(ext_io, FLASH_SFR+4, &status[1]);
	pgm_r_reg(ext_io, FLASH_SFR+8, &status[2]);
	pgm_w_reg(ext_io, FLASH_TM,    0x00);


	pgm_w_reg(ext_io, FLASH_TM,    0x01);
	pgm_w_reg(ext_io, FLASH_BASE,  0x01);

	pgm_w_reg(ext_io, FLASH_BASE,  0x03);
	pgm_w_reg(ext_io, FLASH_PIO,   status[0]);
	pgm_w_reg(ext_io, FLASH_BASE,  0x01);
	pgm_w_reg(ext_io, FLASH_BASE,  0x03);
	pgm_w_reg(ext_io, FLASH_PIO+4, status[1]);
	pgm_w_reg(ext_io, FLASH_BASE,  0x01);
	pgm_w_reg(ext_io, FLASH_BASE,  0x03);
	pgm_w_reg(ext_io, FLASH_PIO+8, status[2]);
	pgm_w_reg(ext_io, FLASH_BASE,  0x01);
	pgm_w_reg(ext_io, FLASH_BASE,  0x03);
	pgm_w_reg(ext_io, FLASH_PIO+12,0x0030027b);
	pgm_w_reg(ext_io, FLASH_BASE,  0x01);

	pgm_w_reg(ext_io, FLASH_TM,    0x00);
	pgm_w_reg(ext_io, FLASH_BASE,  0x00);
}
void hideep_read_6spp(struct ts_bus_info *ext_io)
{
	u32 temp[4];

	TS_LOG_INFO("%s, enter\n",__FUNCTION__);
	pgm_w_reg(ext_io, FLASH_CFG,    0x06);
	pgm_r_reg(ext_io, 0,    &temp[0]);
	pgm_r_reg(ext_io, 0,    &temp[0]);
	pgm_r_reg(ext_io, 4,    &temp[1]);
	pgm_r_reg(ext_io, 8,    &temp[2]);
	pgm_r_reg(ext_io, 0xc,    &temp[3]);
	TS_LOG_INFO("%s, from 0 to 3 is [0x%08x],[0x%08x],[0x%08x],[0x%08x]\n",__FUNCTION__ ,temp[0], temp[1], temp[2], temp[3]);
}
static int hideep_program_nvm(struct ts_bus_info *ext_io, const u8 *ucode, size_t len, int offset)
{
	size_t i;
	s32 ret;
	u32 pages ;
	u32 addr;
	s32 retry = 3;
	s32 len_r;
	s32 len_w;

	while(retry--){
		ret = hideep_enter_pgm(ext_io);
		if(ret >= 0)
			break;
		hideep_sw_reset(ext_io, 10);
	}
	if(retry < 0){
		TS_LOG_ERR("enter_pgm : failed\n");
		return -1;
	}
	TS_LOG_INFO("%s, pgm is enter\n",__FUNCTION__);
	hideep_read_6spp(ext_io);
	hideep_pgm_protect(ext_io);
	pages      = (len + NVM_PAGE_SIZE - 1)/ NVM_PAGE_SIZE;
	addr       = offset;
	TS_LOG_DEBUG("addr = 0x%x, len = %d(0x%x)",addr, len);
	len_r      = len;
	len_w      = len_r;
	for(i=0; i<pages; i++)	{
		if(len_r >= NVM_PAGE_SIZE)
			len_w = NVM_PAGE_SIZE;
		memcpy(packet_w.payload, &(ucode[addr]), len_w);
		ret = hideep_program_page(ext_io, i * NVM_PAGE_SIZE+offset, &packet_w);
		if(ret < 0){
			TS_LOG_ERR("hideep_program_nvm : error(%08x):\n", addr);
		}
		addr   += NVM_PAGE_SIZE;
		len_r  -= NVM_PAGE_SIZE;
		len_w   = len_r;
	}
	return ret;
}

static int hideep_verify_nvm(struct ts_bus_info *ext_io, const u8 *ucode, size_t len, int offset)
{
	s32 i;
	s32 j;
	s32 ret = 0;
	u32 addr  = offset;
	u32 pages = (len + NVM_PAGE_SIZE - 1)/ NVM_PAGE_SIZE;
	s32 len_r = len;
	s32 len_v = len_r;
	u32 *pbuf;
	u32 *psourcebuf;

	for(i=0; i<pages; i++){
		if(len_r >= NVM_PAGE_SIZE)
			len_v = NVM_PAGE_SIZE;
#ifdef PGM_BURST_WR
		pgm_r_mem(ext_io, 0x00000000 + addr, &packet_r ,NVM_PAGE_SIZE);
#else
		for (j = 0; j < NVM_PAGE_SIZE/4; j++){
			if(addr<0x10000)
				pgm_r_reg(ext_io, addr+(j<<2), &(packet_r.payload[j]));
			else
				pgm_r_reg(ext_io, 0x00000000 + addr+(j<<2), &(packet_r.payload[j]));
		}
#endif
		pbuf = packet_r.payload;
		psourcebuf = &ucode[addr];
		for(j=0;j<(len_v/4);j++)
			TS_LOG_DEBUG("address = 0x%08x, Read data = 0x%08x, Source data = 0x%08x",addr+j*4,pbuf[j],psourcebuf[j]);
		ret  = memcmp(&(ucode[addr]), packet_r.payload, len_v);
		if(ret != 0){
			u8 *read = (u8*) packet_r.payload;
			for(j=0; j<NVM_PAGE_SIZE; j++)
			TS_LOG_ERR("%02x : %02x\n", ucode[addr+j], read[j]);
			TS_LOG_ERR("verify : error(addr : %d)\n", addr);
			ret = -1;
		}
		addr   += NVM_PAGE_SIZE;
		len_r  -= NVM_PAGE_SIZE;
		len_v  = len_r;
	}
	return ret;
}

int hideep_fuse_ucode( struct ts_bus_info *ext_io, const u8 *code, size_t len, int offset)
{
	s32 ret = 0;
	s32 retry = 3;
	s32 len_47k;

	TS_LOG_INFO("start, len = %d,offset = 0x%x", len, offset);
	len_47k = len<(62*1024)?len:(62*1024);
	hideep_reset_ic();
	ret = hideep_program_nvm(ext_io, code, len_47k ,offset);
	if(ret != 0)
		return ret;
#ifdef PGM_VERIFY
	while(retry--){
		ret = hideep_verify_nvm (ext_io, code, len_47k, offset);
		if(ret == 0)
			break;
		TS_LOG_ERR(" download uc failed(%d)\n", retry);
	}
	if(retry != 0){
		TS_LOG_INFO("download uc success\n"          );
	}
#endif
	hideep_sw_reset(ext_io, 1000);
	return ret;
}

int hideep_load_ucode(struct ist510e *ts_drv, const char *fn, u16 ver)
{
	s32 ret = 0;
	const struct firmware *fw_entry;
	struct device         *dev  = &ts_drv->huawei_ts_dev->dev;
	struct ts_bus_info *bus_io   = ts_drv->huawei_ts_data->bops;
	u16 version;
	u16 stack_up_version;
	u16 fw_version;
	u16 stack_up_ver;
	u16 fw_ver;

	ret = request_firmware(&fw_entry, fn, dev);
	if(ret != 0){
		TS_LOG_INFO("request_firmware : fail(%d)\n", ret);
		goto err;
	}
	memcpy((unsigned char*)&version,  fw_entry->data+HIDEEP_VR_VERSION_ADDR_BASE,2);
	TS_LOG_INFO("version = 0x%04x, ver = 0x%04x", version, ver);
	stack_up_version = (version>>12)&0xf;
	fw_version = version&0xfff;
	stack_up_ver = (ver>>12)&0xf;
	fw_ver = ver&0xfff;
	//only fw_ver > fw_version will auto update.
	TS_LOG_INFO("IC stackup = %d, fw = 0x%03x, binary stackup = %d, fw = 0x%03x", stack_up_ver, fw_ver, stack_up_version, fw_version);
	if(fw_version <= fw_ver){
		TS_LOG_INFO("no need to update.\n");
		goto hideep_load_ucode_exit;
	}
	ts_drv->dev_state = ISTCORE_PWR_PGM  ;
	mutex_lock(&ts_drv->dev_mutex);
	ret = hideep_fuse_ucode(bus_io, fw_entry->data, fw_entry->size, 0);
	mutex_unlock(&ts_drv->dev_mutex);
	ts_drv->dev_state =ISTCORE_PWR_NORMAL;
	release_firmware(fw_entry);

	return ret;
hideep_load_ucode_exit:
	release_firmware(fw_entry);
err:
	return ret;
}
