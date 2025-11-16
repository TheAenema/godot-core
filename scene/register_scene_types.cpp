/**************************************************************************/
/*  register_scene_types.cpp                                              */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "register_scene_types.h"

#include "core/config/project_settings.h"
#include "core/object/class_db.h"
#include "core/os/os.h"
#include "scene/animation/animation_blend_space_1d.h"
#include "scene/animation/animation_blend_space_2d.h"
#include "scene/animation/animation_blend_tree.h"
#include "scene/animation/animation_mixer.h"
#include "scene/animation/animation_node_extension.h"
#include "scene/animation/animation_node_state_machine.h"
#include "scene/animation/animation_player.h"
#include "scene/animation/animation_tree.h"
#include "scene/animation/tween.h"
#include "scene/audio/audio_stream_player.h"
#include "scene/debugger/scene_debugger.h"
#include "scene/gui/aspect_ratio_container.h"
#include "scene/gui/box_container.h"
#include "scene/gui/button.h"
#include "scene/gui/center_container.h"
#include "scene/gui/check_box.h"
#include "scene/gui/check_button.h"
#include "scene/gui/code_edit.h"
#include "scene/gui/color_picker.h"
#include "scene/gui/color_rect.h"
#include "scene/gui/control.h"
#include "scene/gui/dialogs.h"
#include "scene/gui/file_dialog.h"
#include "scene/gui/flow_container.h"
#include "scene/gui/foldable_container.h"
#include "scene/gui/graph_edit.h"
#include "scene/gui/graph_frame.h"
#include "scene/gui/graph_node.h"
#include "scene/gui/grid_container.h"
#include "scene/gui/item_list.h"
#include "scene/gui/label.h"
#include "scene/gui/line_edit.h"
#include "scene/gui/link_button.h"
#include "scene/gui/margin_container.h"
#include "scene/gui/menu_bar.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/nine_patch_rect.h"
#include "scene/gui/option_button.h"
#include "scene/gui/panel.h"
#include "scene/gui/panel_container.h"
#include "scene/gui/popup_menu.h"
#include "scene/gui/progress_bar.h"
#include "scene/gui/reference_rect.h"
#include "scene/gui/rich_text_effect.h"
#include "scene/gui/rich_text_label.h"
#include "scene/gui/scroll_bar.h"
#include "scene/gui/scroll_container.h"
#include "scene/gui/separator.h"
#include "scene/gui/slider.h"
#include "scene/gui/spin_box.h"
#include "scene/gui/split_container.h"
#include "scene/gui/subviewport_container.h"
#include "scene/gui/tab_bar.h"
#include "scene/gui/tab_container.h"
#include "scene/gui/text_edit.h"
#include "scene/gui/texture_button.h"
#include "scene/gui/texture_progress_bar.h"
#include "scene/gui/texture_rect.h"
#include "scene/gui/tree.h"
#include "scene/gui/video_stream_player.h"
#include "scene/main/canvas_item.h"
#include "scene/main/canvas_layer.h"
#include "scene/main/http_request.h"
#include "scene/main/instance_placeholder.h"
#include "scene/main/missing_node.h"
#include "scene/main/multiplayer_api.h"
#include "scene/main/resource_preloader.h"
#include "scene/main/scene_tree.h"
#include "scene/main/shader_globals_override.h"
#include "scene/main/status_indicator.h"
#include "scene/main/timer.h"
#include "scene/main/viewport.h"
#include "scene/main/window.h"
#include "scene/resources/animation_library.h"
#include "scene/resources/atlas_texture.h"
#include "scene/resources/audio_stream_polyphonic.h"
#include "scene/resources/audio_stream_wav.h"
#include "scene/resources/bit_map.h"
#include "scene/resources/bone_map.h"
#include "scene/resources/camera_attributes.h"
#include "scene/resources/camera_texture.h"
#include "scene/resources/canvas_item_material.h"
#include "scene/resources/color_palette.h"
#include "scene/resources/compositor.h"
#include "scene/resources/compressed_texture.h"
#include "scene/resources/curve_texture.h"
#include "scene/resources/environment.h"
#include "scene/resources/external_texture.h"
#include "scene/resources/font.h"
#include "scene/resources/gradient.h"
#include "scene/resources/gradient_texture.h"
#include "scene/resources/image_texture.h"
#include "scene/resources/immediate_mesh.h"
#include "scene/resources/label_settings.h"
#include "scene/resources/material.h"
#include "scene/resources/mesh_data_tool.h"
#include "scene/resources/mesh_texture.h"
#include "scene/resources/multimesh.h"
#if !defined(NAVIGATION_2D_DISABLED) || !defined(NAVIGATION_3D_DISABLED)
#include "scene/resources/navigation_mesh.h"
#endif // !defined(NAVIGATION_2D_DISABLED) || !defined(NAVIGATION_3D_DISABLED)
#include "scene/resources/dpi_texture.h"
#include "scene/resources/packed_scene.h"
#include "scene/resources/particle_process_material.h"
#include "scene/resources/placeholder_textures.h"
#include "scene/resources/portable_compressed_texture.h"
#include "scene/resources/resource_format_text.h"
#include "scene/resources/shader_include.h"
#include "scene/resources/skeleton_profile.h"
#include "scene/resources/sky.h"
#include "scene/resources/style_box.h"
#include "scene/resources/style_box_flat.h"
#include "scene/resources/style_box_line.h"
#include "scene/resources/style_box_texture.h"
#include "scene/resources/surface_tool.h"
#include "scene/resources/syntax_highlighter.h"
#include "scene/resources/text_line.h"
#include "scene/resources/text_paragraph.h"
#include "scene/resources/texture.h"
#include "scene/resources/texture_rd.h"
#include "scene/resources/theme.h"
#include "scene/resources/video_stream.h"
#include "scene/theme/theme_db.h"

// 2D
#include "scene/2d/animated_sprite_2d.h"
#include "scene/2d/audio_listener_2d.h"
#include "scene/2d/audio_stream_player_2d.h"
#include "scene/2d/back_buffer_copy.h"
#include "scene/2d/camera_2d.h"
#include "scene/2d/canvas_group.h"
#include "scene/2d/canvas_modulate.h"
#include "scene/2d/cpu_particles_2d.h"
#include "scene/2d/gpu_particles_2d.h"
#include "scene/2d/light_2d.h"
#include "scene/2d/light_occluder_2d.h"
#include "scene/2d/line_2d.h"
#include "scene/2d/marker_2d.h"
#include "scene/2d/mesh_instance_2d.h"
#include "scene/2d/multimesh_instance_2d.h"
#include "scene/2d/parallax_2d.h"
#include "scene/2d/path_2d.h"
#include "scene/2d/polygon_2d.h"
#include "scene/2d/remote_transform_2d.h"
#include "scene/2d/skeleton_2d.h"
#include "scene/2d/sprite_2d.h"
#include "scene/2d/tile_map_layer.h"
#include "scene/2d/visible_on_screen_notifier_2d.h"
#include "scene/resources/2d/polygon_path_finder.h"
#include "scene/resources/2d/skeleton/skeleton_modification_2d.h"
#include "scene/resources/2d/skeleton/skeleton_modification_2d_ccdik.h"
#include "scene/resources/2d/skeleton/skeleton_modification_2d_fabrik.h"
#include "scene/resources/2d/skeleton/skeleton_modification_2d_lookat.h"
#include "scene/resources/2d/skeleton/skeleton_modification_2d_stackholder.h"
#include "scene/resources/2d/skeleton/skeleton_modification_2d_twoboneik.h"
#include "scene/resources/2d/skeleton/skeleton_modification_stack_2d.h"
#include "scene/resources/2d/tile_set.h"
#include "scene/resources/world_2d.h"

