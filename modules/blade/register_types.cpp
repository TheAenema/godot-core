
/**********************************************************/
/*            Blade Script | Built-in Module              */
/*                Developed by Hamid Memar                */
/**********************************************************/

#include "register_types.h"

#include "core/io/config_file.h"
#include "core/object/script_language.h"
#include "core/core_bind.h"
#include "core/os/shared_object.h"
#include <unordered_set>

// Blade Script
class BladeScript : public Script {
	GDCLASS(BladeScript, Script);

protected:
	static void _bind_methods() {
	}
	void _notification(int p_what) {
	}
	Variant _get_property_default_value(const StringName &p_property) {
		return Variant();
	}
	TypedArray<Dictionary> _get_script_property_list() {
		return TypedArray<Dictionary>();
	}
	TypedArray<Dictionary> _get_script_method_list() {
		return TypedArray<Dictionary>();
	}
	TypedArray<Dictionary> _get_script_signal_list() {
		return TypedArray<Dictionary>();
	}
	Dictionary _get_script_constant_map() {
		return Dictionary();
	}
	void _set_debugger_break_language() {
	}

public:
	void reload_from_file() override {
		// No-op
	}
	bool can_instantiate() const override {
		return true;
	}
	Ref<Script> get_base_script() const override {
		return Ref<Script>();
	}
	StringName get_global_name() const override {
		return StringName("BladeScript");
	}
	bool inherits_script(const Ref<Script> &p_script) const override {
		return false;
	}
	StringName get_instance_base_type() const override {
		return StringName("BladeScript");
	}
	ScriptInstance *instance_create(Object *p_this) override {
		return nullptr;
	}
	bool instance_has(const Object *p_this) const override {
		return false;
	}
	bool has_source_code() const override {
		return true;
	}
	String get_source_code() const override {
		return "/* Blade Script */";
	}
	void set_source_code(const String &p_code) override {
	}
	Error reload(bool p_keep_state = false) override {
		return OK;
	}
	bool has_method(const StringName &p_method) const override {
		return false;
	}
	MethodInfo get_method_info(const StringName &p_method) const override {
		return MethodInfo();
	}
	bool is_tool() const override {
		return false;
	}
	bool is_valid() const override {
		return true;
	}
	bool is_abstract() const override {
		return false;
	}
	ScriptLanguage *get_language() const override {
		return (ScriptLanguage *)get_blade_language(); 
	}
	bool has_script_signal(const StringName &p_signal) const override {
		return false;
	}
	void get_script_signal_list(List<MethodInfo> *r_signals) const override {
	}
	bool get_property_default_value(const StringName &p_property, Variant &r_value) const override {
		r_value = Variant();
		return false;
	}
	void get_script_method_list(List<MethodInfo> *p_list) const override {
	}
	void get_script_property_list(List<PropertyInfo> *p_list) const override {
	}
	const Variant get_rpc_config() const override {
		return Dictionary();
	}

	#ifdef TOOLS_ENABLED
	String get_class_icon_path() const override {
		return "";
	}
	PropertyInfo get_class_category() const override {
		return PropertyInfo(Variant::NIL, "BladeScript");
	}
	#endif

	BladeScript() {}
};
class BladeScriptResourceLoader : public ResourceFormatLoader {
	GDCLASS(BladeScriptResourceLoader, ResourceFormatLoader);

protected:
	static void _bind_methods() {}

private:
	inline static Ref<BladeScriptResourceLoader> loader;

public:
	static void init() {
		loader.instantiate();
		ResourceLoader::add_resource_format_loader(loader);
	}
	static void deinit() {
		ResourceLoader::remove_resource_format_loader(loader);
		loader.unref();
	}

