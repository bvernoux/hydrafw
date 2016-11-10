/*
 * HydraBus/HydraNFC
 *
 * Copyright (C) 2015-2016 Nicolas OBERLI
 * Copyright (C) 2016 Benjamin VERNOUX
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

/*
 * Basic BBIO modes
 */
#define BBIO_RESET	0b00000000
#define BBIO_SPI	0b00000001
#define BBIO_I2C	0b00000010
#define BBIO_UART	0b00000011
#define BBIO_1WIRE	0b00000100
#define BBIO_RAWWIRE	0b00000101
#define BBIO_JTAG	0b00000110

//Common modes command
#define BBIO_MODE_ID	0b00000001

//Hydrabus specific
#define BBIO_CAN	0b00001000
#define BBIO_PIN	0b00001001

#define BBIO_RESET_HW	0b00001111
#define BBIO_PWM	0b00010010
#define BBIO_PWM_CLEAR	0b00010010
#define BBIO_VOLT	0b00010100
#define BBIO_VOLT_CONT	0b00010101
#define BBIO_FREQ	0b00010110

/*
 * SPI-specific commands
 */
#define BBIO_SPI_CS_LOW		0b00000010
#define BBIO_SPI_CS_HIGH	0b00000011
#define BBIO_SPI_WRITE_READ	0b00000100
#define BBIO_SPI_WRITE_READ_NCS	0b00000101
#define BBIO_SPI_SNIFF_ALL	0b00001101
#define BBIO_SPI_SNIFF_CS_LOW	0b00001110
#define BBIO_SPI_SNIFF_CS_HIGH	0b00001111
#define BBIO_SPI_SNIFF_CS_HIGH	0b00001111
#define BBIO_SPI_BULK_TRANSFER	0b00010000
#define BBIO_SPI_CONFIG_PERIPH	0b01000000
#define BBIO_SPI_SET_SPEED	0b01100000
#define BBIO_SPI_CONFIG		0b10000000

/*
 * I2C-specific commands
 */
#define BBIO_I2C_START_BIT	0b00000010
#define BBIO_I2C_STOP_BIT	0b00000011
#define BBIO_I2C_READ_BYTE	0b00000100
#define BBIO_I2C_ACK_BIT	0b00000110
#define BBIO_I2C_NACK_BIT	0b00000111
#define BBIO_I2C_WRITE_READ	0b00001000
#define BBIO_I2C_START_SNIFF	0b00001111
#define BBIO_I2C_BULK_WRITE	0b00010000
#define BBIO_I2C_CONFIG_PERIPH	0b01000000
#define BBIO_I2C_SET_SPEED	0b01100000

/*
 * CAN-specific commands
 */
#define BBIO_CAN_READ		0b00000010
#define BBIO_CAN_ID		0b00000011
#define BBIO_CAN_FILTER_OFF	0b00000100
#define BBIO_CAN_FILTER_ON	0b00000101
#define BBIO_CAN_FILTER		0b00000110
#define BBIO_CAN_WRITE		0b00001000
#define BBIO_CAN_SET_SPEED	0b01100000

/*
 * PIN control-specific commands
 */
#define BBIO_PIN_READ		0b00000010
#define BBIO_PIN_MODE		0b00000011
#define BBIO_PIN_NOPULL		0b00000100
#define BBIO_PIN_PULLUP		0b00000101
#define BBIO_PIN_PULLDOWN	0b00000110
#define BBIO_PIN_WRITE		0b00001000

/*
 * UART-specific commands
 */
#define BBIO_UART_START_ECHO	0b00000010
#define BBIO_UART_STOP_ECHO	0b00000011
#define BBIO_UART_BAUD_RATE	0b00000111
#define BBIO_UART_BRIDGE	0b00001111
#define BBIO_UART_BULK_TRANSFER 0b00010000
#define BBIO_UART_CONFIG_PERIPH	0b01000000
#define BBIO_UART_SET_SPEED	0b01100000
#define BBIO_UART_CONFIG	0b10000000

/*
 * 2-Wire-specific commands
 */
#define BBIO_RAWWIRE_I2C_START	0b00000010
#define BBIO_RAWWIRE_I2C_STOP	0b00000011
#define BBIO_RAWWIRE_CS_LOW	0b00000100
#define BBIO_RAWWIRE_CS_HIGH	0b00000101
#define BBIO_RAWWIRE_READ_BYTE	0b00000110
#define BBIO_RAWWIRE_READ_BIT	0b00000111
#define BBIO_RAWWIRE_PEEK_INPUT	0b00001000
#define BBIO_RAWWIRE_CLK_TICK	0b00001001
#define BBIO_RAWWIRE_CLK_LOW	0b00001010
#define BBIO_RAWWIRE_CLK_HIGH	0b00001011
#define BBIO_RAWWIRE_DATA_LOW	0b00001100
#define BBIO_RAWWIRE_DATA_HIGH	0b00001101
#define BBIO_RAWWIRE_BULK_TRANSFER 0b00010000
#define BBIO_RAWWIRE_BULK_CLK	0b00100000
#define BBIO_RAWWIRE_BULK_BIT	0b00110000
#define BBIO_RAWWIRE_CONFIG_PERIPH 0b01000000
#define BBIO_RAWWIRE_SET_SPEED	0b01100000
#define BBIO_RAWWIRE_CONFIG	0b10000000

/*
 * 1-Wire-specific commands
 */
#define BBIO_ONEWIRE_RESET	0b00000010
#define BBIO_ONEWIRE_READ	0b00000100
#define BBIO_ONEWIRE_BULK_TRANSFER 0b00010000

int cmd_bbio(t_hydra_console *con);
