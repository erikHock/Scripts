extends Node3D

@onready var grid : Node3D = $"../grid"
@export var object_to_build : PackedScene

var picked_object_to_build : Node3D = null
var picked_object_to_build_dir

func _ready():
	pass # Replace with function body.


func _process(delta):
	#	Instantiate preview object_to_build
	if Input.is_key_pressed(KEY_1) and !picked_object_to_build:
		picked_object_to_build = object_to_build.instantiate()
		picked_object_to_build_dir = picked_object_to_build.DIRECTION.DOWN
		get_tree().root.get_child(0).add_child(picked_object_to_build)
	
	if picked_object_to_build:
		# Instantiate preview object_to_build
		var grid_pos = grid.world_to_grid(grid.screen_to_world_ray())
		var grid_pos_xz = Vector3(grid_pos.x, 0, grid_pos.y)
		var object_origin = Vector2i(grid_pos_xz.x,grid_pos_xz.z)
		picked_object_to_build.transform.origin = grid_pos_xz
		
			
			

		# Check if is grid free for build
		#if grid.get_value_from_grid(grid_pos_xz) != 0: 
			# Grid is not free!

		# Place object_to_build
		if Input.is_mouse_button_pressed(MOUSE_BUTTON_LEFT):
			# Check is is grid position free
			var grid_positions_array = picked_object_to_build.get_grid_position_array(object_origin,picked_object_to_build_dir)
			var can_build = true
			
			# If grid occupied position is free (if is null) than can build
			var occupied_position = Vector3()
			for p in range(grid_positions_array.size()):
				occupied_position = Vector3(grid_positions_array[p].x,0,grid_positions_array[p].y)
				if grid.get_value_from_grid(occupied_position) != 0:
					print(grid.get_value_from_grid(occupied_position))
					can_build = false
					break

			if can_build:
				var rotation_offset = picked_object_to_build.get_rotation_offset(picked_object_to_build_dir)
				# codemonkey grid.GetWorldPosition(placedObjectOrigin.x, placedObjectOrigin.y) + new Vector3(rotationOffset.x, 0, rotationOffset.y) * grid.GetCellSize();
				var picked_object_to_build_world_pos = grid.get_world_from_grid(object_origin.x,object_origin.y) + Vector3(rotation_offset.x,0,rotation_offset.y) * grid.cell_size

				# Set object transforms
				picked_object_to_build.transform.origin = picked_object_to_build_world_pos
				picked_object_to_build.rotate(Vector3.UP,deg_to_rad(picked_object_to_build.get_rotation_angle(picked_object_to_build_dir)))
				# Add data to object
				picked_object_to_build.placed_direction = picked_object_to_build_dir
				picked_object_to_build.placed_origin = object_origin

				for p in range(grid_positions_array.size()):
					# codemonkey grid.GetGridObject(gridPosition.x, gridPosition.y).SetPlacedObject(placedObject)
					occupied_position = Vector3(grid_positions_array[p].x,0,grid_positions_array[p].y)
					grid.add_value_to_grid(occupied_position,3)	


				picked_object_to_build = null;
				picked_object_to_build_dir = null
				print("object_to_build placed!")

				# Debug grid value
			grid.refresh_debug_text()

		# Rotate preview object_to_build
		if Input.is_action_just_released("ROTATE_OBJECT"):
			picked_object_to_build_dir = picked_object_to_build.get_next_direction(picked_object_to_build_dir)

	if Input.is_mouse_button_pressed(MOUSE_BUTTON_RIGHT):
		print(grid.get_value_from_grid(grid.screen_to_world_ray()))

func rotate_object_to_build(picked_object_to_build: Node3D) -> void:
	picked_object_to_build.rotate_y(deg_to_rad(90))
	