	Ref<Resource> load(const String &p_path, const String &p_original_path = "", Error *r_error = nullptr, bool p_use_sub_threads = false, float *r_progress = nullptr, CacheMode p_cache_mode = CACHE_MODE_REUSE) override {
		Ref<BladeScript> blade_script = memnew(BladeScript);
		if (blade_script.is_valid()) {
			blade_script->set_source_code(FileAccess::get_file_as_string(p_path));
			if (r_error) {
				*r_error = OK;
			}
			return blade_script;
		}
		if (r_error) {
			*r_error = ERR_CANT_CREATE;
		}
		return Ref<Resource>();
	}
	bool exists(const String &p_path) const override {
		return FileAccess::exists(p_path);
	}
	void get_recognized_extensions(List<String> *p_extensions) const override {
		p_extensions->push_back("blade");
	}
	bool recognize_path(const String &p_path, const String &p_for_type = String()) const override {
		return p_path.get_extension().to_lower() == "blade";
	}
	bool handles_type(const String &p_type) const override {
		return p_type == "BladeScript" || p_type == "Script";
	}
	String get_resource_type(const String &p_path) const override {
		if (p_path.get_extension().to_lower() == "blade") {
			return "BladeScript";
		}
		return "";
	}
	String get_resource_script_class(const String &p_path) const override {
		return "BladeScript";
	}
};
class BladeScriptResourceSaver : public ResourceFormatSaver {
	GDCLASS(BladeScriptResourceSaver, ResourceFormatSaver);

protected:
	static void _bind_methods() {}

private:
	inline static Ref<BladeScriptResourceSaver> saver;

public:
	static void init() {
		saver.instantiate();
		ResourceSaver::add_resource_format_saver(saver);
	}
	static void deinit()
	{
		ResourceSaver::remove_resource_format_saver(saver);
		saver.unref();
	}
	Error save(const Ref<Resource> &p_resource, const String &p_path, uint32_t p_flags = 0) override {
		BladeScript *_script = Object::cast_to<BladeScript>(p_resource.ptr());
		if (!_script) {
			return ERR_INVALID_PARAMETER;
		}

		Ref<FileAccess> file = FileAccess::open(p_path, FileAccess::WRITE);
		if (!file.is_valid()) {
			return ERR_FILE_CANT_OPEN;
		}

		file->store_string(_script->get_source_code());
		file->close();
		return OK;
	}
	Error set_uid(const String &p_path, ResourceUID::ID p_uid) override {
		return OK;
	}
	bool recognize(const Ref<Resource> &p_resource) const override {
		return Object::cast_to<BladeScript>(p_resource.ptr()) != nullptr;
	}
	void get_recognized_extensions(const Ref<Resource> &p_resource, List<String> *p_extensions) const override {
		if (recognize(p_resource)) {
			p_extensions->push_back("blade");
		}
	}
	bool recognize_path(const Ref<Resource> &p_resource, const String &p_path) const override {
		return recognize(p_resource);
	}
};
class BladeLanguage : public ScriptLanguage {
	GDCLASS(BladeLanguage, ScriptLanguage);

protected:
    static void _bind_methods() {}
    String file;

private:
	inline static BladeLanguage *singleton = nullptr;

public:
    static void create() {
		ClassDB::register_internal_class<BladeScript>();
		ClassDB::register_internal_class<BladeScriptResourceLoader>();
		ClassDB::register_internal_class<BladeScriptResourceSaver>();
		ClassDB::register_internal_class<BladeLanguage>();
		BladeScriptResourceLoader::init();
		BladeScriptResourceSaver::init();
        singleton = memnew(BladeLanguage);
        CoreBind::Engine::get_singleton()->register_script_language(singleton);
    }
    static void destroy() {
		if (singleton) {
			BladeScriptResourceLoader::deinit();
			BladeScriptResourceSaver::deinit();
			CoreBind::Engine::get_singleton()->unregister_script_language(singleton);
			memdelete(singleton);
			singleton = nullptr;
		}
    }
    static BladeLanguage* get_singleton() {
        return singleton;
    }

