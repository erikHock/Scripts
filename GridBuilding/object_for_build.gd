extends Node3D

@export var id : String = "ObjectForBuild"
@export var width : int = 2
@export var height : int = 1

enum DIRECTION{DOWN,LEFT,UP,RIGHT}

var placed_origin : Vector2i
var placed_direction : DIRECTION

func get_grid_position_array(offset : Vector2i,direction : DIRECTION)->Array:
	var grid_position_arr = []
	
	match direction:
		DIRECTION.DOWN:
			pass
		DIRECTION.UP:
			for x in range(width):
				for z in range(height):
					grid_position_arr.append(offset + Vector2i(x,z))
				break
		DIRECTION.LEFT:
			pass
		DIRECTION.RIGHT:
			for x in range(height):
				for z in range(width):
					grid_position_arr.append(offset + Vector2i(x,z))
				break

	return grid_position_arr

func get_next_direction(direction : DIRECTION) -> DIRECTION:
	match direction:
		DIRECTION.DOWN:
			return DIRECTION.LEFT
		DIRECTION.LEFT:
			return DIRECTION.UP
		DIRECTION.UP:
			return DIRECTION.RIGHT
		DIRECTION.RIGHT:
			return DIRECTION.DOWN
	return DIRECTION.DOWN

func get_rotation_angle(direction : DIRECTION) -> int:
	match direction:
		DIRECTION.DOWN:
			return 0
		DIRECTION.LEFT:
			return 90
		DIRECTION.UP:
			return 180
		DIRECTION.RIGHT:
			return 270
	return 0

func get_rotation_offset(direction : DIRECTION) -> Vector2i:
	match direction:
		DIRECTION.DOWN:
			return Vector2i(0,0)
		DIRECTION.LEFT:
			return Vector2i(0,width)
		DIRECTION.UP:
			return Vector2i(width,height)
		DIRECTION.RIGHT:
			return Vector2i(height,0)
	return Vector2i(0,0)
