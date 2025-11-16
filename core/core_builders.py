"""Functions used to generate source files during build time"""

from collections import OrderedDict
from io import TextIOWrapper

import methods


# Generate disabled classes
def disabled_class_builder(target, source, env):
    with methods.generated_wrapper(str(target[0])) as file:
        for c in source[0].read():
            if cs := c.strip():
                file.write(f"#define ClassDB_Disable_{cs} 1\n")


# Generate version info
def version_info_builder(target, source, env):
    with methods.generated_wrapper(str(target[0])) as file:
        file.write(
            """\
#define GODOT_VERSION_SHORT_NAME "{short_name}"
#define GODOT_VERSION_NAME "{name}"
#define GODOT_VERSION_MAJOR {major}
#define GODOT_VERSION_MINOR {minor}
#define GODOT_VERSION_PATCH {patch}
#define GODOT_VERSION_STATUS "{status}"
#define GODOT_VERSION_BUILD "{build}"
#define GODOT_VERSION_MODULE_CONFIG "{module_config}"
#define GODOT_VERSION_WEBSITE "{website}"
#define GODOT_VERSION_DOCS_BRANCH "{docs_branch}"
#define GODOT_VERSION_DOCS_URL "https://docs.godotengine.org/en/" GODOT_VERSION_DOCS_BRANCH
""".format(**source[0].read())
        )


def version_hash_builder(target, source, env):
    with methods.generated_wrapper(str(target[0])) as file:
        file.write(
            """\
#include "core/version.h"

const char *const GODOT_VERSION_HASH = "{git_hash}";
const uint64_t GODOT_VERSION_TIMESTAMP = {git_timestamp};
""".format(**source[0].read())
        )


def encryption_key_builder(target, source, env):
    src = source[0].read() or "0" * 64
    try:
        buffer = bytes.fromhex(src)
        if len(buffer) != 32:
            raise ValueError
    except ValueError:
        methods.print_error(
            f'Invalid AES256 encryption key, not 64 hexadecimal characters: "{src}".\n'
            "Unset `SCRIPT_AES256_ENCRYPTION_KEY` in your environment "
            "or make sure that it contains exactly 64 hexadecimal characters."
        )
        raise

    with methods.generated_wrapper(str(target[0])) as file:
        file.write(
            f"""\
#include "core/config/project_settings.h"

uint8_t script_encryption_key[32] = {{
	{methods.format_buffer(buffer, 1)}
}};"""
        )


def make_certs_header(target, source, env):
    buffer = methods.get_buffer(str(source[0]))
    decomp_size = len(buffer)
    buffer = methods.compress_buffer(buffer)

    with methods.generated_wrapper(str(target[0])) as file:
        # System certs path. Editor will use them if defined. (for package maintainers)
        file.write(f'#define _SYSTEM_CERTS_PATH "{source[2]}"\n')
        if source[1].read():
            # Defined here and not in env so changing it does not trigger a full rebuild.
            file.write(f"""\
#define BUILTIN_CERTS_ENABLED

inline constexpr int _certs_compressed_size = {len(buffer)};
inline constexpr int _certs_uncompressed_size = {decomp_size};
inline constexpr unsigned char _certs_compressed[] = {{
	{methods.format_buffer(buffer, 1)}
}};
""")