	// Methods
    String get_name() const override {
        return "Blade Script";
    }
    void init() override {}
    String get_type() const override {
		return "BladeScript";
    }
    String get_extension() const override {
        return "blade";
    }
	void get_recognized_extensions(List<String> *p_extensions) const override {
		if (p_extensions) {
			p_extensions->push_back("blade");
		}
	}
    void finish() override {}
    Vector<String> get_reserved_words() const override {
		static const PackedStringArray reserved_words{
			"alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept",
			"auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
			"class", "compl", "concept", "const", "consteval", "constexpr", "const_cast", "continue", "co_await",
			"co_return", "co_yield", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else",
			"enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline",
			"int", "int32_t", "int64_t", "uint32_t", "uint64_t", "long", "size_t", "mutable", "namespace", "new",
			"noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected", "public",
			"reflexpr", "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static",
			"static_assert", "static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local",
			"throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void",
			"volatile", "wchar_t", "while", "xor", "xor_eq", "jenova", "godot", "__int64", "__int32", "Caller", "Variant",
			"include", "ifdef", "else", "endif", "pragma"
		};
		return reserved_words;
    }
    bool is_control_flow_keyword(const String &p_string) const override {
		static const std::unordered_set<std::string> control_flow_keywords{
			"if", "else", "switch", "case", "default", "while", "do", "for", "break", "continue", "return", "goto", "try", "catch", "throw", "co_await",
			"co_return", "co_yield", "jenova", "godot", "include", "ifdef", "else", "endif", "pragma"
		};
		return control_flow_keywords.find(p_string.utf8().get_data()) != control_flow_keywords.end();
    }
    Vector<String> get_comment_delimiters() const override {
		PackedStringArray comment_delimiters;
		comment_delimiters.push_back("/* */");
		comment_delimiters.push_back("//");
		return comment_delimiters;
    }
    Vector<String> get_doc_comment_delimiters() const override {
		PackedStringArray doc_comment_delimiters;
		doc_comment_delimiters.push_back("///");
		doc_comment_delimiters.push_back("/** */");
		return doc_comment_delimiters;
    }
    Vector<String> get_string_delimiters() const override {
		PackedStringArray string_delimiters;
		string_delimiters.push_back("' '");
		string_delimiters.push_back("\" \"");
		return string_delimiters;
    }
    Ref<Script> make_template(const String &, const String &, const String &) const override {
		return Ref<Script>(memnew(BladeScript));
    }
    Vector<ScriptTemplate> get_built_in_templates(const StringName &) override {
        return {};
    }
    bool is_using_templates() override {
        return false;
    }
    bool validate(const String &, const String &, List<String> *, List<ScriptError> *, List<Warning> *, HashSet<int> *) const override {
        return true;
    }
    String validate_path(const String &) const override {
        return "";
    }
    Script *create_script() const override {
		return memnew(BladeScript);
    }
    bool has_named_classes() const {
        return false;
    }
    bool supports_builtin_mode() const override {
        return false;
    }
    bool supports_documentation() const override {
        return false;
    }
    bool can_inherit_from_file() const override {
        return false;
    }
    int find_function(const String &, const String &) const override {
        return -1;
    }
    String make_function(const String &, const String &, const PackedStringArray &) const override {
        return "";
    }
    bool can_make_function() const override {
        return false;
    }
    Error open_in_external_editor(const Ref<Script> &, int, int) override {
        return OK;
    }
    bool overrides_external_editor() override {
        return false;
    }
    ScriptNameCasing preferred_file_name_casing() const override {
        return SCRIPT_NAME_CASING_SNAKE_CASE;
    }
    Error complete_code(const String &, const String &, Object *, List<CodeCompletionOption> *, bool &, String &) override {
        return OK;
    }
	Error lookup_code(const String &p_code, const String &p_symbol, const String &p_path, Object *p_owner, LookupResult &r_result) override {
		return ERR_UNAVAILABLE;
	}
	void auto_indent_code(String &p_code, int p_from_line, int p_to_line) const override {}
	void add_global_constant(const StringName &p_variable, const Variant &p_value) override {}
	void add_named_global_constant(const StringName &p_name, const Variant &p_value) override {}
	void remove_named_global_constant(const StringName &p_name) override {}
	void thread_enter() override {}
	void thread_exit() override {}
	String debug_get_error() const override { return ""; }
	int debug_get_stack_level_count() const override { return 0; }
	int debug_get_stack_level_line(int p_level) const override { return 0; }
	String debug_get_stack_level_function(int p_level) const override { return ""; }
	String debug_get_stack_level_source(int p_level) const override { return ""; }
	void debug_get_stack_level_locals(int p_level, List<String> *p_locals, List<Variant> *p_values, int p_max_subitems = -1, int p_max_depth = -1) override {}
	void debug_get_stack_level_members(int p_level, List<String> *p_members, List<Variant> *p_values, int p_max_subitems = -1, int p_max_depth = -1) override {}
	ScriptInstance *debug_get_stack_level_instance(int p_level) override { return nullptr; }
	void debug_get_globals(List<String> *p_globals, List<Variant> *p_values, int p_max_subitems = -1, int p_max_depth = -1) override {}
	String debug_parse_stack_level_expression(int p_level, const String &p_expression, int p_max_subitems = -1, int p_max_depth = -1) override { return ""; }
	Vector<StackInfo> debug_get_current_stack_info() override { return Vector<StackInfo>(); }
	void reload_all_scripts() override {}
	void reload_scripts(const Array &p_scripts, bool p_soft_reload) override {}
	void reload_tool_script(const Ref<Script> &p_script, bool p_soft_reload) override {}
	void get_public_functions(List<MethodInfo> *p_functions) const override {}
	void get_public_constants(List<Pair<String, Variant>> *p_constants) const override {}
	void get_public_annotations(List<MethodInfo> *p_annotations) const override {}
	void profiling_start() override {}
	void profiling_stop() override {}
	void profiling_set_save_native_calls(bool p_enable) override {}
	int profiling_get_accumulated_data(ProfilingInfo *p_info_arr, int p_info_max) override { return 0; }
	int profiling_get_frame_data(ProfilingInfo *p_info_arr, int p_info_max) override { return 0; }
	void frame() override {}
	bool handles_global_class_type(const String &p_type) const override { return false; }
	String get_global_class_name(const String &p_path, String *r_base_type = nullptr, String *r_icon_path = nullptr, bool *r_is_abstract = nullptr, bool *r_is_tool = nullptr) const override {
		return "";
	}

    BladeLanguage() {}
    ~BladeLanguage() {}
};

// Module Routines
void initialize_blade_module(ModuleInitializationLevel p_level) {
	// Validations
	if (p_level != MODULE_INITIALIZATION_LEVEL_SERVERS) {
		return;
	}

	// Register Language
	BladeLanguage::create();
	printf("Blade Script Engine v1.0.5 | Developed By Hamid.Memar\n");
}
void uninitialize_blade_module(ModuleInitializationLevel p_level) {
	BladeLanguage::destroy();
}

// Utilities
void* get_blade_language()
{
	return BladeLanguage::get_singleton();
}
