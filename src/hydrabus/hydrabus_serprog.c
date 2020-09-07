/*
 * HydraBus/HydraNFC
 *
 * Copyright (C) 2014-2020 Benjamin VERNOUX
 * Copyright (C) 2020 Nicolas OBERLI
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "common.h"
#include "tokenline.h"

#include "hydrabus_bbio.h"
#include "hydrabus_serprog.h"
#include "bsp_spi.h"

void bbio_serprog_init_proto_default(t_hydra_console *con)
{
	mode_config_proto_t* proto = &con->mode->proto;

	/* Defaults */
	proto->dev_num = BSP_DEV_SPI2;
	proto->config.spi.dev_gpio_pull = MODE_CONFIG_DEV_GPIO_NOPULL;
	proto->config.spi.dev_mode = DEV_MASTER;
	proto->config.spi.dev_speed = 7;
	proto->config.spi.dev_polarity = 0;
	proto->config.spi.dev_phase = 0;
	proto->config.spi.dev_bit_lsb_msb = DEV_FIRSTBIT_MSB;
}

void bbio_mode_serprog(t_hydra_console *con)
{
	uint8_t serprog_command;
	uint32_t to_rx, to_tx, i;
	uint8_t *tx_data = (uint8_t *)g_sbuf;
	uint8_t *rx_data = (uint8_t *)g_sbuf+4096;
	mode_config_proto_t* proto = &con->mode->proto;

	bbio_serprog_init_proto_default(con);

	// We no not initialize here, since flashrom takes care of starting the
	// SPI interface. this allows to avoid potential electrical issues.
	//bsp_spi_init(proto->dev_num, proto);

	while (!hydrabus_ubtn()) {
		if(chnRead(con->sdu, &serprog_command, 1) == 1) {
			switch(serprog_command) {
			case S_CMD_NOP:
				break;
			case S_CMD_Q_IFACE:
				cprint(con, S_ACK, 1);
				cprint(con, "\x01\x00", 2);
				break;
			case S_CMD_Q_CMDMAP:
				cprint(con, S_ACK, 1);
				cprint(con, "\x3f\x01\x3f\x00", 4);
				cprint(con, "\x00\x00\x00\x00", 4);
				cprint(con, "\x00\x00\x00\x00", 4);
				cprint(con, "\x00\x00\x00\x00", 4);
				cprint(con, "\x00\x00\x00\x00", 4);
				cprint(con, "\x00\x00\x00\x00", 4);
				cprint(con, "\x00\x00\x00\x00", 4);
				cprint(con, "\x00\x00\x00\x00", 4);
				break;
			case S_CMD_Q_PGMNAME:
				cprint(con, S_ACK, 1);
				cprint(con, "Hydrabus\x00\x00\x00\x00\x00\x00\x00\x00", 16);
				break;
			case S_CMD_Q_SERBUF:
				cprint(con, S_ACK, 1);
				//16 bytes  UART buffer
				cprint(con, "\x10\x00", 2);
				break;
			case S_CMD_Q_BUSTYPE:
				cprint(con, S_ACK, 1);
				cprint(con, "\x08", 1);
				break;
			case S_CMD_SYNCNOP:
				cprint(con, S_NAK, 1);
				cprint(con, S_ACK, 1);
				break;
			case S_CMD_S_BUSTYPE:
				// Dummy read
				chnRead(con->sdu, &serprog_command, 1);
				cprint(con, S_ACK, 1);
				break;
			case S_CMD_Q_WRNMAXLEN:
				cprint(con, S_ACK, 1);
				//4096 bytes write buffer
				cprint(con, "\x00\x10\x00", 3);
				break;
			case S_CMD_Q_RDNMAXLEN:
				cprint(con, S_ACK, 1);
				//4096 bytes write buffer
				cprint(con, "\x00\x10\x00", 3);
				break;
			case S_CMD_O_SPIOP:
				chnRead(con->sdu, rx_data, 6);
				to_tx = (rx_data[2] << 16) + (rx_data[1] << 8) + rx_data[0];
				to_rx = (rx_data[5] << 16) + (rx_data[4] << 8) + rx_data[3];
				if ((to_tx > 4096) || (to_rx > 4096)) {
					cprint(con, S_NAK, 1);
					break;
				}
				bsp_spi_select(proto->dev_num);
				if(to_tx > 0) {
					chnRead(con->sdu, tx_data, to_tx);
					i=0;
					while(i<to_tx) {
						if((to_tx-i) >= 255) {
							bsp_spi_write_u8(proto->dev_num,
									tx_data+i,
									255);
						} else {
							bsp_spi_write_u8(proto->dev_num,
									tx_data+i,
									to_tx-i);
						}
						i+=255;
					}
				}
				i=0;
				while(i<to_rx) {
					if((to_rx-i) >= 255) {
						bsp_spi_read_u8(proto->dev_num,
						                rx_data+i,
						                255);
					} else {
						bsp_spi_read_u8(proto->dev_num,
						                rx_data+i,
						                to_rx-i);
					}
					i+=255;
				}
				bsp_spi_unselect(proto->dev_num);
				cprint(con, S_ACK, 1);
				cprint(con, (char *)rx_data, to_rx);
				break;
			case S_CMD_S_SPI_FREQ:
				chnRead(con->sdu, rx_data, 4);
				//TODO: define variable speed.
				cprint(con, S_ACK, 1);
				break;
			case S_CMD_S_PIN_STATE:
				chnRead(con->sdu, rx_data, 1);

				if(rx_data[0] == 0) {
					bsp_spi_deinit(proto->dev_num);
				} else {
					bsp_spi_init(proto->dev_num, proto);
				}
				cprint(con, S_ACK, 1);
				break;
			default:
				break;
			}
		}
	}
	bsp_spi_deinit(proto->dev_num);
	return;
}