#ifndef NAVIGATION_2D_DISABLED
#include "scene/2d/navigation/navigation_agent_2d.h"
#include "scene/2d/navigation/navigation_link_2d.h"
#include "scene/2d/navigation/navigation_obstacle_2d.h"
#include "scene/2d/navigation/navigation_region_2d.h"
#include "scene/resources/2d/navigation_mesh_source_geometry_data_2d.h"
#include "scene/resources/2d/navigation_polygon.h"
#endif // NAVIGATION_2D_DISABLED

#ifndef _3D_DISABLED
#include "scene/3d/aim_modifier_3d.h"
#include "scene/3d/audio_listener_3d.h"
#include "scene/3d/audio_stream_player_3d.h"
#include "scene/3d/bone_attachment_3d.h"
#include "scene/3d/bone_constraint_3d.h"
#include "scene/3d/camera_3d.h"
#include "scene/3d/convert_transform_modifier_3d.h"
#include "scene/3d/copy_transform_modifier_3d.h"
#include "scene/3d/cpu_particles_3d.h"
#include "scene/3d/decal.h"
#include "scene/3d/fog_volume.h"
#include "scene/3d/gpu_particles_3d.h"
#include "scene/3d/gpu_particles_collision_3d.h"
#include "scene/3d/importer_mesh_instance_3d.h"
#include "scene/3d/label_3d.h"
#include "scene/3d/light_3d.h"
#include "scene/3d/lightmap_gi.h"
#include "scene/3d/lightmap_probe.h"
#include "scene/3d/look_at_modifier_3d.h"
#include "scene/3d/marker_3d.h"
#include "scene/3d/mesh_instance_3d.h"
#include "scene/3d/modifier_bone_target_3d.h"
#include "scene/3d/multimesh_instance_3d.h"
#include "scene/3d/node_3d.h"
#include "scene/3d/occluder_instance_3d.h"
#include "scene/3d/path_3d.h"
#include "scene/3d/reflection_probe.h"
#include "scene/3d/remote_transform_3d.h"
#include "scene/3d/retarget_modifier_3d.h"
#include "scene/3d/skeleton_3d.h"
#include "scene/3d/skeleton_modifier_3d.h"
#include "scene/3d/spring_bone_collision_3d.h"
#include "scene/3d/spring_bone_collision_capsule_3d.h"
#include "scene/3d/spring_bone_collision_plane_3d.h"
#include "scene/3d/spring_bone_collision_sphere_3d.h"
#include "scene/3d/spring_bone_simulator_3d.h"
#include "scene/3d/sprite_3d.h"
#include "scene/3d/visible_on_screen_notifier_3d.h"
#include "scene/3d/voxel_gi.h"
#include "scene/3d/world_environment.h"
#include "scene/animation/root_motion_view.h"
#include "scene/resources/3d/fog_material.h"
#include "scene/resources/3d/importer_mesh.h"
#include "scene/resources/3d/mesh_library.h"
#include "scene/resources/3d/navigation_mesh_source_geometry_data_3d.h"
#include "scene/resources/3d/primitive_meshes.h"
#include "scene/resources/3d/sky_material.h"
#include "scene/resources/3d/world_3d.h"
#ifndef NAVIGATION_3D_DISABLED
#include "scene/3d/navigation/navigation_agent_3d.h"
#include "scene/3d/navigation/navigation_link_3d.h"
#include "scene/3d/navigation/navigation_obstacle_3d.h"
#include "scene/3d/navigation/navigation_region_3d.h"
#include "scene/resources/3d/navigation_mesh_source_geometry_data_3d.h"
#endif // NAVIGATION_3D_DISABLED
#endif // _3D_DISABLED

#if !defined(PHYSICS_2D_DISABLED) || !defined(PHYSICS_3D_DISABLED)
#include "scene/resources/physics_material.h"
#endif // !defined(PHYSICS_2D_DISABLED) || !defined(PHYSICS_3D_DISABLED)

#ifndef PHYSICS_2D_DISABLED
#include "scene/2d/physics/animatable_body_2d.h"
#include "scene/2d/physics/area_2d.h"
#include "scene/2d/physics/character_body_2d.h"
#include "scene/2d/physics/collision_polygon_2d.h"
#include "scene/2d/physics/collision_shape_2d.h"
#include "scene/2d/physics/joints/damped_spring_joint_2d.h"
#include "scene/2d/physics/joints/groove_joint_2d.h"
#include "scene/2d/physics/joints/joint_2d.h"
#include "scene/2d/physics/joints/pin_joint_2d.h"
#include "scene/2d/physics/kinematic_collision_2d.h"
#include "scene/2d/physics/physical_bone_2d.h"
#include "scene/2d/physics/physics_body_2d.h"
#include "scene/2d/physics/ray_cast_2d.h"
#include "scene/2d/physics/rigid_body_2d.h"
#include "scene/2d/physics/shape_cast_2d.h"
#include "scene/2d/physics/static_body_2d.h"
#include "scene/2d/physics/touch_screen_button.h"
#include "scene/resources/2d/capsule_shape_2d.h"
#include "scene/resources/2d/circle_shape_2d.h"
#include "scene/resources/2d/concave_polygon_shape_2d.h"
#include "scene/resources/2d/convex_polygon_shape_2d.h"
#include "scene/resources/2d/rectangle_shape_2d.h"
#include "scene/resources/2d/segment_shape_2d.h"
#include "scene/resources/2d/separation_ray_shape_2d.h"
#include "scene/resources/2d/shape_2d.h"
#include "scene/resources/2d/skeleton/skeleton_modification_2d_jiggle.h"
#include "scene/resources/2d/skeleton/skeleton_modification_2d_physicalbones.h"
#include "scene/resources/2d/world_boundary_shape_2d.h"
#endif // PHYSICS_2D_DISABLED

