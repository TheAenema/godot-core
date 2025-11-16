
/*-------------------------------------------------------------+
|                                                              |
|                   _________   ______ _    _____              |
|                  / / ____/ | / / __ \ |  / /   |             |
|             __  / / __/ /  |/ / / / / | / / /| |             |
|            / /_/ / /___/ /|  / /_/ /| |/ / ___ |             |
|            \____/_____/_/ |_/\____/ |___/_/  |_|             |
|                                                              |
|                 Jenova Code IDE Integration                  |
|                   Developed by Hamid.Memar                   |
|                                                              |
+-------------------------------------------------------------*/

#pragma once

#include "core/object/script_language.h"
#include "editor/editor_interface.h"
#include "editor/plugins/editor_plugin.h"
#include "editor/file_system/editor_file_system.h"

class JenovaIDE : public EditorPlugin {
	GDCLASS(JenovaIDE, EditorPlugin);

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	bool handles(Object *p_object) const override;
	void edit(Object *p_object) override;
	String get_plugin_name() const override;
	bool has_main_screen() const override;
	const Ref<Texture2D> get_plugin_icon() const override;
	void make_visible(bool p_visible) override;
	void get_breakpoints(List<String> *p_breakpoints) override;

public:
	Control *get_ide_control() const;
	bool create_new_text_file();
	bool edit_file(const Ref<Script> &script, int line, int col, bool grab_focus);
	bool reload_scripts(bool deep_reload);
	bool open_find_in_files_dialog(const String &text);
	bool save_current_script();
	bool script_goto_method(const Ref<Script> &p_script, const StringName &track_name);
	bool set_live_auto_reload_running_scripts(bool state);
	bool update_script_times();
	bool set_scene_root_script(const Ref<Script> &p_script);

public:
	static void Initialize();
	static JenovaIDE *get_singleton();

public:
	void OnContainerResized();
	void ProcessMouseClick(Vector2i mousePos);
	void ProcessOverlayClick(Vector2 mousePos);
	void EditorThemeUpdate();

private:
	void UpdateActiveState(bool state);

};
