/*
 * HydraBus/HydraNFC
 *
 * Copyright (C) 2014-2015 Benjamin VERNOUX
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

#ifndef _MICROSD_H_
#define _MICROSD_H_

#define SDC_BURST_SIZE  4 /* how many sectors reads at once */
#define IN_OUT_BUF_SIZE (MMCSD_BLOCK_SIZE * SDC_BURST_SIZE)

#include "common.h"

typedef struct {
	char filename[255];
} filename_t;

bool is_fs_ready(void);
bool is_file_present(char * filename);

int write_file(uint8_t* buffer, uint32_t size);
void write_file_get_last_filename(filename_t* out_filename);

int mount(void);
int umount(void);

#endif /* _MICROSD_H_ */
