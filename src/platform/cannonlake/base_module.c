/*
 * Copyright (c) 2018, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the Intel Corporation nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Liam Girdwood <liam.r.girdwood@linux.intel.com>
 */

#include <uapi/user/manifest.h>
#include <platform/memory.h>

/*
 * Each module has an entry in the FW manifest header. This is NOT part of
 * the SOF executable image but is inserted by object copy as a ELF section
 * for parsing by rimage (to genrate the manifest).
 */
struct sof_man_module_manifest cnl_manifest = {
	.module = {
		.name	= "BASEFW",
		.uuid	= {0x32, 0x8c, 0x39, 0x0e, 0xde, 0x5a, 0x4b, 0xba,
				0x93, 0xb1, 0xc5, 0x04, 0x32, 0x28, 0x0e, 0xe4},
		.entry_point = SOF_TEXT_START,
		.type = {
				.load_type = SOF_MAN_MOD_TYPE_MODULE,
				.domain_ll = 1,
		},
		.affinity_mask = 3,
	},
};

/* not used, but stops linker complaining */
int _start;
