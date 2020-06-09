################################################################################
#
# pulp driver
#
################################################################################

PULP_DRIVER_VERSION = 0.1
PULP_DRIVER_SITE_METHOD = local
PULP_DRIVER_SITE = $(BR2_EXTERNAL_HERO_PATH)/support/pulp-driver
PULP_DRIVER_LICENSE = GPL
PULP_DRIVER_INSTALL_TARGET = YES
PULP_DRIVER_DEPENDENCIES = libpulp

PULP_DRIVER_PULP_INC = $(BR2_EXTERNAL_HERO_PATH)/pulp/sdk/pkg/sdk/dev/install/include/
PULP_DRIVER_CFLAGS = -DDEBUG_LEVEL=$(BR2_PACKAGE_PULP_DRIVER_DEBUG_LEVEL)
ifneq ($(BR2_PACKAGE_PULP_DRIVER_DEBUG_LEVEL),0)
PULP_DRIVER_CFLAGS += -g
endif
PULP_DRIVER_CFLAGS += -I$(LIBPULP_SITE)/inc
PULP_DRIVER_CFLAGS += -I$(PULP_DRIVER_PULP_INC)
PULP_DRIVER_CFLAGS += -DPLATFORM=$(BR2_PACKAGE_HERO_PLATFORM)

PULP_DRIVER_MK_OPTS = PLATFORM=$(BR2_PACKAGE_HERO_PLATFORM) CFLAGS="$(PULP_DRIVER_CFLAGS)"
PULP_DRIVER_MODULE_MAKE_OPTS = $(PULP_DRIVER_MK_OPTS)

PULP_DRIVER_TARGET_MAKE_ENV = $(TARGET_MAKE_ENV) $(PULP_DRIVER_MK_OPTS) \
	HERO_PULP_INC_DIR=$(PULP_DRIVER_PULP_INC) \
	HERO_LIBPULP_DIR=${LIBPULP_SITE} \
	KERNEL_ARCH=$(KERNEL_ARCH) \
	KERNEL_DIR=$(LINUX_DIR) \
	KERNEL_CROSS_COMPILE=$(TARGET_CROSS) \
	CROSS_COMPILE=$(TARGET_CROSS)

define PULP_DRIVER_CLEAN_BUILD
	$(PULP_DRIVER_TARGET_MAKE_ENV) $(MAKE) -C $(@D) clean
endef
PULP_DRIVER_PRE_BUILD_HOOKS += PULP_DRIVER_CLEAN_BUILD

define PULP_DRIVER_BUILD_CMDS
	$(PULP_DRIVER_TARGET_MAKE_ENV) $(MAKE) -C $(@D) build
endef

define PULP_DRIVER_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0644 $(@D)/pulp.ko $(TARGET_DIR)/lib/modules/$(LINUX_VERSION_PROBED)/extra/pulp.ko
endef

$(eval $(generic-package))
