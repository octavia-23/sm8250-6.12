# SPDX-License-Identifier: GPL-2.0-only

DISPLAY_ROOT := $(srctree)/drivers/gpu/drm/msm-sde

# auto-detect subdirs
ifneq ($(filter y, $(CONFIG_ARCH_KONA) $(CONFIG_ARCH_QCOM) $(CONFIG_DRM_QCOM_SDE) $(CONFIG_DRM_MSM_SDE)),)
include $(DISPLAY_ROOT)/config/konadisp.conf
LINUXINCLUDE    += -include $(DISPLAY_ROOT)/config/konadispconf.h
endif

ifeq ($(CONFIG_ARCH_LITO), y)
include $(DISPLAY_ROOT)/config/saipdisp.conf
LINUXINCLUDE    += -include $(DISPLAY_ROOT)/config/saipdispconf.h
endif

ifeq ($(CONFIG_ARCH_BENGAL), y)
include $(DISPLAY_ROOT)/config/bengaldisp.conf
LINUXINCLUDE    += -include $(DISPLAY_ROOT)/config/bengaldispconf.h
endif

obj-y += msm/
obj-$(CONFIG_MSM_SDE_ROTATOR) += rotator/
obj-$(CONFIG_QCOM_MDSS_PLL) += pll/
