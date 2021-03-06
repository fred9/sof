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
 *         Keyon Jie <yang.jie@linux.intel.com>
 */

/**
 * \file include/uapi/ipc/topology.h
 * \brief IPC definitions
 * \author Liam Girdwood <liam.r.girdwood@linux.intel.com>
 * \author Keyon Jie <yang.jie@linux.intel.com>
 */

#ifndef __INCLUDE_UAPI_IPC_TOPOLOGY_H__
#define __INCLUDE_UAPI_IPC_TOPOLOGY_H__

#include <uapi/ipc/header.h>

/*
 * Component
 */

/* types of component */
enum sof_comp_type {
	SOF_COMP_NONE = 0,
	SOF_COMP_HOST,
	SOF_COMP_DAI,
	SOF_COMP_SG_HOST,	/**< scatter gather variant */
	SOF_COMP_SG_DAI,	/**< scatter gather variant */
	SOF_COMP_VOLUME,
	SOF_COMP_MIXER,
	SOF_COMP_MUX,
	SOF_COMP_SRC,
	SOF_COMP_SPLITTER,
	SOF_COMP_TONE,
	SOF_COMP_SWITCH,
	SOF_COMP_BUFFER,
	SOF_COMP_EQ_IIR,
	SOF_COMP_EQ_FIR,
	SOF_COMP_FILEREAD,	/**< host test based file IO */
	SOF_COMP_FILEWRITE,	/**< host test based file IO */
};

/* XRUN action for component */
#define SOF_XRUN_STOP		1	/**< stop stream */
#define SOF_XRUN_UNDER_ZERO	2	/**< send 0s to sink */
#define SOF_XRUN_OVER_NULL	4	/**< send data to NULL */

/* create new generic component - SOF_IPC_TPLG_COMP_NEW */
struct sof_ipc_comp {
	struct sof_ipc_hdr hdr;
	uint32_t id;
	enum sof_comp_type type;
	uint32_t pipeline_id;

	/* reserved for future use */
	uint32_t reserved[2];
} __attribute__((packed));

/*
 * Component Buffers
 */

/* create new component buffer - SOF_IPC_TPLG_BUFFER_NEW */
struct sof_ipc_buffer {
	struct sof_ipc_comp comp;
	uint32_t size;		/**< buffer size in bytes */
	uint32_t caps;		/**< SOF_MEM_CAPS_ */
} __attribute__((packed));

/* generic component config data - must always be after struct sof_ipc_comp */
struct sof_ipc_comp_config {
	uint32_t periods_sink;	/**< 0 means variable */
	uint32_t periods_source;	/**< 0 means variable */
	uint32_t preload_count;	/**< how many periods to preload */
	uint32_t frame_fmt;		/**< SOF_IPC_FRAME_ */
	uint32_t xrun_action;

	/* reserved for future use */
	uint32_t reserved[2];
} __attribute__((packed));

/* generic host component */
struct sof_ipc_comp_host {
	struct sof_ipc_comp comp;
	struct sof_ipc_comp_config config;
	uint32_t direction;	/**< SOF_IPC_STREAM_ */
	uint32_t no_irq;	/**< don't send periodic IRQ to host/DSP */
	uint32_t dmac_config; /**< DMA engine specific */
} __attribute__((packed));

/* generic DAI component */
struct sof_ipc_comp_dai {
	struct sof_ipc_comp comp;
	struct sof_ipc_comp_config config;
	uint32_t direction;	/**< SOF_IPC_STREAM_ */
	uint32_t dai_index; /**< index of this type dai */
	uint32_t type;		/**< DAI type - SOF_DAI_ */
	uint32_t dmac_config; /**< DMA engine specific */
} __attribute__((packed));

/* generic mixer component */
struct sof_ipc_comp_mixer {
	struct sof_ipc_comp comp;
	struct sof_ipc_comp_config config;
} __attribute__((packed));

/* volume ramping types */
enum sof_volume_ramp {
	SOF_VOLUME_LINEAR	= 0,
	SOF_VOLUME_LOG,
	SOF_VOLUME_LINEAR_ZC,
	SOF_VOLUME_LOG_ZC,
};

/* generic volume component */
struct sof_ipc_comp_volume {
	struct sof_ipc_comp comp;
	struct sof_ipc_comp_config config;
	uint32_t channels;
	uint32_t min_value;
	uint32_t max_value;
	uint32_t ramp;		/**< SOF_VOLUME_ */
	uint32_t initial_ramp;	/**< ramp space in ms */
} __attribute__((packed));