#ifndef PHYSICS_3D_DISABLED
#include "scene/3d/physics/animatable_body_3d.h"
#include "scene/3d/physics/area_3d.h"
#include "scene/3d/physics/character_body_3d.h"
#include "scene/3d/physics/collision_polygon_3d.h"
#include "scene/3d/physics/collision_shape_3d.h"
#include "scene/3d/physics/joints/cone_twist_joint_3d.h"
#include "scene/3d/physics/joints/generic_6dof_joint_3d.h"
#include "scene/3d/physics/joints/hinge_joint_3d.h"
#include "scene/3d/physics/joints/joint_3d.h"
#include "scene/3d/physics/joints/pin_joint_3d.h"
#include "scene/3d/physics/joints/slider_joint_3d.h"
#include "scene/3d/physics/kinematic_collision_3d.h"
#include "scene/3d/physics/physical_bone_3d.h"
#include "scene/3d/physics/physical_bone_simulator_3d.h"
#include "scene/3d/physics/physics_body_3d.h"
#include "scene/3d/physics/ray_cast_3d.h"
#include "scene/3d/physics/rigid_body_3d.h"
#include "scene/3d/physics/shape_cast_3d.h"
#include "scene/3d/physics/soft_body_3d.h"
#include "scene/3d/physics/spring_arm_3d.h"
#include "scene/3d/physics/static_body_3d.h"
#include "scene/3d/physics/vehicle_body_3d.h"
#include "scene/resources/3d/box_shape_3d.h"
#include "scene/resources/3d/capsule_shape_3d.h"
#include "scene/resources/3d/concave_polygon_shape_3d.h"
#include "scene/resources/3d/convex_polygon_shape_3d.h"
#include "scene/resources/3d/cylinder_shape_3d.h"
#include "scene/resources/3d/height_map_shape_3d.h"
#include "scene/resources/3d/separation_ray_shape_3d.h"
#include "scene/resources/3d/sphere_shape_3d.h"
#include "scene/resources/3d/world_boundary_shape_3d.h"
#endif // PHYSICS_3D_DISABLED

static Ref<ResourceFormatSaverText> resource_saver_text;
static Ref<ResourceFormatLoaderText> resource_loader_text;

static Ref<ResourceFormatLoaderCompressedTexture2D> resource_loader_stream_texture;
static Ref<ResourceFormatLoaderCompressedTextureLayered> resource_loader_texture_layered;
static Ref<ResourceFormatLoaderCompressedTexture3D> resource_loader_texture_3d;

static Ref<ResourceFormatSaverShader> resource_saver_shader;
static Ref<ResourceFormatLoaderShader> resource_loader_shader;

static Ref<ResourceFormatSaverShaderInclude> resource_saver_shader_include;
static Ref<ResourceFormatLoaderShaderInclude> resource_loader_shader_include;

