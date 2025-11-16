
/**********************************************************/
/*            Blade Script | Built-in Module              */
/*                Developed by Hamid Memar                */
/**********************************************************/

#ifndef BLADE_REGISTER_TYPES_H
#define BLADE_REGISTER_TYPES_H

#include "modules/register_module_types.h"

void initialize_blade_module(ModuleInitializationLevel p_level);
void uninitialize_blade_module(ModuleInitializationLevel p_level);

// Utilities
void *get_blade_language();

#endif // BLADE_REGISTER_TYPES_H