/* generic SRC component */
struct sof_ipc_comp_src {
	struct sof_ipc_comp comp;
	struct sof_ipc_comp_config config;
	/* either source or sink rate must be non zero */
	uint32_t source_rate;	/**< source rate or 0 for variable */
	uint32_t sink_rate;	/**< sink rate or 0 for variable */
	uint32_t rate_mask;	/**< SOF_RATE_ supported rates */
} __attribute__((packed));

/* generic MUX component */
struct sof_ipc_comp_mux {
	struct sof_ipc_comp comp;
	struct sof_ipc_comp_config config;
} __attribute__((packed));

/* generic tone generator component */
struct sof_ipc_comp_tone {
	struct sof_ipc_comp comp;
	struct sof_ipc_comp_config config;
	int32_t sample_rate;
	int32_t frequency;
	int32_t amplitude;
	int32_t freq_mult;
	int32_t ampl_mult;
	int32_t length;
	int32_t period;
	int32_t repeats;
	int32_t ramp_step;
} __attribute__((packed));

/** \brief Types of EFFECT */
enum sof_ipc_effect_type {
	SOF_EFFECT_NONE = 0,		/**< None */
	SOF_EFFECT_INTEL_EQFIR,		/**< Intel FIR */
	SOF_EFFECT_INTEL_EQIIR,		/**< Intel IIR */
};

/* general purpose EFFECT configuration */
struct sof_ipc_comp_effect {
	uint32_t type;			/** sof_ipc_effect_type */
} __attribute__((packed));

/* FIR equalizer component */
struct sof_ipc_comp_eq_fir {
	struct sof_ipc_comp comp;
	struct sof_ipc_comp_config config;
	uint32_t size;

	/* reserved for future use */
	uint32_t reserved[8];

	unsigned char data[0];
} __attribute__((packed));

/* IIR equalizer component */
struct sof_ipc_comp_eq_iir {
	struct sof_ipc_comp comp;
	struct sof_ipc_comp_config config;
	uint32_t size;

	/* reserved for future use */
	uint32_t reserved[8];

	unsigned char data[0];
} __attribute__((packed));

/* frees components, buffers and pipelines
 * SOF_IPC_TPLG_COMP_FREE, SOF_IPC_TPLG_PIPE_FREE, SOF_IPC_TPLG_BUFFER_FREE
 */
struct sof_ipc_free {
	struct sof_ipc_hdr hdr;
	uint32_t id;
} __attribute__((packed));

struct sof_ipc_comp_reply {
	struct sof_ipc_reply rhdr;
	uint32_t id;
	uint32_t offset;
} __attribute__((packed));

/*
 * Pipeline
 */

/* new pipeline - SOF_IPC_TPLG_PIPE_NEW */
struct sof_ipc_pipe_new {
	struct sof_ipc_hdr hdr;
	uint32_t comp_id;	/**< component id for pipeline */
	uint32_t pipeline_id;	/**< pipeline id */
	uint32_t sched_id;	/**< sheduling component id */
	uint32_t core;		/**< core we run on */
	uint32_t deadline;	/**< execution completion deadline in us*/
	uint32_t priority;	/**< priority level 0 (low) to 10 (max) */
	uint32_t period_mips;	/**< worst case instruction count per period */
	uint32_t frames_per_sched;/**< output frames of pipeline, 0 is variable */
	uint32_t xrun_limit_usecs; /**< report xruns greater than limit */

	/* non zero if timer scheduled, otherwise DAI DMA irq scheduled */
	uint32_t timer_delay;
} __attribute__((packed));

/* pipeline construction complete - SOF_IPC_TPLG_PIPE_COMPLETE */
struct sof_ipc_pipe_ready {
	struct sof_ipc_hdr hdr;
	uint32_t comp_id;
} __attribute__((packed));

struct sof_ipc_pipe_free {
	struct sof_ipc_hdr hdr;
	uint32_t comp_id;
} __attribute__((packed));

/* connect two components in pipeline - SOF_IPC_TPLG_COMP_CONNECT */
struct sof_ipc_pipe_comp_connect {
	struct sof_ipc_hdr hdr;
	uint32_t source_id;
	uint32_t sink_id;
} __attribute__((packed));

#endif