void register_scene_types() {
	OS::get_singleton()->benchmark_begin_measure("Scene", "Register Types");

	SceneStringNames::create();

	OS::get_singleton()->yield(); // may take time to init

	Node::init_node_hrcr();

	if (GD_IS_CLASS_ENABLED(CompressedTexture2D)) {
		resource_loader_stream_texture.instantiate();
		ResourceLoader::add_resource_format_loader(resource_loader_stream_texture);
	}

	if (GD_IS_CLASS_ENABLED(TextureLayered)) {
		resource_loader_texture_layered.instantiate();
		ResourceLoader::add_resource_format_loader(resource_loader_texture_layered);
	}

	if (GD_IS_CLASS_ENABLED(Texture3D)) {
		resource_loader_texture_3d.instantiate();
		ResourceLoader::add_resource_format_loader(resource_loader_texture_3d);
	}

	resource_saver_text.instantiate();
	ResourceSaver::add_resource_format_saver(resource_saver_text, true);

	resource_loader_text.instantiate();
	ResourceLoader::add_resource_format_loader(resource_loader_text, true);

	if (GD_IS_CLASS_ENABLED(Shader)) {
		resource_saver_shader.instantiate();
		ResourceSaver::add_resource_format_saver(resource_saver_shader, true);

		resource_loader_shader.instantiate();
		ResourceLoader::add_resource_format_loader(resource_loader_shader, true);
	}

	if (GD_IS_CLASS_ENABLED(ShaderInclude)) {
		resource_saver_shader_include.instantiate();
		ResourceSaver::add_resource_format_saver(resource_saver_shader_include, true);

		resource_loader_shader_include.instantiate();
		ResourceLoader::add_resource_format_loader(resource_loader_shader_include, true);
	}

	OS::get_singleton()->yield(); // may take time to init

	GDREGISTER_CLASS(Object);

	GDREGISTER_CLASS(Node);
	GDREGISTER_VIRTUAL_CLASS(MissingNode);
	GDREGISTER_ABSTRACT_CLASS(InstancePlaceholder);

	GDREGISTER_ABSTRACT_CLASS(Viewport);
	GDREGISTER_CLASS(SubViewport);
	GDREGISTER_CLASS(ViewportTexture);

	GDREGISTER_VIRTUAL_CLASS(CompositorEffect);

	GDREGISTER_ABSTRACT_CLASS(MultiplayerPeer);
	GDREGISTER_CLASS(MultiplayerPeerExtension);
	GDREGISTER_ABSTRACT_CLASS(MultiplayerAPI);
	GDREGISTER_CLASS(MultiplayerAPIExtension);

	GDREGISTER_CLASS(HTTPRequest);
	GDREGISTER_CLASS(Timer);
	GDREGISTER_CLASS(CanvasLayer);
	GDREGISTER_CLASS(CanvasModulate);
	GDREGISTER_CLASS(ResourcePreloader);
	GDREGISTER_CLASS(Window);

	GDREGISTER_CLASS(StatusIndicator);

	/* REGISTER GUI */

	GDREGISTER_CLASS(ButtonGroup);
	GDREGISTER_VIRTUAL_CLASS(BaseButton);

	OS::get_singleton()->yield(); // may take time to init

	GDREGISTER_CLASS(Control);
	GDREGISTER_CLASS(Button);
	GDREGISTER_CLASS(Label);
	GDREGISTER_ABSTRACT_CLASS(ScrollBar);
	GDREGISTER_CLASS(HScrollBar);
	GDREGISTER_CLASS(VScrollBar);
	GDREGISTER_CLASS(ProgressBar);
	GDREGISTER_ABSTRACT_CLASS(Slider);
	GDREGISTER_CLASS(HSlider);
	GDREGISTER_CLASS(VSlider);
	GDREGISTER_CLASS(Popup);
	GDREGISTER_CLASS(PopupPanel);
	GDREGISTER_CLASS(CheckBox);
	GDREGISTER_CLASS(CheckButton);
	GDREGISTER_CLASS(LinkButton);
	GDREGISTER_CLASS(Panel);
	GDREGISTER_VIRTUAL_CLASS(Range);

	OS::get_singleton()->yield(); // may take time to init

	GDREGISTER_CLASS(TextureRect);
	GDREGISTER_CLASS(ColorRect);
	GDREGISTER_CLASS(NinePatchRect);
	GDREGISTER_CLASS(ReferenceRect);
	GDREGISTER_CLASS(AspectRatioContainer);
	GDREGISTER_CLASS(TabContainer);
	GDREGISTER_CLASS(TabBar);
	GDREGISTER_ABSTRACT_CLASS(Separator);
	GDREGISTER_CLASS(HSeparator);
	GDREGISTER_CLASS(VSeparator);
	GDREGISTER_CLASS(TextureButton);
	GDREGISTER_CLASS(Container);
	GDREGISTER_CLASS(BoxContainer);
	GDREGISTER_CLASS(HBoxContainer);
	GDREGISTER_CLASS(VBoxContainer);
	GDREGISTER_CLASS(GridContainer);
	GDREGISTER_CLASS(CenterContainer);
	GDREGISTER_CLASS(ScrollContainer);
	GDREGISTER_CLASS(PanelContainer);
	GDREGISTER_CLASS(FlowContainer);
	GDREGISTER_CLASS(HFlowContainer);
	GDREGISTER_CLASS(VFlowContainer);
	GDREGISTER_CLASS(MarginContainer);

	OS::get_singleton()->yield(); // may take time to init

	GDREGISTER_CLASS(TextureProgressBar);
	GDREGISTER_CLASS(ItemList);

	GDREGISTER_CLASS(LineEdit);
	GDREGISTER_CLASS(VideoStreamPlayer);
	GDREGISTER_VIRTUAL_CLASS(VideoStreamPlayback);
	GDREGISTER_VIRTUAL_CLASS(VideoStream);

#ifndef ADVANCED_GUI_DISABLED
	GDREGISTER_CLASS(FileDialog);

	GDREGISTER_CLASS(PopupMenu);
	GDREGISTER_CLASS(Tree);

	GDREGISTER_CLASS(TextEdit);
	GDREGISTER_CLASS(CodeEdit);
	GDREGISTER_CLASS(SyntaxHighlighter);
	GDREGISTER_CLASS(CodeHighlighter);

	GDREGISTER_ABSTRACT_CLASS(TreeItem);
	GDREGISTER_CLASS(MenuBar);
	GDREGISTER_CLASS(MenuButton);
	GDREGISTER_CLASS(OptionButton);
	GDREGISTER_CLASS(SpinBox);
	GDREGISTER_CLASS(ColorPicker);
	GDREGISTER_CLASS(ColorPickerButton);
	GDREGISTER_CLASS(RichTextLabel);
	GDREGISTER_CLASS(RichTextEffect);
	GDREGISTER_CLASS(CharFXTransform);

	GDREGISTER_CLASS(AcceptDialog);
	GDREGISTER_CLASS(ConfirmationDialog);

	GDREGISTER_CLASS(SubViewportContainer);
	GDREGISTER_CLASS(SplitContainer);
	GDREGISTER_CLASS(HSplitContainer);
	GDREGISTER_CLASS(VSplitContainer);

	GDREGISTER_CLASS(GraphElement);
	GDREGISTER_CLASS(GraphNode);
	GDREGISTER_CLASS(GraphFrame);
	GDREGISTER_CLASS(GraphEdit);

	GDREGISTER_CLASS(FoldableGroup);
	GDREGISTER_CLASS(FoldableContainer);

	OS::get_singleton()->yield(); // may take time to init

	int swap_cancel_ok = GLOBAL_DEF(PropertyInfo(Variant::INT, "gui/common/swap_cancel_ok", PROPERTY_HINT_ENUM, "Auto,Cancel First,OK First"), 0);
	if (DisplayServer::get_singleton() && swap_cancel_ok == 0) {
		swap_cancel_ok = DisplayServer::get_singleton()->get_swap_cancel_ok() ? 2 : 1;
	}
	AcceptDialog::set_swap_cancel_ok(swap_cancel_ok == 2);
#endif

	// # //
	Control::set_root_layout_direction(0);
	Window::set_root_layout_direction(0);

	/* REGISTER ANIMATION */
	GDREGISTER_CLASS(Tween);
	GDREGISTER_ABSTRACT_CLASS(Tweener);
	GDREGISTER_CLASS(PropertyTweener);
	GDREGISTER_CLASS(IntervalTweener);
	GDREGISTER_CLASS(CallbackTweener);
	GDREGISTER_CLASS(MethodTweener);
	GDREGISTER_CLASS(SubtweenTweener);

	GDREGISTER_ABSTRACT_CLASS(AnimationMixer);
	GDREGISTER_CLASS(AnimationPlayer);
	GDREGISTER_CLASS(AnimationTree);
	GDREGISTER_CLASS(AnimationNode);
	GDREGISTER_CLASS(AnimationRootNode);
	GDREGISTER_CLASS(AnimationNodeBlendTree);
	GDREGISTER_CLASS(AnimationNodeBlendSpace1D);
	GDREGISTER_CLASS(AnimationNodeBlendSpace2D);
	GDREGISTER_CLASS(AnimationNodeStateMachine);
	GDREGISTER_CLASS(AnimationNodeStateMachinePlayback);
	GDREGISTER_VIRTUAL_CLASS(AnimationNodeExtension);

	GDREGISTER_CLASS(AnimationNodeSync);
	GDREGISTER_CLASS(AnimationNodeStateMachineTransition);
	GDREGISTER_CLASS(AnimationNodeOutput);
	GDREGISTER_CLASS(AnimationNodeOneShot);
	GDREGISTER_CLASS(AnimationNodeAnimation);
	GDREGISTER_CLASS(AnimationNodeAdd2);
	GDREGISTER_CLASS(AnimationNodeAdd3);
	GDREGISTER_CLASS(AnimationNodeBlend2);
	GDREGISTER_CLASS(AnimationNodeBlend3);
	GDREGISTER_CLASS(AnimationNodeSub2);
	GDREGISTER_CLASS(AnimationNodeTimeScale);
	GDREGISTER_CLASS(AnimationNodeTimeSeek);
	GDREGISTER_CLASS(AnimationNodeTransition);

	GDREGISTER_CLASS(ShaderGlobalsOverride); // can be used in any shader

	OS::get_singleton()->yield(); // may take time to init

	/* REGISTER 3D */

#ifndef _3D_DISABLED
	GDREGISTER_CLASS(Node3D);
	GDREGISTER_ABSTRACT_CLASS(Node3DGizmo);
	GDREGISTER_CLASS(Skin);
	GDREGISTER_ABSTRACT_CLASS(SkinReference);
	GDREGISTER_CLASS(Skeleton3D);
	GDREGISTER_CLASS(ImporterMesh);
	GDREGISTER_CLASS(ImporterMeshInstance3D);
	GDREGISTER_VIRTUAL_CLASS(VisualInstance3D);
	GDREGISTER_VIRTUAL_CLASS(GeometryInstance3D);
	GDREGISTER_CLASS(Camera3D);
	GDREGISTER_CLASS(AudioListener3D);
	GDREGISTER_CLASS(MeshInstance3D);
	GDREGISTER_CLASS(OccluderInstance3D);
	GDREGISTER_ABSTRACT_CLASS(Occluder3D);
	GDREGISTER_CLASS(ArrayOccluder3D);
	GDREGISTER_CLASS(QuadOccluder3D);
	GDREGISTER_CLASS(BoxOccluder3D);
	GDREGISTER_CLASS(SphereOccluder3D);
	GDREGISTER_CLASS(PolygonOccluder3D);
	GDREGISTER_ABSTRACT_CLASS(SpriteBase3D);
	GDREGISTER_CLASS(Sprite3D);
	GDREGISTER_CLASS(AnimatedSprite3D);
	GDREGISTER_CLASS(Label3D);
	GDREGISTER_ABSTRACT_CLASS(Light3D);
	GDREGISTER_CLASS(DirectionalLight3D);
	GDREGISTER_CLASS(OmniLight3D);
	GDREGISTER_CLASS(SpotLight3D);
	GDREGISTER_CLASS(ReflectionProbe);
	GDREGISTER_CLASS(Decal);
	GDREGISTER_CLASS(VoxelGI);
	GDREGISTER_CLASS(VoxelGIData);
	GDREGISTER_CLASS(LightmapGI);
	GDREGISTER_CLASS(LightmapGIData);
	GDREGISTER_CLASS(LightmapProbe);
	GDREGISTER_ABSTRACT_CLASS(Lightmapper);
	GDREGISTER_CLASS(GPUParticles3D);
	GDREGISTER_ABSTRACT_CLASS(GPUParticlesCollision3D);
	GDREGISTER_CLASS(GPUParticlesCollisionBox3D);
	GDREGISTER_CLASS(GPUParticlesCollisionSphere3D);
	GDREGISTER_CLASS(GPUParticlesCollisionSDF3D);
	GDREGISTER_CLASS(GPUParticlesCollisionHeightField3D);
	GDREGISTER_ABSTRACT_CLASS(GPUParticlesAttractor3D);
	GDREGISTER_CLASS(GPUParticlesAttractorBox3D);
	GDREGISTER_CLASS(GPUParticlesAttractorSphere3D);
	GDREGISTER_CLASS(GPUParticlesAttractorVectorField3D);
	GDREGISTER_CLASS(CPUParticles3D);
	GDREGISTER_CLASS(Marker3D);
	GDREGISTER_CLASS(ModifierBoneTarget3D);
	GDREGISTER_CLASS(RootMotionView);
	GDREGISTER_VIRTUAL_CLASS(SkeletonModifier3D);
	GDREGISTER_CLASS(RetargetModifier3D);
	GDREGISTER_CLASS(SpringBoneSimulator3D);
	GDREGISTER_VIRTUAL_CLASS(SpringBoneCollision3D);
	GDREGISTER_CLASS(SpringBoneCollisionSphere3D);
	GDREGISTER_CLASS(SpringBoneCollisionCapsule3D);
	GDREGISTER_CLASS(SpringBoneCollisionPlane3D);
	GDREGISTER_VIRTUAL_CLASS(BoneConstraint3D);
	GDREGISTER_CLASS(CopyTransformModifier3D);
	GDREGISTER_CLASS(ConvertTransformModifier3D);
	GDREGISTER_CLASS(AimModifier3D);

	OS::get_singleton()->yield(); // may take time to init

#ifndef PHYSICS_3D_DISABLED
	GDREGISTER_ABSTRACT_CLASS(CollisionObject3D);
	GDREGISTER_ABSTRACT_CLASS(PhysicsBody3D);
	GDREGISTER_CLASS(StaticBody3D);
	GDREGISTER_CLASS(AnimatableBody3D);
	GDREGISTER_CLASS(RigidBody3D);
	GDREGISTER_CLASS(KinematicCollision3D);
	GDREGISTER_CLASS(CharacterBody3D);
	GDREGISTER_CLASS(SpringArm3D);

	GDREGISTER_CLASS(PhysicalBoneSimulator3D);
	GDREGISTER_CLASS(PhysicalBone3D);
	GDREGISTER_CLASS(SoftBody3D);
#endif // PHYSICS_3D_DISABLED

	GDREGISTER_CLASS(BoneAttachment3D);
	GDREGISTER_CLASS(LookAtModifier3D);

#ifndef PHYSICS_3D_DISABLED
	GDREGISTER_CLASS(VehicleBody3D);
	GDREGISTER_CLASS(VehicleWheel3D);
	GDREGISTER_CLASS(Area3D);
	GDREGISTER_CLASS(CollisionShape3D);
	GDREGISTER_CLASS(CollisionPolygon3D);
	GDREGISTER_CLASS(RayCast3D);
	GDREGISTER_CLASS(ShapeCast3D);
#endif // PHYSICS_3D_DISABLED
	GDREGISTER_CLASS(MultiMeshInstance3D);

	GDREGISTER_CLASS(Curve3D);
	GDREGISTER_CLASS(Path3D);
	GDREGISTER_CLASS(PathFollow3D);
	GDREGISTER_CLASS(VisibleOnScreenNotifier3D);
	GDREGISTER_CLASS(VisibleOnScreenEnabler3D);
	GDREGISTER_CLASS(WorldEnvironment);
	GDREGISTER_CLASS(FogVolume);
	GDREGISTER_CLASS(FogMaterial);
	GDREGISTER_CLASS(RemoteTransform3D);

#ifndef PHYSICS_3D_DISABLED
	GDREGISTER_ABSTRACT_CLASS(Joint3D);
	GDREGISTER_CLASS(PinJoint3D);
	GDREGISTER_CLASS(HingeJoint3D);
	GDREGISTER_CLASS(SliderJoint3D);
	GDREGISTER_CLASS(ConeTwistJoint3D);
	GDREGISTER_CLASS(Generic6DOFJoint3D);
#endif // PHYSICS_3D_DISABLED

#ifndef NAVIGATION_3D_DISABLED
	GDREGISTER_CLASS(NavigationMeshSourceGeometryData3D);
	GDREGISTER_CLASS(NavigationRegion3D);
	GDREGISTER_CLASS(NavigationAgent3D);
	GDREGISTER_CLASS(NavigationObstacle3D);
	GDREGISTER_CLASS(NavigationLink3D);
#endif // NAVIGATION_3D_DISABLED

	OS::get_singleton()->yield(); // may take time to init
#endif // _3D_DISABLED

	/* REGISTER SHADER */

	GDREGISTER_CLASS(Shader);
	GDREGISTER_CLASS(ShaderInclude);

	GDREGISTER_VIRTUAL_CLASS(Material);
	GDREGISTER_CLASS(PlaceholderMaterial);
	GDREGISTER_CLASS(ShaderMaterial);
	GDREGISTER_ABSTRACT_CLASS(CanvasItem);
	GDREGISTER_CLASS(CanvasTexture);
	GDREGISTER_CLASS(CanvasItemMaterial);
	SceneTree::add_idle_callback(CanvasItemMaterial::flush_changes);
	CanvasItemMaterial::init_shaders();

	/* REGISTER 2D */

	GDREGISTER_CLASS(Node2D);
	GDREGISTER_CLASS(CanvasGroup);
	GDREGISTER_CLASS(CPUParticles2D);
	GDREGISTER_CLASS(GPUParticles2D);
	GDREGISTER_CLASS(Sprite2D);
	GDREGISTER_CLASS(SpriteFrames);
	GDREGISTER_CLASS(AnimatedSprite2D);
	GDREGISTER_CLASS(Marker2D);
	GDREGISTER_CLASS(Line2D);
	GDREGISTER_CLASS(MeshInstance2D);
	GDREGISTER_CLASS(MultiMeshInstance2D);
#ifndef PHYSICS_2D_DISABLED
	GDREGISTER_ABSTRACT_CLASS(CollisionObject2D);
	GDREGISTER_ABSTRACT_CLASS(PhysicsBody2D);
	GDREGISTER_CLASS(StaticBody2D);
	GDREGISTER_CLASS(AnimatableBody2D);
	GDREGISTER_CLASS(RigidBody2D);
	GDREGISTER_CLASS(CharacterBody2D);
	GDREGISTER_CLASS(KinematicCollision2D);
	GDREGISTER_CLASS(Area2D);
	GDREGISTER_CLASS(CollisionShape2D);
	GDREGISTER_CLASS(CollisionPolygon2D);
	GDREGISTER_CLASS(RayCast2D);
	GDREGISTER_CLASS(ShapeCast2D);
#endif // PHYSICS_2D_DISABLED
	GDREGISTER_CLASS(VisibleOnScreenNotifier2D);
	GDREGISTER_CLASS(VisibleOnScreenEnabler2D);
	GDREGISTER_CLASS(Polygon2D);
	GDREGISTER_CLASS(Skeleton2D);
	GDREGISTER_CLASS(Bone2D);
	GDREGISTER_ABSTRACT_CLASS(Light2D);
	GDREGISTER_CLASS(PointLight2D);
	GDREGISTER_CLASS(DirectionalLight2D);
	GDREGISTER_CLASS(LightOccluder2D);
	GDREGISTER_CLASS(OccluderPolygon2D);
	GDREGISTER_CLASS(BackBufferCopy);

	OS::get_singleton()->yield(); // may take time to init

	GDREGISTER_CLASS(Camera2D);
	GDREGISTER_CLASS(AudioListener2D);
#ifndef PHYSICS_2D_DISABLED
	GDREGISTER_ABSTRACT_CLASS(Joint2D);
	GDREGISTER_CLASS(PinJoint2D);
	GDREGISTER_CLASS(GrooveJoint2D);
	GDREGISTER_CLASS(DampedSpringJoint2D);
	GDREGISTER_CLASS(TouchScreenButton);
#endif // PHYSICS_2D_DISABLED
	GDREGISTER_CLASS(TileSet);
	GDREGISTER_ABSTRACT_CLASS(TileSetSource);
	GDREGISTER_CLASS(TileSetAtlasSource);
	GDREGISTER_CLASS(TileSetScenesCollectionSource);
	GDREGISTER_CLASS(TileMapPattern);
	GDREGISTER_CLASS(TileData);
	GDREGISTER_CLASS(TileMapLayer);
	GDREGISTER_CLASS(Parallax2D);
	GDREGISTER_CLASS(RemoteTransform2D);

	GDREGISTER_CLASS(SkeletonModificationStack2D);
	GDREGISTER_CLASS(SkeletonModification2D);
	GDREGISTER_CLASS(SkeletonModification2DLookAt);
	GDREGISTER_CLASS(SkeletonModification2DCCDIK);
	GDREGISTER_CLASS(SkeletonModification2DFABRIK);
	GDREGISTER_CLASS(SkeletonModification2DTwoBoneIK);
	GDREGISTER_CLASS(SkeletonModification2DStackHolder);

#ifndef PHYSICS_2D_DISABLED
	GDREGISTER_CLASS(PhysicalBone2D);
	GDREGISTER_CLASS(SkeletonModification2DJiggle);
	GDREGISTER_CLASS(SkeletonModification2DPhysicalBones);
#endif // PHYSICS_2D_DISABLED

	OS::get_singleton()->yield(); // may take time to init

	/* REGISTER RESOURCES */

	GDREGISTER_ABSTRACT_CLASS(Shader);
	GDREGISTER_CLASS(ParticleProcessMaterial);
	SceneTree::add_idle_callback(ParticleProcessMaterial::flush_changes);
	ParticleProcessMaterial::init_shaders();

	GDREGISTER_VIRTUAL_CLASS(Mesh);
	GDREGISTER_CLASS(MeshConvexDecompositionSettings);
	GDREGISTER_CLASS(ArrayMesh);
	GDREGISTER_CLASS(PlaceholderMesh);
	GDREGISTER_CLASS(ImmediateMesh);
	GDREGISTER_CLASS(MultiMesh);
	GDREGISTER_CLASS(SurfaceTool);
	GDREGISTER_CLASS(MeshDataTool);

#ifndef _3D_DISABLED
	GDREGISTER_CLASS(AudioStreamPlayer3D);
	GDREGISTER_VIRTUAL_CLASS(PrimitiveMesh);
	GDREGISTER_CLASS(BoxMesh);
	GDREGISTER_CLASS(CapsuleMesh);
	GDREGISTER_CLASS(CylinderMesh);
	GDREGISTER_CLASS(PlaneMesh);
	GDREGISTER_CLASS(PrismMesh);
	GDREGISTER_CLASS(QuadMesh);
	GDREGISTER_CLASS(SphereMesh);
	GDREGISTER_CLASS(TextMesh);
	GDREGISTER_CLASS(TorusMesh);
	GDREGISTER_CLASS(TubeTrailMesh);
	GDREGISTER_CLASS(RibbonTrailMesh);
	GDREGISTER_CLASS(PointMesh);
	GDREGISTER_ABSTRACT_CLASS(BaseMaterial3D);
	GDREGISTER_CLASS(StandardMaterial3D);
	GDREGISTER_CLASS(ORMMaterial3D);
	GDREGISTER_CLASS(ProceduralSkyMaterial);
	GDREGISTER_CLASS(PanoramaSkyMaterial);
	GDREGISTER_CLASS(PhysicalSkyMaterial);
	SceneTree::add_idle_callback(BaseMaterial3D::flush_changes);
	BaseMaterial3D::init_shaders();

	GDREGISTER_CLASS(MeshLibrary);

	OS::get_singleton()->yield(); // may take time to init

#ifndef PHYSICS_3D_DISABLED
	GDREGISTER_ABSTRACT_CLASS(Shape3D);
	GDREGISTER_CLASS(SeparationRayShape3D);
	GDREGISTER_CLASS(SphereShape3D);
	GDREGISTER_CLASS(BoxShape3D);
	GDREGISTER_CLASS(CapsuleShape3D);
	GDREGISTER_CLASS(CylinderShape3D);
	GDREGISTER_CLASS(HeightMapShape3D);
	GDREGISTER_CLASS(WorldBoundaryShape3D);
	GDREGISTER_CLASS(ConvexPolygonShape3D);
	GDREGISTER_CLASS(ConcavePolygonShape3D);
#endif // PHYSICS_3D_DISABLED
	GDREGISTER_CLASS(World3D);

	OS::get_singleton()->yield(); // may take time to init
#endif // _3D_DISABLED

#if !defined(PHYSICS_2D_DISABLED) || !defined(PHYSICS_3D_DISABLED)
	GDREGISTER_CLASS(PhysicsMaterial);
#endif // !defined(PHYSICS_2D_DISABLED) || !defined(PHYSICS_3D_DISABLED)
	GDREGISTER_CLASS(Compositor);
	GDREGISTER_CLASS(Environment);
	GDREGISTER_VIRTUAL_CLASS(CameraAttributes);
	GDREGISTER_CLASS(CameraAttributesPhysical);
	GDREGISTER_CLASS(CameraAttributesPractical);
	GDREGISTER_CLASS(World2D);
	GDREGISTER_VIRTUAL_CLASS(Texture);
	GDREGISTER_VIRTUAL_CLASS(Texture2D);
	GDREGISTER_CLASS(Sky);
	GDREGISTER_CLASS(CompressedTexture2D);
	GDREGISTER_CLASS(PortableCompressedTexture2D);
	GDREGISTER_CLASS(ImageTexture);
	GDREGISTER_CLASS(AtlasTexture);
	GDREGISTER_CLASS(MeshTexture);
	GDREGISTER_CLASS(CurveTexture);
	GDREGISTER_CLASS(CurveXYZTexture);
	GDREGISTER_CLASS(GradientTexture1D);
	GDREGISTER_CLASS(GradientTexture2D);
	GDREGISTER_CLASS(CameraTexture);
	GDREGISTER_CLASS(ExternalTexture);
	GDREGISTER_VIRTUAL_CLASS(TextureLayered);
	GDREGISTER_ABSTRACT_CLASS(ImageTextureLayered);
	GDREGISTER_VIRTUAL_CLASS(Texture3D);
	GDREGISTER_CLASS(ImageTexture3D);
	GDREGISTER_CLASS(CompressedTexture3D);
	GDREGISTER_CLASS(Cubemap);
	GDREGISTER_CLASS(CubemapArray);
	GDREGISTER_CLASS(Texture2DArray);
	GDREGISTER_ABSTRACT_CLASS(CompressedTextureLayered);
	GDREGISTER_CLASS(CompressedCubemap);
	GDREGISTER_CLASS(CompressedCubemapArray);
	GDREGISTER_CLASS(CompressedTexture2DArray);
	GDREGISTER_CLASS(PlaceholderTexture2D);
	GDREGISTER_CLASS(PlaceholderTexture3D);
	GDREGISTER_ABSTRACT_CLASS(PlaceholderTextureLayered);
	GDREGISTER_CLASS(PlaceholderTexture2DArray);
	GDREGISTER_CLASS(PlaceholderCubemap);
	GDREGISTER_CLASS(PlaceholderCubemapArray);
	GDREGISTER_CLASS(DPITexture);

	// These classes are part of renderer_rd
	GDREGISTER_CLASS(Texture2DRD);
	GDREGISTER_ABSTRACT_CLASS(TextureLayeredRD);
	GDREGISTER_CLASS(Texture2DArrayRD);
	GDREGISTER_CLASS(TextureCubemapRD);
	GDREGISTER_CLASS(TextureCubemapArrayRD);
	GDREGISTER_CLASS(Texture3DRD);

	GDREGISTER_CLASS(Animation);
	GDREGISTER_CLASS(AnimationLibrary);

	GDREGISTER_ABSTRACT_CLASS(Font);
	GDREGISTER_CLASS(FontFile);
	GDREGISTER_CLASS(FontVariation);
	GDREGISTER_CLASS(SystemFont);
	GDREGISTER_CLASS(ColorPalette);

	GDREGISTER_CLASS(Curve);

	GDREGISTER_CLASS(LabelSettings);

	GDREGISTER_CLASS(TextLine);
	GDREGISTER_CLASS(TextParagraph);

	GDREGISTER_VIRTUAL_CLASS(StyleBox);
	GDREGISTER_CLASS(StyleBoxEmpty);
	GDREGISTER_CLASS(StyleBoxTexture);
	GDREGISTER_CLASS(StyleBoxFlat);
	GDREGISTER_CLASS(StyleBoxLine);
	GDREGISTER_CLASS(Theme);

	GDREGISTER_CLASS(BitMap);
	GDREGISTER_CLASS(Gradient);

	GDREGISTER_CLASS(SkeletonProfile);
	GDREGISTER_CLASS(SkeletonProfileHumanoid);
	GDREGISTER_CLASS(BoneMap);

	OS::get_singleton()->yield(); // may take time to init

	GDREGISTER_CLASS(AudioStreamPlayer);
	GDREGISTER_CLASS(AudioStreamWAV);
	GDREGISTER_CLASS(AudioStreamPolyphonic);
	GDREGISTER_ABSTRACT_CLASS(AudioStreamPlaybackPolyphonic);

	OS::get_singleton()->yield(); // may take time to init

	GDREGISTER_CLASS(AudioStreamPlayer2D);
	GDREGISTER_CLASS(Curve2D);
	GDREGISTER_CLASS(Path2D);
	GDREGISTER_CLASS(PathFollow2D);

#ifndef PHYSICS_2D_DISABLED
	GDREGISTER_ABSTRACT_CLASS(Shape2D);
	GDREGISTER_CLASS(WorldBoundaryShape2D);
	GDREGISTER_CLASS(SegmentShape2D);
	GDREGISTER_CLASS(SeparationRayShape2D);
	GDREGISTER_CLASS(CircleShape2D);
	GDREGISTER_CLASS(RectangleShape2D);
	GDREGISTER_CLASS(CapsuleShape2D);
	GDREGISTER_CLASS(ConvexPolygonShape2D);
	GDREGISTER_CLASS(ConcavePolygonShape2D);
#endif // PHYSICS_2D_DISABLED

#if !defined(NAVIGATION_2D_DISABLED) || !defined(NAVIGATION_3D_DISABLED)
	GDREGISTER_CLASS(NavigationMesh);
#endif // !defined(NAVIGATION_2D_DISABLED) || !defined(NAVIGATION_3D_DISABLED)

#ifndef NAVIGATION_2D_DISABLED
	GDREGISTER_CLASS(NavigationMeshSourceGeometryData2D);
	GDREGISTER_CLASS(NavigationPolygon);
	GDREGISTER_CLASS(NavigationRegion2D);
	GDREGISTER_CLASS(NavigationAgent2D);
	GDREGISTER_CLASS(NavigationObstacle2D);
	GDREGISTER_CLASS(NavigationLink2D);
	GDREGISTER_CLASS(PolygonPathFinder);

	OS::get_singleton()->yield(); // may take time to init

	// 2D nodes that support navmesh baking need to server register their source geometry parsers.
	MeshInstance2D::navmesh_parse_init();
	MultiMeshInstance2D::navmesh_parse_init();
	NavigationObstacle2D::navmesh_parse_init();
	Polygon2D::navmesh_parse_init();
	TileMapLayer::navmesh_parse_init();
#ifndef PHYSICS_2D_DISABLED
	StaticBody2D::navmesh_parse_init();
#endif // PHYSICS_2D_DISABLED
#endif // NAVIGATION_2D_DISABLED

#ifndef NAVIGATION_3D_DISABLED
	// 3D nodes that support navmesh baking need to server register their source geometry parsers.
	MeshInstance3D::navmesh_parse_init();
	MultiMeshInstance3D::navmesh_parse_init();
	NavigationObstacle3D::navmesh_parse_init();
#ifndef PHYSICS_3D_DISABLED
	StaticBody3D::navmesh_parse_init();
#endif // PHYSICS_3D_DISABLED
#endif // NAVIGATION_3D_DISABLED

#if !defined(NAVIGATION_2D_DISABLED) || !defined(NAVIGATION_3D_DISABLED)
	OS::get_singleton()->yield(); // may take time to init
#endif // !defined(NAVIGATION_2D_DISABLED) || !defined(NAVIGATION_3D_DISABLED)

	GDREGISTER_ABSTRACT_CLASS(SceneState);
	GDREGISTER_CLASS(PackedScene);

	GDREGISTER_CLASS(SceneTree);
	GDREGISTER_ABSTRACT_CLASS(SceneTreeTimer); // sorry, you can't create it

	OS::get_singleton()->yield(); // may take time to init

	for (int i = 0; i < 20; i++) {
		GLOBAL_DEF_BASIC(vformat("%s/layer_%d", PNAME("layer_names/2d_render"), i + 1), "");
		GLOBAL_DEF_BASIC(vformat("%s/layer_%d", PNAME("layer_names/3d_render"), i + 1), "");
	}

	for (int i = 0; i < 32; i++) {
		GLOBAL_DEF_BASIC(vformat("%s/layer_%d", PNAME("layer_names/2d_physics"), i + 1), "");
#ifndef NAVIGATION_2D_DISABLED
		GLOBAL_DEF_BASIC(vformat("%s/layer_%d", PNAME("layer_names/2d_navigation"), i + 1), "");
#endif // NAVIGATION_2D_DISABLED
		GLOBAL_DEF_BASIC(vformat("%s/layer_%d", PNAME("layer_names/3d_physics"), i + 1), "");
#ifndef NAVIGATION_3D_DISABLED
		GLOBAL_DEF_BASIC(vformat("%s/layer_%d", PNAME("layer_names/3d_navigation"), i + 1), "");
#endif // NAVIGATION_3D_DISABLED
	}

	for (int i = 0; i < 32; i++) {
		GLOBAL_DEF_BASIC(vformat("%s/layer_%d", PNAME("layer_names/avoidance"), i + 1), "");
	}

	if (RenderingServer::get_singleton()) {
		// RenderingServer needs to exist for this to succeed.
		ColorPicker::init_shaders();
		GraphEdit::init_shaders();
	}

	SceneDebugger::initialize();

	OS::get_singleton()->benchmark_end_measure("Scene", "Register Types");
}

