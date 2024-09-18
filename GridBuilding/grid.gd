extends Node3D

@export var grid_width : int = 10 
@export var grid_height : int = 10 
@export var cell_size : int = 1.0 
@export var draw_debug_grid : bool = true

var grid = []
var debug_grid_y = 0.1
@onready var debug_grid_text : PackedScene = preload("res://scenes/text_world.tscn")


func _ready():
	initialize_grid()
	
	if draw_debug_grid:
		# Call in idle time of frame
		get_tree().process_frame.connect(initialize_debug_text,CONNECT_ONE_SHOT)

func _process(delta):
	if draw_debug_grid:
		draw_grid()

func draw_grid() -> void:
	for x in grid_width:
		for z in grid_height:
			var from_point = Vector3(x * cell_size,debug_grid_y,z*cell_size)
			var to_point_x = Vector3((x+1) * cell_size,debug_grid_y,z * cell_size)
			var to_point_z = Vector3(x * cell_size, debug_grid_y, (z+1)*cell_size)
			
			DebugDraw3D.draw_line(from_point,to_point_x,Color.RED,2)
			DebugDraw3D.draw_line(from_point,to_point_z,Color.BLUE,2)

func initialize_grid() -> void:
	for x in grid_width:
		var column = []
		for z in grid_height:
			column.append(0)
		grid.append(column)

func is_valid_grid(grid_position : Vector2) -> bool:
	return grid_position.x >= 0 and grid_position.x < grid_width and grid_position.y >= 0 and grid_position.y < grid_height
	
func world_to_grid(world_position : Vector3) -> Vector2:
	return Vector2(int(world_position.x / cell_size),int(world_position.z / cell_size))

func get_world_from_grid(x : int,z : int) -> Vector3:
	return Vector3(x,0,z) * cell_size

func add_value_to_grid(world_position : Vector3, value : int) -> void:
	var grid_position = world_to_grid(world_position)
	if is_valid_grid(grid_position):
		grid[grid_position.x][grid_position.y] += value

func get_value_from_grid(world_position : Vector3) -> int:
	var grid_position = world_to_grid(world_position)
	if is_valid_grid(grid_position):
		return grid[grid_position.x][grid_position.y]
	else:
		return 0

func screen_to_world_ray() -> Vector3:
	var ray_length = 2000
	var camera = get_tree().root.get_camera_3d()
	var mouse_pos = get_viewport().get_mouse_position()
	var from = camera.project_ray_origin(mouse_pos)
	var to = from + camera.project_ray_normal(mouse_pos) * ray_length
	var space_state = get_world_3d().get_direct_space_state()
	var query_params = PhysicsRayQueryParameters3D.create(from,to)
	var results =  space_state.intersect_ray(query_params)
	if results.size() > 0:
		results["position"].y = 0
		return results["position"]
	return Vector3()

func initialize_debug_text()->void:
	# Initialize parent
	var debug_grid_text_parent = Node3D.new()
	debug_grid_text_parent.name = "debug_grid_text_parent"
	get_tree().root.add_child(debug_grid_text_parent)
	
	# Initialize childrens
	for x in range(grid.size()):
		for z in (grid[x].size()):
			var text = debug_grid_text.instantiate()
			debug_grid_text_parent.add_child(text)
			text.transform.origin = Vector3(x + cell_size/2.0,debug_grid_y,z + cell_size/2.0)
			# Set grid value
			var grid_value = is_valid_grid(Vector2(x,z)) if grid[x][z] else 0
			#text.set_label(str(x)+","+str(z))
			text.set_label(str(grid_value))

func refresh_debug_text():
	var text_arr = get_node("/root/debug_grid_text_parent").get_children()
	for t in text_arr:
		var x = int(t.transform.origin.x)
		var z = int(t.transform.origin.z)
		var grid_position = Vector2(x,z)
		var grid_value = is_valid_grid(grid_position) if grid[grid_position.x][grid_position.y] else 0
		t.set_label(str(grid_value))
