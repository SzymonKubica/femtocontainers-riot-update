DEVELHELP = 0
include ../Makefile.build_system_common

USEMODULE += shell

ifeq (native, $(BOARD))
  RIOT_TERMINAL ?= native
endif

# No need for test_utils_interactive_sync in this test since the test
# synchronizes by itself through `shellping` command.
DISABLE_MODULE += test_utils_interactive_sync

# include sys/test_utils/dummy_thread
USEMODULE += dummy_thread

# microbit qemu failing currently
TEST_ON_CI_BLACKLIST += microbit

include $(RIOTBASE)/Makefile.include

# Set the shell echo configuration via CFLAGS if not being controlled via Kconfig
# Disable shell echo and prompt to not have them in the way for testing
ifndef CONFIG_KCONFIG_USEMODULE_SHELL
  CFLAGS += -DCONFIG_SHELL_NO_ECHO -DCONFIG_SHELL_NO_PROMPT
endif