void unregister_scene_types() {
	OS::get_singleton()->benchmark_begin_measure("Scene", "Unregister Types");

	SceneDebugger::deinitialize();

	if (GD_IS_CLASS_ENABLED(TextureLayered)) {
		ResourceLoader::remove_resource_format_loader(resource_loader_texture_layered);
		resource_loader_texture_layered.unref();
	}

	if (GD_IS_CLASS_ENABLED(Texture3D)) {
		ResourceLoader::remove_resource_format_loader(resource_loader_texture_3d);
		resource_loader_texture_3d.unref();
	}

	if (GD_IS_CLASS_ENABLED(CompressedTexture2D)) {
		ResourceLoader::remove_resource_format_loader(resource_loader_stream_texture);
		resource_loader_stream_texture.unref();
	}

	ResourceSaver::remove_resource_format_saver(resource_saver_text);
	resource_saver_text.unref();

	ResourceLoader::remove_resource_format_loader(resource_loader_text);
	resource_loader_text.unref();

	if (GD_IS_CLASS_ENABLED(Shader)) {
		ResourceSaver::remove_resource_format_saver(resource_saver_shader);
		resource_saver_shader.unref();

		ResourceLoader::remove_resource_format_loader(resource_loader_shader);
		resource_loader_shader.unref();
	}

	if (GD_IS_CLASS_ENABLED(ShaderInclude)) {
		ResourceSaver::remove_resource_format_saver(resource_saver_shader_include);
		resource_saver_shader_include.unref();

		ResourceLoader::remove_resource_format_loader(resource_loader_shader_include);
		resource_loader_shader_include.unref();
	}

	// StandardMaterial3D is not initialized when 3D is disabled, so it shouldn't be cleaned up either
#ifndef _3D_DISABLED
	BaseMaterial3D::finish_shaders();
	PhysicalSkyMaterial::cleanup_shader();
	PanoramaSkyMaterial::cleanup_shader();
	ProceduralSkyMaterial::cleanup_shader();
	FogMaterial::cleanup_shader();
#endif // _3D_DISABLED

	ParticleProcessMaterial::finish_shaders();
	CanvasItemMaterial::finish_shaders();
	ColorPicker::finish_shaders();
	GraphEdit::finish_shaders();
	SceneStringNames::free();

	OS::get_singleton()->benchmark_end_measure("Scene", "Unregister Types");
}

void register_scene_singletons() {
	OS::get_singleton()->benchmark_begin_measure("Scene", "Register Singletons");

	GDREGISTER_CLASS(ThemeDB);

	Engine::get_singleton()->add_singleton(Engine::Singleton("ThemeDB", ThemeDB::get_singleton()));

	OS::get_singleton()->benchmark_end_measure("Scene", "Register Singletons");
}
