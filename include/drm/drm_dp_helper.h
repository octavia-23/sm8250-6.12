/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _DRM_DP_HELPER_COMPAT_H_
#define _DRM_DP_HELPER_COMPAT_H_

#include <drm/display/drm_dp.h>
#include <drm/display/drm_dp_helper.h>

#define DP_LINK_CAP_ENHANCED_FRAMING			(1 << 0)

#define DP_TEST_PHY_PATTERN_NONE			0x0
#define DP_TEST_PHY_PATTERN_D10_2_NO_SCRAMBLING		0x1
#define DP_TEST_PHY_PATTERN_SYMBOL_ERR_MEASUREMENT_CNT	0x2
#define DP_TEST_PHY_PATTERN_PRBS7			0x3
#define DP_TEST_PHY_PATTERN_80_BIT_CUSTOM_PATTERN	0x4
#define DP_TEST_PHY_PATTERN_CP2520_PATTERN_1		0x5
#define DP_TEST_PHY_PATTERN_CP2520_PATTERN_2		0x6
#define DP_TEST_PHY_PATTERN_CP2520_PATTERN_3		0x7

#ifndef DP_TEST_PHY_PATTERN
#define DP_TEST_PHY_PATTERN				0x248
#endif

struct drm_dp_link {
	unsigned char revision;
	unsigned int rate;
	unsigned int num_lanes;
	unsigned long capabilities;
};

#endif /* _DRM_DP_HELPER_COMPAT_H_ */
