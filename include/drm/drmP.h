/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _DRMP_H_
#define _DRMP_H_

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/dma-mapping.h>
#include <linux/dma-fence.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/poll.h>

#include <drm/drm_device.h>
#include <drm/drm_drv.h>
#include <drm/drm_file.h>
#include <drm/drm_ioctl.h>
#include <drm/drm_vblank.h>
#include <drm/drm_gem.h>
#include <drm/drm_prime.h>
#include <drm/drm_rect.h>
#include <drm/drm_modes.h>
#include <drm/drm_framebuffer.h>
#include <drm/drm_connector.h>
#include <drm/drm_crtc.h>
#include <drm/drm_encoder.h>
#include <drm/drm_plane.h>
#include <drm/drm_atomic.h>
#include <drm/drm_atomic_helper.h>
#include <drm/drm_probe_helper.h>
#include <drm/drm_modeset_helper.h>
#include <drm/drm_bridge.h>
#include <drm/drm_print.h>

#define drm_gem_object_put_unlocked(obj) drm_gem_object_put(obj)
#define DRIVER_HAVE_IRQ 0
#define DRIVER_PRIME 0

#endif /* _DRMP_H_ */
