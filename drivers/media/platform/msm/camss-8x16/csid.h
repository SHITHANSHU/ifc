/*
 * csid.h
 *
 * Qualcomm MSM Camera Subsystem - CSID Module
 *
 * Copyright (c) 2011-2014, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2016 Linaro Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef QC_MSM_CAMSS_CSID_H
#define QC_MSM_CAMSS_CSID_H

#include <linux/clk.h>
#include <media/media-entity.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-mediabus.h>
#include <media/v4l2-subdev.h>

#define MSM_CSID_PAD_SINK 0
#define MSM_CSID_PAD_SRC 1
#define MSM_CSID_PADS_NUM 2

enum csid_payload_mode {
	CSID_PAYLOAD_MODE_INCREMENTING = 0,
	CSID_PAYLOAD_MODE_ALTERNATING_55_AA = 1,
	CSID_PAYLOAD_MODE_ALL_ZEROES = 2,
	CSID_PAYLOAD_MODE_ALL_ONES = 3,
	CSID_PAYLOAD_MODE_RANDOM = 4,
	CSID_PAYLOAD_MODE_USER_SPECIFIED = 5,
};

struct csid_testgen_config {
	u8 enabled;
	enum csid_payload_mode payload_mode;
};

struct csid_phy_config {
	u8 csiphy_id;
	u8 lane_cnt;
	u32 lane_assign;
};

struct csid_device {
	u8 id;
	struct v4l2_subdev subdev;
	struct media_pad pads[MSM_CSID_PADS_NUM];
	void __iomem *base;
	u32 irq;
	struct clk **clock;
	s32 *clock_rate;
	int nclocks;
	struct regulator *vdda;
	struct completion reset_complete;
	struct csid_testgen_config testgen;
	struct csid_phy_config phy;
	struct v4l2_mbus_framefmt fmt[MSM_CSID_PADS_NUM];
	struct v4l2_ctrl_handler ctrls;
	struct v4l2_ctrl *testgen_mode;
};

struct resources;

int msm_csid_subdev_init(struct csid_device *csid,
			 struct resources *res, u8 id);

int msm_csid_register_entities(struct csid_device *csid,
			       struct v4l2_device *v4l2_dev);

void msm_csid_unregister_entities(struct csid_device *csid);

void msm_csid_get_csid_id(struct media_entity *entity, u8 *id);

#endif /* QC_MSM_CAMSS_CSID_H */
